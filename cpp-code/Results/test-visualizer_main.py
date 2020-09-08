##----------------------------------------------
## Programme to visualize the results generated
##----------------------------------------------



from post_processing import *
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

## Make smooth exact solution for plot
x_s = np.linspace(0,1,10000)
u_exact = 1-(1-np.exp(-10))*x_s-np.exp(-10*x_s)


files = [['simplesolution10.csv', 'simplesolution100.csv', 'simplesolution1000.csv'],['generalsolution10.csv', 'generalsolution100.csv', 'generalsolution1000.csv'],['lu_arma10.csv', 'lu_arma100.csv', 'lu_arma1000.csv']]

n1 = np.zeros(3); n2 = np.zeros(3); n3 = np.zeros(3)
const = np.zeros_like(n1); const2 = np.zeros_like(n1); const3 = np.zeros_like(n1)
rel_e = np.zeros((3,3))

for i in range(len(files[0])):
        h, n1[i], x, num, exact = get_elements(files[0][i])
        h2,n2[i], x2, num2, exact2 = get_elements(files[1][i])
        h3, n3[i], x3, num3, exact3 = get_elements(files[2][i])

        l2, const[i] = L2(h,n1[i],num,exact)
        l2_2,const2[i] = L2(h2,n2[i],num2,exact2)
        l2_3,const3[i] = L2(h3,n3[i],num3,exact3)

        l2s = [l2,l2_2,l2_3]
        u_num = (num,num2,num3)
        rel_e = np.zeros((3,3))

        visualize(h ,l2s, int(n[i]), x, x_s, u_num, u_exact)
        for j in range(len(u_num)):
            rel_e[i,j] = rel_error(u_num[j], exact)
            print('The relativ error of %s is %.4e.' %(files[j][i], rel_e[i,j]))

nums = ('simple algo','general algo','lu_arma')
consts = [const,const2,const3]
plt.figure()
for i in range(len(nums)):
        plt.plot(n[i]**2, consts[i],'.',label = nums[i])

plt.title('L2-norm as a function of stepsize $h^{2}$', fontsize=15)
plt.xlabel('$h^2$', fontsize=15)
plt.ylabel('L2', fontsize=15)
plt.legend(fontsize=12)
plt.savefig("figs/L2h_square.pdf")
plt.show()
#plotting the relativ error
plt.plot(n1, rel_e[0], label = 'Simple solution')
plt.plot(n2, rel_e[1], label = 'General solution')
plt.plot(n3, rel_e[2], label = 'LU decompotision')
plt.title('Relative error as a function of the grid number, n', fontsize=15)
plt.xlabel('n', fontsize=15)
plt.ylabel('Relativ error', fontsize=15)
plt.legend(fontsize=13)
plt.savefig("figs/rel_error.pdf")
plt.show()
