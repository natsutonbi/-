#include<cmath>
#include<iostream>
#include<stdlib.h>
using namespace std;

#include"arti_initial.h"

void set_main()
{
	cout<<"请选择要修改的部位"<<endl; 
	for(int i=0;i<5;++i)
	{
		cout<<i<<"."<<trans_posi(i)<<endl;
	}
	int a;
	int i;
	cin>>i;
	system("cls");
	switch(i)
	{
		case 0:
			cout<<trans_posi(i)<<"无法更改，只能选择"<<trans_stat(2)<<endl;
			break;
		case 1:
			cout<<trans_posi(i)<<"无法更改，只能选择"<<trans_stat(0)<<endl;
			break;
		case 2:
			cout<<"正在修改"<<trans_posi(i)<<endl<<"选择要修改为什么主属性："<<endl;
			cout<<"（当前属性："<<trans_stat(main_stat[i]) <<"；输入-1停止修改）\n\n"; 
			
			for(int j=3,k=0;j<=7;++j,++k){
				if(k==2){
					cout<<endl;
					k=0;
				}
				cout<<j<<"."<<trans_stat(j)<<"	";
			}
			
			cout<<endl;
			cin>>a;
			if(a>=3&&a<=7)
			{
				main_stat[i]=a;
			}
			else cout<<"非法输入！！\n";
			
			cout<<"当前属性："<<trans_stat(main_stat[i])<<endl;
			break;
		case 3:
			cout<<"正在修改"<<trans_posi(i)<<endl<<"选择要修改为什么主属性："<<endl;
			cout<<"（当前属性："<<trans_stat(main_stat[i]) <<"；输入-1停止修改）"<<endl; 
			for(int j=3,k=0;j<=17;++j){
				if(j!=6&&(j<8||j>10)){
					if(k==2)
					{
						cout<<endl;
						k=0;
					}
				cout<<j<<"."<<trans_stat(j)<<" ";
				++k;
				}
			}
			cout<<endl;
			cin>>a;
			if(a>=3&&a<=17&&a!=6&&(a<8||a>10))
			{
				main_stat[i]=a;
			}
			else cout<<"非法输入！!\n";
			
			cout<<"当前属性："<<trans_stat(main_stat[i])<<endl;
			break;
		case 4:
			cout<<"正在修改"<<trans_posi(i)<<endl<<"选择要修改为什么主属性："<<endl;
			cout<<"（当前属性："<<trans_stat(main_stat[i]) <<"；输入-1停止修改）"<<endl; 
			for(int j=3,k=0;j<=17;++j){
				if((j>=3&&j<=5)||(j>=7&&j<=10))
				{
					if(k==2)
					{
						cout<<endl;
						k=0;
					}
				cout<<j<<"."<<trans_stat(j)<<"	";
				++k;
				}
			}
			cout<<endl;
			cin>>a;
			if((a>=3&&a<=5)||(a>=7&&a<=10))
			{
				main_stat[i]=a;
			}
			else cout<<"非法输入！!\n";
			
			cout<<"当前属性："<<trans_stat(main_stat[i])<<endl;
			break;
	}
	system("pause");
	system("cls");
}

void arti_menu()//圣遗物菜单，完成之后才算设置完毕 
{
	int max_choice=2;
	int i=1;
	while(i!=0)
	{
		cout<<"请选择接下来的操作："<<endl;
		cout<<"1.修改主词条\n0.修改完成\n";
		cout<<"--------------------------------------------------------\n";
		cin>>i;
		while(!(i>=0&&i<max_choice))
		{
			cout<<"非法输入，请重新输入";
			cin>>i;
		}
		switch(i)
		{
			case 1:
				set_main();
		}
	}
	
}

int main()
{
	arti_menu();
}
