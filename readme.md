Esp32 LED Clock
---
Noted that this code was created via ChatGPT for IOS 1.2024.347, iphone 8

This code is for an ESP32-based device that connects to Wi-Fi, obtains the current time,
and blinks an LED based on the time of day. It supports deep sleep to save power between operations.  
The device will blink the LED once every 15 minutes, and on the hour it will blink a number of times
corresponding to the hour (12 times at noon, and 1-11 times for other hours).  
The device will also blink the LED at a slower rate for the noon chime.  
The device uses the ESP-IDF framework and requires configuration for Wi-Fi credentials and blink delays.  
The device will wake up every 60 seconds to check the time and blink the LED accordingly.  

Software:
* VSCode, extension ESP-IDF, esp-idf-v5.3.3
* OS used: Debian GNU/Linux 12 (bookworm)
    ``` terminal
    pi@raspberrypi:~/esp $ cat /etc/os-release
    PRETTY_NAME="Debian GNU/Linux 12 (bookworm)"
    NAME="Debian GNU/Linux"
    VERSION_ID="12"
    VERSION="12 (bookworm)"
    VERSION_CODENAME=bookworm
    ID=debian
    HOME_URL="https://www.debian.org/"
    SUPPORT_URL="https://www.debian.org/support"
    BUG_REPORT_URL="https://bugs.debian.org/"
    pi@raspberrypi:~/esp $ cat /proc/version
    Linux version 6.12.25+rpt-rpi-v8 (serge@raspberrypi.com)
        (aarch64-linux-gnu-gcc-12 (Debian 12.2.0-14) 12.2.0, GNU ld
        (GNU Binutils for Debian) 2.40) #1 SMP PREEMPT Debian 1:6.12.25-1+rpt1 (2025-04-30)
    pi@raspberrypi:~/esp $ 
    ```
*  :point_right:  Before compile and flash, need to update Wifi_ssid
	- update in VSCode > ESP-IDF EXPLORER > SDK Configuration Editor (menuconfig)

### ESP32 project using ESP-IDF that:
1. Connects to Wi-Fi and syncs time with NTP.
2. Checks the current time and:
    * Blinks once at every quarter-hour (00, 15, 30, 45).
    * Blinks 12 times at 12:00:00 PM.
3. Goes into deep sleep to save battery, waking up once per minute to check again.

### 1. Wi-Fi + SNTP + Deep Sleep Example
* Using GPIO2 for the LED.
* `sdkconfig` with Wi-Fi and NVS enabled.
* `idf.py menuconfig` is set to the correct Wi-Fi SSID/PASS, or you hardcode them.

### 2. Notes
* First boot: Connects to Wi-Fi and syncs time.
* On wake: Uses the RTC clock to avoid re-syncing NTP every time.
* If battery-powered: you can use external RTC or backup battery for more accurate long-term timekeeping.
* Can customize sleep time to shorter intervals (e.g. every 15s) to increase accuracy.

### 3. Example Durations

| Event        | Blink Count | Duration per Blink | Total Time |
| ------------ | ----------- | ------------------ | ---------- |
| 3 AM Hourly  | 3           | 100 ms             | \~0.6 sec  |
| 12 PM (Noon) | 12          | 200 ms             | \~4.8 sec  |

---
---