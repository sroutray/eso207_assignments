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
#define MAX 2000000

struct St
{
    int v[MAX];
    long int top;
};
typedef struct St St;

int isEmpty(St *S)
{
    return (S->top == 0);
}

int isFull(St *S)
{
    return (S->top == MAX - 1);     
}

void makeEmpty(St *S)
{
    S->top = 0;
}

int push(St *S, int x)
{
    if(!isFull(S))
    {
        S->v[S->top] = x;
        S->top = S->top + 1;
        return 1;
    }
    else return -1;
}

int pop(St *S) // take care while calling pop
{
    if(!isEmpty(S))
    {
        int value = S->v[S->top - 1];
        S->top = S->top - 1;
        return value;
    }
    else return -1;
}

int top(St *S) // take care while calling top
{
    if(!isEmpty(S))
    {
        return S->v[S->top - 1];
    }
    else return -1;
}

long int min(int in[], long int l, long int r)
{
    long int mini = l;
    for(long int i = l; i <= r; i++)
    {
        if(in[i] < in[mini])
            mini = i;
    }
    return mini;
}

void run(void)
{
    long int m;
    scanf("%ld", &m);
    int in[m];
    for(long int i = 0; i < m; i++)
        scanf("%d", &in[i]);

    St *S = (St*)malloc(sizeof(St));
    S->top = 0;
    int out[m];
    long int i, j, min_ind;
    i = 0;
    j = 0;
    while(i < m)
    {
        if(isEmpty(S))
        {
            min_ind = min(in, i, m - 1);
            for(; i <= min_ind; i++)
                push(S, in[i]);
            out[j] = pop(S);
            j++;
        }
        else
        {
            min_ind = min(in, i, m - 1);
            while(!isEmpty(S) && top(S) <= in[min_ind])
            {
                out[j] = pop(S);
                j++;
            }
            for(; i <= min_ind; i++)
                push(S, in[i]);
            out[j] = pop(S);
            j++;
        }
    }
    while(!isEmpty(S))
    {
        out[j] = pop(S);
        j++;
    }
    for(i = 0; i < m; i++)
        printf("v%d", out[i]);
    printf("\n");
}

int main(void)
{
    int T;
    scanf("%d", &T);
    for(int i = 0; i < T; i++)
        run();
}