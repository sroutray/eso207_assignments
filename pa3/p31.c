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
struct node 
{
    int hi;
    int lo;
    int max_hi;
    struct node *left;
    struct node *right;
    struct node *parent;
    struct node *left_hi;
    struct node *right_hi;
    struct node *parent_hi;
};
typedef struct node node;


node *create_node(int in_lo, int in_hi)
{
    node *new_node = (node *)malloc(sizeof(node));
    new_node->lo = in_lo;
    new_node->hi = in_hi;
    new_node->max_hi = in_hi;
    new_node->parent = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->parent_hi = NULL;
    new_node->left_hi = NULL;
    new_node->right_hi = NULL;
    return new_node;
}

void insert(node *root, node *root_hi, int in_lo, int in_hi)
{
    // lo based tree insertion position
    node *y = NULL;
    node *x = root;
    while(x)
    {
        if(in_lo < x->lo)
        {
            y = x;
            x = x->left;
        }
        else
        {
            y = x;
            x = x->right;
        }
    }
    // hi based tree insertion position
    node *y_hi = NULL;
    node *x_hi = root_hi;
    while(x_hi)
    {
        if(in_hi < x_hi->hi)
        {
            y_hi = x_hi;
            x_hi = x_hi->left_hi;
        }
        else
        {
            y_hi = x_hi;
            x_hi = x_hi->right_hi;
        }
    }
    // create new node
    node *new_node = create_node(in_lo, in_hi);
    if(!y && !y_hi)  // both trees are empty
    {
        root = new_node;
        root_hi = new_node;
    }
    else
    {
        // insert in root tree
        if(in_lo < y->lo)
        {
            y->left = new_node;
            y->left->parent = y;
            // fix max_hi all the way to root
            node *p = y;
            node *q = y->left;
            while(p && p->max_hi < q->max_hi)
            {
                p->max_hi = q->max_hi;
                q = p;
                p = p->parent;
            }
        }
        else
        {
            y->right = new_node;
            y->right->parent = y;
            // fix max_hi all the way to root
            node *p = y;
            node *q = y->right;
            while(p && p->max_hi < q->max_hi)
            {
                p->max_hi = q->max_hi;
                q = p;
                p = p->parent;
            }            
        }
        // insert in root_hi tree
        if(in_hi < y_hi->hi)
        {
            y_hi->left_hi = new_node;
            y_hi->left_hi->parent_hi = y_hi;
        }
        else
        {
            y_hi->right_hi = new_node;
            y_hi->right_hi->parent_hi = y_hi;
        }        
    }    
}

node *min(node *root, node *root_hi)
{
    node *x = root;
    while(x->left)
        x = x->left;
    return x;
}

node *max(node *root, node *root_hi)
{
    // node *x_hi = root_hi;
    // while(x_hi->right_hi)
    //     x_hi = x_hi->right_hi;
    // return x_hi;
    node *x = root;
    node *max_node = NULL;
    while(x && !max_node)
    {
        if(x->max_hi == x->hi)
            max_node = x;   // loop breaks after this
        else if(x->left && x->max_hi == x->left->max_hi)
            x = x->left;
        else    // we can go right without checking
            x = x->right;
    }
    return max_node;
}

node *lo_succ(node *root, node *root_hi, int in_lo, int in_hi)
{
    // search the corresponding node
    node *x = root;
    while(x && x->lo != in_lo)
    {
        if(x->lo < in_lo)
            x = x->right;
        else
            x = x->left;
    }
    if(x)
    {
        if(x->right)
        {
            // find min in tree rooted at x->right
            node *y = x->right;
            while(y->left)
                y = y->left;
            return y;
        }
        else
        {
            node *z = x;
            node *y = x->parent;
            while(y && z == y->right)
            {
                z = y;
                y = z->parent;
            }
            return y;
        }
    }
    else return NULL;
}

node *hi_succ(node *root, node *root_hi, int in_lo, int in_hi)
{
    // search the corresponding node
    node *x_hi = root_hi;
    while(x_hi && x_hi->hi != in_hi)
    {
        if(x_hi->hi < in_hi)
            x_hi = x_hi->right_hi;
        else
            x_hi = x_hi->left_hi;
    }
    if(x_hi)
    {
        if(x_hi->right_hi)
        {
            // find min in tree rooted at x_hi->right_hi
            node *y_hi = x_hi->right_hi;
            while(y_hi->left_hi)
                y_hi = y_hi->left_hi;
            return y_hi;
        }
        else
        {
            node *z_hi = x_hi;
            node *y_hi = x_hi->parent_hi;
            while(y_hi && z_hi == y_hi->right_hi)
            {
                z_hi = y_hi;
                y_hi = z_hi->parent_hi;
            }
            return y_hi;
        }
    }
    else return NULL;    
}

