#ifndef CHARA
#define CHARA
#include<iostream>
using namespace std;

#include "modifier.h"
#include "damageCalculator.h"
#include "monster.h"
int dmgsource(string a);//根据目录翻译伤害来源
string dmgsource(int a);
int dmgtype(string a);//根据目录翻译伤害属性
string dmgtype(int a);
/*
class Talent
{
private:
    
public:
    
};
*/

//buff分类：属性修正、伤害修正
//都有：直接加，基于xx加
class Buff//储存属性buff名，buff更改的属性，buff内部分基础区和额外区
{
public:
    string buff_name;
    State_modifier *ptr;//state类型指针，指向一种“属性改变方式”————随时可能改变
};
/*buff跟角色或武器或环境buff，储存在对应位置，有需要才链入，（增删改会回调更新状态）*/


class Chara
{
    friend double damage(Chara,Monster);

    static double scale[2][90];//储存等级系数，会由初始化程序赋值
    static const double fourBasicScale=3.577982,fiveBasicScale=4.106541;//基础属性星级基数
    static const double ascension_basic[7];//突破基础值增加,突破等级有0~6
    static int ascension_add[7];//突破附件属性系数
private:
    /*不可变属性*/
    double atk_1,def_1,hp_1;//1级基础属性
    string ascension_state;//突破属性
    string name;//角色名字
    int star;//星级
    string element;//元素属性
    double hp,atk,def;//随等级变化影响

    /*可变属性*/
    int level,ascension;//等级，突破等级，星级

    State_modifier state_basic=State_modifier();//基础区，可被任何“基于”调用，通常就是人物计算圣遗物突破武器后的属性，外加部分buff
    State_modifier extra=State_modifier();//额外区，不能被某些“基于”调用，通常以天赋武器buff等产生
    
    /*
    Talent talent;//角色天赋
    */

    string assessment;//存储评判标准
    int need[19];//圣遗物需求词条，根据评价函数生成
    void set_3basic();
    double BasicScale();//基础属性系数（等级，突破等级，星级）
    double AscensionScale();//突破属性系数（突破等级）
public:
    static void initialize();//初始化

    void set_level(int);//改变等级
    void set_ascension(int);//改变突破等级
    void to_level(string);//以"80/90"的方式设置等级
    double socre();//根据评分标准打分
    void set_score();//设置评分标准
    Chara();
    Chara(string name,int star,string element,double hp,double atk,double def,string ascension_state,int level=1,int accession=0);
};
#endif