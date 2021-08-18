# Lab5 Adafruit_IO
# Universidad del Valle de Guatemala
# IE3027 - Electrónica Digital 2
# Julio Avila

# Adafruit IO
# https://io.adafruit.com/

# if Module not Found. Open Terminal/CMD and execute:
# pip3 install Adafruit_IO

from Adafruit_IO import Client, RequestError, Feed
import serial
import time

ser = serial.Serial(port = "COM3",baudrate = 9600, timeout = 1)
#ser.open()

ADAFRUIT_IO_KEY = "aio_iOIe13gm8JHkeur3VzAdOsXrMI8q"
ADAFRUIT_IO_USERNAME = "JulioAv"
aio = Client(ADAFRUIT_IO_USERNAME, ADAFRUIT_IO_KEY)

#while True:
digital_feed3 = aio.feeds('boton')
    #if aio.receive(digital_feed3.key) == 1:
Valor = ser.read();
digital_feed1 = aio.feeds('contador')
aio.send_data(digital_feed1.key, int(Valor))
digital_feed2 = aio.feeds('barra')
valor2 = aio.receive(digital_feed2.key)
var3 = str(int(valor2.value))
ser.write(var3.encode('ascii'))
        
    

