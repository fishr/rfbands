if __name__=='__main__':
  try:
    
    import serial
    import time
    import os
    import sys
        
    ser=serial.Serial('/dev/ttyUSB0',1200)
    
    delay=1
    
    start_byte=55
    end_byte=43
    dle=47
    null_indicator=53
    i=65
    while(1):
      ser.write(bytearray([start_byte,start_byte,0,0x00,i,0,end_byte]))
      ser.write(bytearray([0x20,0x60,0xA0]))
      ser.flush()
      time.sleep(delay)
      i=i-1
      if i==start_byte:
        i=0x52
      elif i==dle:
        i=0x42
      elif i==0:
        ser.write(bytearray([start_byte,start_byte,0,0x00,0x00,255,end_byte]))        
        i=65
        ser.flush()
      #ser.write(bytearray([start_byte,start_byte,0, null_indicator,null_indicator,null_indicator,end_byte]))
      #ser.write(bytearray([0]))
    
      time.sleep(delay)
    
      print('blip')

  except KeyboardInterrupt:
    ser.close()
    try:
      sys.exit(0)
    except SystemExit:
      os._exit(0)
