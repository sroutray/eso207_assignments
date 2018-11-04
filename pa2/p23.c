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

#define MAX 30000

// define operand type
int opd = 1;
// define operator type
int op = 2;
int plus = 0;
int min = 1;
int mul = 2;
int mod = 3;
int divi = 4;
int pwf = 5;
int umin = 6;

struct Tk
{
    int type;
    int val;
};
typedef struct Tk Tk;

struct St
{
    Tk* v[MAX];
    int top;
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

int push(St *S, Tk *x)
{
    if(!isFull(S))
    {
        S->v[S->top] = x;
        S->top = S->top + 1;
        return 1;
    }
    else return 0;
}

Tk* pop(St *S) // take care while calling pop
{
    if(!isEmpty(S))
    {
        Tk* value = S->v[S->top - 1];
        S->top = S->top - 1;
        return value;
    }
    else return NULL;
}

Tk* top(St *S) // take care while calling top
{
    if(!isEmpty(S))
    {
        return S->v[S->top - 1];
    }
    else return NULL;
}


int max_size(char in[])
{
    // find number of tokens
    int size = 0;
    long int i = 0, j;
    while(in[i] != '\0')
    {
        if(in[i] != ' ') size++;
        i++;
    }
    return size;
}

Tk** tokenize(char in[], int size)
{

    Tk **tokens = (Tk**)malloc((size + 1) * sizeof(Tk*));
    
    // convert to tokens
    int i = 0;
    int j = 0;
    while(in[i] != '\0')
    {
        if('0' <= in[i] && in[i] <= '9')  // operand can be multi digit
        {
            tokens[j] = (Tk*)malloc(sizeof(Tk));
            tokens[j]->type = opd;
            char str_num[10] = {0};
            int p = 0;
            while(in[i] != ' ' && in[i] != '\0')
            {
                str_num[p] = in[i];
                i++;
                p++;
            }
            tokens[j]->val = atoi(str_num);
            j++;
        }
        else if(in[i] != ' ') // operators
        {
            tokens[j] = (Tk*)malloc(sizeof(Tk));
            tokens[j]->type = op;
            if(in[i] == '+')
                tokens[j]->val = plus;
            else if(in[i] == '-')
                tokens[j]->val = min;
            else if(in[i] == '*')
                tokens[j]->val = mul;
            else if(in[i] == '%')
                tokens[j]->val = mod;
            else if(in[i] == '/')
                tokens[j]->val = divi;
            else if(in[i] == '^')
                tokens[j]->val = pwf;
            else
                tokens[j]->val = umin;
            i++;
            j++;
        }
        else i++; // space
    }
    tokens[j] = NULL;
    return tokens;
}

Tk* operate(Tk *x, Tk *y, Tk *operation)
{
    Tk *z = (Tk*)malloc(sizeof(Tk));
    z->type = opd;
    if(operation->val == plus)
        z->val = x->val + y->val;
    else if(operation->val == min)
        z->val = x->val - y->val;
    else if(operation->val == mul)
        z->val = x->val * y->val;
    else if(operation->val == divi)
        z->val = x->val / y->val;
    else if(operation->val == mod)
        z->val = x->val % y->val;
    else if(operation->val == pwf)
    {
        double r = pow(x->val, y->val);
        r = round(r);
        z->val = (int)r;
    }
        
    return z;
}

void print_token(Tk *t)
{
    printf("%d ", t->val);
}

void evaluate(void)
{
    char in[MAX];
    fgets(in, MAX, stdin);
    if(in[strlen(in) - 1] == '\n') in[strlen(in) - 1] = '\0';
    
    int maxsize = max_size(in);
    Tk **tokens = tokenize(in, maxsize);
    // for(int i = 0; tokens[i] != NULL; i++)
    //     printf("%d ", tokens[i]->val);
    // printf("\n");  
    
    St *S = (St*)malloc(sizeof(St));
    S->top = 0;
    int i = 0;
    while(tokens[i] != NULL)
    {
        if(tokens[i]->type == opd)
            push(S, tokens[i]);
        else // operator
        {
            if(tokens[i]->val != umin)
            {
                Tk *r = pop(S);
                Tk *l = pop(S);
                Tk *z = operate(l, r, tokens[i]);
                push(S, z); // put the result on stack
            }
            else
            {
                top(S)->val = - top(S)->val;
            }
        }
        i++;
    }
    print_token(top(S));
    printf("\n");
}

int main(void)
{
    int T;
    scanf("%d", &T);
    getchar();
    for(int i = 0; i < T; i++)
        evaluate();
    return 0;
}