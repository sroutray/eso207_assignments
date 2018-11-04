/*
// Sample code to perform I/O:
#include <stdio.h>

int main(){
	int num;
	scanf("%d", &num);              			// Reading input from STDIN
	printf("Input number is %d.\n", num);       // Writing output to STDOUT
}

// Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail
*/

// Write your code here
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct complex
{
    long double x;
    long double y;
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

complex *fft(complex *a, long long int n)
{
    if(n == 1)
        return a;   
    
    complex *a_odd = (complex *)malloc((n/2) * sizeof(complex));
    complex *a_even = (complex *)malloc((n/2) * sizeof(complex));
    for(long long int i = 0; 2 * i + 1 < n; i++)
        a_odd[i] = a[2 * i + 1];
    for(long long int i = 0; 2 * i < n; i++)
        a_even[i] = a[2 * i];

    complex *y_odd = fft(a_odd, n/2);
    complex *y_even = fft(a_even, n/2);

    complex W, r;
    complex *y = (complex *)malloc(n * sizeof(complex));
    W.x = cos(2.0 * M_PI / n);
    W.y = sin(2.0 * M_PI / n);
    r.x = 1.0;
    r.y = 0.0;

    for(long long int i = 0; i < n/2; i++)
    {
        y[i] = add(y_even[i], multiply(r, y_odd[i]));
        y[i + n/2] =  subtract(y_even[i], multiply(r, y_odd[i]));
        r = multiply(W, r);
    }
    
    return y; 
}

complex *ifft(complex *a, long long int n)
{
    if(n == 1)
        return a;   
    
    complex *a_odd = (complex *)malloc((n/2) * sizeof(complex));
    complex *a_even = (complex *)malloc((n/2) * sizeof(complex));
    for(long long int i = 0; 2 * i + 1 < n; i++)
        a_odd[i] = a[2 * i + 1];
    for(long long int i = 0; 2 * i < n; i++)
        a_even[i] = a[2 * i];

    complex *y_odd = ifft(a_odd, n/2);
    complex *y_even = ifft(a_even, n/2);

    complex W, r;
    complex *y = (complex *)malloc(n * sizeof(complex));
    W.x = cos(2.0 * M_PI * (n - 1) / n);
    W.y = sin(2.0 * M_PI * (n - 1) / n);
    r.x = 1.0;
    r.y = 0.0;

    for(long long int i = 0; i < n/2; i++)
    {
        y[i] = add(y_even[i], multiply(r, y_odd[i]));
        y[i + n/2] =  subtract(y_even[i], multiply(r, y_odd[i]));
        r = multiply(W, r);
    }
    
    return y; 
}

long long int find_pow2(long long int n)
{
 	long long int i = 0;
	long long int div = 1;
	long long int q = n/div;
    long long int r = -1;
	while(q != 0)
	{
	    r = n%div;
	    i++;
	    div = 2*div;
	    q = n/div;
	   
	}
	if(!r) i = i-1;

    long long int j = 0;
    long long int p = 1;
    while(j<i)
    {
        p = 2*p;
        j++;
    }
    return p;   
}

int main(void)
{
    long long int n, m;
    scanf("%lld %lld", &n, &m);

    long double a_real_parts[n];
    long double a_img_parts[n];
    long double b_real_parts[m];
    long double b_img_parts[m];

    for(long long int i = 0; i < n; i++)
        scanf("%Lf", &a_real_parts[i]);
    for(long long int i = 0; i < n; i++)
        scanf("%Lf", &a_img_parts[i]);
    for(long long int i = 0; i < m; i++)
        scanf("%Lf", &b_real_parts[i]);
    for(long long int i = 0; i < m; i++)
        scanf("%Lf", &b_img_parts[i]);

    long long int c_terms = m + n - 1;

    // find the highest power of 2
    long long int pad_len = find_pow2(c_terms);

    complex *a = (complex *)malloc(pad_len * sizeof(complex));
    complex *b = (complex *)malloc(pad_len * sizeof(complex));
    complex *abt = (complex *)malloc(pad_len * sizeof(complex));
    complex *at, *bt, *c;

    for(long long int i = 0; i < pad_len; i++)
    {
        if(i < n)
        {
            complex t;
            t.x = a_real_parts[i];
            t.y = a_img_parts[i];
            a[i] = t;
        }
        else
        {
            complex t = {0, 0};
            a[i] = t;
        }

        if(i < m)
        {
            complex u;
            u.x = b_real_parts[i];
            u.y = b_img_parts[i];
            b[i] = u;
        }
        else
        {
            complex u = {0, 0};
            b[i] = u;
        }
    }

    at = fft(a, pad_len);
    bt = fft(b, pad_len);

    // multiply
    for(long long int i = 0; i < pad_len; i++)
        abt[i] = multiply(at[i], bt[i]);
    

    c = ifft(abt, pad_len);
    for(long long int i = 0; i < pad_len; i++)
    {
        c[i].x = c[i].x / (long double)pad_len;
        c[i].y = c[i].y / (long double)pad_len;
        if(fabs(c[i].x) <= 0.0000099999999999) c[i].x = 0.0;
        if(fabs(c[i].y) <= 0.0000099999999999) c[i].y = 0.0;
    }

    for(long long int i = 0; i < c_terms; i++)
        printf("%.5Lf ", c[i].x);
    printf("\n");
    for(long long int i = 0; i < c_terms; i++)
        printf("%.5Lf ", c[i].y);
    
    return 0;
}