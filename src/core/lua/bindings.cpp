#include "bindings.h"
#include "../logs/luaLogger.hpp"

void RegisterAllLuaFunctions(lua_State* L) {
    RegisterLuaLogger(L);   // add more later, like RegisterMoonMath(L);
}