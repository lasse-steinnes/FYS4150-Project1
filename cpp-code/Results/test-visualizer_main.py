from post_processing import *
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np


files = [['simplesolution10.csv', 'simplesolution100.csv', 'simplesolution1000.csv'],['generalsolution10.csv', 'generalsolution100.csv', 'generalsolution1000.csv']]
n = np.zeros(6)
const = np.zeros_like(n)
for i in range(len(files)):
    for j in range(len(files[0])):
        h, n[i], x, num, exact = get_elements(files[i][j])
        l2, const[i] = L2(h, n[i], num, exact)
        visualize(h ,l2, n[i], x, num, exact)
        rel_e = rel_error(num, exact)
        print('The relativ error of %s is %.2f.' %(files[i][j], rel_e))


plt.plot(n**2, const)
plt.title('L2')
plt.xlabel('$h^2$')
plt.ylabel('L2')
plt.show()
