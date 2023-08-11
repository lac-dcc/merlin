# Docker instructions

Building the LLVM project yourself might be a bit troublesome, and take some time. An alternative is using a Docker image that already has the LLVM project compiled inside it.

Notice that this is different from using pre-built binaries: the project is actually compiled in the operating system you get from the image, so you have access to all the libraries you get when you build LLVM! Just be aware of the target architecture of the build. We use x86 as a default, but if your computer uses another architecture you should change the parameter `-DLLVM_TARGETS_TO_BUILD` in the Dockerfile. You can visit [LLVM's website](https://llvm.org/docs/CMake.html#llvm-related-variables) to check all available targets.

Note that, if you are using Linux, you might need root access whenever you run a docker command! Just add "sudo" before every docker command listed below.

# What you need

You need to install Docker on your machine. You can take a look at [Docker's website](https://docs.docker.com/desktop/install/linux-install/) on how to install it.

# Run the Dockerfile

In the docker directory run the code below:

    docker build -t merlin .

The command above takes ~20-30 minutes on a good computer. After executing the command above you can access the container in your machine with the command:

    docker run -it merlin