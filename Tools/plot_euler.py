# -*- coding: utf-8 -*-
# @Time    : 17-8-14 上午9:39
# @Author  : FeiXue
# @Email   : Fei.Xue@uisee.com
# @File    : plot_euler.py
# @Software: PyCharm Community Edition

import numpy as np
import matplotlib.pyplot as plt
import os


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
        if k > 44000:
            break

        for i in  range(3):
            t[i] = float(values[i])

        x.append(t[0])
        y.append(t[1])
        z.append(t[2])

    return x, y, z


def load_v_a(data, K=None):
    t = np.zeros(6)
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
        if k > 5000:
            break

        for i in range(6):
            t[i] = float(values[i])

        v1.append(t[0])
        v2.append(t[1])
        v3.append(t[2])

        a1.append(t[3])
        a2.append(t[4])
        a3.append(t[5])

    return v1, v2, v3, a1, a2, a3

data = open('../data/euler_integrated_20170816.txt', 'r')
x, y, z = load_data(data)
data2 = open('../data/euler_raw_20170816.txt', 'r')
_, _, z_raw = load_data(data2)

yticks =  range(-100, 800, 50)

fig, ax = plt.subplots()
ax.set_yticks(yticks)

# plt.figure(figsize=(19.2, 10.8))
plt.plot(z, '--r', label="Yaw")
plt.plot(x, '--b', label="Roll")
plt.plot(y, '--g', label="Pitch")
# plt.plot(z_raw, '--m', label='raw_Yaw')
# plt.plot(z_raw, '--m', label='Yaw_raw')
plt.grid(True, lineStyle='-.', color='m')
plt.legend()
plt.title("Euler angles along time")
plt.xlabel('time/0.01s')
plt.ylabel('angle/deg')
plt.savefig("euler_post_auto_20170816_44000.png")
plt.show()

# data = open("v_a.txt", 'r')
# v1, v2, v3, a1, a2, a3 = load_v_a(data)
# print v1, v2, v3, a1, a2, a3
#
# plt.figure()
# plt.plot(v1, '-r', label='v1')
# plt.plot(v2, '-g', label='v2')
# plt.plot(v3, '-b', label='v3')
# plt.grid()
# plt.legend()
#
# plt.savefig('vels_5000.png')
# # plt.show()
#
# plt.figure()
# plt.plot(a1, '-r', label='a1')
# plt.plot(a2, '-g', label='a2')
# plt.plot(a3, '-b', label='a3')
# plt.grid()
# plt.legend()
#
# plt.savefig('accs_5000.png')
# plt.show()