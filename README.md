# Elderly Supervisor

Embedded system based on Raspberry Pi equiped with a Lepton LWIR module with the intent to supervise elderly people using computer vision algorithms

## Development

### Hardware Set Up

TODO

### Environment Set Up

Default IP:
Default Password:

### Compilation

**Requirements**
    
    * CMake version 3.0 or higher (check with cmake --version)
    * Raspberry Pi cross compiler (see instructions below)

To install the cross compiler you need to clone the raspberry pi toolchain and copy it inside /usr/local:

```bash
cd ~/
git clone https://github.com/raspberrypi/tools

# Use this line in case your system is 32 bits
cp -r /usr/local/gcc-linaro-arm-linux-gnueabihf-raspbian/ /usr/local/

# Use this line in case your system is 64 bits
cp -r /usr/local/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/ /usr/local/
```

Now add the cross compiler directory in your PATH environment variable. You can do this by adding the following line inside the ~/.bashrc file

```bash
# Use this line in case your system is 32 bits
export PATH="/usr/local/gcc-linaro-arm-linux-gnueabihf-raspbian/bin:$PATH"

# Use this line in case your system is 64 bits
export PATH="/usr/local/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin:$PATH"
```
