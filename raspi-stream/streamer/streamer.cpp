/*

Working:
We recieve FrameBuffers from main loop in main.cpp, which are then sent as planes to the socket connection.
Possible usage are setting up a socket connection to a UDP stream on a laptop, recieve the planes, 
reconstruct the frame and display it using ffplay or similar tools.

*/

#include "streamer/streamer.h"
#include <cstring>
#include <unistd.h>
#include <algorithm>
#include <stdexcept>

constexpr size_t MAX_UDP_SIZE = 65507; // Maximum size for a UDP packet

Streamer::Streamer(const std::string &url, int port){
    // Initialize the camera manager and camera
    sockfd_ = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd_<0) throw std::runtime_error("Failed to create socket");
    memset(&destination_addr_, 0, sizeof(destination_addr_));
    destination_addr_.sin_family = AF_INET;
    destination_addr_.sin_port = htons(port);
    if(inet_aton(ip.c_str(), &destination_addr_.sin_addr) == 0) {
        close(sockfd_);
        throw std::runtime_error("Invalid IP address");
    }
}

Streamer::~Streamer() {
    if(sockfd_ >= 0) {
        close(sockfd_);
    }
}


bool Streamer::processFrame(const std::shared_ptr<libcamera::FrameBuffer> &buffer, const StreamInfo &info) {
    for (unsigned int i = 0; i < buffer->planes().size(); ++i) {
        void* data = buffer->planes()[i].mem();
        size_t size = buffer->planes()[i].length; // Use the actual plane size if available

        const uint8_t *ptr = static_cast<const uint8_t*>(data);
        size_t remaining = size;
        while (remaining > 0) {
            size_t chunk = std::min(remaining, MAX_UDP_SIZE);
            ssize_t sent = sendto(sockfd_, ptr, chunk, 0,
                                  reinterpret_cast<const sockaddr*>(&destination_addr_),
                                  sizeof(destination_addr_));
            if (sent < 0) return false;
            ptr += chunk;
            remaining -= chunk;
        }
    }
    return true;
}


