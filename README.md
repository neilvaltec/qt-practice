# qt-practice

## Build a docker image for compiling Qt
```sh
docker build --file ./deploy/docker/Dockerfile-build-linux -t qt-linux-docker:5.15.2 .
```

## Compile using the docker image
```sh
docker run --rm -v ${PWD}:/project/source -v ${PWD}/build:/project/build qt-linux-docker:5.15.2
```
