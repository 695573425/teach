#include <iostream>

using namespace std;

/*两个多项式a,b相乘算法：将多项式b分为若干单项式分别与多项式a相乘得到新的多项式，
  再将得到的若干多项式相加，即可得到多项式相乘结果。*/


struct polynode{
    int coef;
    int exp;
    polynode *next;
};
typedef polynode *polynomial;

polynomial attch(int c,int e,polynomial m)              //建立一个新单项式，并把它链到d所指节点之后
{
    polynomial x;
    x = new polynode;
    x->coef = c;
    x->exp  = e;
    m->next = x;
    return x;
}

polynomial add(polynomial a, polynomial b)              //两个多项式相加算法
{
    polynomial p,q,d,c;
    int x;
    p = a->next;
    q = b->next;
    c = new polynode;
    d = c;

    while ((p!=NULL)&&(q!=NULL))
    {
        if (p->exp > q->exp)
        {
            d = attch(p->coef, p->exp ,d);
            p = p->next;
        }
        else if (p->exp < q->exp)
        {
            d = attch(q->coef, q->exp ,d);
            q = q->next;
        }
        else
        {
            x = p->coef + q->coef;
            if(x) d = attch(x, p->exp, d);
            p = p->next;
            q = q->next;
        }

    }

    while(p!=NULL)
    {
        d = attch(p->coef, p->exp, d);
        p = p->next;
    }

    while(q!=NULL)
    {
        d = attch(q->coef, q->exp, d);
        q = q->next;
    }

    d->next = NULL;
    p = c;
    delete p;
    return c;
}

polynomial multiply_1(polynomial a, polynomial b)       //多项式a与单项式b相乘算法
{
    polynomial p, q, c;
    int x, y;
    p = a->next;
    c = new polynode;
    q = c;
    while(p!=NULL)
    {
        x = p->coef * b->coef;
        y = p->exp + b->exp;
        q = attch(x,y,q);
        p = p->next;
    }
    q->next = NULL;

    return c;
}

polynomial multiply(polynomial a, polynomial b)         //两个多项式相乘算法
{
    polynomial q, c;
    q = b->next;
    if (q!=NULL)
    {
        c = multiply_1(a,q);
        q = q->next;
    }
    while (q!=NULL)
    {
        c = add(c,multiply_1(a,q));
        q = q->next;
    }

    return c;

}
int main()
{

    polynomial a,b,c,p,q,m;
    int x,y;
    a = new polynode;
    b = new polynode;
    m = new polynode;
    p = a;
    q = b;
    c = m;
/*
    cout<<"求两个多项式相乘"<<endl;
    cout<<"输入第一个多项式（依次输入各项系数指数，常数项指数为0，若无常数项，以0，0结尾）："<<endl;
    do{
        cin>>x>>y;
        if ((x!=0)&&(y!=0))
        p = attch(x,y,p);
    }while(y!=0);
    p->next = NULL;

    cout<<"输入第二个多项式（依次输入各项系数指数，常数项指数为0，若无常数项，以0，0结尾）："<<endl;
    do{
        cin>>x>>y;
        if ((x!=0)&&(y!=0))
        q = attch(x,y,q);
    }while(y!=0);
    q->next = NULL;



    c = multiply(a,b);
    m = c->next;
    while (m!=NULL)
    {
        cout<<m->coef<<"x^"<<m->exp;
        m = m->next;
        if (m!=NULL)
            cout<<" + ";
        else
            cout<<endl;
    }
*/
    p = attch(1,2,p);
    p = attch(2,3,p);
    p->next = NULL;
    delete a;
    q = attch(3,3,q);
    q = attch(4,5,q);
    q = attch(5,6,q);
    q = attch(9,3,q);


    cout<<a->next<<endl;
    cout<<b->next->next<<endl;
    cout<<m->next->coef<<endl;

    return 0;
}
