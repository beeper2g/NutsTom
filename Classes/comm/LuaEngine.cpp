#include "LuaEngine.h"
#include "Cocos2dxPlatform.h"
extern "C"
{
#include "../lua/lua.h"
#include "../lua/lualib.h"
#include "../lua/lauxlib.h"
};

lua_State*  _gL = nullptr;

struct SafeLua
{
    SafeLua(lua_State* L)
        :_luaState(L)
    {
        _top = lua_gettop(_luaState);
    }
    ~SafeLua()
    {
        lua_settop(_luaState, _top);
    }
    int         _top;
    lua_State*  _luaState;
};





#define LEVELS1	12	/* size of the first part of the stack */
#define LEVELS2	10	/* size of the second part of the stack */

inline int lua_errormessage(lua_State *L)
{
    int level = 0;  /* skip level 0 (it's this function) */
    int firstpart = 1;  /* still before eventual `...' */	
    lua_Debug ar;
    if (!lua_isstring(L, 1))
        return lua_gettop(L);
    lua_settop(L, 1);
    lua_pushliteral(L, "\r\n");
    lua_pushliteral(L, "调用堆栈:\r\n");
    while (lua_getstack(L, level++, &ar)) 
    {
        char buff[10];
        if (level > LEVELS1 && firstpart) 
        {
            /* no more than `LEVELS2' more levels? */
            if (!lua_getstack(L, level+LEVELS2, &ar))
                level--;  /* keep going */
            else 
            {
                lua_pushliteral(L, "       ...\r\n");  /* too many levels */
                while (lua_getstack(L, level+LEVELS2, &ar))  /* find last levels */
                    level++;				
            }
            firstpart = 0;
            continue;
        }

        sprintf(buff, "%4d-  ", level-1);
        lua_pushstring(L, buff);
        lua_getinfo(L, "Snl", &ar);
        lua_pushfstring(L, "%s:", ar.short_src);
        if (ar.currentline > 0)
            lua_pushfstring(L, "%d:", ar.currentline);
        switch (*ar.namewhat) 
        {
        case 'g':  /* global */ 
        case 'l':  /* local */
        case 'f':  /* field */
        case 'm':  /* method */
            lua_pushfstring(L, " 在函数 `%s'", ar.name);
            break;
        default: 
            {
                if (*ar.what == 'm')  /* main? */
                    lua_pushfstring(L, " in main chunk");
                else if (*ar.what == 'C')  /* C function? */
                    lua_pushfstring(L, "%s", ar.short_src);
                else
                    lua_pushfstring(L, " 在函数 <%s:%d>", ar.short_src, ar.linedefined);
            }

        }
        lua_pushliteral(L, "\r\n");
        lua_concat(L, lua_gettop(L));
    }
    lua_concat(L, lua_gettop(L)); 	

    time_t t = time(NULL);
    struct tm* t2 = localtime(&t);

    char szTime[128];
    sprintf(szTime,  
        "%04d%02d%02d %02d:%02d:%02d\r\n", 
        t2->tm_year + 1900, t2->tm_mon + 1, t2->tm_mday, t2->tm_hour, t2->tm_min, t2->tm_sec);

    FILE* pf = fopen("scripterr.log", "a+b");

    size_t luaerrlen = 0;
    const char* luaerr = lua_tolstring(L, -1, &luaerrlen);
    if (luaerr)
    {
        printf(luaerr);
    }	
    if(pf)
    {
        fwrite(szTime, 1, strlen(szTime), pf);
        fwrite(luaerr, 1, luaerrlen, pf);
        fclose(pf);
    }
    return 0;
}

LuaEngine::LuaEngine()
{
    _gL = luaL_newstate();
    luaL_openlibs(_gL);

}

LuaEngine::~LuaEngine()
{
    lua_close(_gL);
    _gL = nullptr;
}

LuaEngine* LuaEngine::getInstance()
{
    static LuaEngine engine;
    return &engine;
}

bool LuaEngine::loadScriptFile(const char* path, const char* file)
{
    char fileName[512] = {0};
    if (nullptr==file)
    {
        snprintf(fileName, 511, "%s", path);
    }
    else
    {
        snprintf(fileName, 511, "%s/%s", path, file);
    }	
    lua_pushcfunction(_gL, &lua_errormessage);	
    int error = luaL_loadfile(_gL, fileName) ||  lua_pcall(_gL, 0, LUA_MULTRET, 1);
    if (error != 0)
    {
        CCLOG("LUA ERROR [%s]", lua_tolstring(_gL, -1, NULL));
        lua_pop(_gL, 1);
        return false;
    }
    return true;

}

bool LuaEngine::loadScriptFiles(const char* path, const char* files[], int fileCount)
{
    return false;
}

bool LuaEngine::loadScriptString(const char* script)
{
    return false;
}

int LuaEngine::getIntValue(const char* paramName, int defValue)
{
    return 0;
}

double LuaEngine::getDoubleValue(const char* paramName, double defValue)
{
    return 0.0;
}

std::string LuaEngine::getStringValue(const char* paramName, const char* defValue)
{
    return "";
}

int LuaEngine::getTableIntValue(const char* tableName, const char* keyName, int defValue)
{
    SafeLua safeLua(_gL);
    lua_getglobal(_gL, tableName);
    int type = lua_type(_gL, -1);
    lua_getfield(_gL, -1, keyName);
    return lua_tointeger(_gL, -1);
}

double LuaEngine::getTableDoubleValue(const char* tableName, const char* keyName, double defValue)
{
    SafeLua safeLua(_gL);
    lua_getglobal(_gL, tableName);
    int type = lua_type(_gL, -1);
    lua_getfield(_gL, -1, keyName);
    return lua_tonumber(_gL, -1);
}

std::string LuaEngine::getTableStringValue(const char* tableName, const char* keyName, const char* defValue)
{
    SafeLua safeLua(_gL);
    lua_getglobal(_gL, tableName);
    int type = lua_type(_gL, -1);
    lua_getfield(_gL, -1, keyName);
    return lua_tostring(_gL, -1);
}
