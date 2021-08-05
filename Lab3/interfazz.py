import serial


serialPort = serial.Serial(port = "COM3", baudrate = "9600", bytesize = 8, timeout = 2, stopbits=serial.STOPBITS_ONE)

Serial_Input = int(input("0 para los pots"))
if Serial_Input == 0:
    write("0")
    x = int(readline())
    print(x)
