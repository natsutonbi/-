#include"arti_initial.h"
#include<stdlib.h>
#include<iostream>
using namespace std;
class chara_state//可以被副词条影响的属性 
{
	private:
		double hp_=0,atk_=0,def_=0;//基础属性，只被等级控制 
		double HP_=hp_,ATK_=atk_,DEF_=def_;//面板属性，大小词条控制 
		double em_=0,er_=1;
		double cr_=0.05,cd_=0.5;
		string index[10]={"atk","def","hp","ATK","DEF","HP","er","em","cr","cd"};
	public:
		int trans(string a);
		string trans(int a);//互相翻译角色属性
		
		int need_sub[10]={0};//需求的副词条，10个
		
		double hp();//调用各属性，并上报需求属性
		double HP();
		double atk();
		double ATK();
		double def();
		double DEF();
		double em();
		double er();
		double cr();
		double cd();
		
		double hp(double a);
		double HP(double a,string type);//"p"表示百分比，"num"表示数值(支持负数值，以免出现减少生命上限bug)
		double atk(double a);
		double ATK(double a,string type);
		double def(double a);
		double DEF(double a,string type);
		double em(double a);
		double er(double a);
		double cr(double a);
		double cd(double a);//设置数值 
		//typedef double(*access)();
		//access p[]={atk,def,hp,ATK,DEF,HP,er,em,cr,cd};//与stat[18]表对应，故可用trans 
};

int chara_state::trans(string a)
{
	for(int i=0;i<10;++i)
	{
		if(a==index[i]) return i;
	}
	cout<<"角色属性翻译到标号里面存在非法参数！！！";
	exit(EXIT_FAILURE);
}

string chara_state::trans(int a)
{
	if(a>=0&&a<10) return index[a];
	cout<<"角色属性翻译到字符串里面存在非法参数！！！";
	exit(EXIT_FAILURE);
}

double chara_state::hp(){
	return hp_; 
} 

double chara_state::HP(){
	need_sub[trans_stat("hp")]=1;
	need_sub[trans_stat("hp_p")]=1;
	return HP_;
}

double chara_state::atk(){
	return atk_;
}
		
double chara_state::ATK(){
	need_sub[trans_stat("atk")]=1;
	need_sub[trans_stat("atk_p")]=1;
	return ATK_;
} 

double chara_state::def(){
	return def_;
}

double chara_state::DEF(){
	need_sub[trans_stat("def")]=1;
	need_sub[trans_stat("def_p")]=1;
	return DEF_;
}

double chara_state::em(){
	need_sub[trans_stat("em")]=1;
	return em_;
}

double chara_state::er(){
	need_sub[trans_stat("er")]=1;
	return er_;
}

double chara_state::cr(){
	need_sub[trans_stat("cr")]=1;
	return cr_;
}

double chara_state::cd(){
	need_sub[trans_stat("cd")]=1;
	return cd_;
}

double chara_state::hp(double a){
	hp_=a;
	return hp_;
}

double chara_state::HP(double a,string type){
//"p"表示百分比，"num"表示数值 
	if(a<0){
		cout<<"HP(double a,string type)内有非法数值！！";
		exit(EXIT_FAILURE); 
	}
	if(type=="p"){
		HP_+=hp_*a;
		return HP_;
	}	
	if(type=="num"){
		HP_+=a;
		return HP_;
	}
	cout<<"HP(double a,string type)内有非法类型！！";
	exit(EXIT_FAILURE); 
}

double chara_state::atk(double a){
	atk_=a;
	return atk_;
}
double chara_state::ATK(double a,string type){
//"p"表示百分比，"num"表示数值 
	if(a<0){
		cout<<"ATK(double a,string type)内有非法数值！！";
		exit(EXIT_FAILURE); 
	}
	if(type=="p"){
		ATK_+=atk_*a;
		return ATK_;
	}	
	if(type=="num"){
		ATK_+=a;
		return ATK_;
	}
	cout<<"ATK(double a,string type)内有非法类型！！";
	exit(EXIT_FAILURE); 
}

double chara_state::def(double a){
	def_=a;
	return def_;
}

double chara_state::DEF(double a,string type){
//"p"表示百分比，"num"表示数值 
	if(a<0){
		cout<<"DEF(double a,string type)内有非法数值！！";
		exit(EXIT_FAILURE); 
	}
	if(type=="p"){
		DEF_+=def_*a;
		return DEF_;
	}	
	if(type=="num"){
		DEF_+=a;
		return DEF_;
	}
	cout<<"ATK(double a,string type)内有非法类型！！";
	exit(EXIT_FAILURE); 
}

double chara_state::em(double a){
	em_=a;
	return em_;
}
double chara_state::er(double a){
	er_=a;
	return er_;
}
double chara_state::cr(double a){
	em_=a;
	return em_;
}
double chara_state::cd(double a){
	cd_+=a;
	return cd_;
}

class chara
{
	private:
		string name;
		chara_state state;
	public:
		chara();
		chara(string a);//输入名字的构建 
		
		int match(string namae);//匹配名字 
		double default_value();//测评时的估分 
		double set_value();//自设评测方法 
		double (chara::*value)()=chara::default_value;
};

chara::chara()
{
	name="undefined";
	
}

chara::chara(string a)
{
	name=a;
	cout<<"输入基础生命值";
	cout<<"输入基础攻击力";
	
	cout<<"输入基础防御力";
	
} 

int chara::match(string namae){
	if(namae==name) return 1;
	return 0;
}

double chara::default_value()
{
	double point;
	return point;
}

