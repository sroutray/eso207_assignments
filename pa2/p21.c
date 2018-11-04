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
#include <string.h>

#define MAX 10000

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
// define parantheses type
int par = 3;
int opar = 1;
int cpar = 2;
// define precedence
int prec[7] = {1, 1, 2, 3, 3, 4, 5};
// define associativity
int asso[7] = {1, 1, 1, 1, 1, 2, 1}; // 1 = LR, 2 = RL
int lr = 1;
int rl = 2;

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
    int i = 0, j;
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
        else if('(' <= in[i] && in[i] <= ')') // parantheses
        {
            tokens[j] = (Tk*)malloc(sizeof(Tk));
            tokens[j]->type = par;
            tokens[j]->val = in[i] - '(' + 1;
            i++;
            j++;
        }
        else if(in[i] != ' ') // operators
        {
            tokens[j] = (Tk*)malloc(sizeof(Tk));
            tokens[j]->type = op;
            if(in[i] == '+')
                tokens[j]->val = plus;
            else if(in[i] == '*')
                tokens[j]->val = mul;
            else if(in[i] == '%')
                tokens[j]->val = mod;
            else if(in[i] == '/')
                tokens[j]->val = divi;
            else if(in[i] == '^')
                tokens[j]->val = pwf;
            else
            {
                if(j == 0) // starting expression with unary minus
                    tokens[j]->val = umin;
                else if(tokens[j - 1]->type == op) // preceded by operator
                    tokens[j]->val = umin;
                else if(tokens[j - 1]->type == par && tokens[j - 1]->val == opar) // preceded by opening parantheses 
                    tokens[j]->val = umin;
                else
                    tokens[j]->val = min;
            }
            i++;
            j++;
        }
        else i++; // space
    }
    tokens[j] = NULL;
    return tokens;
}

void print_token(Tk *t)
{
    if(t->type == opd)
        printf("%d ", t->val);
    else if(t->type == par)
    {
        char p = t->val + '(' - 1;
        printf("%c ", p);
    }
    else
    {
        if(t->val == plus)
            printf("%c ", '+');
        else if(t->val == min)
            printf("%c ", '-');
        else if(t->val == mul)
            printf("%c ", '*');
        else if(t->val == mod)
            printf("%c ", '%');
        else if(t->val == divi)
            printf("%c ", '/');
        else if(t->val == pwf)
            printf("%c ", '^');
        else if(t->val == umin)
            printf("%c ", '~');
    }
}

void run(void)
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
    int j = 0;
    int INVALID = 0;
    Tk* out[maxsize];
    while(tokens[i] != NULL)
    {
        if(tokens[i]->type == opd)
        {
            if(i == 0)  // first element
            {
                out[j] = tokens[i];
                j++;
            }
            else if(tokens[i - 1]->type == opd) // operand precedes operand
            {
                INVALID = 1;
                break;
            }
            else if(tokens[i - 1]->type == par && tokens[i - 1]->val == cpar) // closing parantheses precedes operand
            {
                INVALID = 1;
                break;
            }
            else
            {
                out[j] = tokens[i];
                j++;
            }
        }
        else if(tokens[i]->type == op)
        {
            if(tokens[i]->val != umin) // unary minus can never make invalid
            {
                if(i == 0 || tokens[i + 1] == NULL) // dangling binary operators
                {
                    INVALID = 1;
                    break;
                }
                else if(tokens[i - 1]->type == op) // operator before a binary operator
                {
                    INVALID = 1;
                    break;
                }
                else if(tokens[i - 1]->type == par && tokens[i - 1]->val == opar)
                // opening parantheses before a binary operator
                {
                    INVALID = 1;
                    break;
                }
            }
            // implement stack
            while(1)
            {
                if(isEmpty(S) || (top(S)->type == par && top(S)->val == opar))
                // stack becomes empty or has (
                {
                    push(S, tokens[i]);
                    break;
                }
                else if(prec[top(S)->val] > prec[tokens[i]->val])
                // stack top operator has higher precedence
                {
                    out[j] = pop(S);
                    j++;
                    continue;
                }
                else if(prec[top(S)->val] == prec[tokens[i]->val] && asso[tokens[i]->val] == lr)
                // same precedence LR associativity
                {
                    out[j] = pop(S);
                    j++;
                    push(S, tokens[i]);
                    break;
                }
                else if(prec[top(S)->val] == prec[tokens[i]->val] && asso[tokens[i]->val] == rl)
                // same precedence RL associativity
                {
                    push(S, tokens[i]);
                    break;
                }
                else
                // stack top has lower precedence
                {
                    push(S, tokens[i]);
                    break;
                }
            }    
        }
        else // parantheses
        {
            if(tokens[i]->val == opar && i != 0) 
            {
                if(tokens[i - 1]->type == opd) // operand before opening parantheses
                {
                    INVALID = 1;
                    break;
                }
                else if(tokens[i - 1]->type == par && tokens[i - 1]->val == cpar)
                // closing parantheses before opening parantheses
                {
                    INVALID = 1;
                    break;
                }
            }
            else if(tokens[i]->val == cpar) 
            {
                if(i == 0) // starts with closed parantheses
                {
                    INVALID = 1;
                    break;
                }
                else if(tokens[i - 1]->type == op) // operator before closed parantheses
                {
                    INVALID = 1;
                    break;
                }
                else if(tokens[i - 1]->type == par && tokens[i - 1]->val == opar)
                // open parantheses before closed parantheses
                {
                    INVALID = 1;
                    break;
                }
            }
            // implement stack
            if(tokens[i]->val == opar)
                push(S, tokens[i]);
            else // token is closed parantheses
            {
                while(1)
                {
                    if(isEmpty(S)) // no open parantheses found
                    {
                        INVALID = 1;
                        break;
                    }
                    else if(top(S)->type == par && top(S)->val == opar) // matching open parantheses found
                    {
                        pop(S);
                        break;
                    }
                    else // between parantheses
                        out[j] = pop(S);
                        j++;
                }
                if(INVALID) break;
            }
        }
        i++;
    }
    
    if(INVALID)
    {
        printf("INVALID\n");
        return;
    }
    while(!isEmpty(S))
    {
        if(top(S)->type == par)  // unmatched parantheses found
        {
            INVALID = 1;
            break;
        }
        else
        {
            out[j] = pop(S);
            j++;
        }
    }
    if(INVALID)
    {
        printf("INVALID\n");
        return;
    }
    else
    {
        out[j] = NULL;
        for(int k = 0; out[k] != NULL; k++)
        {
            print_token(out[k]);
        }
        printf("\n");
    }
}

int main(void)
{
    int T;
    scanf("%d", &T);
    getchar();
    for(int i = 0; i < T; i++)
        run();
    return 0;
}