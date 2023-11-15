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

index = count()
def animate(i):
    data = s.readline()
    # print(data)
    try:
        payload = json.loads(data)
    except Exception as e:
        # print(e)
        return
    print(payload)

    global air_humidity_dht, air_humidity_inpe_hz
    
    air_humidity_dht.append(payload['air_humidity_dht'])
    air_humidity_inpe_hz.append(payload['air_humidity_inpe_hz'])

    air_humidity_dht = air_humidity_dht[::-1][:2000][::-1]
    air_humidity_inpe_hz = air_humidity_inpe_hz[::-1][:2000][::-1]

   
    plt.cla()

    plt.plot(
        air_humidity_inpe_hz,
        air_humidity_dht,
        'o',
        color='BLUE', 
        label="DHT22 Umidade (%)"
    )

    plt.annotate(
        f"{payload['air_humidity_dht']}", 
        xy=(air_humidity_inpe_hz[-1], 
        air_humidity_dht[-1]), 
        xytext=(air_humidity_inpe_hz[-1], 
        air_humidity_dht[-1]),
        arrowprops=dict(facecolor='black', shrink=0.05),
    )

    plt.legend(loc='lower left')


fig = plt.figure()
ani = FuncAnimation(fig, animate, interval=1)
plt.show()
