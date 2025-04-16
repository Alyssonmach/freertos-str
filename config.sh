sudo apt update
sudo apt install zip
sudo apt install build-essential

unzip FreeRTOS.zip

export FREERTOS_PATH=~/freertos-str/FreeRTOS-LTS

make
