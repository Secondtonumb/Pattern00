# coding=utf-8
from __future__ import division

import numpy as np
import argparse

parser = argparse.ArgumentParser()
parser.add_argument("x_upper", nargs='?', type=float, default=8)
parser.add_argument("x_lower", nargs='?', type=float, default=0)
parser.add_argument("y_upper", nargs='?', type=float, default=8)
parser.add_argument("y_lower", nargs='?', type=float, default=0)
parser.add_argument("n", nargs='?', type=int, default=100)
args = parser.parse_args()

x = np.linspace(args.x_lower, args.x_upper, args.n + 1)
y = np.linspace(args.y_lower, args.y_upper, args.n + 1)

# x, y = np.meshgrid(x, y)

f = open("grid.dat", "w+")

for b in y:
    for a in x:
        print(a, args.y_upper - b, file=f)

# f = open("grid.dat", "w")

# print(f, x, y)
