import serial
import time

ser=serial.Serial('/dev/ttyUSB0',1200)

delay=1

while(1):
  ser.write(bytearray([0x40,0x80,0xC0]))
  
  time.sleep(delay)

  ser.write(bytearray([0]))

  time.sleep(delay)

  print('blip')
