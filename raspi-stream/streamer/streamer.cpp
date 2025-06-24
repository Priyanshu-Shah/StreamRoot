#include "streamer/streamer.h"

Streamer::Streamer(const VideoOptions &options)
    : options_(options), initialized_(false) {
    // Initialize the camera manager and camera
    camera_manager_ = std::make_unique<libcamera::CameraManager>();
    //TODO
}

Streamer::~Streamer() {
    shutdown();
}

bool Streamer::initialize() {
    //TODO
}

bool Streamer::processFrame(const std::shared_ptr<libcamera::FrameBuffer> &buffer, const StreamInfo &info) {
    if (!initialized_) {
        return false;
    }

    // TODO: Process the frame buffer here, sending it to network stream or save to file

    return true; // Frame processed successfully
}

void Streamer::shutdown() {
    if (camera_) {
        camera_->stop();
        camera_->release();
        camera_.reset();
    }
    if (camera_manager_) {
        camera_manager_->stop();
        camera_manager_.reset();
    }
    initialized_ = false;
}

void Streamer::setDestination(const std::string &url, int port) {
    destination_url_ = url;
    port_ = port;
}

