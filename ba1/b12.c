/*
// Sample code to perform I/O:
#include <stdio.h>

long int main(){
	long int num;
	scanf("%d", &num);              			// Reading input from STDIN
	prlong intf("Input number is %d.\n", num);       // Writing output to STDOUT
}

// Warning: Prlong inting unwanted or ill-formatted data to output will cause the test cases to fail
*/

// Write your code here
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct complex
{
    double x;
    double y;
};

typedef struct complex complex;

complex add(complex a, complex b)
{
    complex r;
    r.x = a.x + b.x;
    r.y = a.y + b.y;
    return r;
}

complex subtract(complex a, complex b)
{
    complex r;
    r.x = a.x - b.x;
    r.y = a.y - b.y;
    return r;
}

complex multiply(complex a, complex b)
{
    complex r;
    r.x = a.x * b.x - a.y * b.y;
    r.y = a.x * b.y + a.y * b.x;
    return r;
}

complex *fft(complex *a, long int n)
{
    if(n == 1)
        return a;   
    
    complex *a_odd = (complex *)malloc((n/2) * sizeof(complex));
    complex *a_even = (complex *)malloc((n/2) * sizeof(complex));
    for(long int i = 0; 2 * i + 1 < n; i++)
        a_odd[i] = a[2 * i + 1];
    for(long int i = 0; 2 * i < n; i++)
        a_even[i] = a[2 * i];

    complex *y_odd = fft(a_odd, n/2);
    complex *y_even = fft(a_even, n/2);

    complex W, r;
    complex *y = (complex *)malloc(n * sizeof(complex));

    for(long int i = 0; i < n/2; i++)
    {
        r.x = cos(2.0 * M_PI * i / n);
        r.y = sin(2.0 * M_PI * i / n);
        y[i] = add(y_even[i], multiply(r, y_odd[i]));
        y[i + n/2] =  subtract(y_even[i], multiply(r, y_odd[i]));
    }
    
    return y; 
}

complex *ifft(complex *a, long int n)
{
    if(n == 1)
        return a;   
    
    complex *a_odd = (complex *)malloc((n/2) * sizeof(complex));
    complex *a_even = (complex *)malloc((n/2) * sizeof(complex));
    for(long int i = 0; 2 * i + 1 < n; i++)
        a_odd[i] = a[2 * i + 1];
    for(long int i = 0; 2 * i < n; i++)
        a_even[i] = a[2 * i];

    complex *y_odd = ifft(a_odd, n/2);
    complex *y_even = ifft(a_even, n/2);

    complex W, r;
    complex *y = (complex *)malloc(n * sizeof(complex));

    for(long int i = 0; i < n/2; i++)
    {
        r.x = cos(2.0 * M_PI * i / n);
        r.y = -sin(2.0 * M_PI * i / n);
        y[i] = add(y_even[i], multiply(r, y_odd[i]));
        y[i + n/2] =  subtract(y_even[i], multiply(r, y_odd[i]));
    }
    
    return y; 
}

long int find_pow2(long int n)
{
 	long int i = 0;
	long int div = 1;
	long int q = n/div;
    long int r = -1;
	while(q != 0)
	{
	    r = n%div;
	    i++;
	    div = 2*div;
	    q = n/div;
	   
	}
	if(!r) i = i-1;

    long int j = 0;
    long int p = 1;
    while(j<i)
    {
        p = 2*p;
        j++;
    }
    return p;   
}


void run(void)
{
    long int n;
    scanf("%ld", &n);
    
    long int a[n];
    long int b[n];
    for(long int i = 0; i < n; i++)
        scanf("%ld", &a[i]);
    for(long int i = 0; i < n; i++)
        scanf("%ld", &b[i]);
        
    long int range = 10 * n + 1;
    long int len = find_pow2(2 * range);
    complex a_poly[len];
    complex b_poly[len];
    for(long int i = 0; i < len; i++)
    {
        complex t = {0, 0};
        a_poly[i] = t;
        b_poly[i] = t;
    }
    for(long int i = 0; i < n; i++)
    {
        a_poly[a[i]].x = a_poly[a[i]].x + 1;
        b_poly[b[i]].x = b_poly[b[i]].x + 1;
    }
    
    complex *at, *bt, *ab;
    complex abt[len];
    
    at = fft(a_poly, len);
    bt = fft(b_poly, len);
    
    for(long int i = 0; i < len; i++)
        abt[i] = multiply(at[i], bt[i]);
        
    ab = ifft(abt, len);
    
    long int count = 0;
    for(long int i = 0; i < len; i++)
    {
        ab[i].x = round(ab[i].x / len);
        ab[i].y = round(ab[i].y / len);
        
        if(ab[i].x != 0)
            count++;
    }
    printf("%ld\n", count);
    for(long int i = 0; i < len; i++)
    {
        if(ab[i].x != 0)
            printf("%ld %0.f\n", i, ab[i].x);
    }
}

int main(void)
{
    long int T;
    scanf("%ld", &T);
    for(long int i = 0; i < T; i++)
        run();
}