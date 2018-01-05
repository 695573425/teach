#include <iostream>

using namespace std;

struct node{
    node *ltree;
    node *rtree;
    node *parent;
    char data;
};
typedef node *Btree;




bool isCompleteBT(Btree root)   //判断是否为完全二叉树
{
    Btree Q[100];
    Btree q;
    int fron,rear,tap;
    fron = rear = 0;
    if (root==NULL)
        return true;
    Q[++rear] = root;
    while(Q[rear]!=NULL)
    {
        q = Q[++fron];
        if (q->ltree!=NULL)
            Q[++rear] = q->ltree;
        else
        {
            Q[++rear] = NULL;
            tap = 1;
            break;
        }
        if (q->rtree!=NULL)
            Q[++rear] = q->rtree;
        else
        {
            Q[++rear] = NULL;
            tap = 2;
            break;
        }
    }
    for(fron;fron<rear;fron++)
    {
        q = Q[fron];
        switch(tap)
        {
            case 1:{
                if(q->ltree!=NULL || q->rtree!=NULL)
                    return false;
            }
            case 2: tap = 1;
        }
    }
    return true;
}


Btree* co_parent(Btree p, Btree q)     //返回任意节点的公共祖先的集合
{
    Btree *Q;
    Btree temp[10];
    Btree x,y;
    x=p;y=q;
    int len,i,j,k;
    len = j = 0;
    while(x->parent != NULL)
    {
        temp[len++] = x->parent;
        x = x->parent;
    }
    while(y->parent != NULL)
    {
        for(i=0;i<len;i++)
        {
            if(temp[i] == y->parent)
            {
                for(k=i;k<len;k++)
                    Q[j++] = temp[k];
                return Q;
            }
        }
        y = y->parent;
    }
    return NULL;
}

int main()
{

    return 0;
}
