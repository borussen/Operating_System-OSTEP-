import argparse
import subprocess
import matplotlib.pyplot as plt
import numpy as np

parser = argparse.ArgumentParser()
parser.add_argument('pages', type=int)
parser.add_argument('trials')
args = parser.parse_args()

data = []
x = np.arrange(args.pages)
pages = 2 ** x

for i in pages:
    r = subprocess.run(['./tlb.out', str(i), args.trials], capture_output=True, check=True, text=True)
    data.append(float(r.stdout))

plt.margins(0)
plt.plot(x, data, 'bo-')
plt.xticks(x, pages)
plt.xlabel('Number of Pages Accessed')
plt.ylabel('Time Per Access (ns)')
plt.savefig('result.png')
plt.show()