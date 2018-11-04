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

struct P
{
    int x;
    int y;
    int z;
    struct P *next;
};
typedef struct P P;

P *createP(int x, int y, int z);
void enqueue(P **next_list, P *curr_p, int next_level, int L1, int L2, int L3, int space[L1+1][L2+1][L3+1]);
void BFS(int L1, int L2, int L3, int S1, int S2, int S3, int space[L1+1][L2+1][L3+1]);

int main(void)
{
    int M;
    scanf("%d\n", &M);
    for(; M > 0; M--)
    {
        int L1, L2, L3, S1, S2, S3, N;
        scanf("%d %d %d\n", &L1, &L2, &L3);
        scanf("%d %d %d\n", &S1, &S2, &S3);
        scanf("%d\n", &N);
        int space[L1+1][L2+1][L3+1];
        for(int i = 0; i <= L1; i++)
            for(int j = 0; j <= L2; j++)
                for(int k = 0; k <= L3; k++)
                    space[i][j][k] = 0;
        BFS(L1, L2, L3, S1, S2, S3, space);
        for(int i = 0; i < N; i++)
        {
            int E1, E2, E3;
            scanf("%d %d %d\n", &E1, &E2, &E3);
            if(space[E1][E2][E3])
                printf("%d\n", space[E1][E2][E3]);
            else
                printf("%s\n", "IMPOSSIBLE");
        }
    }
    return 0;
}

P *createP(int x, int y, int z)
{
    P *node = (P *)malloc(sizeof(P));
    node->x = x;
    node->y = y;
    node->z = z;
    node->next = NULL;
    return node;
}

void insert(P **list, int x, int y, int z)
{
    P *new_p = createP(x, y, z);
    new_p->next = *list;
    *list = new_p;
}

