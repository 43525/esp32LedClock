ESP32 LED Clock - Setup Guide
---

## Setup Using Command-Line Tools
To build, configure, and flash the ESP32 firmware without using VSCode or any IDE, you can rely solely on the ESP-IDF command-line tools. Below is a complete step-by-step guide using only the terminal.

### ✅ 1. Install ESP-IDF
Follow the official instructions based on your operating system:
- **Linux/macOS (Terminal):**
    ```bash
    mkdir esp
    git clone --recursive https://github.com/espressif/esp-idf.git
    cd esp-idf
    ./install.sh
    ```
- **Windows (PowerShell):**
    ```powershell
    git clone --recursive https://github.com/espressif/esp-idf.git
    cd esp-idf
    .\install.ps1
    ```

### ✅ 2. Load Your Project
Download and unzip your project:
```bash
unzip esp32LedClock.zip
cd esp32LedClock
```

### ✅ 3. Set Up the Environment
Before running any `idf.py` commands, source the environment script:
- **Linux/macOS:**
    ```bash
    . $HOME/esp/esp-idf/export.sh
    ```
- **Windows (PowerShell):**
    ```powershell
    . $env:USERPROFILE\esp\esp-idf\export.ps1
    ```

### ✅ 4. Configure with MenuConfig
Use `idf.py menuconfig` to update settings:
```bash
idf.py menuconfig
```

You will see a terminal-based configuration menu. Navigate using the arrow keys:
- Go to **Component config** → **ESP32 LED CLOCK Configuration**
- Update the following:
  - Wi-Fi SSID
  - Wi-Fi Password
  - Chime Mode (ALL, HOURLY_ONLY, NOON_ONLY)
  - Blink Durations
- Press `Esc` twice to exit and save changes.

### ✅ 5. Build the Project
```bash
idf.py build
```

### ✅ 6. Flash to ESP32
- Connect your ESP32 and run:
	```bash
	idf.py -p /dev/ttyUSB0 flash monitor
	```
- Replace `/dev/ttyUSB0` with your actual port (use `ls /dev/ttyUSB*` on Linux or check Device Manager on Windows).
- Or use auto-detect:
	```bash
	idf.py flash monitor
	```

### ✅ 7. Done!
You're now running the firmware with your custom settings.  
The monitor will display logs. Press `Ctrl+]` to exit.

---
---
## Setup Using Visual Studio Code (VSCode)

### Extensions Required
- ESP-IDF Extension `v5.3.3` (latest at the time of writing)
- Ensure **ESP-IDF: Explorer** appears in the sidebar

### Test the Connection
Use the built-in `scan` example to test communication with your ESP32.

Steps:
1. Open **ESP-IDF: Explorer**
2. Select the correct port (e.g., `/dev/ttyUSB0`)
3. Build the project
4. Flash the device using `UART`
5. Monitor output from the device

---
### Update Configuration with MenuConfig
To update Wi-Fi SSID and password:
- Open **ESP-IDF: Explorer**
- Go to **SDK Configuration Editor (menuconfig)**

Make changes under **ESP32 LED CLOCK Configuration**.

---
