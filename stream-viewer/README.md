# UDP YUV420 Video Receiver

This is a simple UDP receiver for raw YUV420 video frames sent from a Raspberry Pi or other device.

## Usage

1. **Build the receiver:**
   ```sh
   g++ -o udp_receiver udp_receiver.cpp
   ```

2. **Run the receiver:**
   ```sh
   ./udp_receiver <listen_port> <width> <height> <output_file>
   ```
   Example:
   ```sh
   ./udp_receiver 5000 1280 720 out.yuv
   ```

3. **View the stream with ffplay:**
   In another terminal, run:
   ```sh
   ffplay -f rawvideo -pixel_format yuv420p -video_size 1280x720 out.yuv
   ```

   Or, for live viewing, use# UDP YUV420 Video Receiver

This is a simple UDP receiver for raw YUV420 video frames sent from a Raspberry Pi or other device.

## Usage

1. **Build the receiver:**
   ```sh
   g++ -o udp_receiver udp_receiver.cpp
   ```

2. **Run the receiver:**
   ```sh
   ./udp_receiver <listen_port> <width> <height> <output_file>
   ```
   Example:
   ```sh
   ./udp_receiver 5000 1280 720 out.yuv
   ```

3. **View the stream with ffplay:**
   In another terminal, run:
   ```sh
   ffplay -f rawvideo -pixel_format yuv420p -video_size 1280x720 out.yuv
   ```

   Or, for live viewing,