void enqueue(P **next_list, P *curr_p, int next_level, int L1, int L2, int L3, int space[L1+1][L2+1][L3+1])
{
    int new_x, new_y, new_z;
    // throw x
    if(curr_p->x)   // check if x is already 0
    {
        new_x = 0;
        new_y = curr_p->y;
        new_z = curr_p->z;
        if(!space[new_x][new_y][new_z])
        {
            insert(next_list, new_x, new_y, new_z);
            space[new_x][new_y][new_z] = next_level;
        }
    }
    // throw y
    if(curr_p->y)   // check if x is already 0
    {
        new_x = curr_p->x;
        new_y = 0;
        new_z = curr_p->z;
        if(!space[new_x][new_y][new_z])
        {
            insert(next_list, new_x, new_y, new_z);
            space[new_x][new_y][new_z] = next_level;
        }
    }
    // throw z
    if(curr_p->z)   // check if z is already 0
    {
        new_x = curr_p->x;
        new_y = curr_p->y;
        new_z = 0;
        if(!space[new_x][new_y][new_z])
        {
            insert(next_list, new_x, new_y, new_z);
            space[new_x][new_y][new_z] = next_level;
        }
    }
    // exchange x to y
    if(curr_p->y != L2)     // check if y is already full
    {
        if(curr_p->x + curr_p->y > L2)
        {
            new_x = curr_p->x - (L2 - curr_p->y);
            new_y = L2;
            new_z = curr_p->z;
            if(!space[new_x][new_y][new_z])
            {
                insert(next_list, new_x, new_y, new_z);
                space[new_x][new_y][new_z] = next_level;
            }
        }
        else
        {
            new_x = 0;
            new_y = curr_p->x + curr_p->y;
            new_z = curr_p->z;
            if(!space[new_x][new_y][new_z])
            {
                insert(next_list, new_x, new_y, new_z);
                space[new_x][new_y][new_z] = next_level;
            }
        }
    }
    // exchange x to z
    if(curr_p->z != L3)     // check if z is already full
    {
        if(curr_p->x + curr_p->z > L3)
        {
            new_x = curr_p->x - (L3 - curr_p->z);
            new_y = curr_p->y;
            new_z = L3;
            if(!space[new_x][new_y][new_z])
            {
                insert(next_list, new_x, new_y, new_z);
                space[new_x][new_y][new_z] = next_level;
            }
        }
        else
        {
            new_x = 0;
            new_y = curr_p->y;
            new_z = curr_p->x + curr_p->z;
            if(!space[new_x][new_y][new_z])
            {
                insert(next_list, new_x, new_y, new_z);
                space[new_x][new_y][new_z] = next_level;
            }
        }
    }
    // exchange y to z
    if(curr_p->z != L3)     // check if z is already full
    {
        if(curr_p->y + curr_p->z > L3)
        {
            new_x = curr_p->x;
            new_y = curr_p->y - (L3 - curr_p->z);
            new_z = L3;
            if(!space[new_x][new_y][new_z])
            {
                insert(next_list, new_x, new_y, new_z);
                space[new_x][new_y][new_z] = next_level;
            }
        }
        else
        {
            new_x = curr_p->x;
            new_y = 0;
            new_z = curr_p->y + curr_p->z;
            if(!space[new_x][new_y][new_z])
            {
                insert(next_list, new_x, new_y, new_z);
                space[new_x][new_y][new_z] = next_level;
            }
        }
    }
    // exchange y to x
    if(curr_p->x != L1)     // check if x is already full
    {
        if(curr_p->x + curr_p->y > L1)
        {
            new_x = L1;
            new_y = curr_p->y - (L1 - curr_p->x);
            new_z = curr_p->z;
            if(!space[new_x][new_y][new_z])
            {
                insert(next_list, new_x, new_y, new_z);
                space[new_x][new_y][new_z] = next_level;
            }
        }
        else
        {
            new_x = curr_p->x + curr_p->y;
            new_y = 0;
            new_z = curr_p->z;
            if(!space[new_x][new_y][new_z])
            {
                insert(next_list, new_x, new_y, new_z);
                space[new_x][new_y][new_z] = next_level;
            }
        }
    }
    // exchange z to x
    if(curr_p->x != L1)     // check if x is already full
    {
        if(curr_p->x + curr_p->z > L1)
        {
            new_x = L1;
            new_y = curr_p->y;
            new_z = curr_p->z - (L1 - curr_p->x);
            if(!space[new_x][new_y][new_z])
            {
                insert(next_list, new_x, new_y, new_z);
                space[new_x][new_y][new_z] = next_level;
            }
        }
        else
        {
            new_x = curr_p->x + curr_p->z;
            new_y = curr_p->y;
            new_z = 0;
            if(!space[new_x][new_y][new_z])
            {
                insert(next_list, new_x, new_y, new_z);
                space[new_x][new_y][new_z] = next_level;
            }
        }
    }
    // exchange z to y
    if(curr_p->y != L2)     // check if z is already full
    {
        if(curr_p->y + curr_p->z > L2)
        {
            new_x = curr_p->x;
            new_y = L2;
            new_z = curr_p->z - (L2 - curr_p->y);
            if(!space[new_x][new_y][new_z])
            {
                insert(next_list, new_x, new_y, new_z);
                space[new_x][new_y][new_z] = next_level;
            }
        }
        else
        {
            new_x = curr_p->x;
            new_y = curr_p->y + curr_p->z;
            new_z = 0;
            if(!space[new_x][new_y][new_z])
            {
                insert(next_list, new_x, new_y, new_z);
                space[new_x][new_y][new_z] = next_level;
            }
        }
    }
}

void BFS(int L1, int L2, int L3, int S1, int S2, int S3, int space[L1+1][L2+1][L3+1])
{
    P *curr_list = NULL;
    P *next_list = NULL;
    int curr_level = 1;
    int next_level = 2;
    int px = S1;
    int py = S2;
    int pz = S3;
    insert(&curr_list, px, py, pz);
    space[px][py][pz] = 1;
    while(curr_list)
    {
        P *curr_p = curr_list;
        while(curr_p)
        {
            enqueue(&next_list, curr_p, next_level, L1, L2, L3, space);
            curr_p = curr_p->next;
        }
        curr_list = next_list;
        next_list = NULL;
        curr_level = next_level;
        next_level = next_level + 1;
    }
}
