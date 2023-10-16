FROM mcr.microsoft.com/devcontainers/base:bookworm

RUN wget -qO- https://apt.llvm.org/llvm-snapshot.gpg.key | sudo tee /etc/apt/trusted.gpg.d/apt.llvm.org.asc && \
    sudo echo 'deb http://apt.llvm.org/bookworm/ llvm-toolchain-bookworm-16 main' > /etc/apt/sources.list.d/llvm.list && \
    sudo apt update && \
    sudo apt install gdb clangd-16 -y
