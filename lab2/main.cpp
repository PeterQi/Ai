#include <iostream>
#include <queue>
#include<stdlib.h>
using namespace std;

struct state{//状态四元组
    int x;
    int y;
    int z;
    int n;
};

struct point{//树节点，包括当前状态以及已有路径
    state s;
    queue<state> path;
};

queue<point> q;
void print_state(state s)//打印状态的函数
{
    cout<<"("<<s.x<<","<<s.y<<","<<s.z<<")";
}
void print_path(point p)//打印路径的函数
{
    while(!p.path.empty())
    {
        state tmp_s = p.path.front();
        p.path.pop();
        print_state(tmp_s);
        if (!p.path.empty())
            cout<<" -> ";
    }
}
int main()
{
    point start;
    start.s = {1,1,0,0};
    start.path.push(start.s);
    q.push(start);//将初始状态压入队列
    while(!q.empty())
    {
        point tmp_p = q.front();
        q.pop();
        //print_state(tmp_p.s);
        //system("pause");
        if((tmp_p.s.x==1&&tmp_p.s.y==1&&tmp_p.s.z==1)||(tmp_p.s.x==0&&tmp_p.s.y==0&&tmp_p.s.z==0))//如果为目标节点则打印路径，不再拓展节点
        {
            print_path(tmp_p);
            cout<<endl;
            continue;
        }
        if(tmp_p.s.n>=3)//如果树的深度已经为3则不再拓展
            continue;
        point r1, r2, r3;//拓展的三个节点
        r1=tmp_p;
        r1.s.x = 1- r1.s.x;
        r1.s.n++;
        r1.path.push(r1.s);
        r2=tmp_p;
        r2.s.y = 1-r2.s.y;
        r2.s.n++;
        r2.path.push(r2.s);
        r3=tmp_p;
        r3.s.z = 1-r3.s.z;
        r3.s.n++;
        r3.path.push(r3.s);
        q.push(r1);
        q.push(r2);
        q.push(r3);
    }
    return 0;
}
