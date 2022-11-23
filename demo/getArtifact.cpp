#include<list>
#include".\header\getArtifact.h"
using namespace std;
/*double differWeight(State_modifier currentResult,int* weight,double (*score)(State_modifier result))//求每个“微分”权重，并写入weight
{
    double valueOfStat[19]={
        253.94,//hp
	    4.955,//HP，单位为%
	    16.535,//atk
	    4.955,//ATK
	    19.675,//def
	    6.195,//DEF
	    5.505,//er(%)
	    19.815,//em
	    3.305,//cr(%)
	    6.605,//cd(%)
        4.955, 4.955, 4.955, 4.955, 4.955, 4.955, 4.955,//元素(%)
	    6.195,//物理(%)
	    3.815//hb(%)
    };
    for(int i=0;i<19;++i)
    {
        double differedModifier[20]={0};
        int scalor[19]={0};
        scalor[i]=1;
        for(int j=0;j<19;++j)
        {
            differedModifier[j]=scalor[j]*valueOfStat[j];
        }
        weight[i]=score(currentResult+differedModifier);
    }
}*/

class scoredArtifact;

class equippedArtifact
{
    friend scoredArtifact;
private:
    double (*assess_suit)(State_modifier,int suit_effect);
    const Artifact* suit[5];//都在list内，所以只储存地址
    State_modifier suit_modifier;
    double suitScore;
    int Demo_suit_effect;//默认只测4件，分0/1，生效/不生效
public:
    equippedArtifact(double (*assess)(State_modifier,int suit_effect)){
        for(int i=0;i<5;++i) suit[i]=nullptr;
        assess_suit=assess;
        suitScore=0;
    }//默认无装备
    double changeArtifact(const Artifact*);//返回更改后分数
    double refresh();
    double getVariation(const scoredArtifact&) const;//返回分数变化
    double getVariation(const int ,const int,const State_modifier&) const;
};
double equippedArtifact::changeArtifact(const Artifact* another)
{
    int position=another->get_position();
    suit[position]=another;
    suit_modifier=suit_modifier-suit[position]->Artifact_modifier+another->Artifact_modifier;
    suitScore=assess_suit(suit_modifier,Demo_suit_effect);
    return suitScore;
}
double equippedArtifact::refresh()
{
    State_modifier temp;
    for(int i=0;i<5;++i)
    {
        if(suit[i]!=nullptr)
        {
            temp=temp+suit[i]->Artifact_modifier;
        }
    }
    suit_modifier=temp;
    suitScore=assess_suit(suit_modifier,Demo_suit_effect);
    short count=0;
    for(int i=0;i<5;++i)
    {
        if(suit[i]->get_suit()==1)
            count+=1;
    }
    if(count>=4)
        Demo_suit_effect=1;
    else Demo_suit_effect=0;
}
double equippedArtifact::getVariation(const scoredArtifact& another) const
{
    int position=another.get_position();
    State_modifier temp=suit_modifier-suit[position]->Artifact_modifier+another.Artifact_modifier;
    short count=0,changedSuitEffect=0;
    for(int i=0;i<5;++i)
    {
        if(i==position)
        {
            if(another.get_suit()==1)
                count+=1;
            continue;
        }
        if(suit[i]->get_suit()==1)
            count+=1;
    }
    if(count>=4)
        changedSuitEffect=1;
    return assess_suit(temp,changedSuitEffect)-suitScore;
}
double equippedArtifact::getVariation(const int position,const int suitID,const State_modifier& another) const
{
    State_modifier temp=suit_modifier-suit[position]->Artifact_modifier+another;
    short count=0,changedSuitEffect=0;
    for(int i=0;i<5;++i)
    {
        if(i==position)
        {
            if(suitID==1)
                count+=1;
            continue;
        }
        if(suit[i]->get_suit()==1)
            count+=1;
    }
    if(count>=4)
        changedSuitEffect=1;
    return assess_suit(temp,changedSuitEffect)-suitScore;
}

class scoredArtifact:public Artifact//被指定装备位评分的圣遗物，隶属于套装而存在的评分标准
{
    const equippedArtifact* equip;
    double score;//更改为有无此圣遗物的分数变化（更换后-更换前），在0附近波动，初始化为4分位，后续以百分比
public:
    scoredArtifact(const equippedArtifact* suit){
        equip=suit;
        score=equip->getVariation(get_position(),get_suit(),Artifact_modifier);
    }//设定从属装备栏和对应分数
    void refreshScore(){
        score=equip->getVariation(*this);
    }//刷新分数
    double getScore() const{
        return score;
    }//查询score
};

class ArtifactInBag//先统一套装
{
    const equippedArtifact* equip;
    list<scoredArtifact> Flower;//圣遗物池，用于存储可能的最优，外界无法接触
	list<scoredArtifact> Plume;
	list<scoredArtifact> Sands;
	list<scoredArtifact> Goblet;
	list<scoredArtifact> Circlet;
    void pushToStorage(const scoredArtifact&);//入库
    void popOut(list<scoredArtifact>&);//对某位置进行筛除
public:
    ArtifactInBag(const equippedArtifact* equipment){
        equip=equipment;
    }
    void getArtifact(int n);//获取n件评分圣遗物
    void equipBest();//装备最好的圣遗物
    void refresh();//刷新圣遗物评分
};
void ArtifactInBag::pushToStorage(const scoredArtifact& item)
{
    list<scoredArtifact>* target;
    switch (item.get_position())
    {
    case 0:
        target=&Flower;
        break;
    case 1:
        target=&Plume;
        break;
    case 2:
        target=&Sands;
        break;
    case 3:
        target=&Goblet;
        break;
    case 4:
        target=&Circlet;
        break;
    default:
        break;
    }
    list<scoredArtifact>::iterator ptr=target->begin();
    const list<scoredArtifact>::iterator end=target->end();
    while(ptr!=end)
    {
        if(ptr->getScore()>item.getScore())//分数从小到大
        {
            target->insert(ptr,item);
            return;
        }
    }
    target->push_back(item);
}//无筛选动作，仅入库
void ArtifactInBag::popOut(list<scoredArtifact>& target)//对异常低的进行剔除（下边缘以外，对称补齐）
{

}
void ArtifactInBag::equipBest()//有筛选，会剔除————装最好，刷新分数，剔除，直到最高不大于0
{

}
void ArtifactInBag::getArtifact(int n)
{
    for(int i=0;i<n;++i)
    {
        scoredArtifact temp(equip);
        switch (temp.get_position())
        {
        case 0:
            /* code */
            break;
        
        default:
            break;
        }
    }
}
void ArtifactInBag::refresh()
{
    list<scoredArtifact>::iterator ptr=Flower.begin();
    while (ptr!=Flower.end())
    {
        ptr->refreshScore();
        ++ptr;
    }
    ptr=Plume.begin();
    while (ptr!=Plume.end())
    {
        ptr->refreshScore();
        ++ptr;
    }
    ptr=Sands.begin();
    while (ptr!=Sands.end())
    {
        ptr->refreshScore();
        ++ptr;
    }
    ptr=Goblet.begin();
    while (ptr!=Goblet.end())
    {
        ptr->refreshScore();
        ++ptr;
    }
    ptr=Circlet.begin();
    while (ptr!=Circlet.end())
    {
        ptr->refreshScore();
        ++ptr;
    }
}
double toArtifactDomain(int n,const int* need,double (*assess_suit)(State_modifier result),int preOtherArti=200)
{
	double weight[19];//主副词条权重
    
    
    while (n>0)
    {
        Artifact suits[5];
    }
    
	
	return 0;
}//剔除未刷满