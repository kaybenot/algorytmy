import matplotlib.pyplot as pp
import numpy as np

l = [
    179.6, 179.2, 178.8, 179.9, 179.4, 179.8, 179.9, 179.8,
    179.3, 178.7, 179.8, 177.6, 176.9, 175.8, 175.6, 175.4,
    174.8, 174.0, 172.7, 161.1, 144.5, 138.5, 128.4,
    115.2, 111.6, 106.9, 105.9, 101.7, 91.10, 79.91, 73.14
]

p = [
    0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1,
    2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40, 50, 60, 70,
    80, 90, 100, 200, 300, 400
]

pp.plot(p, l)
pp.title("Charakterystyka fazowa")
pp.xlabel("Częstotliwość [kHz]")
pp.ylabel("Przesunięcie fazowe [stopnie]")
pp.show()
