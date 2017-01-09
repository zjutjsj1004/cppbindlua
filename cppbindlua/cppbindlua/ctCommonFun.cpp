#include "ctCommonFun.h"
const char ctCommonFun::className[] = "ctCommonFun";

Lunar<ctCommonFun>::RegType ctCommonFun::methods[] = {
    LUNAR_DECLARE_METHOD(ctCommonFun, mytest),
    LUNAR_DECLARE_METHOD(ctCommonFun, addNum),
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

int ctCommonFun::addNum( lua_State *L )
{
    int a = luaL_checknumber(L, -1);
    int b = luaL_checknumber(L, -2);
    printf("ctCommonFun::addNum -- a + b = %d \n", a + b);
    return 0;
}
