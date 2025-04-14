## FreeRTOS Setup (POSIX Port on Ubuntu)

### Requirements

- **FreeRTOS Version:** `FreeRTOSv202210.01-LTS`  
- **Official Site:** [FreeRTOS.org](https://freertos.org/)
- **Linux Distro Tested:** Ubuntu 24.04 LTS

### Installing FreeRTOS

1. **Download FreeRTOS LTS**

   You can download the latest LTS release from the official site:

   [https://github.com/FreeRTOS/FreeRTOS-LTS](https://github.com/FreeRTOS/FreeRTOS-LTS)

   Then extract the archive and place it somewhere accessible, for example:

   ```bash
   mkdir -p ~/FreeRTOSv202210.01-LTS
   tar -xzf FreeRTOSv202210.01-LTS.tar.gz -C ~/FreeRTOSv202210.01-LTS
   ```

2. **Set FreeRTOS Path**

   Add the following line to your `.profile`, `.bashrc`, or `.zshrc`:

   ```bash
   export FREERTOS_PATH=~/FreeRTOSv202210.01-LTS/FreeRTOS-LTS
   ```

   Then source the file or restart your terminal:

   ```bash
   source ~/.profile
   ```

3. **Build Dependencies**

   Ensure you have GCC and pthreads installed:

   ```bash
   sudo apt update
   sudo apt install build-essential
   ```

---
