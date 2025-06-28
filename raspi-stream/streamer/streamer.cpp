/*

Working:
We recieve FrameBuffers from main loop in main.cpp, which are then sent as planes to the socket connection.
Possible usage are setting up a socket connection to a UDP stream on a laptop, recieve the planes, 
reconstruct the frame and display it using ffplay or similar tools.

*/

#include "streamer/streamer.hpp"
#include <cstring>
#include <unistd.h>
#include <algorithm>
#include <stdexcept>
#include <arpa/inet.h>
#include <sys/mman.h>

constexpr size_t MAX_UDP_SIZE = 65507; // Maximum size for a UDP packet

Streamer::Streamer(const std::string &url, int port){
    // Initialize the camera manager and camera
    sockfd_ = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd_<0) throw std::runtime_error("Failed to create socket");
    memset(&destination_addr_, 0, sizeof(destination_addr_));
    destination_addr_.sin_family = AF_INET;
    destination_addr_.sin_port = htons(port);
    if(inet_aton(url.c_str(), &destination_addr_.sin_addr) == 0) {
        close(sockfd_);
        throw std::runtime_error("Invalid IP address");
    }
}

Streamer::~Streamer() {
    if(sockfd_ >= 0) {
        close(sockfd_);
    }
}


bool Streamer::processFrame(libcamera::FrameBuffer *buffer, const StreamInfo &info) {
    for (unsigned int i = 0; i < buffer->planes().size(); ++i) {
        // Get the file descriptor and size for this plane
        int fd = buffer->planes()[i].fd.get(); // or just .fd if not a smart pointer
        size_t size = buffer->planes()[i].length;

        // Map the buffer into user space
        void *ptr = mmap(nullptr, size, PROT_READ, MAP_SHARED, fd, 0);
        if (ptr == MAP_FAILED) {
            continue; // or handle error
        }

        // Send the data over UDP in chunks
        uint8_t *data = static_cast<uint8_t *>(ptr);
        size_t remaining = size;
        while (remaining > 0) {
            size_t chunk = std::min(remaining, MAX_UDP_SIZE);
            ssize_t sent = sendto(sockfd_, data, chunk, 0,
                                  reinterpret_cast<const sockaddr*>(&destination_addr_),
                                  sizeof(destination_addr_));
            if (sent < 0) {
                munmap(ptr, size);
                return false;
            }
            data += chunk;
            remaining -= chunk;
        }

        // Unmap the buffer
        munmap(ptr, size);
    }
    return true;
}


