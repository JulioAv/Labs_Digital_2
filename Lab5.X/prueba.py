import serial
ser = serial.Serial(port = "COM3",baudrate = 9600, timeout = 1)
while 1:
    val1 = ser.read()
    print(val1)
    val2 = int(input())
    ser.write(chr(val2).encode('ascii'))

