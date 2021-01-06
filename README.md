# Focus Box

## Introduction

This is an IOT project developed for the Advanced Human-Interface Design subject, under Hochschule Rhein-Waal's Usability Engineering M. Sc. program.

## Hardware Components

- AZDelivery NodeMCU Lua Lolin V3 (ESP8266)

## Software Libraries

- Firebase-ESP8266 (https://github.com/mobizt/Firebase-ESP8266)
- VueJS (https://vuejs.org/)
- Vuefire (https://vuefire.vuejs.org/)

## Getting Started in Linux

This guide was written to work on [ElementaryOS](https://elementary.io/) using VSCode, but should work on any Ubuntu or Debian-based distribution.

### 1. Install Arduino IDE

We need the Arduino IDE to be installed in order to configure VSCode's Arduino extension. We will not be running it directly.

Go to the [Arduino Website](https://www.arduino.cc/en/software) and download the IDE. Extract it, and run `install.sh` after extracting it. The IDE will be installed.

Copy the location where you extracted and installed the Arduino IDE in. We will need it for configuring VSCode's Arduino extension in step 3.

### 2. Install NVM and NodeJS

We need NodeJS to run the web client. In Terminal:

```bash
$ curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.37.2/install.sh | bash
$ nvm install --lts
```

Make sure you installed it correctly by running `npm -v` and `node -v`.

### 3. Install Arduino Extension for VSCode

Search for "arduino" in VSCode's extensions. Find Microsoft's official extension and install it.

After installation, we have to tell VSCode where the Arduino IDE is located. Go to the extension's settings, find "Arduino: Path" and paste the location where you extracted and installed the Arduino IDE in on step 1.

### 4. Install and configure your ESP8266 Board

#### Installation

Still in VSCode's Arduino extension settings, find "Arduino: Additional Urls". Click on "Edit in settings.json". Edit the `arduino.additionalUrls` property. The extension expects a string with URLs separated by a comma (,). Add the following URL to the string:

```
http://arduino.esp8266.com/stable/package_esp8266com_index.json
```

Save `settings.json` and close it.

Open the Arduino extension Board Manager window. It should update its list using the new URL you just added to `settings.json`.

Search for "esp8266" on the search field. Install the board named "esp8266" by ESP8266 Community.

#### Configuration

First, connect your ESP8266 board to the computer if you haven't already.

On VSCode's bottom bar, click on "Select Board Type". On this window, select the following options:

- **Selected Board:**  NodeMCU 1.0 (ESP-12E Module)
- **CPU Frequency:** 80MHz
-  **Flash Size:** 4MB (FS:3MB OTA:~512KB)

We will now select the serial port to where our board is connected. Linux creates a folder for this. On your Terminal, type `ls /dev/tty*` and look for a folder that includes either `USB*` or `ACM*`, where "*" is a number (i.e. USB0). That's the serial port name you should select in VSCode. Go to VSCode's bottom bar, click on "Select Serial Port" and select the corresponding folder you found on your Terminal.

Just to make sure we get no errors, we have to give our user permission to modify this folder, or else we will not be able to upload sketches to our board. To do that, run `chmod` like so:

```bash
$ sudo chmod a+rw /dev/ttyUSB0
```

Replace `/dev/ttyUSB0` with the folder you selected when configuring the serial port.

### 5. Install Library Dependencies

In the project's root folder, cd into `webclient` and run `npm install` to install the web client's dependencies.

Go to the Arduino extension's Library Manager on VSCode and install the following libraries:

- **Firebase ESP8266 Client** _by Mobizt_

### Bonus: Configure C IntelliSense for Libraries

TODO