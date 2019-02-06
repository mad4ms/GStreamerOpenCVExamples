#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>

// Assume your webcam as device video0. You can check the format by executing v4l2-ctl --list-formats-ext
// Usually, Ubuntu gives you the pixel format YUYV (uncompressed) with different resolutions.
// E.g. the best my shitty webcam can do is 640x480 on YUYV (or YUY2 in gstreamer string)

/// Funny note. If you exec "export GST_DEBUG=4" and then try something like displaying your webcam on the autovideosink
/// like this "gst-launch-1.0 v4l2src ! videoconvert ! autovideosink", the debug spits out all possible caps that you
/// can actually copy and paste. (caps are the preferences for the cam .. the video/x-raw , format, res and stuff.
const std::string webcam2appsink_YUY2_640_480 = "v4l2src device=/dev/video0 ! video/x-raw, format=YUY2, width=640, height=480, pixel-aspect-ratio=1/1, framerate=30/1 ! videoconvert ! appsink";
// My webcam can apparently do some fancy jpeg compression on higher res.
const std::string webcam2appsink_JPEG_1280_720 = "v4l2src device=/dev/video0 ! image/jpeg, width=(int)1280, height=(int)720, pixel-aspect-ratio=(fraction)1/1, framerate=(fraction)30/1 ! jpegparse ! jpegdec ! videoconvert ! appsink";

// I got this one from https://gist.github.com/esrever10/7d39fe2d4163c5b2d7006495c3c911bb.
/// I think the src appsink is clear. After this, videoconvert it so the x264enc can do it's work. After that, don't forger to acutally attach the payload
/// before u sink it into udp sink.
const std::string appsink2rtp_H264 = "appsrc ! videoconvert ! x264enc tune=zerolatency bitrate=500 speed-preset=superfast ! rtph264pay ! udpsink host=127.0.0.1 port=5000";

const std::string appsink2rtp_H264_multi = "appsrc ! videoconvert ! x264enc tune=zerolatency bitrate=500 speed-preset=superfast ! rtph264pay ! udpsink host=239.255.0.1 port=5000 auto-multicast=true";




/// Funny note: Use the following lines as an sdp file (e.g. test.sdp) for watching the videostream in VLC. (of course without the ///)
/// c=IN IP4 127.0.0.1
/// m=video 5000 RTP/AVP 96
/// a=rtpmap:96 H264/90000

/// Save it as test.sdp and execute this application and also "vlc test.sdp".
/// If everythink went fine, the stream should show up on VLC.
/// gg.

// gst-launch-1.0 -v udpsrc port=5000 caps = "application/x-rtp, media=(string)video, clock-rate=(int)90000, encoding-name=(string)H264, payload=(int)96" ! rtph264depay ! decodebin ! videoconvert ! autovideosink
const std::string rtp2appsink_H264 = "udpsrc port=5000 ! application/x-rtp, media=video, clock-rate=90000, encoding-name=H264, payload=96 ! rtph264depay ! decodebin ! videoconvert ! appsink";

/// MULTICAST! Make sure that your router supports Multicast. Usually it's a setting like "Optimize for IPTV" or stuff like that. I assume that you can google it.
/// Funny note: Use the following lines as an sdp file (e.g. test.sdp) for watching the videostream in VLC. (of course without the ///)
/// c=IN IP4 239.255.0.1
/// m=video 5004 RTP/AVP 96
/// a=rtpmap:96 H264/90000

/// Save it as test.sdp and execute this application and also "vlc test.sdp".
/// If everythink went fine, the stream should show up on VLC.
/// gg.
const std::string rtp2appsink_H264_multi = "udpsrc multicast-group=239.255.0.1 auto-multicast=true port=5000 ! application/x-rtp, media=video, clock-rate=90000, encoding-name=H264, payload=96 ! rtph264depay ! decodebin ! videoconvert ! appsink";

#endif // COMMANDS_H
