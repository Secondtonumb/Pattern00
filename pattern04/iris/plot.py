# coding=utf-8
from __future__ import division

import numpy as np
import matplotlib.pyplot as plt
import argparse
import pandas as pd


data = pd.read_csv("log.csv", header=None).values
data = data[:, 0: (len(data[0, :]) - 1)]

parser = argparse.ArgumentParser()
parser.add_argument("ptn_num", nargs='?', type=int)
args = parser.parse_args()

clu = len(data[0, :]) // args.ptn_num

# for x in xrange(len(data[0, :])):
#     plt.plot(xrange(len(data[:, 0])), data[:, x], label="column%d" % (x))
pics = args.ptn_num // 10
for i in range(pics):
    for x in range(10):
        plt.subplot(10 // 2, 2, x + 1)
        for y in range(clu):
            plt.title("pattern%d" %(i * 10 + x))
            plt.plot(range(len(data[:, 0])), data[:, i * 10 * clu + x * clu + y], label="Clu %d" % (y))
            plt.ylim(0, 1)
            plt.legend(fontsize=5)
    plt.tight_layout()
    plt.show()
