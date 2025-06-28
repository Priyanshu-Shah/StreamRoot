#pragma once

#include <condition_variable>
#include <memory>
#include <mutex>
#include <map>
#include <queue>
#include <libcamera/camera.h>
#include <libcamera/controls.h>
#include <libcamera/framebuffer.h>
#include <libcamera/formats.h>
#include <libcamera/stream.h>
#include <libcamera/camera_manager.h>

#include "core/stream_info.hpp"
#include "core/video_options.hpp"

class RPiCamApp {
public:
    using Stream = libcamera::Stream;
    using FrameBuffer = libcamera::FrameBuffer;

    struct CompletedRequest {
        std::map<Stream *, FrameBuffer *> buffers;
        libcamera::ControlList metadata;
    };
    using CompletedRequestPtr = std::shared_ptr<CompletedRequest>;

    RPiCamApp();
    ~RPiCamApp();

    void openCamera();
    void closeCamera();
    void startCamera();
    void stopCamera();
    void configureVideo(const VideoOptions &video_options);

    Stream *videoStream(StreamInfo *info = nullptr) const;

    // Buffer handling
    CompletedRequestPtr wait(); //Wait function to block until a request is completed

protected:
    // Called internally when a request completes
    void handleRequestComplete(CompletedRequestPtr request);

    std::queue<CompletedRequestPtr> request_queue_;  // Queue for completed requests
    std::mutex queue_mutex_;
    std::condition_variable queue_cv_;

private:
    bool camera_started_ = false;
    std::unique_ptr<libcamera::CameraManager> camera_manager_;
    std::shared_ptr<libcamera::Camera> camera_;
    std::unique_ptr<libcamera::CameraConfiguration> config_;
    libcamera::Stream *stream_ = nullptr;
};