# Minimal Embedded Linux OS for Video Streaming on Raspberry Pi 3

## 📌 Project Overview

[Wiki Overview Page](https://github.com/Priyanshu-Shah/StreamRoot/wiki/Project-Overview)

This project aims to create a **custom, headless embedded Linux distribution** using **Buildroot** for the **Raspberry Pi 3**. The OS is designed to **stream video** from the **Raspberry Pi Camera Module 3** with minimal resource usage (CPU, RAM, storage), in contrast to typical streaming setups like FFmpeg on Ubuntu.

> 🚀 Future Prospect: This base will eventually support a web-based dashboard for live video view, object tracking, and alert notifications.

---

## 🎯 Objectives

- Build a minimal Linux OS using Buildroot.
- Enable compatibility with Raspberry Pi 4b hardware.
- Integrate drivers for the Raspberry Pi Camera Module 2.
- Capture and stream video efficiently **over UDP using a custom C++ application**.
- Benchmark performance against traditional full OS solutions.

---

## 🛠️ Tools & Technologies

- **Buildroot**
- **Linux Kernel**
- **Raspberry Pi 4b**
- **Camera Module 2 (Sony IMX219)**
- **libcamera**
- **BusyBox**
- **Custom C++ UDP streaming application**
- **UDP receiver/viewer utility (for desktop viewing)**

---

## 📁 Project Structure

project-root/

│

├── buildroot/ # Buildroot configuration and source along with the build files 

├── raspi-stream/ # C++ camera and streaming application

   ├── core/ # Stores all core cpp modules and class definitions for camera utility
   ├── src/ # Contains the main application
   ├── streamer/ # Contains logic of the streaming applicaiton

├── stream-viewer/ # UDP receiver/viewer utility for desktop



---

## 🚦 Project Status

| Phase                  | Status   |
|------------------------|----------|
| Buildroot setup        | 🟡 Complete |
| RPi4b bring-up          | 🔲 Complete |
| Camera integration     | 🔲 Complete |
| Streaming application  | 🟡 Complete |
| Performance validation | 🔲 In progress |

---

## 📅 Scrum Plan

This project is broken into 3 major scrums:

1. **Scrum 1: OS Bring-up**  
   - Minimal Buildroot config  
   - Boot on RPi4b

2. **Scrum 2: Camera Integration**  
   - Enable and test camera drivers  
   - Capture sample frames  

3. **Scrum 3: Streaming & Optimization**  
   - Implement low-overhead streaming  
   - Benchmark vs Ubuntu + FFmpeg  

---

## 🖥️ Streaming Application

- The main streaming application is written in C++ and uses **libcamera** to capture frames from the Pi Camera.
- Frames are sent over UDP using a custom `Streamer` class, which transmits all planes of each frame.
- The application supports resolution selection (720p, 1080p, 480p) via command-line arguments.
- Usage example: ./raspi-stream 720p <destination_ip> [port]
- Default port is 8554 if not specified.

---

## 🖥️ UDP Receiver/Viewer

- A simple UDP receiver utility (`udp-receiver.cpp`) is provided for desktop use.
- It listens for incoming UDP packets, reconstructs YUV420 frames, and writes them to a file.
- Example usage: ./udp-receiver 5000 1280 720 out.yuv
- You can view the resulting file with `ffplay`: ffplay -f rawvideo -pixel_format yuv420p -video_size 1280x720 out.yuv

---

## 📌 Future Extensions

- Web-based dashboard for stream viewing
- Object tracking (OpenCV / ML models)
- Alert system based on detected events
- WebSocket or MQTT-based backend integration

---

## 📚 References

- [Buildroot Documentation](https://buildroot.org/docs.html)
- [Raspberry Pi Camera Docs](https://www.raspberrypi.com/documentation/accessories/camera.html)
- [V4L2 API Reference](https://linuxtv.org/downloads/v4l-dvb-apis/)
- [Libcamera](https://libcamera.org/)

---

## 📜 License

This project is for academic and educational purposes.