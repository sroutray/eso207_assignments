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

struct vertex
{
    int key;
    int d;  // discovery time
    int low;    
    int if_ap;  // if articulation point
    int parent; // parent in dfs tree
    int visited;    // if discovered by dfs 
};
typedef struct vertex vertex;

struct node
{
    vertex *v;
    struct node *next;
};
typedef struct node node;

struct list
{
    int V;
    node **adj;
};
typedef struct list list;

void addEdge(int p, int q, int M, vertex V[M], list *L, list *O);

int main(void)
{
    int M, N;
    scanf("%d%d", &M, &N);
    vertex V[M];
    list *L = (list *)malloc(sizeof(list));
    list *O = (list *)malloc(sizeof(list));
    // initialization
    L->V = M;
    L->adj = (node **)malloc(M * sizeof(node *));
    O->V = M;
    O->adj = (node **)malloc(M * sizeof(node *));
    for(int i = 0; i < M; i++)
    {
        V[i].key = i;
        V[i].d = -1;
        V[i].low = -1;
        V[i].if_ap = 0;
        V[i].parent = -1;
        V[i].visited = 0;

        L->adj[i] = NULL;
        O->adj[i] = NULL;
    }
    
    int p, q;
    node *p_node, *q_node, *pt1, *pt2;
    for(int i = 0; i < N; i++)
    {
        scanf("%d %d", &p, &q);
        
        p_node = (node *)malloc(sizeof(node));
        p_node->v = &V[p];
        pt1 = NULL;
        pt2 = L->adj[q];
        while(pt2 && pt2->v->key < p)
        {
            pt1 = pt2;
            pt2 = pt2->next;
        }
        if(pt1)
        {
            p_node->next = pt2;
            pt1->next = p_node;
        }
        else
        {
            p_node->next = L->adj[q];
            L->adj[q] = p_node;
        }
        
        q_node = (node *)malloc(sizeof(node));
        q_node->v = &V[q];
        pt1 = NULL;
        pt2 = L->adj[p];
        while(pt2 && pt2->v->key < q)
        {
            pt1 = pt2;
            pt2 = pt2->next;
        }
        if(pt1)
        {
            q_node->next = pt2;
            pt1->next = q_node;
        }
        else
        {
            q_node->next = L->adj[p];
            L->adj[p] = q_node;
        }
    }
    
    DFS(0, M, V, L, O);
    
    int if_empty = 1;
    for(int i = 0; i < M; i++)
    {
        if(V[i].if_ap)
        {
            printf("%d ", V[i].key);
            if_empty = 0;
        }
    }
    if(if_empty)
        printf("EMPTY");
    printf("\n");
    for(int i = 0; i < M; i++)
    {
        node *ptr = O->adj[i];
        while(ptr)
        {
            printf("%d %d\n", i, ptr->v->key);
            ptr = ptr->next;
        }
    }
    return 0;
}

void DFS(int v, int M, vertex V[M], list *L, list *O)
{
    static int t = 0;
    int children  = 0;
    V[v].visited = 1;
    V[v].d = t + 1;
    V[v].low = t + 1;
    t++;
    node *p = L->adj[v];
    while(p)
    {
        int u = p->v->key;
        if(V[u].visited == 0)
        {
            children++;
            V[u].parent = v;
            DFS(u, M, V, L, O);
            V[v].low = V[v].low > V[u].low ? V[u].low : V[v].low;

            if(V[v].parent == -1 && children > 1) // if v is root and articulation point
                V[v].if_ap = 1;
            else if(V[v].parent != -1 && V[u].low >= V[v].d)  // v is not root and child of v has higher low value
                V[v].if_ap = 1;
            
            // check for bridge
            if(V[u].low > V[v].d)
            {
                int m1, m2;
                m1 = v > u ? u : v;
                m2 = v > u ? v : u;
                node *o_node = (node *)malloc(sizeof(node));
                o_node->v = &V[m2];
                node *pt1 = NULL;
                node *pt2 = O->adj[m1];
                while(pt2 && pt2->v->key < m2)
                {
                    pt1 = pt2;
                    pt2 = pt2->next;
                }
                if(pt1)
                {
                    o_node->next = pt2;
                    pt1->next = o_node;
                }
                else
                {
                    o_node->next = O->adj[m1];
                    O->adj[m1] = o_node;
                }
            }
        }
        else if(V[u].key != V[v].parent)   // backedge if u is not parent of v
            V[v].low = V[v].low > V[u].d ? V[u].d : V[v].low;
            
        p = p->next;
    }
}