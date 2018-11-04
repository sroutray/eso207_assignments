'''
# Sample code to perform I/O:

name = input()                  # Reading input from STDIN
print('Hi, %s.' % name)         # Writing output to STDOUT

# Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail
'''

# Write your code here
import cmath
####
from p12 import ifft

def fft(a, n):
    if n == 1:
        return a

    a_odd = [a[x] for x in range(1, n, 2)]
    a_even = [a[x] for x in range(0, n, 2)]

    y_odd = fft(a_odd, n//2)
    y_even = fft(a_even, n//2)

    y = [complex(0, 0) for x in range(n)]
    w_n = cmath.rect(1, 2*cmath.pi/n)
    r = complex(1, 0)
    x = 0
    while x < n//2:
        y[x] = y_even[x] + r*y_odd[x]
        y[x + n//2] = y_even[x] - r*y_odd[x]
        r = r*w_n
        x = x + 1

    return y

def run():
    d = int(input())

    real_parts = []
    raw = input()
    raw_list = raw.split(" ")
    real_parts = [float(raw_list[x]) for x in range(0, d)]


    img_parts = []
    raw = input()
    raw_list = raw.split(" ")
    img_parts = [float(raw_list[x]) for x in range(0, d)]

    n = int(input())
    a = [complex(real_parts[x], img_parts[x]) for x in range(0, d)]

    ################################
    x = len(a)
    while x < n:
        a.append(complex(0, 0))
        x = x + 1
    ################################

    y = fft(a, n)
    ######
    y_c = [x.conjugate() for x in y]
    z_c = fft(y_c, n)
    z = [x.conjugate() for x in z_c]
    for x in range(0, n):
        print("{:.5f}".format(z[x].real), end=" ")

    print("")

    for x in range(0, n):
        print("{:.5f}".format(z[x].imag), end=" ")

if __name__ == '__main__':
    run()

