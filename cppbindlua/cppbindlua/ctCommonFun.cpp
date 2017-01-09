#include "ctCommonFun.h"
const char ctCommonFun::className[] = "ctCommonFun";

Lunar<ctCommonFun>::RegType ctCommonFun::methods[] = {
    LUNAR_DECLARE_METHOD(ctCommonFun, mytest),
    {0,0}
};

ctCommonFun::ctCommonFun(lua_State *L)
{
}

ctCommonFun::~ctCommonFun()
{
}

int ctCommonFun::mytest(lua_State *L)
{
    printf("ctCommonFun::mytest\n");
    return 0;
}
