/************************************************************************/
/* �ο�:
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
    int balance (lua_State *L) { lua_pushnumber(L, m_balance); return 1; } //Lua���ÿ��C���ͣ�����һ��C API������֮��Ӧ��void lua_pushnumber(lua_State* L, lua_Number n); --������
    int getTwoParam(lua_State *L) { lua_pushnumber(L, m_balance); lua_pushnumber(L, 1); return  2;} // �෵��ֵ,�����return ��ʾ����ֵ�ĸ���
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
    lua_State *L = lua_open();//lua_State��Ҫ�ǹ���һ��lua�������ִ�л���, һ��lua����������ж��ִ�л�����Lua�����ͨ��ά������һ������ջ��ʵ������֮���ͨ��

    luaL_openlibs(L); //luaL_openlibs�������ڴ�Lua�е����б�׼�⣬��io�⡢string���

    Lunar<Account>::Register(L);
    Lunar<ctCommonFun>::Register(L);

    if(argc>1) luaL_dofile(L, argv[1]);//luaL_dofile:C++����lua��ʱ��Ҫ���ز�����lua�ļ���luaL_loadfile:ֻ��������Lua�ļ�
    
    printf("%s luaL_dofile(%s) end \n", argv[0], argv[1]);
    
    lua_gc(L, LUA_GCCOLLECT, 0);  // collected garbage
    lua_close(L);
    return 0;
}