CC = g++
CFLAGS = -std=c++11 `pkg-config --libs opencv4` `pkg-config --cflags opencv4` -O3

TARGET = main
SRCS = main.cpp

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) 
