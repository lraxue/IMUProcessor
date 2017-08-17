# -*- coding: utf-8 -*-
# @Time    : 17-8-14 下午4:46
# @Author  : FeiXue
# @Email   : Fei.Xue@uisee.com
# @File    : plot_imu.py
# @Software: PyCharm Community Edition

import numpy as np
import matplotlib.pyplot as plt
import os
import math

def red2deg(red):
    return red * 180.0 / math.pi

def load_data(data):
    t = np.zeros(3)
    x = []
    y = []
    z = []

    k = 0

    for line in data.readlines():
        line.strip()
        values = line.split()
        k += 1
        # if k > 5000:
        #     break

        for i in  range(3):
            t[i] = float(values[i])

        x.append(t[0])
        y.append(t[1])
        z.append(t[2])

    return x, y, z


def load_v_a(data, K=None):
    t = np.zeros(7)
    v1 = []
    v2 = []
    v3 = []
    a1 = []
    a2 = []
    a3 = []


    k = 0

    for line in data.readlines():
        line.strip()
        values = line.split()
        k += 1
        if k > 2000:
            break

        for i in range(7):
            t[i] = float(values[i])

        v1.append(red2deg(t[1]))
        v2.append(red2deg(t[2]))
        v3.append(red2deg(t[3]))

        a1.append(t[4])
        a2.append(t[5])
        a3.append(t[6])

    return v1, v2, v3, a1, a2, a3

data = open("t_v_a.txt", 'r')
v1, v2, v3, a1, a2, a3 = load_v_a(data)
print v1, v2, v3, a1, a2, a3

plt.figure()
# plt.plot(v1, '-r', label='X')
# plt.plot(v2, '-g', label='Y')
plt.plot(v3, '-b', label='Z')
plt.xlabel('time point')
plt.ylabel('deg/s')
plt.grid()
plt.legend()
plt.savefig('vel_z_2000.png')

# plt.savefig('vels_5000.png')
# plt.show()


# plt.figure(19.2, 10.8)
# plt.plot(a1, '-r', label='a1')
# plt.plot(a2, '-g', label='a2')
# plt.plot(a3, '-b', label='a3')
# plt.grid()
# plt.legend()

# plt.savefig('accs_5000.png')
plt.show()