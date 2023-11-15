# ros2_tutorial_ws

1. Publish and subscribe using RQT in C++

![Alt text](<screen_capture/Screenshot from 2023-11-10 10-16-21.png>)

Here is just one simple example of using qt5 widget as plugin in rqt. It publish and subcribe cmd_vel topic. The slider will publish the cmd_vel topic and the odometer needles will display subsribed cmd_vel.   

The example is based on ros2 Humble. So install that first, then rosdep install this package dependencies, colcon build and source the built package.   

2. RTSP stream

![Alt text](<screen_capture/Screenshot from 2023-11-15 14-22-17.png>)

This is example on how to view RTSP stream in RQT. I use mediamtx from here https://github.com/bluenviron/mediamtx/releases/download/v1.3.0/mediamtx_v1.3.0_darwin_amd64.tar.gz to stream the video in RTSP but add few lines in it's YML file to use ffmpeg codec. It provides better latency and use a lot smaller bandwidth than display ros2 image topic.

Edit mediamtx.yml and replace everything inside section paths with the following content -->

```
  paths:
    cam:
      runOnInit: ffmpeg -f v4l2 -i /dev/video0 -an -pix_fmt rgb24 -preset ultrafast -b:v 600k -f rtsp rtsp://localhost:$RTSP_PORT/$MTX_PATH
      runOnInitRestart: yes
```

/dev/video0 -> is source of the video to stream. This might not be the same if have more than 1 camera.
$RTSP_PORT -> by default is 8554
$MTX_POST -> is 'cam'
