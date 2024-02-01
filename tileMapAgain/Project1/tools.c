#include "tools.h"

int iRand(int _min, int _max)
{
    return rand() % (_max - _min + 1) + _min;
}

void initTools()
{
    sfclock = sfClock_create();
    srand(time(NULL));
}

void restartClock()
{
    sftime = sfClock_restart(sfclock);
}

float getDeltaTime()
{
    if (sfTime_asSeconds(sftime) > 1.0f) return 1.0f;
    return sfTime_asSeconds(sftime);
}

