# Elderly Supervisor

Embedded system based on Raspberry Pi equiped with a Lepton LWIR module the intent to supervise elderly people using computer vision algorithms


## Development

### Hardware Set Up

TODO

### Environment Set Up

TODO

### Compilation

This chapter aims to explain the tools needed to compile the application.

First you'll need a cross compiler, so clone the raspberry toolchain:

```bash
cd ~/
git clone https://github.com/raspberry/tools
```

Now add the cross compiler directory in your PATH environment variable. You can do this by adding the following line inside the ~/.bashrc file

```bash
# Use this line in case your system is 32 bits
export PATH="/home/<USER_NAME>/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin:$PATH"

# Use this line in case your system is 64 bits
export PATH="/home/<USER_NAME>/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin:$PATH"
```
