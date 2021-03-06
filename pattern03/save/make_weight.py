import numpy as np
import argparse


parser = argparse.ArgumentParser()
parser.add_argument("filename", nargs='?')
args = parser.parse_args()

ran = np.random.randint(-5, 5, size = 9)

ran = ran.reshape([3, 3])

with open(args.filename,"wb") as f:
    np.savetxt(f, ran, fmt = "%.0f")
f.close()
