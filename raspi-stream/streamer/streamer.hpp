#pragma once

#include "core/stream_info.hpp"
#include "core/video_options.hpp"

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <netinet/in.h>
#include <libcamera/camera.h>
#include <libcamera/controls.h>
#include <libcamera/framebuffer.h>
#include <libcamera/formats.h>
#include <libcamera/stream.h>
#include <libcamera/camera_manager.h>

class Streamer{
public:
    Streamer(const std::string &url, int port);
    ~Streamer();
    bool processFrame(libcamera::FrameBuffer *buffer, const StreamInfo &info);

private:
    int sockfd_;
    struct sockaddr_in destination_addr_;
};