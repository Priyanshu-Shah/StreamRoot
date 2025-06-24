#include <string>

#include "core/camera_app.hpp"
#include "core/stream_info.hpp"
#include "core/video_options.hpp"

#include "streamer/streamer.hpp"

using namespace std;

int main(int argc, char *argv[]){
    VideoOptions options;
    options.width = 1280;
    options.height = 720;

    if(argc > 1){
        string res = argv[1];
        if(res == "720p"){
            options.width = 1280;
            options.height = 720;
        } else if(res == "1080p"){
            options.width = 1920;
            options.height = 1080;
        } else if(res == "480p"){
            options.width = 640;
            options.height = 480;
        } else {
            cerr << "Invalid resolution option, using default 720p" << endl;
        }
    }

    RPiCamApp cam;
    cam.openCamera();
    cam.configureVideo(options);
    cam.startCamera();

    // Main loop to process video stream
    //TODO: Make consistent with the streamer class
    Streamer streamer(options);

    while(true){
        auto req = cam.wait();
        if(!req) {
            cerr << "Failed to get request" << endl;
            continue;
        }

        StreamInfo stream_info;
        auto video_stream = cam.videoStream(&stream_info);
        auto buffers = req->buffers[video_stream];

        streamer.processFrame(buffers, stream_info);
    }

    cam.stopCamera();
    cam.closeCamera();
    return 0;
}
