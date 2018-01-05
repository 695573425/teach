#include <iostream>

using namespace std;

/*��������ʽa,b����㷨��������ʽb��Ϊ���ɵ���ʽ�ֱ������ʽa��˵õ��µĶ���ʽ��
  �ٽ��õ������ɶ���ʽ��ӣ����ɵõ�����ʽ��˽����*/


struct polynode{
    int coef;
    int exp;
    polynode *next;
};
typedef polynode *polynomial;

polynomial attch(int c,int e,polynomial m)              //����һ���µ���ʽ������������d��ָ�ڵ�֮��
{
    polynomial x;
    x = new polynode;
    x->coef = c;
    x->exp  = e;
    m->next = x;
    return x;
}

polynomial add(polynomial a, polynomial b)              //��������ʽ����㷨
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

polynomial multiply_1(polynomial a, polynomial b)       //����ʽa�뵥��ʽb����㷨
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

polynomial multiply(polynomial a, polynomial b)         //��������ʽ����㷨
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
    cout<<"����������ʽ���"<<endl;
    cout<<"�����һ������ʽ�������������ϵ��ָ����������ָ��Ϊ0�����޳������0��0��β����"<<endl;
    do{
        cin>>x>>y;
        if ((x!=0)&&(y!=0))
        p = attch(x,y,p);
    }while(y!=0);
    p->next = NULL;

    cout<<"����ڶ�������ʽ�������������ϵ��ָ����������ָ��Ϊ0�����޳������0��0��β����"<<endl;
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
