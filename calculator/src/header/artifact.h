#ifndef ARTIFACT
#define ARTIFACT
#include"modifier.h"
double toArtifactDomain(int n,const int* need,double (*access_suit)(State_modifier result));//刷n次，传评价函数，评价函数传StateModifier————主副词条，套装效果在外部设定

class Artifact
{
private:
    static const string index_posi[5];//圣遗物位置目录
    //圣遗物主/副词条目录沿用modifier的前19个，前10为副词条
    //19个主词条，前10个兼副词条
    static int sub_weight[10];//副词条分布
    static int main_weight[5][19];
    
    static double main_addState[19];//平均值
    static double sub_addState[10];

    //int star;//星级
    //string suit;
    int suit;//套装类型，目前用0,1,2表示其他，套装1，套装2
    int position;//位置
    int main_stat;//主词条,用index
    int sub_stat[10];//10个副词条
    //int level;

    State_modifier Artifact_modifier;//对人物属性的影响
public:
    static int trans_posi(string);
    static string trans_posi(int);//翻译位置和词条
    Artifact();//默认随机生成
    Artifact(int suit,int position=-1);//指定套装
    void random_reset();
    void update_modifier();

    void random_suit();
    void random_posi();
    void random_main();
    void random_sub();
    void random_upgrade();//随机升级，20%5次，80%4次

    void print();
};
#endif