#include "MoonLoggers.hpp"
#include <lua.hpp>
int Lua_Logger(lua_State* L) {
    const char* msg = luaL_checkstring(L, 1);
    Logger::Log(LogLevel::Info, "System", msg);
    return 0;
}
int Lua_LoggerDebug(lua_State* L) {
    const char* msg = luaL_checkstring(L, 1);
    Logger::Log(LogLevel::Debug, "System", msg);
    return 0;
}
int Lua_LoggerError(lua_State* L) {
    const char* msg = luaL_checkstring(L, 1);
    Logger::Log(LogLevel::Error, "System", msg);
    return 0;
}
int Lua_LoggerWarning(lua_State* L) {
    const char* msg = luaL_checkstring(L, 1);
    Logger::Log(LogLevel::Warning, "System", msg);
    return 0;
}
// Register the function
void RegisterLuaLogger(lua_State* L) {
    lua_register(L, "Logger", Lua_Logger);
    lua_register(L, "LoggerDebug", Lua_LoggerDebug);
    lua_register(L, "LoggerWarning", Lua_LoggerWarning);
    lua_register(L, "LoggerError", Lua_LoggerError);

}