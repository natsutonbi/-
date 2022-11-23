#include<iostream>
#include<stdlib.h>
#include<random>
#include<list>
#include<thread>
#include".\header\artifact.h"

using namespace std;
int randomNum(int min,int max)
{
	random_device rd;
	default_random_engine r_eng(rd());
	uniform_int_distribution<int> id(min,max);
	return id(r_eng);
}
const string Artifact::index_posi[5]={"flower","plume","sands","goblet","circlet"};//圣遗物位置目录
int Artifact::trans_posi(string a)//将名称翻译为序号（位置）
{
	for(int i=0;i<5;++i)
	{
		if(index_posi[i]==a)
			return i;
	}
	cout<<"illegal input about position!!!"<<endl;
	exit(EXIT_FAILURE);
}
string Artifact::trans_posi(int a)//将序号翻译为名称（位置）
{
	if(a<5&&a>=0)
	{
		return index_posi[a];
	}
	cout<<"illegal input about position!!!"<<endl;
	exit(EXIT_FAILURE);
}

int Artifact::sub_weight[10]={150,100,150,100,150,100,100,100,75,75};
int Artifact::main_weight[5][19]={
	{0},
	{0},
	{0,1334,0,1333,0,1333,500,500,0,0,0,0,0,0,0,0,0,0,0},
	{0,766,0,767,0,767,0,100,0,0,200,200,200,200,200,200,200,200,0},
	{0,1100,0,1100,0,1100,0,200,500,500,0,0,0,0,0,0,0,0,500}
};
double Artifact::sub_addState[10]={
	253.94,//hp
	4.955,//HP，单位为%
	16.535,//atk
	4.955,//ATK
	19.675,//def
	6.195,//DEF
	5.505,//er(%)
	19.815,//em
	3.305,//cr(%)
	6.605//cd(%)
};
double Artifact::main_addState[19]={
	4780,46.6,311,46.6,0,58.3,//hp,HP,atk,ATK,def,DEF
	51.8,186.5,31.1,62.2,//er,em,cr,cd
	46.6, 46.6, 46.6, 46.6, 46.6, 46.6, 46.6,//元素
	58.3,//物理
	35.9//hb
};
Artifact::Artifact()
{
	suit=randomNum(1,2);
	//随机位置
	position=randomNum(0,4);

	//随机主词条
	if(position==0)//花
	{
		main_stat=0;//hp
	}
	else if(position==1)//羽
	{
		main_stat=2;//atk
	}
	else{
		int totalWeight=0;
		for(int i=0;i<19;++i)
		{
			totalWeight+=main_weight[position][i];
		}
		int random=randomNum(1,totalWeight);
		for(int i=0,j=0;i<19;++i)
		{
			j+=main_weight[position][i];
			if(j>=random)
			{
				main_stat=i;
				break;
			}
		}
	}

	//随机副词条
	int sub_weightCopy[10];
	int totalWeight=0;
	for(int i=0;i<10;++i)
	{
		sub_weightCopy[i]=sub_weight[i];
		totalWeight+=sub_weight[i];
	}
	if(main_stat<10){
		sub_weightCopy[main_stat]=0;
		totalWeight-=sub_weight[main_stat];
	}//不能冲突
	int random=randomNum(1,totalWeight);
	for(int k=0;k<4;++k)//抽取4次副词条
	{
		for(int i=0,j=0;i<10;++i)
		{
			j+=sub_weightCopy[i];
			if(j>=random)
			{
				sub_stat[i]=1;
				break;
			}
		}
	}

	//随机强化
	int distribution[4];
	for(int i=0;i<4;++i)
	{
		distribution[i]=0;
	}
	for(int i=0;i<4;++i)//强化基础的4次
	{
		distribution[randomNum(0,3)]+=1;
	}
	if(randomNum(1,1000)>800)
	{
		distribution[randomNum(0,3)]+=1;
	}
	for(int i=0,j=0;i<10;++i)
	{
		if(sub_stat[i]==1)
		{
			sub_stat[i]+=distribution[j++];
		}
	}

	//改modifier
	double temp[20]={0};
	temp[main_stat]+=main_addState[main_stat];
	for(int i=0;i<10;++i)
	{
		temp[i]+=sub_stat[i]*sub_addState[i];
	}
	Artifact_modifier.update(temp);
}
Artifact::Artifact(int Suit,int Position)
{
	this->suit=Suit;

	if(Position>=0&&Position<5)
		this->position=Position;
	else{//随机位置
		position=randomNum(0,4);
	}

	//随机主词条
	if(position==0)//花
	{
		main_stat=0;//hp
	}
	else if(position==1)//羽
	{
		main_stat=2;//atk
	}
	else{
		int totalWeight=0;
		for(int i=0;i<19;++i)
		{
			totalWeight+=main_weight[position][i];
		}
		int random=randomNum(1,totalWeight);
		for(int i=0,j=0;i<19;++i)
		{
			j+=main_weight[position][i];
			if(j>=random)
			{
				main_stat=i;
				break;
			}
		}
	}

	//随机副词条
	int sub_weightCopy[10];
	int totalWeight=0;
	for(int i=0;i<10;++i)
	{
		sub_weightCopy[i]=sub_weight[i];
		totalWeight+=sub_weight[i];
	}
	if(main_stat<10){
		sub_weightCopy[main_stat]=0;
		totalWeight-=sub_weight[main_stat];
	}//不能冲突
	uniform_int_distribution<unsigned> id(1,totalWeight);
	int random=randomNum(1,totalWeight);
	for(int k=0;k<4;++k)//抽取4次副词条
	{
		for(int i=0,j=0;i<10;++i)
		{
			j+=sub_weightCopy[i];
			if(j>=random)
			{
				sub_stat[i]=1;
				break;
			}
		}
	}

	//随机强化
	int distribution[4];
	for(int i=0;i<4;++i)
	{
		distribution[i]=0;
	}
	for(int i=0;i<4;++i)//强化基础的4次
	{
		distribution[randomNum(0,3)]+=1;
	}
	if(randomNum(1,1000)>800)
	{
		distribution[randomNum(0,3)]+=1;
	}
	for(int i=0,j=0;i<10;++i)
	{
		if(sub_stat[i]==1)
		{
			sub_stat[i]+=distribution[j++];
		}
	}

	//改modifier
	double temp[20]={0};
	temp[main_stat]+=main_addState[main_stat];
	for(int i=0;i<10;++i)
	{
		temp[i]+=sub_stat[i]*sub_addState[i];
	}
	Artifact_modifier.update(temp);
}
void Artifact::random_posi()//随机位置
{
	random_device rd;
	default_random_engine r_eng(rd());
	uniform_int_distribution<unsigned> id(0,4);
	position=id(r_eng);
}
void Artifact::random_main()//随机主词条
{
	if(position==0)//花
	{
		main_stat=0;//hp
		return;
	}
	else if(position==1)//羽
	{
		main_stat=2;//atk
		return;
	}
	else{
		int totalWeight=0;
		for(int i=0;i<19;++i)
		{
			totalWeight+=main_weight[position][i];
		}
		random_device rd;
		default_random_engine r_eng(rd());
		uniform_int_distribution<unsigned> id(1,totalWeight);
		int randomNum=id(r_eng);
		for(int i=0,j=0;i<19;++i)
		{
			j+=main_weight[position][i];
			if(j>=randomNum)
			{
				main_stat=i;
				return;
			}
		}
	}
}
void Artifact::random_sub()//随机副词条
{
	int sub_weightCopy[10];
	int totalWeight=0;
	for(int i=0;i<10;++i)
	{
		sub_weightCopy[i]=sub_weight[i];
		totalWeight+=sub_weight[i];
	}
	if(main_stat<10){
		sub_weightCopy[main_stat]=0;
		totalWeight-=sub_weight[main_stat];
	}//不能冲突
	random_device rd;
	default_random_engine r_eng(rd());
	uniform_int_distribution<unsigned> id(1,totalWeight);
	int randomNum=id(r_eng);
	for(int k=0;k<4;++k)//抽取4次副词条
	{
		for(int i=0,j=0;i<10;++i)
		{
			j+=sub_weightCopy[i];
			if(j>=randomNum)
			{
				sub_stat[i]=1;
				break;
			}
		}
	}
	
}
void Artifact::random_upgrade()//随机强化副词条
{
	random_device rd;
	default_random_engine r_eng(rd());
	uniform_int_distribution<unsigned> id(0,3);
	int distribution[4];
	for(int i=0;i<4;++i)
	{
		distribution[i]=0;
	}
	for(int i=0;i<4;++i)//强化基础的4次
	{
		distribution[id(r_eng)]+=1;
	}
	uniform_int_distribution<unsigned> ifExtra(1,1000);
	if(ifExtra(r_eng)>800)
	{
		distribution[id(r_eng)]+=1;
	}
	for(int i=0,j=0;i<10;++i)
	{
		if(sub_stat[i]==1)
		{
			sub_stat[i]+=distribution[j++];
		}
	}
}
void Artifact::update_modifier()
{
	double temp[20]={0};
	temp[main_stat]+=main_addState[main_stat];
	for(int i=0;i<10;++i)
	{
		temp[i]+=sub_stat[i]*sub_addState[i];
	}
	Artifact_modifier.update(temp);
}
void Artifact::random_reset()
{
    random_posi();
    random_main();
    random_sub();
    random_upgrade();

	update_modifier();
}
void Artifact::print()
{
	cout<<"suit:"<<suit<<"   position: "<<trans_posi(position)<<endl;
	cout<<"main_stat: "<<State_modifier::translator(main_stat)<<endl<<"sub_stat:"<<endl;
	for(int i=0;i<10;++i)
	{
		if(sub_stat[i]>0)
		{
			cout<<State_modifier::translator(i)<<" "<<sub_stat[i]*sub_addState[i];
			if(i==1||i==3||i==5)
				cout<<"%";
			cout<<endl;
		}
	}
	cout<<endl;
}
double toArtifactDomain(int n,const int* need,double (*access_suit)(State_modifier result))
{
	list<Artifact> Flower;//圣遗物池，用于存储可能的最优
	list<Artifact> Plume;
	list<Artifact> Sands;
	list<Artifact> Goblet;
	list<Artifact> Circlet;
	Artifact suits[5];
	return 0;
}//剔除未刷满