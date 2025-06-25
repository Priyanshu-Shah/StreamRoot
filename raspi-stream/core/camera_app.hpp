#pragma once

#include <condition_variable>
#include <memory>
#include <mutex>
#include <map>
#include <queue>
#include <libcamera/camera.h>
#include <libcamera/controls.h>
#include <libcamera/framebuffer.h>

#include "core/stream_info.hpp"

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
    void configureVideo(const VideoOptions &options);

    Stream *videoStream(StreamInfo *info = nullptr) const;

    // Buffer handling
    CompletedRequestPtr wait(); //Wait function to block until a request is completed

protected:
    // Called internally when a request completes
    void handleRequestComplete(CompletedRequestPtr request);

    std::queue<CompletedRequestPtr> request_queue_;  // Queue for completed requests
    std::mutex queue_mutex_;
    std::condition_variable queue_cv_;
};