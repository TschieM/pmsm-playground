# PMSM Playground

A cpp based project to run PMSM simulation with a servo system. It is intended for helping understand the dynamics of the PMSM and testing of its control algorithm(e.g. FOC) as well as implementation. 

An overview of the project is described [here](doc/Overview.md).

Other related documents, including the dynamic model of the PMSM, software architetucre of the firmware design, etc. can be found in the [doc folder](doc/).

## How to Use
On Mac M1 platform
```
docker build --build-arg TARGETARCH=arm64 -t <image-name> .
docker run -it <image-name>
```

On other amd64 based unix platform
```
docker build --build-arg TARGETARCH=amd64 -t <image-name> .
docker run -it <image-name>
```

## How to Contribute
