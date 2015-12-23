#include <iostream>
#include <time.h>
#include <stdlib.h>
#define N 10000
using namespace std;

float random01()
{
    return rand()/float(RAND_MAX);
}

float cloudy = 0.5;
float sprinkle[2] = {0.1, 0.5};
float rain[2] = {0.8, 0.2};
float wet[2][2];


void print_sample(bool *a)
{
    cout<<a[0]<<' '<<a[1]<<' '<<a[2]<<' '<<a[3]<<endl;
}

bool *sample()
{
    bool *a = new bool[4];
    if (random01() < cloudy)
    {
        a[0] = true;
    }
    else
    {
        a[0] = false;
    }

    if(a[0])
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
    else
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
    if (a[1])
    {
        if(a[2])
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
    else
    {
        if(a[2])
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

    bool *b = sample();
    bool **dataset = new bool *[N];
    int Cnum = 0;
    int Snum = 0;
    int Rnum = 0;
    int Wnum = 0;
    int SCnum = 0;
    int SNCnum = 0;
    int RCnum = 0;
    int RNCnum = 0;
    int SRnum = 0;
    int SNRnum = 0;
    int NSRnum = 0;
    int NSNRnum = 0;
    int WSRnum = 0;
    int WNSRnum = 0;
    int WSNRnum = 0;
    int WNSNRnum = 0;
    for (int i = 0;i < N;i++)
    {
        dataset[i] = sample();
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

    cout<<"Cloudy:"<<(float)Cnum/N<<endl;
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
