'''
# Sample code to perform I/O:

name = input()                  # Reading input from STDIN
print('Hi, %s.' % name)         # Writing output to STDOUT

# Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail
'''

# Write your code here
import cmath
import math

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

def ifft(a, n):
    if n == 1:
        return a

    a_odd = [a[x] for x in range(1, n, 2)]
    a_even = [a[x] for x in range(0, n, 2)]

    y_odd = fft(a_odd, n//2)
    y_even = fft(a_even, n//2)

    y = [complex(0, 0) for x in range(n)]
    w_n = cmath.rect(1, -2*cmath.pi/n)
    r = complex(1, 0)
    x = 0
    while x < n//2:
        y[x] = y_even[x] + r*y_odd[x]
        y[x + n//2] = y_even[x] - r*y_odd[x]
        r = r*w_n
        x = x + 1

    y = [x/n for x in y]
    return y

def run():
    raw = input()
    raw_list = raw.split(" ")
    n = int(raw_list[0])
    m = int(raw_list[1])

    raw = input()
    raw_list = raw.split(" ")
    a_real_parts = [float(raw_list[x]) for x in range(0, n)]

    raw = input()
    raw_list = raw.split(" ")
    a_img_parts = [float(raw_list[x]) for x in range(0, n)]

    raw = input()
    raw_list = raw.split(" ")
    b_real_parts = [float(raw_list[x]) for x in range(0, m)]

    raw = input()
    raw_list = raw.split(" ")
    b_img_parts = [float(raw_list[x]) for x in range(0, m)]

    c_terms = m + n - 1
    p = math.ceil(math.log2(c_terms))
    pad_len = 2**p

    a = [complex(a_real_parts[x], a_img_parts[x]) for x in range(0, n)]
    b = [complex(b_real_parts[x], b_img_parts[x]) for x in range(0, m)]

    x = len(a)
    while x < pad_len:
        a.append(complex(0, 0))
        x = x + 1

    x = len(b)
    while x < pad_len:
        b.append(complex(0, 0))
        x = x + 1

    y_a = fft(a, pad_len)
    y_b = fft(b, pad_len)
    y_c = [y_a[x]*y_b[x] for x in range(0, pad_len)]
    c = ifft(y_a, pad_len)

    for x in range(0, c_terms):
        print("{:.5f}".format(c[x].real), end=" ")

    print("")

    for x in range(0, c_terms):
        print("{:.5f}".format(c[x].imag), end=" ")


if __name__ == '__main__':
    run()
    


    
