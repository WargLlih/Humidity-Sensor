import matplotlib.pyplot as plt
from itertools import count
from matplotlib.animation import FuncAnimation

import serial
import json

s = serial.Serial("/dev/ttyUSB0")
s.baudrate = 115200

# plt.style.use('dark_background')
plt.style.use('ggplot')

air_humidity_dht = []
air_humidity_inpe_hz = []
modle_arr = []

index = count()
def animate(i):
    data = s.readline()
    print(data)
    try:
        payload = json.loads(data)
    except Exception as e:
        # print(e)
        return
    # print(payload)

    global air_humidity_dht, air_humidity_inpe_hz

    rhz = payload['air_humidity_inpe_hz']
    model = -0.3236888671696293*rhz + 163.5348810653951
    modle_arr.append(model)
    
    air_humidity_dht.append(payload['air_humidity_dht'])
    air_humidity_inpe_hz.append(rhz)

    air_humidity_dht = air_humidity_dht[::-1][:2000][::-1]
    air_humidity_inpe_hz = air_humidity_inpe_hz[::-1][:2000][::-1]

    plt.cla()

    plt.plot(air_humidity_inpe_hz, air_humidity_dht, '.', color='red', label="INPE b3-n5 Frequência (kHz)")

    plt.plot(air_humidity_inpe_hz, modle_arr, color='black', label="INPE b3-n5 Frequência (kHz)")

    plt.legend(loc='lower left')


fig = plt.figure()
ani = FuncAnimation(fig, animate, interval=1)
plt.show()
