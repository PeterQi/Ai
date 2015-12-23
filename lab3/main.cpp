#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

float random01()//0-1之间产生浮点随机数
{
    return rand()/float(RAND_MAX);
}

float cloudy = 0.5;//多云的概率
float sprinkle[2] = {0.1, 0.5};//sprinkle[0]表示在多云时候浇灌的概率，sprinkle[1]表示在没有多云时浇灌的概率
float rain[2] = {0.8, 0.2};//rain[0]表示在多云的时候下雨的概率，rain[1]表示在没有多云时下雨的概率
float wet[2][2];/*wet[0][0]表示sprinkle且rain时wetgrass的概率；
                  wet[0][1]表示sprinkle且未下雨时wetgrass的概率；
                  wet[1][0]表示未浇灌且rain时wetgrass的概率；
                  wet[1][1]表示未浇灌且未下雨时wetgrass的概率；*/


void print_sample(bool *a)//打印样本数据四元组
{
    cout<<a[0]<<' '<<a[1]<<' '<<a[2]<<' '<<a[3]<<endl;
}

bool *sample(int N)//样本随机产生函数
{
    bool *a = new bool[4];//预设样本数据四元组,a[0]表示是否多云，a[1]表示是否浇灌，a[2]表示是否下雨，a[3]表示是否草湿
    if (random01() < cloudy)//如果随机数小于多云的概率则多云，否则不多云
    {
        a[0] = true;
    }
    else
    {
        a[0] = false;
    }

    if(a[0])//在多云的情况下判断是否浇灌和下雨
    {
        if (random01() < sprinkle[0])
        {
            a[1] = true;
        }
        else
        {
            a[1] = false;
        }
        if (random01() < rain[0])
        {
            a[2] =true;
        }
        else
        {
            a[2] = false;
        }
    }
    else//在未多云的情况下判断
    {
        if (random01() < sprinkle[1])
        {
            a[1] = true;
        }
        else
        {
            a[1] = false;
        }
        if (random01() < rain[1])
        {
            a[2] =true;
        }
        else
        {
            a[2] = false;
        }
    }
    if (a[1])//在浇灌的情况下
    {
        if(a[2])//下雨
        {
            if (random01() < wet[0][0])
            {
                a[3] = true;
            }
            else
            {
                a[3] = false;
            }
        }
        else
        {
            if (random01() <wet[0][1])
            {
                a[3] = true;
            }
            else
            {
                a[3] = false;
            }
        }
    }
    else//在未浇灌的情况下
    {
        if(a[2])//下雨
        {
            if (random01() < wet[1][0])
            {
                a[3] = true;
            }
            else
            {
                a[3] = false;
            }
        }
        else
        {
            if (random01() <wet[1][1])
            {
                a[3] = true;
            }
            else
            {
                a[3] = false;
            }
        }
    }
    //print_sample(a);
    return a;
}

int main()
{
    srand((unsigned)time(NULL));
    random01();
    wet[0][0] = 0.99;
    wet[0][1] = 0.9;
    wet[1][0] = 0.9;
    wet[1][1] = 0.0;
    int N = 10000;
    bool *b = sample(N);
    bool **dataset = new bool *[N];
    int Cnum = 0;//统计多云的次数
    int Snum = 0;//统计浇灌的次数
    int Rnum = 0;//统计下雨的次数
    int Wnum = 0;//统计草湿的次数
    int SCnum = 0;//统计多云且浇灌的次数
    int SNCnum = 0;//统计未多云且浇灌的次数
    int RCnum = 0;//多云且下雨的次数
    int RNCnum = 0;//未多云且下雨的次数
    int SRnum = 0;//浇灌且下雨的次数
    int SNRnum = 0;//浇灌且未下雨的次数
    int NSRnum = 0;//未浇灌且下雨的次数
    int NSNRnum = 0;//未浇灌且未下雨的次数
    int WSRnum = 0;//草湿且浇灌且下雨的次数
    int WNSRnum = 0;//草湿且未浇灌且下雨的次数
    int WSNRnum = 0;//草湿且浇灌且未下雨的次数
    int WNSNRnum = 0;//草湿且未浇灌且未下雨的次数
    for (int i = 0;i < N;i++)//生成随机样本，并统计次数
    {
        dataset[i] = sample(N);
        //print_sample(dataset[i]);
        if (dataset[i][0])
        {
            Cnum ++;
            if (dataset[i][1])
                SCnum ++;
            if (dataset[i][2])
                RCnum ++;
        }
        else
        {
            if (dataset[i][1])
                SNCnum ++;
            if (dataset[i][2])
                RNCnum ++;
        }

        if (dataset[i][1])
            Snum ++;
        if (dataset[i][2])
            Rnum ++;
        if (dataset[i][3])
            Wnum ++;
        if (dataset[i][1])
        {
            if(dataset[i][2])
            {
                SRnum ++;
                if(dataset[i][3])
                    WSRnum ++;
            }
            else
            {
                SNRnum ++;
                if(dataset[i][3])
                    WSNRnum ++;
            }
        }
        else
        {
            if(dataset[i][2])
            {
                NSRnum ++;
                if(dataset[i][3])
                    WNSRnum ++;
            }
            else
            {
                NSNRnum ++;
                if(dataset[i][3])
                    WNSNRnum ++;
            }
        }
    }
    cout<<"N:"<<N<<endl;
    cout<<"Cloudy:"<<(float)Cnum/N<<endl;//打印各类概率的估计值
    cout<<"Sprinkle | Cloudy:"<<(float)SCnum/Cnum<<endl;
    cout<<"Sprinkle | !Cloudy:"<<(float)SNCnum/(N-Cnum)<<endl;
    cout<<"Rain | Cloudy:"<<(float)RCnum/Cnum<<endl;
    cout<<"Rain | !Cloudy:"<<(float)RNCnum/(N-Cnum)<<endl;
    cout<<"WetGrass | Sprinkle && Rain:"<<(float)WSRnum/SRnum<<endl;
    cout<<"WetGrass | Sprinkle && !Rain:"<<(float)WSNRnum/SNRnum<<endl;
    cout<<"WetGrass | !Sprinkle && Rain:"<<(float)WNSRnum/NSRnum<<endl;
    cout<<"WetGrass | !Sprinkle && !Rain:"<<(float)WNSNRnum/NSNRnum<<endl;






    return 0;
}
