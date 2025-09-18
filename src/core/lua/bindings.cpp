#include "bindings.h"
#include "../logs/luaLogger.hpp"
#include "../module/UI/panel/panel_bind.hpp"

void RegisterAllLuaFunctions(lua_State* L) {
    // Register all custom Lua functions here
    // Helper function registrations
    RegisterLuaLogger(L);   // Custom logger functions

    // UI Panel functions
    RegisterLuaPanel(L);

    // Add more registrations as needed
}