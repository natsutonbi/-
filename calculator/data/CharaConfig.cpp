#include<iostream>
#include<fstream>
#include<list>
#include<cstring>
#include<cstdlib>
using namespace std;
//已实现：增查
//待实现：改删
class CharaItem
{
public:
    char name[20];
    int star;
    char elementType[20];
    double hp;
    double atk;
    double def;
    char addState[20];
    CharaItem(char* n,int s,char* ele,double h,double a,double d,char*add)
    :star(s),hp(h),atk(a),def(d){
        for(int i=0;i<20;++i)
        {
            name[i]=n[i];
            elementType[i]=ele[i];
            addState[i]=add[i];
        }//逐个拷贝，源会变
    }
    CharaItem(const CharaItem& copist)
    {
        star=copist.star;
        hp=copist.hp;
        atk=copist.atk;
        def=copist.def;
        for(int i=0;i<20;++i)
        {
            name[i]=copist.name[i];
            elementType[i]=copist.elementType[i];
            addState[i]=copist.addState[i];
        }//逐个拷贝，源会变
    }
    CharaItem()
    :name("default"),elementType(""),addState(""),star(0),hp(0),atk(0),def(0){}
};
list<CharaItem> charas;
void getCharaList()
{
    list<CharaItem>::iterator ptr=charas.begin();
    int i=1;
    char head=toupper(ptr->name[0]);
    cout<<head<<":\n";
    while (ptr!=charas.end())
    {
        if(isalpha(ptr->name[0])&&toupper(ptr->name[0])!=head)
        {
            head=toupper(ptr->name[0]);
            cout<<endl<<head<<":\n";
            i=1;
        }
        cout<<i++<<"."<<ptr->name<<endl;
        ++ptr;
    }
}
void addChara(const CharaItem& add)//增，传结构值
{
    list<CharaItem>::iterator ptr=charas.begin();
    while (ptr!=charas.end())
    {
        for(int i=0;i<20;++i)
        {
            if((add.name[i]-ptr->name[i])<0)
            {
                charas.insert(ptr,add);
                return;
            }
            if((add.name[i]-ptr->name[i])>0)
            {
                break;
            }
        }
        ptr++;
    }
}
void Add()
{
    char name[20];
    int star;
    char elementType[20];
    double hp;
    double atk;
    double def;
    char addState[20];
    char key;//消除逗号
    cin.getline(name,20,',');//吞逗号
    name[0]=toupper(name[0]);
    cin>>star>>key;
    cin.getline(elementType,20,',');
    cin>>hp>>key>>atk>>key>>def>>key;
    cin.getline(addState,20);
    if(!isalpha(name[0]))//name部位的首字符不为字母
    {
        cout<<"\nwrong name";
        while(!isalpha(name[0]))
        {
            cin.getline(name,20,',');
            if(name[0]=='!') return;
        }
    }
    addChara(CharaItem(name,star,elementType,hp,atk,def,addState));
}
int getChara(char* name)//查，根据名字，不分大小写去除非字符
{
    list<CharaItem>::iterator ptr=charas.begin();
    while (ptr!=charas.end())
    {
        int j=0;
        for(int i=0;i<20;++i)
        {
            if(isalpha(name[i]))
            {
                if(tolower(name[i])!=tolower(ptr->name[j++]))
                    break;//不匹配退出
                if(!isalpha(ptr->name[j]))
                {
                    cout<<"name:"<<ptr->name<<endl<<"star:"<<ptr->star<<" elementType:"<<ptr->elementType<<endl<<"addState:";
                    cout<<ptr->addState<<"\nbasicState(atk,def,hp):"<<ptr->atk<<" "<<ptr->def<<" "<<ptr->hp<<endl;
                    return 1;
                }
            }
            
        }
        ptr++;
    }
    cout<<"not found"<<endl;
    return 0;
}
void load()
{
    ifstream read("character.csv",ios::in);
    {
        char name[20];
        int star;
        char elementType[20];
        double hp;
        double atk;
        double def;
        char addState[20];
        char key;//消除逗号
        if(!read)
        {
            cout<<"open file erro";
            system("pause");
        }
        while (!read.eof())
        {
            read.getline(name,20,',');
            if(!isalpha(name[0])) break;//name部位的首字符不为字母
            read>>star>>key;
            read.getline(elementType,20,',');
            read>>hp>>key>>atk>>key>>def>>key;
            read.getline(addState,20);//吞掉末尾'\n'
            charas.push_back(CharaItem(name,star,elementType,hp,atk,def,addState));//传入const
        }
        read.close();
    }
    cout<<"character data loaded"<<endl;
}
void save()
{
    ofstream write("character_new.csv",ios::out);
    list<CharaItem>::iterator ptr=charas.begin();
    while(ptr!=charas.end())
    {
        write<<ptr->name<<','<<ptr->star<<','<<ptr->elementType<<','<<ptr->hp<<','<<ptr->atk<<','<<ptr->def<<','<<ptr->addState<<'\n';
        ++ptr;
    }
    write.close();
}
int main(int argc,char** argv)
{
    load();
    getCharaList();
    Add();
    getCharaList();
    char name[20];
    cin.getline(name,20);
    getChara(name);
    save();
    system("pause");
    return 0;
}