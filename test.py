# Send some SPI commands to test the Arduino sketch

from spi import SPI
import time

spi = SPI()

commands = ["red", "green", "blue", "off"]

for command in commands:
    print("Sending " + command)
    spi.write(command + "\n");
    time.sleep(2)
