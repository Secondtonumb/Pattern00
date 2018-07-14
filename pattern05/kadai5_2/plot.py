# coding=utf-8
from __future__ import division

import numpy as np
import matplotlib.pyplot as plt
import argparse
import pandas as pd


data = pd.read_csv("label.csv", header=None).values

parser = argparse.ArgumentParser()
parser.add_argument("ptn_dim", nargs='?', type=float, default=8)
args = parser.parse_args()


plt.imshow(data,
           extent=[0, args.ptn_dim, 0, args.ptn_dim],
           cmap="GnBu",
           origin='upper',
           )
plt.xlabel("Dimension 0")
plt.ylabel("Dimension 1")

plt.colorbar()
plt.show()
