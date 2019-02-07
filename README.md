# GStreamerOpenCVExamples
GStreamer inside OpenCV examples in C++ 

It was very troublesome to get proper working examples of GStreamer inside the OpenCV framework.
So here are a few.

## Info
I'm working on Ubuntu 18.04, no custom shit here.

Besides the usual stuff (cmake, build-essentials, etc.) for working with C++ you need to have installed,
your OpenCV's build information should look similar to the following (especially FFMPEG, GSTREAMER section).
I work with QT as an IDE, you don't need this necessarily. Also, Intel Media SDK isn't necessary.
```
General configuration for OpenCV 4.0.1 =====================================
  Version control:               4.0.1

  Platform:
    Timestamp:                   2019-01-21T14:04:48Z
    Host:                        Linux 4.15.0-43-generic x86_64
    CMake:                       3.10.2
    CMake generator:             Unix Makefiles
    CMake build tool:            /usr/bin/make
    Configuration:               Release

  CPU/HW features:
    Baseline:                    SSE SSE2 SSE3
      requested:                 SSE3
    Dispatched code generation:  SSE4_1 SSE4_2 FP16 AVX AVX2 AVX512_SKX
      requested:                 SSE4_1 SSE4_2 AVX FP16 AVX2 AVX512_SKX
      SSE4_1 (7 files):          + SSSE3 SSE4_1
      SSE4_2 (2 files):          + SSSE3 SSE4_1 POPCNT SSE4_2
      FP16 (1 files):            + SSSE3 SSE4_1 POPCNT SSE4_2 FP16 AVX
      AVX (5 files):             + SSSE3 SSE4_1 POPCNT SSE4_2 AVX
      AVX2 (13 files):           + SSSE3 SSE4_1 POPCNT SSE4_2 FP16 FMA3 AVX AVX2
      AVX512_SKX (1 files):      + SSSE3 SSE4_1 POPCNT SSE4_2 FP16 FMA3 AVX AVX2 AVX_512F AVX512_SKX

  C/C++:
    Built as dynamic libs?:      YES
    C++ Compiler:                /usr/bin/c++  (ver 7.3.0)
    C++ flags (Release):         -fsigned-char -W -Wall -Werror=return-type -Werror=non-virtual-dtor -Werror=address -Werror=sequence-point -Wformat -Werror=format-security -Wmissing-declarations -Wundef -Winit-self -Wpointer-arith -Wshadow -Wsign-promo -Wuninitialized -Winit-self -Wno-narrowing -Wno-delete-non-virtual-dtor -Wno-comment -Wimplicit-fallthrough=3 -Wno-strict-overflow -fdiagnostics-show-option -Wno-long-long -pthread -fomit-frame-pointer -ffunction-sections -fdata-sections  -msse -msse2 -msse3 -fvisibility=hidden -fvisibility-inlines-hidden -fopenmp -O3 -DNDEBUG  -DNDEBUG
    C++ flags (Debug):           -fsigned-char -W -Wall -Werror=return-type -Werror=non-virtual-dtor -Werror=address -Werror=sequence-point -Wformat -Werror=format-security -Wmissing-declarations -Wundef -Winit-self -Wpointer-arith -Wshadow -Wsign-promo -Wuninitialized -Winit-self -Wno-narrowing -Wno-delete-non-virtual-dtor -Wno-comment -Wimplicit-fallthrough=3 -Wno-strict-overflow -fdiagnostics-show-option -Wno-long-long -pthread -fomit-frame-pointer -ffunction-sections -fdata-sections  -msse -msse2 -msse3 -fvisibility=hidden -fvisibility-inlines-hidden -fopenmp -g  -O0 -DDEBUG -D_DEBUG
    C Compiler:                  /usr/bin/cc
    C flags (Release):           -fsigned-char -W -Wall -Werror=return-type -Werror=non-virtual-dtor -Werror=address -Werror=sequence-point -Wformat -Werror=format-security -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Winit-self -Wpointer-arith -Wshadow -Wuninitialized -Winit-self -Wno-narrowing -Wno-comment -Wimplicit-fallthrough=3 -Wno-strict-overflow -fdiagnostics-show-option -Wno-long-long -pthread -fomit-frame-pointer -ffunction-sections -fdata-sections  -msse -msse2 -msse3 -fvisibility=hidden -fopenmp -O3 -DNDEBUG  -DNDEBUG
    C flags (Debug):             -fsigned-char -W -Wall -Werror=return-type -Werror=non-virtual-dtor -Werror=address -Werror=sequence-point -Wformat -Werror=format-security -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef -Winit-self -Wpointer-arith -Wshadow -Wuninitialized -Winit-self -Wno-narrowing -Wno-comment -Wimplicit-fallthrough=3 -Wno-strict-overflow -fdiagnostics-show-option -Wno-long-long -pthread -fomit-frame-pointer -ffunction-sections -fdata-sections  -msse -msse2 -msse3 -fvisibility=hidden -fopenmp -g  -O0 -DDEBUG -D_DEBUG
    Linker flags (Release):      
    Linker flags (Debug):        
    ccache:                      NO
    Precompiled headers:         YES
    Extra dependencies:          dl m pthread rt /usr/lib/x86_64-linux-gnu/libGL.so /usr/lib/x86_64-linux-gnu/libGLU.so
    3rdparty dependencies:

  OpenCV modules:
    To be built:                 calib3d core dnn features2d flann gapi highgui imgcodecs imgproc java_bindings_generator ml objdetect photo python2 python3 python_bindings_generator stitching ts video videoio
    Disabled:                    world
    Disabled by dependency:      -
    Unavailable:                 java js
    Applications:                tests perf_tests apps
    Documentation:               NO
    Non-free algorithms:         NO

  GUI: 
    QT:                          YES (ver 5.12.0)
      QT OpenGL support:         YES (Qt5::OpenGL 5.12.0)
    GTK+:                        NO
    OpenGL support:              YES (/usr/lib/x86_64-linux-gnu/libGL.so /usr/lib/x86_64-linux-gnu/libGLU.so)
    VTK support:                 NO

  Media I/O: 
    ZLib:                        /usr/lib/x86_64-linux-gnu/libz.so (ver 1.2.11)
    JPEG:                        /usr/lib/x86_64-linux-gnu/libjpeg.so (ver 80)
    WEBP:                        build (ver encoder: 0x020e)
    PNG:                         /usr/lib/x86_64-linux-gnu/libpng.so (ver 1.6.34)
    TIFF:                        build (ver 42 - 4.0.9)
    JPEG 2000:                   build (ver 1.900.1)
    OpenEXR:                     build (ver 1.7.1)
    HDR:                         YES
    SUNRASTER:                   YES
    PXM:                         YES
    PFM:                         YES

  Video I/O:
    DC1394:                      YES (ver 2.2.5)
    FFMPEG:                      YES
      avcodec:                   YES (ver 57.107.100)
      avformat:                  YES (ver 57.83.100)
      avutil:                    YES (ver 55.78.100)
      swscale:                   YES (ver 4.8.100)
      avresample:                NO
    GStreamer:                   
      base:                      YES (ver 1.14.1)
      video:                     YES (ver 1.14.1)
      app:                       YES (ver 1.14.1)
      riff:                      YES (ver 1.14.1)
      pbutils:                   YES (ver 1.14.1)
    v4l/v4l2:                    linux/videodev2.h
    Intel Media SDK:             YES (/opt/intel/mediasdk/lib/libmfx.so)

  Parallel framework:            OpenMP

  Trace:                         YES (with Intel ITT)

  Other third-party libraries:
    Intel IPP:                   2019.0.0 Gold [2019.0.0]
           at:                   /home/madams/dev/libraries/opencv/build/3rdparty/ippicv/ippicv_lnx/icv
    Intel IPP IW:                sources (2019.0.0)
              at:                /home/madams/dev/libraries/opencv/build/3rdparty/ippicv/ippicv_lnx/iw
    Lapack:                      NO
    Eigen:                       YES (ver 3.3.4)
    Custom HAL:                  NO
    Protobuf:                    build (3.5.1)

  OpenCL:                        YES (no extra features)
    Include path:                /home/madams/dev/libraries/opencv/3rdparty/include/opencl/1.2
    Link libraries:              Dynamic load

  Python 2:
    Interpreter:                 /usr/bin/python2.7 (ver 2.7.15)
    Libraries:                   /usr/lib/x86_64-linux-gnu/libpython2.7.so (ver 2.7.15rc1)
    numpy:                       /usr/lib/python2.7/dist-packages/numpy/core/include (ver 1.13.3)
    install path:                lib/python2.7/dist-packages/cv2/python-2.7

  Python 3:
    Interpreter:                 /usr/bin/python3 (ver 3.6.7)
    Libraries:                   /usr/lib/x86_64-linux-gnu/libpython3.6m.so (ver 3.6.7)
    numpy:                       /usr/lib/python3/dist-packages/numpy/core/include (ver 1.13.3)
    install path:                lib/python3.6/dist-packages/cv2/python-3.6

  Python (for build):            /usr/bin/python2.7
    Pylint:                      /home/madams/.local/bin/pylint (ver: 3.6.7, checks: 168)

  Java:                          
    ant:                         NO
    JNI:                         NO
    Java wrappers:               NO
    Java tests:                  NO

  Install to:                    /usr/local
-----------------------------------------------------------------
```

