/************************************************************************/
/* 参考:
http://lua-users.org/wiki/CppBindingWithLunar  
http://www.cnblogs.com/ringofthec/archive/2010/10/26/luabindobj.html
http://blog.csdn.net/liaowenfeng/article/details/9905083
http://blog.csdn.net/asmc51/article/details/3848221  */
/************************************************************************/
#include "lunar.h"
#include "ctCommonFun.h"
extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

class Account {
    lua_Number m_balance;
public:
    static const char className[];
    static Lunar<Account>::RegType methods[];

    Account(lua_State *L)      { m_balance = luaL_checknumber(L, 1); } //luaL_checknumber function checks whether a given argument is a number
    int deposit (lua_State *L) { m_balance += luaL_checknumber(L, 1); return 0; }
    int withdraw(lua_State *L) { m_balance -= luaL_checknumber(L, 1); return 0; }
    int balance (lua_State *L) { lua_pushnumber(L, m_balance); return 1; } //Lua针对每种C类型，都有一个C API函数与之对应：void lua_pushnumber(lua_State* L, lua_Number n); --浮点数
    int getTwoParam(lua_State *L) { lua_pushnumber(L, m_balance); lua_pushnumber(L, 1); return  2;} // 多返回值,这里的return 表示返回值的个数
    ~Account() { printf("deleted Account (%p)\n", this); }
};

const char Account::className[] = "Account";

Lunar<Account>::RegType Account::methods[] = {
    LUNAR_DECLARE_METHOD(Account, deposit),
    LUNAR_DECLARE_METHOD(Account, withdraw),
    LUNAR_DECLARE_METHOD(Account, balance),
    LUNAR_DECLARE_METHOD(Account, getTwoParam),
    {0,0}
};

int main(int argc, char *argv[])
{
    lua_State *L = lua_open();//lua_State主要是管理一个lua虚拟机的执行环境, 一个lua虚拟机可以有多个执行环境。Lua虚拟机通过维护这样一个虚拟栈来实现两种之间的通信

    luaL_openlibs(L); //luaL_openlibs函数用于打开Lua中的所有标准库，如io库、string库等

    Lunar<Account>::Register(L);
    Lunar<ctCommonFun>::Register(L);

    if(argc>1) luaL_dofile(L, argv[1]);//luaL_dofile:C++调用lua的时候要加载并运行lua文件，luaL_loadfile:只单单加载Lua文件
    
    printf("%s luaL_dofile(%s) end \n", argv[0], argv[1]);
    
    lua_gc(L, LUA_GCCOLLECT, 0);  // collected garbage
    lua_close(L);
    return 0;
}