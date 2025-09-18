#include "panel.hpp"
#include <lua.hpp>
#include "../helper/Color.hpp"

int Lua_Panel(lua_State* L) {
    int x = luaL_checkinteger(L, 1);
    int y = luaL_checkinteger(L, 2);
    int w = luaL_checkinteger(L, 3);
    int h = luaL_checkinteger(L, 4);

    SDL_Color color = {255, 255, 255, 255}; // default white

    // 5th argument: color
    if (lua_type(L, 5) == LUA_TSTRING) {
        color = HexToColor(lua_tostring(L, 5));
    } else if (lua_istable(L, 5)) {
        lua_getfield(L, 5, "r"); color.r = (Uint8)luaL_optinteger(L, -1, 255); lua_pop(L, 1);
        lua_getfield(L, 5, "g"); color.g = (Uint8)luaL_optinteger(L, -1, 255); lua_pop(L, 1);
        lua_getfield(L, 5, "b"); color.b = (Uint8)luaL_optinteger(L, -1, 255); lua_pop(L, 1);
        lua_getfield(L, 5, "a"); color.a = (Uint8)luaL_optinteger(L, -1, 255); lua_pop(L, 1);
    } else {
        return luaL_error(L, "Expected string or table for color");
    }

    // 6th argument: PanelOptions
    PanelOptions opt;
    if (lua_istable(L, 6)) {
        lua_getfield(L, 6, "border");
        if (lua_istable(L, -1)) {
            lua_getfield(L, -1, "enabled");
            opt.border.isEnabled = lua_toboolean(L, -1);
            lua_pop(L, 1);

            lua_getfield(L, -1, "thickness");
            opt.border.thickness = (int)luaL_optinteger(L, -1, 1);
            lua_pop(L, 1);

            lua_getfield(L, -1, "color");
            if (lua_type(L, -1) == LUA_TSTRING) {
                opt.border.color = HexToColor(lua_tostring(L, -1));
            } else if (lua_istable(L, -1)) {
                lua_getfield(L, -1, "r"); opt.border.color.r = (Uint8)luaL_optinteger(L, -1, 255); lua_pop(L, 1);
                lua_getfield(L, -1, "g"); opt.border.color.g = (Uint8)luaL_optinteger(L, -1, 255); lua_pop(L, 1);
                lua_getfield(L, -1, "b"); opt.border.color.b = (Uint8)luaL_optinteger(L, -1, 255); lua_pop(L, 1);
                lua_getfield(L, -1, "a"); opt.border.color.a = (Uint8)luaL_optinteger(L, -1, 255); lua_pop(L, 1);
            }
            lua_pop(L, 1); // pop color
        }
        lua_pop(L, 1); // pop border
    }

    int id = Panel(x, y, w, h, color, opt);

    // Return the ID
    lua_pushinteger(L, id);
    return 1;
}

void RegisterLuaPanel(lua_State* L) {
    lua_register(L, "Panel", Lua_Panel);
}
