# Minimal Embedded Linux OS for Video Streaming on Raspberry Pi 3

## 📌 Project Overview

[Wiki Overview Page](https://github.com/Priyanshu-Shah/StreamRoot/wiki/Project-Overview)

This project aims to create a **custom, headless embedded Linux distribution** using **Buildroot** for the **Raspberry Pi 3**. The OS is designed to **stream video** from the **Raspberry Pi Camera Module 3** with minimal resource usage (CPU, RAM, storage), in contrast to typical streaming setups like FFmpeg on Ubuntu.

> 🚀 Future Prospect: This base will eventually support a web-based dashboard for live video view, object tracking, and alert notifications.

---

## 🎯 Objectives

- Build a minimal Linux OS using Buildroot.
- Enable compatibility with Raspberry Pi 3 hardware.
- Integrate drivers for the Raspberry Pi Camera Module 3.
- Capture and stream video efficiently.
- Benchmark performance against traditional full OS solutions.

---

## 🛠️ Tools & Technologies

- **Buildroot**
- **Linux Kernel**
- **Raspberry Pi 3**
- **Camera Module 3 (Sony IMX708)**
- **V4L2 / libcamera**
- **BusyBox / Dropbear / Minimal Shell**

---

## 📁 Project Structure

project-root/

│

├── buildroot/ # Buildroot configuration and source

├── board-support/ # Raspberry Pi overlays and boot files

├── scripts/ # Streaming and capture scripts

├── docs/ # Planning, logs, and benchmarks

└── output/ # Buildroot generated rootfs, kernel, images


---

## 🚦 Project Status

| Phase                  | Status   |
|------------------------|----------|
| Buildroot setup        | 🟡 Pending |
| RPi3 bring-up          | 🔲 Not started |
| Camera integration     | 🔲 Not started |
| Streaming application  | 🔲 Not started |
| Performance validation | 🔲 Not started |

---

## 📅 Scrum Plan

This project is broken into 3 major scrums:

1. **Scrum 1: OS Bring-up**  
   - Minimal Buildroot config  
   - Boot on RPi3  

2. **Scrum 2: Camera Integration**  
   - Enable and test camera drivers  
   - Capture sample frames  

3. **Scrum 3: Streaming & Optimization**  
   - Implement low-overhead streaming  
   - Benchmark vs Ubuntu + FFmpeg  

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

