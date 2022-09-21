#include<iostream>
#include<stdlib.h>
using namespace std;

string stat[18]={"atk","def","hp","atk_p","def_p","hp_p","er","em","cr","cd","heal","pryo","electro","cryo","hydro","anemo","geo","phy"};
string posi[5]={"flower","plume","sands","goblet","circlet"};

int main_stat[5]={2,0,3,11,8};//表明主词条选择情况，默认攻火暴 

int trans_stat(string a)
{
	for(int i=0;i<18;++i)
	{
		if(stat[i]==a)
			return i;
	}
	cout<<"illegal input exist!!!"<<endl;
	exit(EXIT_FAILURE);
}
string trans_stat(int a)
{
	if(a<18&&a>=0)
	{
		return stat[a];
	}
	cout<<"illegal input exist!!!"<<endl;
	exit(EXIT_FAILURE);
}
int trans_posi(string a)
{
	for(int i=0;i<5;++i)
	{
		if(posi[i]==a)
			return i;
	}
	cout<<"illegal input exist!!!"<<endl;
	exit(EXIT_FAILURE);
}
string trans_posi(int a)
{
	if(a<5&&a>=0)
	{
		return posi[a];
	}
	cout<<"illegal input exist!!!"<<endl;
	exit(EXIT_FAILURE);
}

