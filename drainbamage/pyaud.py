import math
import pyaudio
import sys
import numpy as np

PyAudio = pyaudio.PyAudio
RATE = 8000
WAVE = 1000
data = '''
   #####
  #
  #
   #####
        #
        #
  ######
'''

data = data.split('\n')
n_rows = len(data)
n_cols = max(map(len, data))

for x in range(n_rows):
    stream = ([chr(int(math.sin(x/((RATE/WAVE)/math.pi))*127+128)) for x in xrange(RATE)])

#sin = chr(float(np.sin(np.array((0., 30., 45., 60., 90.)) * np.pi / 180. )))
chrstr = data[0] + (data[1]) + (data[2]) + (data[3])

data = chrstr.join(stream)
#charstr = data.split('\n')
p = PyAudio()
stream = p.open(format =
                p.get_format_from_width(1),
                channels = 1,
                rate = RATE,
                output = True)
for DISCARD in xrange(10):
    stream.write(data)
stream.stop_stream()
stream.close()
p.terminate()
