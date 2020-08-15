/*
 *  AddIn Tester
 *  Copyright (C) 2020  Infactum
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include "ScriptEngine.h"

using namespace luabridge;

LuaRef Load(const std::string &path, lua_State *L) {
    AddInObjectFactory factory(path);
    return {L, factory};
}

ScriptEngine::ScriptEngine() : L(luaL_newstate()) {
    luaL_openlibs(L);

    getGlobalNamespace(L)
            .beginClass<AddInObjectFactory>("AddInFactory")
            .addFunction("GetClassNames", &AddInObjectFactory::GetClassNames)
            .addFunction("GetClassObject", &AddInObjectFactory::GetClassObject)
            .endClass();

    getGlobalNamespace(L)
            .beginClass<AddInObject>("AddInObject")
            .addFunction("GetInfo", &AddInObject::GetInfo)
            .addFunction("RegisterExtensionAs", &AddInObject::RegisterExtensionAs)
            .endClass();

    getGlobalNamespace(L)
            .addFunction("Load", &Load);
}

ScriptEngine::~ScriptEngine() {
    lua_close(L);
}

void ScriptEngine::Run(std::string_view path) {
    if (luaL_dofile(L, path.data()) != LUA_OK)
        throw std::runtime_error(lua_tostring(L, -1));
}
