#include <iostream>
#include <queue>
#include<stdlib.h>
using namespace std;

struct state{//״̬��Ԫ��
    int x;
    int y;
    int z;
    int n;
};

struct point{//���ڵ㣬������ǰ״̬�Լ�����·��
    state s;
    queue<state> path;
};

queue<point> q;
void print_state(state s)//��ӡ״̬�ĺ���
{
    cout<<"("<<s.x<<","<<s.y<<","<<s.z<<")";
}
void print_path(point p)//��ӡ·���ĺ���
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
    q.push(start);//����ʼ״̬ѹ�����
    while(!q.empty())
    {
        point tmp_p = q.front();
        q.pop();
        //print_state(tmp_p.s);
        //system("pause");
        if((tmp_p.s.x==1&&tmp_p.s.y==1&&tmp_p.s.z==1)||(tmp_p.s.x==0&&tmp_p.s.y==0&&tmp_p.s.z==0))//���ΪĿ��ڵ����ӡ·����������չ�ڵ�
        {
            print_path(tmp_p);
            cout<<endl;
            continue;
        }
        if(tmp_p.s.n>=3)//�����������Ѿ�Ϊ3������չ
            continue;
        point r1, r2, r3;//��չ�������ڵ�
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
