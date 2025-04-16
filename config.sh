sudo apt update
sudo apt install zip
sudo apt install build-essential

unzip /workspaces/freertos-str/FreeRTOS-LTS.zip

export FREERTOS_PATH=/workspaces/freertos-str/FreeRTOS-LTS

make

cd build

./main