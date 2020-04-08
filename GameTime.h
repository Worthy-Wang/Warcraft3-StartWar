#ifndef _WARCRAFT_GAMETIME_H_
#define _WARCRAFT_GAMETIME_H_
#include <iomanip>
#include <iostream>

namespace warcraft
{

class GameTime
{
    static GameTime *_pInstance;
    size_t _hour;
    size_t _minute;

public:
    static GameTime *getInstance()
    {
        return _pInstance;
    }

    static void destory()
    {
        if (_pInstance)
        {
            delete _pInstance;
            _pInstance = NULL;
        }
    }

    void showTime() const
    {
        std::cout << std::setw(3) << std::setfill('0') << _hour << ":" << std::setw(2) << std::setfill('0') << _minute << std::endl;
    }
    void updateTime()
    {
        if ((_minute + 5) == 60)
        {
            _hour++;
            _minute = 0;
        }
        else
        {
            _minute += 5;
        }
    }
    size_t getTime() const { return 60 * _hour + _minute; }

private:
    GameTime() : _hour(0), _minute(0) { atexit(destory); }
    ~GameTime() {}
};

} //end of namespace warcraft

#endif