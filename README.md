# Lumen Firmware

Firmware for the **Lumen** LED controller based on ESP8266.

The firmware controls an addressable LED strip and provides a WebSocket interface for communication with the [Lumen mobile application](https://github.com/Malberee/lumen-app). The controller initially creates its own Wi-Fi access point, allowing the application to connect and configure the controller. After connecting the controller to a Wi-Fi network, it switches to station mode and becomes available on the local network.

## Features

- Addressable RGB LED strip control
- Multiple built-in lighting modes
- WebSocket-based communication
- Wi-Fi provisioning through the mobile application
- Automatic switching between access point and station modes
- Gamma-corrected brightness control
- Connection status indication using the LED strip

## Hardware

The firmware currently targets:

- **ESP8266 NodeMCU**
- **WS2812/NeoPixel-compatible addressable LED strip**

The default configuration is:

- 24 LEDs
- LED data pin: GPIO 12
- Access point SSID: `Lumen`
- Access point password: `12345678`

## Configuration

Hardware and access point settings can be changed in [`include/config.h`](https://github.com/Malberee/lumen-firmware/blob/main/include/config.h).

The following definitions should be adjusted when using different hardware or access point credentials:

```cpp
#define NUM_LEDS 24
#define PIN 12
#define AP_SSID "Lumen"
#define AP_PASSWORD "12345678"
```

- `NUM_LEDS` — number of LEDs in the strip
- `PIN` — ESP8266 GPIO pin connected to the LED data line
- `AP_SSID` — Wi-Fi network name created by the controller
- `AP_PASSWORD` — password for the controller's Wi-Fi access point

These values are compiled into the firmware, so the firmware must be rebuilt and flashed after changing them.

## Building and Flashing

The project uses **PlatformIO** with the Arduino framework for ESP8266. The project configuration defines the `nodemcuv2` environment and its required dependencies, including FastLED and WebSockets.

### Requirements

- VS Code
- PlatformIO extension
- ESP8266 NodeMCU
- USB data cable

### Setup

Clone the repository and open it in VS Code with PlatformIO installed:

```bash
git clone https://github.com/Malberee/lumen-firmware.git
cd lumen-firmware
```

Adjust `include/config.h` if necessary, then build and upload the firmware using PlatformIO.

From the project directory:

```bash
pio run
pio run --target upload
```

Alternatively, the **Build** and **Upload** commands can be run directly from the PlatformIO interface in VS Code.

## Using the Firmware

After flashing and powering on, the controller creates the configured Wi-Fi access point.

1. Power on the controller.
2. Connect a phone to the controller's Wi-Fi network.
3. Use the Lumen mobile application to connect to the controller.
4. Configure the Wi-Fi network that the controller should join.
5. After a successful connection, the controller switches to Wi-Fi station mode.
6. The mobile application can then communicate with the controller over the local network using WebSockets.

The LED strip provides visual feedback during connection and configuration.

## License

This project is licensed under the **PolyForm Noncommercial License 1.0.0**.

Commercial use is not permitted under this license. See the [LICENSE](https://github.com/Malberee/lumen-firmware/blob/main/LICENSE) file for the full license terms.
