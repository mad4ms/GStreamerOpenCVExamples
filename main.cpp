// OS stuff
#include <iostream>

// CV stuff
#include <opencv2/opencv.hpp>

// My stuff. Read the comments in the header.
#include "commands.h"

// Lazy stuff
using namespace std;
using namespace cv;

/// My webcam can do YUYV (or YUV2) format uncompressed @ 640x480 @ 30 FPS
/// or some mjpeg compression. Usually, if you didn't mess up the installation,
/// you can look up the gstreamer caps by exec "v4l2-ctl --list-formats-ext".
/// There, you can see the pixel format and adapt it accordingly in the commands.h
///
/// Just leave it commented. All webcams usually support YUYV umcompressed at this resolution.
#define COMPRESSED // Use jpeg compression provided by webcam


/// Uncomment if you wanna stream to multicast UDP. Usually, these are the IPs > 239.x.x.x, i guess.
/// Cuz im using 239.255.1.1 and it's working smoothly with some stuttering (key frame loss) in between.
///
/// Leave commented if you wanna prototype on your local pc
#define MULTICAST // Define if multicast

#ifdef COMPRESSED // Select resolution based on compression
#define WIDTH 1280
#define HEIGHT 720
#else
#define WIDTH 640
#define HEIGHT 480
#endif

void task_webcam_to_appsink_to_rtp(bool show_device) {
    // Get the device string here
#ifdef COMPRESSED
    string tmp_device = webcam2appsink_JPEG_1280_720;
#else
    string tmp_device = webcam2appsink_YUY2_640_480;
#endif
#ifndef MULTICAST
    string tmp_out = appsink2rtp_H264;
#else
    string tmp_out = appsink2rtp_H264_multi;
#endif
    // Initialize the capture
    VideoCapture cap(tmp_device, CAP_GSTREAMER);
    // Check
    if (!cap.isOpened()) {
        cerr << "[Error] Cannot open capture " << tmp_device << endl;
        return;
    } else {
        cout << "[Success] Capture " << tmp_device << " opened." << endl;
    }

    // Initialize the writer
    VideoWriter writer(tmp_out, CAP_GSTREAMER, 0, 30, Size(WIDTH,HEIGHT), true);
    // Check
    if (!writer.isOpened()) {
        cerr << "[Error] Cannot open writer " << tmp_out << endl;
        return;
    } else {
        cout << "[Success] Writer " << tmp_out << " opened." << endl;
    }

    // OpenCV frame
    Mat frame;

    // Inf loop

    while (1) {

        cap >> frame;

        // Check if valid
        if (frame.empty())
            break;
        // Show if needed
        if (show_device) {
            imshow("task_capture_wecam", frame);
            waitKey(1);
        }

        writer << frame;
    }
    // Clean up
    cap.release();
    cout << tmp_device << " done." << endl;
}

void task_rtp_to_appsink(bool show_device) {
#ifndef MULTICAST
    string tmp_device = rtp2appsink_H264;
#else
    string tmp_device = rtp2appsink_H264_multi;
#endif

    // Initialize the writer
    VideoCapture cap(tmp_device, CAP_GSTREAMER);
    // Check
    if (!cap.isOpened()) {
        cerr << "[Error] Cannot open cap " << tmp_device << endl;
        return;
    } else {
        cout << "[Success] Capture " << tmp_device << " opened." << endl;
    }
    // OpenCV frame
    Mat frame;

    while (1) {
        // Read frame from v4l2src
        cap >> frame;
        // Check the frame
        if (frame.empty()) {
            break;
        }
        if (show_device) {
            imshow("rtp_to_appsink",frame);
            waitKey(33);
        }
    }
}

void task_webcam_to_appsink_to_sm(bool show_device) {
    // Get the device string here
#ifdef COMPRESSED
    string tmp_device = webcam2appsink_JPEG_1280_720;
#else
    string tmp_device = webcam2appsink_YUY2_640_480;
#endif
    string tmp_out = appsink2sharedmemory;

    // Initialize the capture
    VideoCapture cap(tmp_device, CAP_GSTREAMER);
    // Check
    if (!cap.isOpened()) {
        cerr << "[Error] Cannot open capture " << tmp_device << endl;
        return;
    } else {
        cout << "[Success] Capture " << tmp_device << " opened." << endl;
    }

    // Initialize the writer
    VideoWriter writer(tmp_out, CAP_GSTREAMER, 0, 30, Size(WIDTH,HEIGHT), true);
    // Check
    if (!writer.isOpened()) {
        cerr << "[Error] Cannot open writer " << tmp_out << endl;
        return;
    } else {
        cout << "[Success] Writer " << tmp_out << " opened." << endl;
    }

    // OpenCV frame
    Mat frame;

    // Inf loop

    while (1) {

        cap >> frame;

        // Check if valid
        if (frame.empty())
            break;
        // Show if needed
        if (show_device) {
            imshow("task_webcam_to_appsink_to_sm", frame);
            waitKey(1);
        }

        writer << frame;
    }
    // Clean up
    cap.release();
    cout << tmp_device << " done." << endl;
}

void task_sm_to_appsink(bool show_device) {
#ifdef COMPRESSED
    string tmp_device = sharedmemory2appsink_1280_720;
#else
    string tmp_device = sharedmemory2appsink_640_480;
#endif

    // Initialize the writer
    VideoCapture cap(tmp_device, CAP_GSTREAMER);
    // Check
    if (!cap.isOpened()) {
        cerr << "[Error] Cannot open cap " << tmp_device << endl;
        return;
    } else {
        cout << "[Success] Capture " << tmp_device << " opened." << endl;
    }
    // OpenCV frame
    Mat frame;

    while (1) {
        // Read frame from v4l2src
        cap >> frame;
        // Check the frame
        if (frame.empty()) {
            break;
        }
        if (show_device) {
            imshow("task_sm_to_appsink",frame);
            waitKey(33);
        }
    }
}

int main() {
#ifdef COMPILE_WEBCAM
    task_webcam_to_appsink_to_rtp(true);
#endif
#ifdef COMPILE_STREAM
    task_rtp_to_appsink(true);
#endif
#ifdef COMPILE_WEBCAM_SHARED_MEMORY
    task_webcam_to_appsink_to_sm(true);
#endif
#ifdef COMPILE_SHARED_MEMORY_WEBCAM
    task_sm_to_appsink(true);
#endif
    return 0;
}
