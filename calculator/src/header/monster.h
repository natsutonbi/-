#ifndef MONSTER
#define MONSTER
class Monster
{
private:
    int level;//影响防御力
    double resist[8];//火水雷冰风岩草物抗性
    double buff_def,buff_resist,buff_damageBonus;//防御抗性增伤buff
public:
    Monster();
};
#endif