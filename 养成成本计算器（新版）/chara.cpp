#include<iostream>
using namespace std;

const string source[5]={"normal","charge","plunge","skill","burst"};
const string type[8]={"pyro","hydro","dendro","electro","anemo","cryo","geo","phy"};
const string stat[];

int trans_source(string a)
{
    for(int i=0;i<5;i++)
    {
        if(a==source[i])
        return i;
    }
    return -1;//-1表示出错
}
string trans_source(int a)
{
    if(a<5&&a>=0)
    return source[a];
    return "\0";
}
int trans_type(string a)
{
    for(int i=0;i<8;i++)
    {
        if(a==type[i])
        return i;
    }
    return -1;//-1表示出错
}
string trans_type(int a)
{
    if(a<8&&a>=0)
    return type[a];
    return "\0";
}


class state
{
private:
    /* 数据用下划线“data_”，对应取消下划线的为修改函数 */
    double hp_,HP_,atk_,ATK_,def_,DEF_,
            em_,cr_,cd_,hb_,ihb_,er_;
    double db_[8];
    
public:
    state(/* args */);
    ~state();
};

state::state(/* args */)
{
}

state::~state()
{
}


class talent_of_chara
{
private:
    /* data */

public:
    talent_of_chara(/* args */);
    ~talent_of_chara();
};

talent_of_chara::talent_of_chara(/* args */)
{
}

talent_of_chara::~talent_of_chara()
{
}



class chara
{
private:
    /* data */
    state basic;
public:
    chara(/* args */);
    ~chara();
};

chara::chara(/* args */)
{
}

chara::~chara()
{
}
