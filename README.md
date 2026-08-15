# ESPClaw-DevBoard

ESP32-DevKitC (Classic ESP32) board support for ESP-Claw.

This repository provides board configuration files for the classic ESP32-DevKitC development board with CP2102 USB-to-UART bridge, enabling it to run ESP-Claw AI agent framework.

## Overview

The ESP32-DevKitC is the classic ESP32 development board featuring:
- ESP32 (single/dual core, Xtensa LX6 processor)
- 4MB Flash (no external PSRAM)
- CP2102 USB-to-UART bridge for serial communication
- Built-in components: Blue LED (GPIO2), BOOT button (GPIO0)

## Features Supported

Due to hardware limitations of the classic ESP32, certain features are not available:

| Feature | Status | Notes |
|---------|--------|-------|
| Wi-Fi / BLE | Supported | Full wireless connectivity |
| LLM API Calls | Supported | Via HTTPS to OpenAI, Anthropic, etc. |
| Telegram / QQ / Feishu / WeChat | Supported | HTTP-based IM platforms |
| Local LLM Execution | Not supported | Uses external APIs only |
| Camera / Vision | Not supported | Requires PSRAM (not available) |
| Audio (Mic/Speaker) | Not supported | Requires PSRAM or external codec |
| LVGL System UI | Not supported | Insufficient RAM (~30KB available) |
| USB Host/Device | Not supported | No native USB on classic ESP32 |

## Installation

### Prerequisites
- ESP-Claw repository cloned locally
- ESP-IDF v5.x installed and configured

### Steps

1. Clone this repository:
   git clone https://github.com/yourusername/ESPClaw-DevBoard.git

2. Copy the board configuration to your esp-claw installation:
   cp -r ESPClaw-DevBoard/board/ esp-claw/application/edge_agent/boards/community/esp32_devkitc/

3. Set the IDF target (if not using sdkconfig defaults):
   cd esp-claw/application/edge_agent
   idf.py set-target esp32

4. Build and flash:
   # Generate board-manager files
   idf.py bmgr -c ./boards -b esp32_devkitc
   
   # Build
   idf.py build
   
   # Flash (replace /dev/ttyUSB0 with your port)
   idf.py -p /dev/ttyUSB0 flash monitor

## Board Files

This repository contains:
- board_info.yaml - Board identification (chip, manufacturer, description)
- board_peripherals.yaml - I2C, UART, SPI pin configurations
- board_devices.yaml - Available devices (LED, BOOT button)
- sdkconfig.defaults.board - Default SDK configuration
- setup_device.c - Minimal board initialization code
- README.md - This documentation
- partitions_4MB.csv - 4MB flash partition table

## GPIO Mapping

| Function | GPIO | Notes |
|----------|------|-------|
| UART0 TX (Console) | 1 | Connected to CP2102 |
| UART0 RX (Console) | 3 | Connected to CP2102 |
| I2C SDA | 21 | Default I2C0 pins |
| I2C SCL | 22 | Default I2C0 pins |
| SPI MOSI | 23 | VSPI default |
| SPI MISO | 19 | VSPI default |
| SPI CLK | 18 | VSPI default |
| SPI CS | 5 | VSPI default (available) |
| User LED (Blue) | 2 | Active low |
| BOOT Button | 0 | Active low, strapping pin |
| EN Button | - | Reset pin (not a GPIO) |

## Usage Examples

Once flashed, you can use ESP-Claw to:
- Control the built-in LED via Lua or HTTP API
- Read the BOOT button state
- Connect I2C sensors (GPIO21/22)
- Connect SPI displays (VSPI pins)
- Make HTTPS calls to LLM APIs (OpenAI, Anthropic, etc.)
- Use Telegram, QQ, Feishu, or WeChat for messaging
- Run Lua scripts for automation
- Use skills for extended functionality

## Web Flasher (GitHub Pages)

**Flash your ESP32-DevKitC directly from the browser!** 

Visit the hosted web flasher at: **https://YOUR_USERNAME.github.io/ESPClaw-DevBoard/flasher/**

This web-based flasher uses the **Web Serial API** (Chrome/Edge 89+) to flash ESP-Claw firmware directly to your ESP32-DevKitC via USB. No command line tools required!

### Features:
- ✅ Select firmware from GitHub Releases automatically
- ✅ Upload custom `.bin` files
- ✅ Auto-detect CP2102/CH340 USB-to-UART bridges
- ✅ Real-time flash progress with verification
- ✅ Works with classic ESP32 (CP2102) - NOT WebUSB, uses Web Serial API

### Requirements:
- Chrome 89+ or Edge 89+ (Web Serial API)
- CP2102 VCP driver installed on your OS
- ESP32-DevKitC connected via USB

### Alternative: Built-in OTA Flasher
After initial flash via Web Serial, the device runs a built-in OTA flasher accessible at `http://<device-ip>/flash` for future updates over Wi-Fi.


## Important Notes

### Memory Constraints
The classic ESP32 has approximately 30KB of usable RAM after the Wi-Fi stack. This limits:
- Concurrent Lua scripts
- Size of HTTP request/response buffers
- Complexity of skills
- Number of simultaneously active capabilities

### LLM Considerations
While the ESP32 cannot run LLMs locally due to memory constraints, it excels as an edge agent that:
- Collects sensor data via I2C/SPI/GPIO
- Makes decisions based on simple logic or Lua scripts
- Communicates with powerful cloud LLMs for complex reasoning
- Acts on LLM decisions via GPIO/outputs

This follows the traditional edge computing model: simple preprocessing locally, complex reasoning in the cloud.

## References

- ESP-Claw Documentation: https://esp-claw.com/en/
- ESP32-DevKitC Guide: https://docs.espressif.com/projects/esp-idf/en/latest/esp32/hw-reference/esp32/get-started-devkitc.html
- ESP-IDF Programming Guide: https://docs.espressif.com/projects/esp-idf/en/latest/esp32/

## Support

For issues or questions:
1. Check the ESP-Claw documentation
2. Review the ESP-Claw GitHub Issues
3. Ensure your board matches the ESP32-DevKitC specification

---

Created for the ESP-Claw community. Happy hacking! 🦞
