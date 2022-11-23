#include<iostream>
#include<fstream>
using namespace std;

#include".\header\artifact.h"
#include".\header\chara.h"

/*Chara*/
const double Chara::ascension_basic[7]={0,38/182,65/182,101/182,128/182,155/182,1};
int Chara::ascension_add[7]={0,0,1,2,2,3,4};
void Chara::initialize()
{
    ifstream level_file(".\\data\\level.csv",ios::in);
        char key;
        while(!level_file.eof())
        {
            int i;
            level_file>>i>>key;
            level_file>>scale[0][i-1]>>key>>scale[1][i-1];
        }
        level_file.close();
}//初始化只执行一次
void Chara::set_3basic()
{
    double scalor=BasicScale();
    atk=atk_1*scalor;
    def=def_1*scalor;
    hp=hp_1*scalor;
}
double Chara::BasicScale()
{
    switch (star)
    {
    case 4:
        return scale[star-4][level-1]+ascension_basic[ascension]*fourBasicScale;

    case 5:
        return scale[star-4][level-1]+ascension_basic[ascension]*fiveBasicScale;
    
    default:
        cout<<"erro in BasicScale";
        exit(0);
    }
}//基础属性系数，在1级属性上改
void Chara::set_level(int x)
{
    level=x;
    set_3basic();
}
void Chara::set_ascension(int x)
{
    ascension=x;
    set_3basic();
}
void Chara::to_level(string a)
{
    int lv=0,lv_m=0;//分割出的俩数
    for(int i=0;i<a.length();++i)
    {
        if(a[i]=='/')
            {
                for(int j=i-1,k=1;j>=0;--j,k*=10)
                {
                    if(a[j]>='0'&&a[j]<='9')
                        lv+=(a[j]-'0')*k;
                }
                for(int j=a.length()-1,k=1;j>i;--j,k*=10)
                {
                    if(a[j]>='0'&&a[j]<='9')
                        lv_m+=(a[j]-'0')*k;
                }
            }
    }

}
Chara::Chara()//初始化
{
    
}

void Chara::set_score()
{
    cout<<"利用角色属性设置\n请按照角色属性对照表输入(目前只能设定一种评判标准):\n";//目前手动添加，后续再支持测特定招式伤害
    /*for (int i = 0;i < count; i++)
    {
        
    }
    */
    cin>>assessment;
}