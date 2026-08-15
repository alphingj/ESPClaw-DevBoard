# ESP32-DevKitC (Classic ESP32) - Community Board

## Hardware Overview

| Feature       | Specification                              |
|---------------|--------------------------------------------|
| Chip          | ESP32 (Classic, single/dual core, Xtensa)  |
| Flash         | 4 MB QIO @ 40 MHz                          |
| PSRAM         | None (external PSRAM not supported on classic ESP32) |
| USB-to-UART   | CP2102 (Silicon Labs)                      |
| Console       | UART0 (GPIO1 TX, GPIO3 RX) via CP2102      |
| User LED      | Blue LED on GPIO 2 (active low)            |
| BOOT Button   | GPIO 0 (active low)                        |
| EN Button     | Reset (not a GPIO)                         |

Upstream board page: [ESP32-DevKitC](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/hw-reference/esp32/get-started-devkitc.html)

## GPIO Mapping

| Function            | GPIO | Notes                                    |
|---------------------|------|------------------------------------------|
| UART0 TX (Console)  | 1    | Connected to CP2102                      |
| UART0 RX (Console)  | 3    | Connected to CP2102                      |
| I2C SDA             | 21   | Default I2C0 pins                        |
| I2C SCL             | 22   | Default I2C0 pins                        |
| SPI MOSI            | 23   | VSPI default                             |
| SPI MISO            | 19   | VSPI default                             |
| SPI CLK             | 18   | VSPI default                             |
| SPI CS              | 5    | VSPI default (not used by default)       |
| User LED (Blue)     | 2    | Active low                               |
| BOOT Button         | 0    | Active low, also strapping pin           |
| EN Button           | -    | Reset pin, not a GPIO                    |

## Important Notes

### Classic ESP32 Limitations

The classic ESP32 (non-S3/P4/C5/S31) has several limitations compared to newer chips:

1. **No PSRAM support** - External PSRAM is not supported on classic ESP32
2. **No USB OTG** - Uses UART0 via CP2102 for console and flashing
3. **No native USB** - Cannot use USB Serial/JTAG or USB Host/Device
4. **No camera interface** - No DVP/CSI camera support
5. **Limited I2S** - Basic I2S support only
6. **Single/dual core** - Xtensa LX6 cores (not RISC-V)
7. **4 MB Flash max** - Typically 4 MB flash on DevKitC

### Strapping Pins

GPIO 0 (BOOT button) is a strapping pin. When held LOW during reset, the chip enters download mode.
The BOOT button on DevKitC pulls GPIO 0 low when pressed.

### Console

The console uses UART0 (GPIO1/3) via the CP2102 USB-to-UART bridge. No special drivers needed on most OSes.

## Build & Flash

### Option 1: Web Serial Flasher (Easiest - No Tools Required!)
**Flash directly from your browser:** https://alphingj.github.io/ESPClaw-DevBoard/flasher/

1. Open the link in **Chrome 89+** or **Edge 89+**
2. Select firmware from GitHub Releases (or upload your own `.bin`)
3. Click "Connect to ESP32" → Select your CP2102 device
4. Click "Start Flashing" → Wait for completion
5. Done! No ESP-IDF or command line needed.

### Option 2: Command Line (Traditional)

```bash
cd application/edge_agent

# Generate board-manager glue. Always rerun this after editing the YAML
# files under this directory, otherwise the stale generated C code under
# components/gen_bmgr_codes/ is compiled instead.
idf.py bmgr -c ./boards -b esp32_devkitc

# Build and flash
idf.py build
idf.py -p /dev/ttyUSB0 flash monitor    # Windows: -p COM3
```

The ESP32-DevKitC enters download mode automatically on most hosts; if the
flash hangs at "Connecting...", hold **BOOT**, tap **EN**, release
**BOOT**, then retry.

## Partition Table

Uses `partitions_4MB.csv` (auto-selected from `CONFIG_ESPTOOLPY_FLASHSIZE_4MB=y`
by `tools/cmake/flash_partition_defaults.cmake`). The 4 MB layout reserves a
read-only system FAT image and a writable data FAT image on flash.

## Files

| File                          | Description                                              |
|-------------------------------|----------------------------------------------------------|
| `board_info.yaml`             | Board identity (chip, manufacturer, description)         |
| `board_peripherals.yaml`      | I2C0, UART0, SPI2 pin and bus configuration              |
| `board_devices.yaml`          | LED, BOOT button device list                             |
| `sdkconfig.defaults.board`    | Flash/PSRAM/console defaults for classic ESP32           |
| `setup_device.c`              | Minimal board initialization                             |

## Supported ESP-Claw Features

Due to hardware limitations of the classic ESP32, the following features are **NOT** available:

- Camera / Vision modules
- Audio (microphone/speaker) modules
- USB Host/Device (MCP, UVC, UAC)
- LVGL System UI (insufficient RAM)
- PSRAM-dependent features

The following features **ARE** available:

- GPIO control (LED, buttons)
- LEDC PWM
- I2C sensors
- SPI devices
- WiFi / BLE
- Basic Lua modules (GPIO, LEDC, System, Delay, JSON, Button, Storage)
- HTTP Server
- Event Publisher
- Skill Manager
- MCP Client/Server (over WiFi)
- LLM Agent (claw_core) - text only

## Adding External Hardware

You can extend this board by adding external components via the available GPIOs:

- **I2C Sensors**: Connect to GPIO21 (SDA) / GPIO22 (SCL)
- **SPI Displays**: Use VSPI (GPIO18/19/23) or HSPI (GPIO12/13/14/15)
- **UART Devices**: Use UART1 (GPIO9/10) or UART2 (GPIO16/17)
- **ADC**: GPIO32-39 (ADC1 channels 0-7) - Note: ADC2 cannot be used when WiFi is active
- **DAC**: GPIO25, GPIO26 (8-bit DAC)

To add a device, edit `board_devices.yaml` and `board_peripherals.yaml`, then re-run `idf.py bmgr`.