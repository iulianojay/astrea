### Building and running your application

When you're ready, start your application by running:
`docker compose up --build`.

### Deploying your application to the cloud

First, build your image, e.g.: `docker build -t myapp .`.
If your cloud uses a different CPU architecture than your development
machine (e.g., you are on a Mac M1 and your cloud provider is amd64),
you'll want to build the image for that platform, e.g.:
`docker build --platform=linux/amd64 -t myapp .`.

Then, push it to your registry, e.g. `docker push myregistry.com/myapp`.

Consult Docker's [getting started](https://docs.docker.com/go/get-started-sharing/)
docs for more detail on building and pushing.


### My Notes

list images:
    > docker images
list running containers:
    > docker ps

start docker image: 
    > docker run -it <tag or hash> bash
start image with astrea mounted:    
    > docker run -it -v /home/jay/projects/astrea:/home/appuser/astrea astrea-image bash
image with astrea and open-source files mounted:
    > docker run -it \
        -v ~/projects/astrea/cmake:/home/appuser/astrea/cmake \
        -v ~/projects/astrea/data:/home/appuser/astrea/data \
        -v ~/projects/astrea/extern:/home/appuser/astrea/extern \
        -v ~/projects/astrea/scripts:/home/appuser/astrea/scripts \
        -v ~/projects/astrea/astrea:/home/appuser/astrea/astrea \
        -v ~/projects/astrea/CMakeLists.txt:/home/appuser/astrea/CMakeLists.txt \
        -v ~/projects/astrea/conanfile.txt:/home/appuser/astrea/conanfile.txt \
        -v ~/projects/astrea/Makefile:/home/appuser/astrea/Makefile \
        -v ~/open-source:/home/appuser/open-source \
        -v ~/.conan2:/home/appuser/.conan2 \
        astrea:latest bash

new: 
    > docker build -t jayiuliano/astrea:latest -f ./docker/Dockerfile ~
    > docker image push jayiuliano/astrea:latest

new: 
    > docker build -t jayiuliano/astrea:latest -f ./docker/Dockerfile .
    > docker image push jayiuliano/astrea:latest