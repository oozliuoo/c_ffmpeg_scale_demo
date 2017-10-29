# c_ffmpeg_scale_demo

Quick demo for ffmpeg swscale using C

# Install and compile ffmpeg (On Mac)

1. Follow the [official documentation](https://trac.ffmpeg.org/wiki/CompilationGuide/macOS) to compile and install **ffmpeg** in your system
2. After installation (i.e. executing `make && sudo make install`), please quickly check the path `/usr/local/lib/pkgconfig` to make sure that all ffmpeg libs are presented
3. Execute the following command line to set env variable:
```bash
export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig:$PKG_CONFIG_PATH
```

After the above three steps, you should be able to run the demo

# Running demo
1. Compile the demo by running `make` under this dir
2. Configure parameters passed to the demo program in `run.sh`, as explained below:
```
--src: the source .yuv file name
--dst the destination .yuv file name
--sw: frame width of the source file
--sh: frame height of the source file
--dw: frame width of the destination file
--dh: frame height of the destination file
--framenum: number of frame this .yuv file contains, if there is only one frame, then simply pass 1
```
NOTE: the sample file in this repository has `width = 176` and `height = 144`, and `framenum == 8`
3. Execute the demo by running `./run.sh`.

# Verifying result

Download [YUView](https://github.com/IENT/YUView/releases), and run it to open the source and the destination file. Then you could verify that the resolution has been changed.

# References
1. [how to use ffmpeg scale](http://guguclock.blogspot.sg/2009/12/ffmpeg-swscale.html)
2. [ffmpeg github](https://github.com/FFmpeg/FFmpeg)