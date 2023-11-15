import serial
import json
import os

s = serial.Serial("/dev/ttyUSB0")
s.baudrate = 115200

def gather():
    data = s.readline()
    print(data)
    try:
        payload = json.loads(data)
    except Exception as e:
        # print(e)
        return None
    # print(payload)
    return payload

def appdend_to_file(f, data):
    f.write(json.dumps(data) + '\n')

if __name__ == '__main__':
    absolute_path = os.path.dirname(__file__)
    relative_path = "data_sets/data_set_1.txt"
    full_path = os.path.join(absolute_path, relative_path)

    f = open(full_path, 'w')

    while True:
        try:
            p = gather()
            if p is not None:
                appdend_to_file(f, p)
        except KeyboardInterrupt:
            break
    f.close()
    