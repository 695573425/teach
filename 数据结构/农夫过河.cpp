#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;


struct Crossing{                  //以二进制位表示4者各自所在岸，0为北岸，1为南岸，则以4位二进制位表示4者所在岸，故有16种可能状态
    int condition[16][16];        //将4位二进制转化为10进制数，则数组下标即位对应状态，例如：4：0100表示狼在南岸，其余在北岸
    int solution[100];             //condition 为状态转换，内容为一个状态到另一状态的方式    solution为过河方案
};
typedef Crossing *Cross;

void build_state(Cross G)
{
    int i,j,k;
    for(i=0;i<16;i++)
    {
        if(i==3||i==6||i==7||i==8||i==9||i==12)       //按题目要求，状态3，6，7，8，9，12是不允许的
        {
            for(j=0;j<16;j++)
                G->condition[i][j] = -1;
        }
        else
            G->condition[i][i] = 0;
    }

    for(i=0;i<16;i++)
    {
        if(G->condition[i][i] == 0)
        {
            for(j=0;j<16;j++)
            {
                if(j!=i){
                if(G->condition[j][j] == 0)
                {
                    k=(int)fabs(j-i);
                    switch(k)
                    {
                        case 8:G->condition[i][j]=1;break;      //表示农夫不带任何东西过河
                        case 9:G->condition[i][j]=4;break;      //表示农夫带菜过河
                        case 10:G->condition[i][j]=3;break;     //表示农夫带羊过河
                        case 12:G->condition[i][j]=2;break;     //表示农夫带狼过河
                        default:G->condition[i][j]=-1;break;
                    }
                }
                else
                    G->condition[i][j]=-1;
            }}
        }
    }
    G->condition[1][10]=-1;           //特例处理
    G->condition[10][1]=-1;
    G->condition[5][14]=-1;
    G->condition[14][5]=-1;
    cout<<"     0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 "<<endl;
    for(i=0;i<16;i++)
    {
        cout<<setw(3)<<i;
        for(j=0;j<16;j++)
            cout<<setw(3)<<G->condition[i][j];
        cout<<endl;
    }

    for(i=0;i<10;i++)
        G->solution[i]=0;
}

bool visited[16];
int Cross_solution(Cross G,int i,int j,int n)
{
    int k,m;
    if(i==j)
        return 1;
    else
    {
        visited[i]=true;
        for(k=0;k<16;k++)
        {
            if(G->condition[i][k]>0)
            {
                if(!visited[k])
                {
                    G->solution[n++]=G->condition[i][k];
                    m=Cross_solution(G,k,j,n);
                    if(m==1)
                        return 1;
                    else if(m==0)
                        return 0;
                    visited[k]= false;
                }
            }
        }
    }
    if(!visited[i])
    {
        G->solution[0]=0;
        return 0;
    }
}
int main()
{
    int i,j,k;
    j=0;
    Cross G;
    G=new Crossing;
    cout<<"状态转换表："<<endl;
    build_state(G);
    for(i=0;i<16;i++)
        visited[i]=false;
    k=Cross_solution(G,0,15,0);
    cout<<"农夫过河方案如下：（1/2/3/4分别表示农夫不带东西/带狼/带羊/带菜到对岸）"<<endl;
    if(G->solution[j]==0)
        cout<<"无解"<<endl;
    while(G->solution[j]>0)
        cout<<G->solution[j++]<<endl;

    return 0;
}
