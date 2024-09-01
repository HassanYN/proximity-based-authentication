import serial

# Establish serial connection with Arduino
ser = serial.Serial('COM3', 9600)  # Replace 'COM3' with the appropriate port name

file_path = 'C:/Users/gwize/OneDrive - KFUPM/231/COE 446/Project/Programs/micros_002/3mACC.txt'
counter = 0
while True:
    if ser.in_waiting > 0:
        data = ser.readline().rstrip()
        print(counter)
        if (counter < 300):
            with open(file_path, 'a') as file:
                file.write(str(data).replace('\'', '').replace('b', '') + '\n')
                counter = counter + 1
        else:
            break
