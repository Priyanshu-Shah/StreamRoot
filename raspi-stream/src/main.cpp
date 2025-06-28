/*

Working:
Stream info is a struct carrying the width, height, stride, pixel format and color space of the video stream.
We have set the pixel_format currently to YUV420, which is a common format for video streaming.

The videostream function in the camera app is responsible for populating this struct using the camera configurations.
req->buffers[videostream] gives us a pointer to the FrameBuffer containing the video data.
So this is passed as the buffer to the streamer class. 

*/

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

    if(argc < 3){
        cerr << "Usage: " << argv[0] << " <resolution> <destination_url> [port]" << endl;
        cerr << "Example: " << argv[0] << " 720p rtsp://localhost:8554/stream" << endl;
        return 1;
    }

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

    string destination_url = argv[2];
    int port = 8554;
    if(argc > 3) port = stoi(argv[3]);
    else {
        cout << "No port specified, using default 8554" << endl;
    }

    cout << "Starting stream with resolution " << options.width << "x" << options.height
         << ", destination: " << destination_url << ":" << port << endl;


    RPiCamApp cam;
    cam.openCamera();
    cam.configureVideo(options);
    cam.startCamera();

    // Main loop to process video stream
    Streamer streamer(destination_url, port);

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
