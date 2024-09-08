# qt-practice

## Build a docker image for compiling Qt
The deploy folder is copied from [QGC v4.4](https://github.com/mavlink/qgroundcontrol/tree/Stable_V4.4/deploy).
```sh
docker build --file ./deploy/docker/Dockerfile-build-linux -t qt-linux-docker:5.15.2 .
```

## Compile using the docker image
```sh
docker run --rm -v ${PWD}:/project/source -v ${PWD}/build:/project/build qt-linux-docker:5.15.2
```

## Demo
https://github.com/user-attachments/assets/5bf1b921-7e6e-4324-ac84-84f219a19de9

