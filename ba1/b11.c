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

long int countCrossInversions(long int *A, long int lo, long int mid, long int hi)
{
    long int total = hi - lo + 1;
    // count inversions
    long int cl = mid;
    long int cr = hi;
    long int inv = 0;
    for(long int i = total; i > 0; i--)
    {
        if(cl < lo)
        {
            cr--;
            continue;
        }
        else if(cr <= mid)
        {
            cl--;
            continue;
        }
        
        if(A[cl] > 2 * A[cr])
        {
            inv = inv + cr - mid;
            cl--;
        }
        else
            cr--;
    }

    // merge in sorted order
    cl = lo;
    cr = mid + 1;
    long int B[total];
    for(long int i = 0; i < total; i++)
    {
        if(cl > mid)
        {
            B[i] = A[cr];
            cr++;
            continue;
        }
        else if(cr > hi)
        {
            B[i] = A[cl];
            cl++;
            continue;
        }

        if(A[cl] > A[cr])
        {
            B[i] = A[cr];
            cr++;
        }
        else
        {
            B[i] = A[cl];
            cl++;
        }
    }

    for(long int i = 0; i < total; i++)
        A[i + lo] = B[i];

    return inv;
    // long int nl = mid - lo + 1;
    // long int nr = hi - mid;
    // long int L[nl], R[nr];
    // for(long int i = 0; i < nl; i++)
    //     L[i] = A[lo + i];
    // for(long int i = 0; i < nr; i++)
    //     R[i] = A[mid + 1 + i];
    
    // long int i, j, inv, k;
    // // find significant inversions
    // i = nl - 1;
    // j = nr - 1;
    // k = nl + nr - 1;
    // inv = 0;
    // while(k >= 0)
    // {
    //     if(i < 0)
    //     {
    //         j--;
    //         k--;
    //     }
    //     else if(j < 0)
    //     {
    //         i--;
    //         k--;
    //     }
        
    //     if(i >=0 && j >=0 && L[i] > 2 * R[j])
    //     {
    //         inv = inv + j + 1;
    //         i--;
    //         k--;
    //     }
    //     else if(i >=0 && j >=0 && L[i] <= 2 * R[j])
    //         j--;
    //         k--;
    // }
    // // merge in sorted order
    // i = 0;
    // j = 0;
    // k = lo;
    // while(i < nl && j < nr)
    // {
    //     if(L[i] > R[j])
    //     {
    //         A[k] = R[j];
    //         j++;
    //         k++;
    //     }
    //     else
    //     {
    //         A[k] = L[i];
    //         i++;
    //         k++;
    //     }
    // }
    // while(i < nl)
    // {
    //     A[k] = L[i];
    //     i++;
    //     k++;
    // }
    // while(j < nr)
    // {
    //     A[k] = R[j];
    //     j++;
    //     k++;
    // }
    
    // return inv;
}

long int countInversions(long int *A, long int lo, long int hi)
{
    if(lo >= hi)
        return 0;

    else
    {
        long int mid = (lo + hi) / 2;
    
        long int il = countInversions(A, lo, mid);
        long int ir = countInversions(A, mid + 1, hi);
        long int ic = countCrossInversions(A, lo, mid, hi);
        long int it = il + ir + ic;
        return it;
    }
}

void run()
{
    long int n;
    scanf("%ld", &n);

    long int A[n];
    for(long int i = 0; i < n; i++)
        scanf("%ld", &A[i]);
    
    long int c = countInversions(A, 0, n-1);
    // for(long int i = 0; i < n; i++)
    //     prlong intf("%d ", A[i]);
    printf("%ld\n", c);
}

long int main(void)
{
    long int T;
    scanf("%ld", &T);
    for(long int i = 0; i < T; i++)
        run();
    return 0;
}