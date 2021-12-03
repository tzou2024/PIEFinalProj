# Importing Libraries
import serial
import time
arduino = serial.Serial(port='COM10', baudrate=9600, timeout=.1)
def write_read(x):
    arduino.write(bytes(x, 'utf-8'))
    time.sleep(0.1)
    data = arduino.readline()
    return data
while True:
    num = input("Enter: ") # Taking input from user
    value = write_read(num + "\0")
    print(value)
