import serial
import csv
import time

arduino_port = "/dev/ttyUSB0" #serial port of Arduino
baud = 9600 #arduino uno runs at 9600 baud
fileName = "analog-data.csv" #name of the CSV file generated

ser = serial.Serial(arduino_port, baud)
print("Connected to Arduino port:" + arduino_port)
file = open(fileName, "w")
print("Created file")

samples = 30000 #how many samples to collect
print_labels = False #do you want to print out line ids to serial?
line = 0 #start at 0 because our header is 0 (not real data)
sensor_data = [] #store data
start_time = time.time()

try:
    # collect the samples
    while line <= samples:
        current_time = time.strftime("%H:%M:%S", time.gmtime(time.time() - start_time)) # get elapsed time
        getData=ser.readline()
        dataString = getData.decode('iso-8859-1')
        data = dataString.strip()

        readings = data.split(",")
        print(readings)

        sensor_data.append([current_time, readings])
        line += 1
finally:
    # save the data to the CSV file
    with open(fileName, "w") as f:
        writer = csv.writer(f)
        writer.writerows(sensor_data)

    # close the serial port and file
    ser.close()
    file.close()

print("Data collection complete!")

