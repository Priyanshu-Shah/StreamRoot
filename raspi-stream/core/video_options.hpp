#pragma once

#include <string>

struct VideoOptions
{
    // Video resolution
    unsigned int width = 1280;      // Default: 1280 (720p)
    unsigned int height = 720;      // Default: 720 (720p)
    unsigned int framerate = 30;    // Default: 30 fps

    // Encoding options
    std::string codec = "h264";     // Default: h264
    unsigned int bitrate = 2000000; // Default: 2 Mbps

    // Optionally, add a constructor to set from command line or config
    VideoOptions() = default;
};