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

#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>
#include <LuaBridge/Vector.h>

#include "AddInObjectFactory.h"

using namespace luabridge;

LuaRef Load(const std::string &path, lua_State *L) {
    AddInObjectFactory factory(path);
    return {L, factory};
}

int main() {
    lua_State *L = luaL_newstate();
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

    int rc = luaL_dofile(L, "../script.lua");
    if (rc != LUA_OK)
        std::cout << lua_tostring(L, -1);

    lua_close(L);
    return 0;
}
