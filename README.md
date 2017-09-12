# Elderly Supervisor

Embedded system based on Raspberry Pi equiped with a Lepton LWIR module with the intent to supervise elderly people using computer vision algorithms

## Development

### Hardware Set Up

TODO

### Environment Set Up

    * The host 'pia' needs to be defined in the file /etc/hosts in order to run the unit tests inside the Raspberry Pi

You can copy a ssh key to your raspberry so you don't have to type the password every time, but this is optional

```bash
# If you don't have a ssh key yet (check ~/.ssh/), create one. Jus hit enter in all the options
ssh-keygen

# Copy the key to your raspberry. The host 'pia' should be defined
ssh-copykey pi@pia
```

### Compilation

#### Requirements
    
    * CMake version 3.5 or higher (check with cmake --version)
    * Install required packages for [curl](https://github.com/curl/curl/blob/master/GIT-INFO)
    * Raspberry Pi cross compiler (see 'Instructions' below)

### Optional

    * Install required packages for [kcov](https://github.com/SimonKagstrom/kcov/blob/master/INSTALL.md)

#### Instructions
To install the cross compiler you need to clone the raspberry pi toolchain and copy it inside /usr/local:

```bash
cd ~/
git clone https://github.com/raspberrypi/tools

# Use this line in case your system is 32 bits
cp -r ~/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/ /usr/local/

# Use this line in case your system is 64 bits
cp -r tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/ /usr/local/
```

Now add the cross compiler directory in your PATH environment variable. You can do this by adding the following line inside the ~/.bashrc file

```bash
# Use this line in case your system is 32 bits
export PATH="/usr/local/gcc-linaro-arm-linux-gnueabihf-raspbian/bin:$PATH"

# Use this line in case your system is 64 bits
export PATH="/usr/local/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin:$PATH"
```
