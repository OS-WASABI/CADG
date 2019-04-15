# Travis Test - CADG SOAP Server Runtime

If the base image needs to be adjusted, this is the Dockerfile that generates it. Leave off `my-tag` to update the latest version for production.

Build simply with 
```
docker build -t cadg-soap-env:my-tag .
```

To push image to DockerHub
```
$ docker tag cadg-soap-env:my-tag oswasabi/cadg-soap-env:my-tag

$ docker push oswasabi/cadg-soap-env:my-tag
```