#include<iostream>
using namespace std;

#include "./header/monster.h"
Monster::Monster()
{
    level=90;
    for(int i=0;i<8;++i)
    {
        resist[i]=0.1;
    }
    buff_def=buff_resist=buff_damageBonus=0;
}