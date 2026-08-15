# Web Flasher Guide for ESPClaw-DevBoard

ESP-Claw includes a built-in web flasher that allows you to update firmware over-the-air (OTA) via a web interface.
This guide explains how to access and use the web flasher on your ESP32-DevKitC board running ESP-Claw.

## Prerequisites

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
