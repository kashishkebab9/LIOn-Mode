# Base image
FROM ubuntu:24.04

# Environment setup
ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Etc/UTC

# Update and install dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    locales \
    tzdata \
    lsb-release \
    curl \
    gnupg2 \
    build-essential \
    cmake \
    git \
    wget \
    libeigen3-dev \
    && rm -rf /var/lib/apt/lists/*

# Set locale (required by ROS 2)
RUN locale-gen en_US en_US.UTF-8 && \
    update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
ENV LANG=en_US.UTF-8
ENV LC_ALL=en_US.UTF-8

# Set up ROS 2 Jazzy sources
RUN apt-get update && apt-get install -y --no-install-recommends \
    software-properties-common \
    && add-apt-repository universe

RUN curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key | gpg --dearmor -o /usr/share/keyrings/ros-archive-keyring.gpg && \
    echo "deb [signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(lsb_release -cs) main" \
    > /etc/apt/sources.list.d/ros2.list

# Install ROS 2 base (or you can use ros-base, desktop, etc.)
RUN apt-get update && apt-get install -y --no-install-recommends \
    ros-jazzy-desktop \
    && rm -rf /var/lib/apt/lists/*

# Source ROS 2 setup on container startup
SHELL ["/bin/bash", "-c"]
RUN echo "source /opt/ros/jazzy/setup.bash" >> ~/.bashrc
ENV ROS_DISTRO=jazzy

COPY ./library/ /home/library
WORKDIR /home/
