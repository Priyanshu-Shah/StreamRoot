#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <netinet/in.h>
#include <unistd.h>

constexpr size_t MAX_UDP_SIZE = 65507;

int main(int argc, char* argv[]) {
    if (argc < 5) {
        std::cerr << "Usage: " << argv[0] << " <listen_port> <width> <height> <output_file>\n";
        std::cerr << "Example: " << argv[0] << " 5000 1280 720 out.yuv\n";
        return 1;
    }

    int port = std::stoi(argv[1]);
    int width = std::stoi(argv[2]);
    int height = std::stoi(argv[3]);
    std::string output_file = argv[4];

    // Calculate YUV420 frame size
    size_t y_size = width * height;
    size_t uv_size = (width / 2) * (height / 2);
    size_t frame_size = y_size + 2 * uv_size;

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        return 1;
    }

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind");
        close(sockfd);
        return 1;
    }

    std::ofstream ofs(output_file, std::ios::binary | std::ios::trunc);
    if (!ofs) {
        std::cerr << "Failed to open output file\n";
        close(sockfd);
        return 1;
    }

    std::vector<uint8_t> frame_buf(frame_size);
    size_t received = 0;

    std::cout << "Listening for UDP packets on port " << port << "...\n";
    std::cout << "Writing raw frames to " << output_file << "\n";

    while (true) {
        ssize_t len = recv(sockfd, frame_buf.data() + received, frame_size - received, 0);
        if (len < 0) {
            perror("recv");
            break;
        }
        received += len;
        if (received >= frame_size) {
            ofs.write(reinterpret_cast<char*>(frame_buf.data()), frame_size);
            ofs.flush();
            received = 0;
            std::cout << "Frame written\n";
        }
    }

    ofs.close();
    close(sockfd);
    return 0;
}