
## Dependencies

### SPI

SPI dev support is required for RF24.
For OrangePI enable it with armbian-config or editing /boot/armbianEnv.txt

### RF24

git clone https://github.com/nRF24/RF24
cd RF24
make
sudo make install

### mosquitto

sudo apt install libmosquittopp-dev

