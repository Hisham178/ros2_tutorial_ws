# ros2_tutorial_ws

1. Publish and subscribe using RQT in C++

![Alt text](<screen_capture/Screenshot from 2023-11-10 10-16-21.png>)

Here is just one simple example of using qt5 widget as plugin in rqt. It publish and subcribe cmd_vel topic. The slider will publish the cmd_vel topic and the odometer needles will display subsribed cmd_vel.   

The example is based on ros2 Humble. So install that first, then rosdep install this package dependencies, colcon build and source the built package.   

2. RTSP stream

![Alt text](<screen_capture/Screenshot from 2023-11-15 14-22-17.png>)

This is example on how to view RTSP stream in RQT. I use mediamtx from here https://github.com/bluenviron/mediamtx/releases/download/v1.3.0/mediamtx_v1.3.0_darwin_amd64.tar.gz to stream the video in RTSP but add few lines in it's YML file to use ffmpeg codec. It provides better latency and use a lot smaller bandwidth than display ros2 image topic.

You need to install GStreamer first. Please follow the installation guide from here https://linux.how2shout.com/installing-gstreamer-on-ubuntu-22-04-or-20-04-lts-linux/

This example use this address to view the stream in tutorial_2.cpp:

```
  // RTSP
  QString camIP = "127.0.0.1";
  QString camPort = "8554";
  QString camPath = "cam";
```

Edit mediamtx.yml and replace everything inside section paths with the following content:

```
  paths:
    cam:
      runOnInit: ffmpeg -f v4l2 -i /dev/video0 -an -pix_fmt rgb24 -preset ultrafast -b:v 600k -f rtsp rtsp://localhost:$RTSP_PORT/$MTX_PATH
      runOnInitRestart: yes
```

/dev/video0 -> is source of the video to stream. This might not be the same if have more than 1 camera.
$RTSP_PORT -> by default is 8554
$MTX_POST -> is 'cam'

Run ./mediamtx first before view the stream on RQT

3. This is tutorial to read data from serial port from Sparkfun RTK-Ekspress. The data in this codes extract gps accuracy and publish back as a topic that can be used to display on RQT. 

This example does not cover the RQT part.

![Alt text](<screen_capture/18019-SparkFun_RTK_Express-09.jpg>)

How to :  1. Connect using usb to your pc(Ubuntu 22.04 Tested) using port that I higlighted on the photo.
          2. Type --> cd /dev/serial/by-path && ls -la
          3. Choose the one that is RTK-Express and take note something like this "pci-0000:00:14.0-usb-0:6:1.0-port0"
          4. Copy and replace in the code
          5. colcon build 
          6. source install/setup.bash
          7. ros2 run gps_serial gps_accuracy

  In few seconds the terminal will start print the accuracy data of the gps which also at the same time publishing gps accuracy in ros topic

  ![Alt text](<screen_capture/Screenshot from 2023-12-15 10-57-43.png>)

  You can subsribe the data and display in RQT like this : 
  ![Alt text](<screen_capture/Screenshot from 2023-12-15 10-57-43.png>)
        



