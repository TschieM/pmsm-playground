# pmsm-playground

A cpp based project to run PMSM simulation with a servo system

## How to build
In Mac M1 platform
```
docker build --build-arg TARGETARCH=arm64 -t <image-name> .
docker run -it <image-name>
```

In other unix amd64 platform
```
docker build --build-arg TARGETARCH=amd64 -t <image-name> .
docker run -it <image-name>
```
