set up
---
## Set Up in command-line tools
To build, configure, and flash ESP32 code without VSCode or any IDE,
 you can use the ESP-IDF command-line tools.
 Here’s a complete guide using terminal only.
### ✅ 1. Install ESP-IDF
Follow the official instructions for your OS:
* Linux/macOS (Terminal):
	```
	mkdir esp
	git clone --recursive https://github.com/espressif/esp-idf.git
	cd esp-idf
	./install.sh
	```
* Windows (PowerShell):
	```
	git clone --recursive https://github.com/espressif/esp-idf.git
	cd esp-idf
	.\install.ps1
	```
### ✅ 2. Load Your Project
- Download and unzip your project:
	```
	unzip esp32LedClock.zip
	cd esp32LedClock
	```
### ✅ 3. Set Up the Environment
Before running any idf.py commands, source the environment script:
* Linux/macOS:
	```
	. $HOME/esp/esp-idf/export.sh
	```
* Windows (PowerShell):
	```
	. $env:USERPROFILE\esp\esp-idf\export.ps1
	```
### ✅ 4. Open MenuConfig to Update Wi-Fi or Chime Options
**`idf.py menuconfig`**

You will see a terminal-based menu (like make menuconfig):
* Navigate with arrows
* to `Component config`, scroll below to `ESP32 LED CLOCK Configuration`
* Press Enter to select
* Press Esc twice to exit and save

Update:
* Wi-Fi SSID
* Wi-Fi Password
* Chime Mode (ALL, HOURLY_ONLY, NOON_ONLY)
* Blink Durations

### ✅ 5. Build the Project
**`idf.py build`**

### ✅ 6. Flash to ESP32
* Plug in your ESP32 and run:
	```
	idf.py -p /dev/ttyUSB0 flash monitor
	```
* Replace `/dev/ttyUSB0` with the correct port (use `ls /dev/ttyUSB*`
 on Linux or check Device Manager on Windows).
* You can also auto-detect:
	```
	idf.py flash monitor
	```
### ✅ 7. Done!
* You’re now running the firmware with updated settings.
* The monitor will show logs and allow you to press `Ctrl+]` to exit.

---
## Set up thru Visual Studio Code (VSCode)
Extensions
- ESP-IDF extension > `v5.3.3` (currently the latest version)
- The **ESP-IDF:Explorer** should be shown at the side bar

Do a test first
- Use Exmaple > `scan` to test ESP32
- ESP-IDF:Explorer
	- Select Port to Use: > `/dev/ttyUSB0`
	- Build Project
	- Flask Device > `UART`
	- Monitor Device

### menuconfig
To update `Wifi_ssid` aand `wifi_pass`
- ESP-IDF:Explorer
	- SDK Configuration Editor (menuconfig)

---
