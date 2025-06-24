#include "core/camera_app.hpp"
#include "core/video_options.hpp"

using namespace std;
using namespace libcamera;

RPICamApp::RPiCamApp() {
    // Constructor implementation
    camera_started_ = false;
    openCamera();
    
}

RPICamApp::~RPiCamApp() {
    // Destructor implementation
    stopCamera();
    closeCamera();
}

void RPiCamApp::openCamera() {
    // initializing the libcamera library and opening the camera device
    camera_manager_ = make_unique<CameraManager>();
    if (camera_manager_->start()){
        throw runtime_error("Failed to start camera manager");
    }
    if (camera_manager_->cameras().empty()) {
        throw runtime_error("No cameras found");
    }
    camera_ = camera_manager_->cameras()[0];
    if(camera_->acquire()) {
        throw runtime_error("Failed to acquire camera");
    }
}

void RPiCamApp::closeCamera() {
    // releasing the camera and stopping the camera manager
    if (camera_) {
        camera_->release();
        camera_.reset();
    }
    if (camera_manager_) {
        camera_manager_->stop();
        camera_manager_.reset();
    }
}

void RPiCamApp::configureVideo(const VideoOptions &video_options) {
    if(!camera_) {
        throw runtime_error("Camera not opened");
    }

    StreamRoles roles = {
        { StreamRole::VideoRecording, "video" }
    };
    config_ = camera_->generateConfiguration(roles);
    if (!config_) {
        throw runtime_error("Failed to generate configuration for video stream");
    }

    auto &cnfg = config_->at(0);
    cnfg.pixelFormat = libcamera::formats::YUV420;
    cnfg.size.width = video_options_.width;
    cnfg.size.height = video_options_.height;
    cnfg.bufferCount = 4; // Set buffer count for video stream

    if (camera_->configure(config_.get()) < 0) {
        throw runtime_error("Failed to configure camera for video stream");
    }

    stream_ = config_->at(0).stream();
}

void RPiCamApp::startCamera() {
    if (!camera_) {
        throw runtime_error("Camera not opened");
    }

    if (camera_->start()) {
        throw runtime_error("Failed to start camera");
    }

    camera_started_ = true;
}

void RPiCamApp::stopCamera() {
    if (camera_started_) {
        camera_->stop();
        camera_started_ = false;
    }
}

RPICamApp::Stream *RPICamApp::videoStream(StreamInfo *info) const {
    if (!stream_) {
        throw runtime_error("Video stream not configured");
    }

    if (info) {
        info->width = stream_->configuration().size.width;
        info->height = stream_->configuration().size.height;
        info->stride = stream_->configuration().stride;
        info->pixel_format = stream_->configuration().pixelFormat;
        info->colour_space = stream_->configuration().colorSpace;
    }

    return stream_;
}

RPICamApp::CompletedRequestPtr RPICamApp::wait() {
    std::unique_lock<std::mutex> lock(queue_mutex_);
    queue_cv_.wait(lock, [this] { return !request_queue_.empty(); });

    auto request = request_queue_.front();
    request_queue_.pop();
    return request;
}

void RPICamApp::handleRequestComplete(CompletedRequestPtr request) {
    std::lock_guard<std::mutex> lock(queue_mutex_);
    request_queue_.push(request);
    queue_cv_.notify_one();
}




