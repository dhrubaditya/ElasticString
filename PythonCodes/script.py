from functions import *
import matplotlib.pyplot as plt

frequency = 3;
Np = 100;
TMAX= 20;
Totalfiles=2000

curvatureplot(omega=frequency, Np=Np)	

figure=MSD_plot(step=1)
# show(figure)
plt.savefig('MSD_complete.png', dpi=400)
close()

chitra = plt.figure()
chitra=MSD_plot(fig=chitra,step=Totalfiles*3.14*2/(frequency*TMAX))
# step=Totalfiles*3.14*2/(frequency*TMAX)
# print(step)
# show(figure)
plt.savefig('MSD_cycle.png', dpi=400)
close()
