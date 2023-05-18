FROM osrf/ros:humble-desktop

SHELL ["/bin/bash", "-c"]

RUN source /opt/ros/humble/setup.bash && \
    export ROS_DOMAIN_ID=57 && \
    export ROS_LOCALHOST_ONLY=1

RUN apt-get update && apt-get install -y \
    libxcb-xinerama0 \
    libxkbcommon-x11-0 \
    libgl1-mesa-glx \
    libgl1-mesa-dri

ENV LIBGL_ALWAYS_INDIRECT=1