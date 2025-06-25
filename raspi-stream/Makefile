# Cross-compiler prefix (adjust path if needed)
CROSS_COMPILE ?= aarch64-linux-gnu-
CC := $(CROSS_COMPILE)g++
CFLAGS := -O2 -Wall -std=c++17

# Source and build directories
SRC_DIR := src
CORE_DIR := core
STREAMER_DIR := streamer

SRCS := $(wildcard $(SRC_DIR)/*.cpp) \
        $(wildcard $(CORE_DIR)/*.cpp) \
        $(wildcard $(STREAMER_DIR)/*.cpp)

OBJS := $(SRCS:.cpp=.o)

INCLUDES := -I$(SRC_DIR) -I$(CORE_DIR) -I$(STREAMER_DIR)

# Libraries (add libcamera if needed)
LIBS := -lpthread -lstdc++fs -lcamera

TARGET := raspi-stream

all: $(TARGET)

$(TARGET): $(OBJS)
    $(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS)

%.o: %.cpp
    $(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
    rm -f $(SRC_DIR)/*.o $(CORE_DIR)/*.o $(STREAMER_DIR)/*.o $(TARGET)

.PHONY: all clean