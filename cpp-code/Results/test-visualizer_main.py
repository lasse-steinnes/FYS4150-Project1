from post_processing import *
import matplotlib.pyplot as plt
import pandas as pd


files = [['simplesolution10.csv', 'simplesolution100.csv', 'simplesolution1000.csv'],['generalsolution10.csv', 'generalsolution100.csv', 'generalsolution1000.csv']]
for i in range(len(files)):
    for j in range(len(files[0])):
        n, x, num, exact = get_elements(files[i][j])
        l2, const = L2(n, num, exact)
        visualize(l2, n, x, num, exact)
        rel_error = rel_error(num, exact)
        print('The relativ error of %s is %.2f.' %(filename, rel_error))
        plt.plot(n**2, const, label = filename)
        plt.title('L2')
        plt.xlabel('$h^2$')
        plt.ylabel('L2')
        plt.legend()
        plt.show()
