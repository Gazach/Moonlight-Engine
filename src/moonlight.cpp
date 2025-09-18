#include "core/lua/bindings.h"
#include "client/client.hpp"
#include <lua.hpp>

int main() {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    RegisterAllLuaFunctions(L);

    // Instead of just running test.lua, open Project Manager
    RunClient(L);

    lua_close(L);
    return 0;
}