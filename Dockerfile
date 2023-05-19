# Use a multi-stage build to handle different base images
FROM ros:humble-ros-base-jammy AS amd64_builder
FROM arm64v8/ros:humble-ros-base-jammy AS arm64_builder

# Choose the appropriate base image based on the platform architecture
ARG TARGETARCH
FROM ${TARGETARCH}_builder AS builder

# install ros package
RUN apt-get update && apt-get install -y \
    ros-${ROS_DISTRO}-demo-nodes-cpp \
    ros-${ROS_DISTRO}-demo-nodes-py && \
    rm -rf /var/lib/apt/lists/*

# Set the working directory
WORKDIR /app

# Copy the application files to the container
COPY . /app

SHELL ["/bin/bash", "-c"]
RUN echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc