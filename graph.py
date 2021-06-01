import matplotlib.pyplot as plt
import sys

s_file_name = R"D:\GoogleDrive\sync\source\clion\DoubleIntegral\spline.txt"

with open(s_file_name) as s_in:
    xs = [float(num) for num in s_in.readline().strip().split()]
    ys = [float(num) for num in s_in.readline().strip().split()]
    xin = [float(num) for num in s_in.readline().strip().split()]
    yin = [float(num) for num in s_in.readline().strip().split()]
    xout = [float(num) for num in s_in.readline().strip().split()]
    yout = [float(num) for num in s_in.readline().strip().split()]
    xc = float(s_in.readline())
    yc = float(s_in.readline())
    plt.plot(xin, yin, '.', label="Points in figure",markersize=1)
    plt.plot(xout, yout, '.', label="Points out of figure",markersize=1)
    plt.plot(xs, ys, label="S(x)")
    plt.plot([xc], [yc], '.', label="Center of gravity", markersize=10)
    plt.legend()
    plt.show()
