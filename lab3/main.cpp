#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

float random01()//0-1֮��������������
{
    return rand()/float(RAND_MAX);
}

float cloudy = 0.5;//���Ƶĸ���
float sprinkle[2] = {0.1, 0.5};//sprinkle[0]��ʾ�ڶ���ʱ�򽽹�ĸ��ʣ�sprinkle[1]��ʾ��û�ж���ʱ����ĸ���
float rain[2] = {0.8, 0.2};//rain[0]��ʾ�ڶ��Ƶ�ʱ������ĸ��ʣ�rain[1]��ʾ��û�ж���ʱ����ĸ���
float wet[2][2];/*wet[0][0]��ʾsprinkle��rainʱwetgrass�ĸ��ʣ�
                  wet[0][1]��ʾsprinkle��δ����ʱwetgrass�ĸ��ʣ�
                  wet[1][0]��ʾδ������rainʱwetgrass�ĸ��ʣ�
                  wet[1][1]��ʾδ������δ����ʱwetgrass�ĸ��ʣ�*/


void print_sample(bool *a)//��ӡ����������Ԫ��
{
    cout<<a[0]<<' '<<a[1]<<' '<<a[2]<<' '<<a[3]<<endl;
}

bool *sample(int N)//���������������
{
    bool *a = new bool[4];//Ԥ������������Ԫ��,a[0]��ʾ�Ƿ���ƣ�a[1]��ʾ�Ƿ񽽹࣬a[2]��ʾ�Ƿ����꣬a[3]��ʾ�Ƿ��ʪ
    if (random01() < cloudy)//��������С�ڶ��Ƶĸ�������ƣ����򲻶���
    {
        a[0] = true;
    }
    else
    {
        a[0] = false;
    }

    if(a[0])//�ڶ��Ƶ�������ж��Ƿ񽽹������
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
    else//��δ���Ƶ�������ж�
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
    if (a[1])//�ڽ���������
    {
        if(a[2])//����
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
    else//��δ����������
    {
        if(a[2])//����
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
    int Cnum = 0;//ͳ�ƶ��ƵĴ���
    int Snum = 0;//ͳ�ƽ���Ĵ���
    int Rnum = 0;//ͳ������Ĵ���
    int Wnum = 0;//ͳ�Ʋ�ʪ�Ĵ���
    int SCnum = 0;//ͳ�ƶ����ҽ���Ĵ���
    int SNCnum = 0;//ͳ��δ�����ҽ���Ĵ���
    int RCnum = 0;//����������Ĵ���
    int RNCnum = 0;//δ����������Ĵ���
    int SRnum = 0;//����������Ĵ���
    int SNRnum = 0;//������δ����Ĵ���
    int NSRnum = 0;//δ����������Ĵ���
    int NSNRnum = 0;//δ������δ����Ĵ���
    int WSRnum = 0;//��ʪ�ҽ���������Ĵ���
    int WNSRnum = 0;//��ʪ��δ����������Ĵ���
    int WSNRnum = 0;//��ʪ�ҽ�����δ����Ĵ���
    int WNSNRnum = 0;//��ʪ��δ������δ����Ĵ���
    for (int i = 0;i < N;i++)//���������������ͳ�ƴ���
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
    cout<<"Cloudy:"<<(float)Cnum/N<<endl;//��ӡ������ʵĹ���ֵ
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
