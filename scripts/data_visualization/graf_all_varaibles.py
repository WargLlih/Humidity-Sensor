import matplotlib.pyplot as plt
from itertools import count
from matplotlib.animation import FuncAnimation

import serial
import json

s = serial.Serial("/dev/ttyUSB0")
s.baudrate = 115200

# plt.style.use('dark_background')
plt.style.use('ggplot')

x =[]
temperature_dht = []
air_humidity_dht = []
air_humidity_inpe_hz = []
air_humidity_inpe_model = []

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

    global x, temperature_dht, air_humidity_dht, air_humidity_inpe_hz, air_humidity_inpe_model

    rhz = payload['air_humidity_inpe_hz']
    # model = 35.9/-101.305 * (rhz) + 158.62
    # model = 109.2365 - 0.156*rhz
    # model = 109.9128 - 0.1645 * rhz
    # model = 159.794788979652 - 0.365979079326695*rhz
    model = 110.967036461073 - 0.177165179036473*rhz
    
    x.append(next(index))
    temperature_dht.append(payload['temperature_dht'])
    air_humidity_dht.append(payload['air_humidity_dht'])
    air_humidity_inpe_hz.append(rhz)
    air_humidity_inpe_model.append(model)

    x = x[::-1][:2000][::-1]
    temperature_dht = temperature_dht[::-1][:2000][::-1] 
    air_humidity_dht = air_humidity_dht[::-1][:2000][::-1]
    air_humidity_inpe_hz = air_humidity_inpe_hz[::-1][:2000][::-1]
    air_humidity_inpe_model = air_humidity_inpe_model[::-1][:2000][::-1]

   
    plt.cla()

    plt.plot(x, temperature_dht, color='RED', label="DHT22 Temperatura (°C)")
    plt.plot(x, air_humidity_dht, color='BLUE', label="DHT22 Umidade (%)")
    plt.annotate(f"{payload['temperature_dht']}", xy=(x[-1], temperature_dht[-1]), xytext=(x[-1], temperature_dht[-1]), arrowprops=dict(facecolor='black', shrink=0.05),)
    plt.annotate(f"{payload['air_humidity_dht']}", xy=(x[-1], air_humidity_dht[-1]), xytext=(x[-1], air_humidity_dht[-1]), arrowprops=dict(facecolor='black', shrink=0.05),)

    plt.plot(x, air_humidity_inpe_hz, color='BLACK', label="INPE b3-n5 Frequência (kHz)")
    plt.annotate(f"{payload['air_humidity_inpe_hz']}", xy=(x[-1], air_humidity_inpe_hz[-1]), xytext=(x[-1], air_humidity_inpe_hz[-1]), arrowprops=dict(facecolor='black', shrink=0.05),)
    plt.plot(x, air_humidity_inpe_model, color='GREEN', label="INPE b3-n5 UR (%)")    
    plt.annotate(f"{model : .2f}", xy=(x[-1], air_humidity_inpe_model[-1]), xytext=(x[-1], air_humidity_inpe_model[-1]), arrowprops=dict(facecolor='black', shrink=0.05),)
    
    plt.legend(loc='lower left')


fig = plt.figure()
ani = FuncAnimation(fig, animate, interval=1)
plt.show()
