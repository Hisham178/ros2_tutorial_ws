#!/usr/bin/python3
# -*- coding: utf-8 -*-
from launch_ros.actions import Node

import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile
from std_msgs.msg import Float32

import serial
import re


class gpsRTK_serial(Node):
    def __init__(self):
        super().__init__("gpsRTK_serial_node")
        qos_profile = QoSProfile(depth=100)
        self.current_time = self.get_clock().now()
        self.last_time = self.get_clock().now()

        #Extracted accuracy data is publish into a ros2 topic
        self.accuracyGPS1 = self.create_publisher(Float32, "gps1/accuracy", qos_profile)

        timer_period = 0.01  # seconds

        self.timer = self.create_timer(timer_period, self.timer_callback)

        self.i = 0

    def timer_callback(self):
        #Need to identify where gps rtk is connected to host pc first
        #cd /dev/serial/by-path && ls -la
        serGPS1 = serial.Serial(
            port="/dev/serial/by-path/pci-0000:00:14.0-usb-0:6:1.0-port0",
            baudrate=115200,
            timeout=5,
        )

        messageGPS1 = serGPS1.readline()
        outputGPS1 = messageGPS1.decode("utf-8")

        accuracyGPS1 = Float32()

        substring = "Accuracy"
        substringError = "Waiting"

        if substringError in outputGPS1:
            p = "[\d]+[.,\d]+|[\d]*[.][\d]+|[\d]+"
            s = outputGPS1
            if re.search(p, s) is not None:
                for catch in re.finditer(p, s):
                    if catch[0] != "1.00":
                        print(catch[0])
                        accuracyGPS1.data = float(catch[0])
                        self.accuracyGPS1.publish(accuracyGPS1)

        else:
            if substring in outputGPS1:
                p = "[\d]+[.,\d]+|[\d]*[.][\d]+|[\d]+"
                s = outputGPS1
                if re.search(p, s) is not None:
                    for catch in re.finditer(p, s):
                        if catch[0] != "1.00":
                            accuracyGPS1.data = float(catch[0])
                            self.accuracyGPS1.publish(accuracyGPS1)
                            print(catch[0])

def main(args=None):
    rclpy.init(args=args)

    gpsRTK_serial_node = gpsRTK_serial()

    rclpy.spin(gpsRTK_serial_node)

    gpsRTK_serial_node.destroy_node()
    rclpy.shutdown()

if __name__ == "__main__":
    main()
