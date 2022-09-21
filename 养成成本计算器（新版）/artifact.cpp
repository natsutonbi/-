#include<iostream>
#include<stdlib.h>
using namespace std;

string stat[18]={"atk","def","hp","atk_p","def_p","hp_p","er","em","cr","cd","heal","pryo","electro","cryo","hydro","anemo","geo","phy"};//圣遗物主/副词条目录
string posi[5]={"flower","plume","sands","goblet","circlet"};//圣遗物位置目录


int trans_stat(string a)//将名称翻译为序号（词条）
{
	for(int i=0;i<18;++i)
	{
		if(stat[i]==a)
			return i;
	}
	cout<<"illegal input exist!!!"<<endl;
	exit(EXIT_FAILURE);
}

string trans_stat(int a)//将序号翻译为名称（词条）
{
	if(a<18&&a>=0)
	{
		return stat[a];
	}
	cout<<"illegal input exist!!!"<<endl;
	exit(EXIT_FAILURE);
}

int trans_posi(string a)//将名称翻译为序号（位置）
{
	for(int i=0;i<5;++i)
	{
		if(posi[i]==a)
			return i;
	}
	cout<<"illegal input exist!!!"<<endl;
	exit(EXIT_FAILURE);
}

string trans_posi(int a)//将序号翻译为名称（位置）
{
	if(a<5&&a>=0)
	{
		return posi[a];
	}
	cout<<"illegal input exist!!!"<<endl;
	exit(EXIT_FAILURE);
}