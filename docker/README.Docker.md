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
start image with waveguide mounted:    
    > docker run -it -v /home/jay/projects/waveguide:/home/appuser/waveguide waveguide-image bash
image with waveguide and open-source files mounted:
    > docker run -it \
        -v ~/projects/waveguide/cmake:/home/appuser/waveguide/cmake \
        -v ~/projects/waveguide/data:/home/appuser/waveguide/data \
        -v ~/projects/waveguide/extern:/home/appuser/waveguide/extern \
        -v ~/projects/waveguide/scripts:/home/appuser/waveguide/scripts \
        -v ~/projects/waveguide/waveguide:/home/appuser/waveguide/waveguide \
        -v ~/projects/waveguide/CMakeLists.txt:/home/appuser/waveguide/CMakeLists.txt \
        -v ~/projects/waveguide/conanfile.txt:/home/appuser/waveguide/conanfile.txt \
        -v ~/projects/waveguide/Makefile:/home/appuser/waveguide/Makefile \
        -v ~/open-source:/home/appuser/open-source \
        -v ~/.conan2:/home/appuser/.conan2 \
        waveguide:latest bash

new: 
    > docker build -t jayiuliano/waveguide:latest -f ./docker/Dockerfile ~
    >  ~/projects/waveguide >> docker build -t jayiuliano/waveguide:latest -f ./docker/Dockerfile ~