import matplotlib.pyplot as plt
from itertools import count
from matplotlib.animation import FuncAnimation
import numpy as np

import json

# plt.style.use('dark_background')
plt.style.use('ggplot')


ur_base = []
air_humidity_inpe_hz = []
model = []

f = open('data_set_1.txt', 'r')
data = f.readlines()

def UR(rhz):
  return 110.967036461073 - 0.177165179036473*rhz

for d in data:
    # print(d)
    try:
        payload = json.loads(d)
    except Exception as e:
        print(e)
        continue

    
    rhz = payload['air_humidity_inpe_hz']
    
    air_humidity_inpe_hz.append(rhz)
    # model.append(UR(rhz))
    ur_base.append(payload['air_humidity_dht'])

plt.plot(air_humidity_inpe_hz, ur_base, '.', color='red', label="UR Base")

plt.annotate(f"{ur_base[-1]}",
            xy=(air_humidity_inpe_hz[-1], ur_base[-1]), 
            xytext=(air_humidity_inpe_hz[-1], ur_base[-1]),
            arrowprops=dict(facecolor='black', shrink=0.05),)


m, b = np.polyfit(air_humidity_inpe_hz, ur_base, 1)
print(f'model: {m}x + {b}')

plt.plot(air_humidity_inpe_hz, [m*x+b for x in air_humidity_inpe_hz], color='black', label="Model")

# plt.annotate(f"{model[-1]}",
#             xy=(air_humidity_inpe_hz[-1], model[-1]), 
#             xytext=(air_humidity_inpe_hz[-1], model[-1]),
#             arrowprops=dict(facecolor='black', shrink=0.05),)


plt.legend(loc='lower left')
plt.show()
