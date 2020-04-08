#include "GameConfig.h"

namespace warcraft
{
size_t GameConfig::_currentGroupId = 0;
GameConfig *GameConfig::_pInstance = new GameConfig();
/************************GameConfig定义*****************************/
void GameConfig::readFromConsole()
{
    cout << "please input data:" << endl;
    readFromStream(std::cin);
}

void GameConfig::readFromFile(const string filename)
{
    std::ifstream ifs(filename, std::ifstream::in);
    if (!ifs.good())
    {
        cout << filename << " GameConfig::readFromFile ERROR!" << endl;
        exit(-1);
    }
    readFromStream(ifs);
    ifs.close();
}

void GameConfig::readFromStream(std::istream &is)
{
    while (is.good())
    {
        nextGroupId(); //每一次读新数据组时 Case 组数++
        InitData group;
        //读取第一行 组数
        size_t caseNum;
        is >> caseNum;

        //读取第二行 基地生命元 城市数 Lion每前进一步的降低的忠诚度  截止时间
        is >> group._initBaseHp;
        is >> group._cityNum;
        is >> group._lionReduceLoyalty;
        is >> group._deadline;

        //读取第三行 武士初始生命值 
        for (size_t i = 0; i < _initWarriorOrder.size(); i++)
            is >> group._initWarriorHp[GameConfig::getInstance()->_initWarriorOrder[i]];
        
        //读取第四行 武士初始攻击力 
        for (size_t i = 0; i < _initWarriorOrder.size(); i++)
            is >> group._initWarriorAttack[GameConfig::getInstance()->_initWarriorOrder[i]];

        _groups.push_back(std::move(group));
    }
}

//测试程序
void GameConfig::print() const
{
    for (size_t i = 0; i < _groups.size(); i++)
    {
        //第一行
        cout << i + 1 << endl;
        //第二行
        cout << _groups[i]._initBaseHp << " ";
        cout << _groups[i]._cityNum << " ";
        cout << _groups[i]._lionReduceLoyalty << " ";
        cout << _groups[i]._deadline << endl;
        //第三行
        for (auto &e : _groups[i]._initWarriorHp)
            cout << e.second << " ";
        cout << endl;
        //第四行
        for (auto &e : _groups[i]._initWarriorAttack)
            cout << e.second << " ";
        cout << endl;
        cout << "---------------" << endl;
    }
}

} // namespace warcraft