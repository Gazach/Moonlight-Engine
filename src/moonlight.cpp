#include "core/lua/bindings.h"
#include "client/client.hpp"
#include <lua.hpp>

int main() {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    // Register everything in one place
    RegisterAllLuaFunctions(L);

    luaL_dofile(L, "test.lua");
    lua_close(L);

    RunClient();
}