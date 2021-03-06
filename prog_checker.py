if __name__=='__main__':
  try:
    
    import serial
    import time
    import os
    import sys
        
    ser=serial.Serial('/dev/ttyUSB0',1200)
    
    delay=0.5
    
    start_byte=0x37
    end_byte=0x2B
    dle=0x2F
    null_indicator=0x35

    while(1):
      ser.write(bytearray([start_byte,start_byte,0,255,255,255,end_byte]))
      
      time.sleep(delay)
    
      ser.write(bytearray([start_byte,start_byte,0, null_indicator,null_indicator,null_indicator,end_byte]))
    
      time.sleep(delay)
    
      print('blip')

  except KeyboardInterrupt:
    ser.close()
    try:
      sys.exit(0)
    except SystemExit:
      os._exit(0)
