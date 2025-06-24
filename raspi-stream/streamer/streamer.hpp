#pragma once

#include "core/stream_info.hpp"
#include "core/video_options.hpp"
#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>

class Streamer{
public:
    Streamer(const VideoOptions &options);
    ~Streamer();
    bool initialize();
    bool processFrame(const std::shared_ptr<libcamera::FrameBuffer> &buffer, const StreamInfo &info);
    void shutdown();

private:
    VideoOptions options_;
    std::unique_ptr<libcamera::Camera> camera_;
    std::unique_ptr<libcamera::CameraManager> camera_manager_;
    std::unique_ptr<libcamera::StreamConfiguration> config_;
    bool initialized_ = false;

    std::string destination_url_;
    int port_;
}