## Prerequisites

Fairly simple if your system is set up properly.

Just to be sure, here are the most important packages before building OpenCV:
```
sudo apt-get install libgstreamer1.0-dev libgstreamer-plugins-bad1.0-dev libgstreamer-plugins-base1.0-dev libgstreamer-plugins-good1.0-dev cmake-qt-gui
```

Now compile OpenCV from source. I've got a script that configures and builds OpenCV to my needs, you can use cmake-gui making sure WITH_GSTREAMER is checked (if checked, uncheck WITH_GSTREAMER_0_10). Build and install OpenCV.

## Installation

```
git clone https://github.com/madams1337/GStreamerOpenCVExamples.git
cd GStreamerOpenCVExamples
mkdir -p build
cd build
cmake ..
make

./gstExampleWebcamToRTP # Starts and displays webcam to appsink to rtp
./gstExampleRTPtoAppsink # Starts RTP to appsink

```

Mind that this might not work out of the box since your computer could have a different kind of webcam than mine. Pls read the comments in the code carefully, i think i explained a lot there as well. Adapt the settings accordingly.

## Props

Check out [Tik0s mat2gstreamer](https://github.com/tik0/mat2gstreamer), also a lot of stuff explained there.
Shared Memory examples are available in Python on my other [Repo](https://github.com/madams1337/python-opencv-gstreamer-examples)