int is_overlap(node *root, node *root_hi, int in_lo, int in_hi)
{
    node *x = root;
    while(x && (x->hi <= in_lo || x->lo >= in_hi))
    {
        if(x->left && x->left->max_hi >= in_lo)
            x = x->left;
        else
            x = x->right;
    }
    if(x) return 1;
    else return 0;
}

void transplant(node *root, node *u, node *v)
{
    if(!u->parent)
        root = v;
    else if(u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if(v)
        v->parent = u->parent;
}

void transplant_hi(node *root_hi, node *u_hi, node *v_hi)
{
    if(!u_hi->parent_hi)
        root_hi = v_hi;
    else if(u_hi == u_hi->parent_hi->left_hi)
        u_hi->parent_hi->left_hi = v_hi;
    else
        u_hi->parent_hi->right_hi = v_hi;
    if(v_hi)
        v_hi->parent_hi = u_hi->parent_hi;    
}

void delete_node(node *root, node *root_hi, int in_lo, int in_hi)
{
    // search the corresponding node
    node *x = root;
    while(x && x->lo != in_lo)
    {
        if(x->lo < in_lo)
            x = x->right;
        else
            x = x->left;
    }
    if(!x) return;
    // delete in tree at root_hi
    if(!(x->left_hi))
        transplant_hi(root_hi, x, x->right_hi);
    else if(!(x->right_hi))
        transplant_hi(root_hi, x, x->left_hi);
    else
    {
        // find min in x.right_hi
        node *y_hi;
        node *p_hi = x->right_hi;
        while(p_hi)
        {
            y_hi = p_hi;
            p_hi = p_hi->left_hi;
        }
        // check if x is not y_hi parent
        if(y_hi->parent_hi != x)
        {
            transplant_hi(root_hi, y_hi, y_hi->right_hi);
            y_hi->right_hi = x->right_hi;
            y_hi->right_hi->parent_hi = y_hi;
        }
        transplant_hi(root_hi, x, y_hi);
        y_hi->left_hi = x->left_hi;
        y_hi->left_hi->parent_hi = y_hi;
    }
    // delete in tree at root
    node *z;    // z is the node form where corrections start
    if(!(x->left))
    {
        z = x->parent;
        transplant(root, x, x->right);
    }
    else if(!(x->right))
    {
        z = x->parent;
        transplant(root, x, x->left);
    }
    else
    {
        // find min in x.right
        node *y;
        node *p = x->right;
        while(p)
        {
            y = p;
            p = p->left;
        }
        // check if x is not y_hi parent
        z = y;
        if(y->parent != x)
        {
            z = y->parent;
            transplant(root, y, y->right);
            y->right = x->right;
            y->right->parent = y;
        }
        transplant(root, x, y);
        y->left = x->left;
        y->left->parent = y;
    }
    //  fix max_hi from z to root
    while(z)
    {
        int c = z->hi;
        int l = (!(z->left)) ? 0 : z->left->max_hi;
        int r =  (!(z->right)) ? 0 : z->right->max_hi;
        int out;
        if(c > l)
        {
            if(c > r)
                out = c;
            else
                out = r;
        }
        else
        {
            if(l > r)
                out = l;
            else
                out = r;
        }
        z->max_hi = out;
        z = z->parent;
    }
}

int main(void)
{
    int T;
    scanf("%d", &T);
    for(; T > 0; T--)
    {
        int N;
        scanf("%d", &N);
        node *root = NULL;
        node *root_hi = NULL;
        for(; N > 0; N--)
        {
            char op[20];
            scanf("\n%s\n", op);
            if(op[0] == 'm')
            {
                node *r;
                if(op[1] == 'i')
                    r = min(root, root_hi);
                else if(op[1] == 'a')
                    r = max(root, root_hi);
                printf("[%d %d]\n", r->lo, r->hi);
            }
            else
            {
                int in_lo, in_hi;
                scanf("%d %d", &in_lo, &in_hi);
                if(op[0] == '+')
                    insert(root, root_hi, in_lo, in_hi);
                else if(op[0] == '-')
                    delete_node(root, root_hi, in_lo, in_hi);
                else if(op[0] == 'l')
                {
                    node *r = lo_succ(root, root_hi, in_lo, in_hi);
                    if(r)
                        printf("[%d %d]\n", r->lo, r->hi);
                    else
                        printf("INVALID\n");
                }
                else if(op[0] == 'h')
                {
                    node *r = hi_succ(root, root_hi, in_lo, in_hi);
                    if(r)
                        printf("[%d %d]\n", r->lo, r->hi);
                    else
                        printf("INVALID\n");
                }
                else if(op[0] == 'o')
                {
                    int r = is_overlap(root, root_hi, in_lo, in_hi);
                    printf("%d\n", r);
                }
            }
        }

    }
    return 0;
}