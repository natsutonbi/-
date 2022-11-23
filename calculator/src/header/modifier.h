#ifndef MODIFIER
#define MODIFIER
#include<iostream>
using namespace std;
class State_modifier//面板属性改变方式
{
private:
    double data[20];//以index指定对应属性
    //面板属性的更改只可以通过：等级（对每个角色基础不一样——手动输入），武器，圣遗物，buff，命座
public:
    static const string index_state[20];//面板属性目录(绝对值和相对值)
    static int translator(string a);
    static string translator(int a);

    State_modifier();//默认全0
    State_modifier(double source[20]);
    State_modifier& operator +(const State_modifier& add);//属性相加
    State_modifier& operator +(const double add[20]);
    void update(const double update[20]);//用数组更新
};

class Damage_modifier//对于天赋，有仅作用单个技能的；外部有全局增伤的；也有检查标签/属性的
{
private:
    double basicDamage;//基础区
    double damage_bonus[5];//增伤
public:
    static const string damage_type[6];
    static int translator(string a);
    static string translator(int a);
};
class Talent_modifier
{

};
#endif