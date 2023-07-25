"""Python script to save MPU9250 raw data into csv file"""

from datetime import datetime
import serial
import csv
import os
import keyboard

print('\nWaiting for data from Arduino serial port')
print('------------------------------------------\n')

current_time = datetime.now().strftime("%d-%m-%Y_%H-%M-%S")
value = 0
file_path = './Raw data'
file_name = f"{current_time}.csv"
file_full_path = os.path.join(file_path, file_name)

# Write the header to the CSV file
header = ['sr_no', 'timestamp', 'acc_x', 'acc_y', 'acc_z', 'gyro_x', 'gyro_y', 'gyro_z', 'mag_x', 'mag_y', 'mag_z', 'event_class']
with open(file_full_path, 'a', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(header)

# Open serial port
ser = serial.Serial('COM4', 115200)
ser.flush()

try:
    while True:
        received_string = ser.readline().decode('utf-8').strip()  # Get the data from Arduino serial port
        mpu_values = received_string.split('|')  # Split the string into 9 values at '|'
        now = datetime.now().strftime("%d-%m-%Y %H:%M:%S:%f")
        value += 1
        sr_no = str(value)
        data_row = [sr_no, now] + mpu_values
        with open(file_full_path, 'a', newline='') as file:
            writer = csv.writer(file)
            writer.writerow(data_row)
        print(data_row)

        # Check if the 'esc' key was pressed to stop capturing data
        if keyboard.is_pressed('esc'):
            break

except Exception as e:
    print(f"An error occurred: {str(e)}")

finally:
    # Close the serial port
    ser.close()
