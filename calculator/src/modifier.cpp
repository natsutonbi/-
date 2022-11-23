#include<iostream>
using namespace std;

#include "./header/modifier.h"

//State_modifier

const string State_modifier::index_state[20]=
    {"hp","HP","atk","ATK","def","DEF",//小大生攻防
    "er","em","cr","cd",//充精双暴
    "pyro","hydro","electro","cryo","anemo","geo","dendro","phy",//火水雷冰风岩草物
    "hb","ihb"};//双治疗，受治疗加成放最后
//包括圣遗物也是state_modifier，除ihb全设为0之外（少女可改），其他均可沿用
int State_modifier::translator(string a)
{
    for(int i=0;i<20;++i)
        if(a==index_state[i])
        return i;
    return -1;
}
string State_modifier::translator(int a)
{
    return index_state[a];
}

State_modifier::State_modifier()
{
    for(int i=0;i<20;++i)
    {
        data[i]=0;//全设0
    }
}
State_modifier::State_modifier(double source[20])
{
    for(int i=0;i<20;++i)
    {
        data[i]=source[i];//copy
    }
}

State_modifier& State_modifier::operator +(const State_modifier& add)
{
    for(int i=0;i<20;++i)
    {
        data[i]+=add.data[i];
    }
    return *this;
}
State_modifier& State_modifier::operator +(const double add[20])
{
    for(int i=0;i<20;++i)
    {
        data[i]+=add[i];
    }
    return *this;
}
void State_modifier::update(const double update[20])
{
    for(int i=0;i<20;++i)
    {
        data[i]=update[i];
    }
}

//damage_modifier
const string Damage_modifier::damage_type[6]={"all","normal","charge","plunge","skill","burst"};
//全伤，普攻，重击，下落，战技，爆发
int Damage_modifier::translator(string a)
{
    for(int i=0;i<5;++i)
        if(a==damage_type[i])
        return i;
    return -1;
}
string Damage_modifier::translator(int a)
{
    return damage_type[a];
}