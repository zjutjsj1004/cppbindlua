#ifndef __CT_COMMON_FUN_H
#define  __CT_COMMON_FUN_H
#include "lunar.h"
class ctCommonFun
{
public:
    ctCommonFun(lua_State *L);
    ~ctCommonFun();
    static const char className[];
    static Lunar<ctCommonFun>::RegType methods[];

private:
    int mytest(lua_State *L);
};
#endif

