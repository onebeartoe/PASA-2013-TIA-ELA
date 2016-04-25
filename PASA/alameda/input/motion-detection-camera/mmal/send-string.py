import serial;

ser = serial.Serial('/dev/ttyACM0', 9600);

import time
time.sleep(2.0);

ser.open();

ser.write('1234567898765432\n');
ser.write('1');

ser.close();

