#pragma once

#include "core/stream_info.hpp"
#include "core/video_options.hpp"

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <netinet/in.h>

class Streamer{
public:
    Streamer(const std::string &url, int port);
    ~Streamer();
    bool processFrame(const std::shared_ptr<libcamera::FrameBuffer> &buffer, const StreamInfo &info);

private:
    int sockfd_;
    struct sockaddr_in destination_addr_;
}