# Web Flasher Guide for ESPClaw-DevBoard

There are two web flashers in this project:

1. **GitHub Pages Web Serial flasher** (`https://alphingj.github.io/ESPClaw-DevBoard/flasher/`) - flashes the board over USB from any Chrome/Edge browser, no tools installed.
2. **Built-in OTA flasher** on the device (`http://<device-ip>/flash`) - updates firmware over Wi-Fi once ESP-Claw is running.

Both are documented below.

## GitHub Pages Flasher (Web Serial)

### Prerequisites

1. Chrome 89+ or Edge 89+ (Web Serial API)
2. CP2102 VCP driver installed (or CH340 driver for clone boards)
3. ESP32-DevKitC connected via USB

### Steps

1. Open **https://alphingj.github.io/ESPClaw-DevBoard/flasher/**
2. **Step 1**: Pick a firmware from the release list, or upload your own `.bin`.
   - Released firmware comes as an esp-claw package (`.tar.gz`, all partitions) or as a merged full-flash image - either flashes a fresh board completely.
   - Custom uploads: choose *full flash* (0x0, must contain bootloader) or *app only* (0x20000, update over an existing install).
3. **Step 2**: Click *Connect to ESP32*, select the CP2102/CH340 port. Chip and flash size are shown after connecting.
4. **Step 3**: Click *Start Flashing*. Progress and logs are shown; the flash is read-back verified and the device reboots automatically.

### Getting firmware into Releases

Firmware is built and published by the **Release Firmware** workflow. Push a tag to publish:

```bash
git tag v1.0.0 && git push origin v1.0.0
```

The workflow builds `edge_agent` (with this board configuration) against `espressif/esp-claw` in the `espressif/idf:release-v5.5` container, then attaches these assets to the release:

| Asset | Purpose |
|-------|---------|
| `esp32_devkitc__uart_console.tar.gz` | esp-claw package: flasher_args.json + every partition image at its exact offset (recommended) |
| `edge_agent-esp32_devkitc-fullflash.bin` | Merged whole-flash image, flash at offset 0x0 |
| `edge_agent.bin` | Raw application image only |

You can also run the workflow manually (Actions tab) with custom inputs (esp-claw ref, board, target, IDF image).

## Built-in OTA Flasher (on-device)

ESP-Claw includes a built-in web flasher that allows you to update firmware over-the-air (OTA) via a web interface.
This section explains how to access and use the web flasher on your ESP32-DevKitC board running ESP-Claw.

### Prerequisites

1. ESP32-DevKitC with ESP-Claw firmware flashed (using the board configuration from this repository)
2. Wi-Fi connection established (the device must be connected to your network)
3. Web browser on a device connected to the same network as the ESP32

## Finding Your Device's IP Address

After flashing and running the ESP-Claw firmware, the device will print its IP address to the serial console.
You can find it by:

### Method 1: Serial Monitor
- Connect to your ESP32 via USB/UART (e.g., idf.py -p /dev/ttyUSB0 monitor)
- Look for a line like: IP address: 192.168.1.100

### Method 2: Router Admin Page
- Log into your router's admin interface
- Look for connected devices and find the one with hostname esp-claw or similar

### Method 3: Network Scanning Tools
- Use nmap or arp -a to find devices on your network
- Example: nmap -sn 192.168.1.0/24

## Accessing the Web Flasher

Once you have the IP address (e.g., 192.168.1.100), open a web browser and navigate to:

http://192.168.1.100/flash

You should see the ESP-Claw web flasher interface.

## Using the Web Flasher Interface

The web flasher provides a simple interface to upload and flash new firmware binaries.

### Steps to Flash New Firmware:

1. Prepare the firmware binary:
   - Build your ESP-Claw project: idf.py build
   - The binary will be at: build/edge_agent.bin
   - Ensure you have the correct binary for your board (ESP32-DevKitC)

2. Upload the binary:
   - Click the Choose File button
   - Select build/edge_agent.bin
   - Click Start OTA Update

3. Wait for completion:
   - The progress bar will show the upload and flashing status
   - Do not power off the device during this process
   - The device will automatically reboot after flashing

4. Verify:
   - After reboot, check the serial monitor for the new firmware version
   - Reconnect to the web flasher at the same IP address (or new IP if DHCP changed)

## Important Notes

### Network Requirements
- The ESP32 and your computer must be on the same local network
- The web flasher is not accessible over the internet for security reasons
- Ensure no firewall is blocking port 80 (HTTP) on the ESP32

### Security Considerations
- The web flasher does not require authentication by default
- For production use, consider:
  - Using a secure network
  - Disabling the web flasher in production builds (remove CONFIG_WEB_FLASHER_ENABLED if available)
  - Implementing your own authentication layer

## Troubleshooting

| Issue | Solution |
|-------|----------|
| Cannot connect to http://<IP>/flash | 1. Verify IP is correct<br>2. Check device is connected to Wi-Fi<br>3. Ensure computer is on same network<br>4. Try pinging the IP: ping <IP> |
| Upload fails or times out | 1. Check Wi-Fi signal strength<br>2. Reduce network traffic<br>3. Try a binary with smaller size (optimize build)<br>4. Increase timeout in source code if needed |
| Device doesn't reboot after flash | 1. Power cycle the device<br>2. Check serial monitor for errors<br>3. Ensure you flashed the correct binary for ESP32 |
| Web interface shows error | 1. Verify you're using edge_agent.bin (not .elf or .map)<br>2. Check binary was built for esp32 target<br>3. Ensure sufficient free space on OTA partition |

## Alternative: Serial Flashing

If web flashing fails, you can always use serial flashing:

idf.py -p /dev/ttyUSB0 flash monitor

This is more reliable for initial setup and recovery.

## Related Documentation

- Main README - Board overview and setup
- GPIO Mapping - Pinout reference
- Usage Examples - Lua scripts and API usage
- ESP-Claw Documentation - Official framework docs

Flash your ESP32-DevKitC with confidence using the built-in web flasher!
