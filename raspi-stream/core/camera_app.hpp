/*

This file is responsible for managing the camera application,
firstly initializing the main camera class, which is the RPiCamApp,
and then providing the necessary methods to handle camera operations
like opening, closing, starting, and stopping the camera and coniguring video streams.

The class also handles buffer management and request completion,
i.e. maintain a queue of completed requests that can be processed by the application.
mutex and condition variable are used to synchronize access to the queue in case of multiple threads accessing it.
It also provides a method to wait method to the application, which blocks until a request is completed.

The application uses the libcamera library to interface with the camera hardware,
and it provides a way to access the video stream and its buffers.
*/


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