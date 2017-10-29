# use pkg-config for getting CFLAGS and LDLIBS  
# FFMPEG_LIBS=    libavdevice                        \  
#                 libavformat                        \  
#                 libavfilter                        \  
#                 libavcodec                         \  
#                 libswresample                      \  
FFMPEG_LIBS =	libswscale libavutil

CC = gcc
CFLAGS += -Wall -O2 -g  
CFLAGS += $(shell pkg-config --cflags $(FFMPEG_LIBS))  
LDLIBS += $(shell pkg-config --libs $(FFMPEG_LIBS))  

main:
	$(CC) $(CFLAGS) $(LDLIBS) main.c

clean:  
	rm -rf main main.o