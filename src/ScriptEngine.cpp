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

#include <variant>

#include "str_convert.h"

using namespace luabridge;

typedef std::variant<int32_t, double> LuaNumber;

// This one gives us a way to distinct integers and doubles inside LuaRef
template<>
struct Stack<LuaNumber> {
    static LuaNumber get(lua_State *L, int index) {
        int is_num;
        lua_Integer int_val = lua_tointegerx(L, index, &is_num);
        if (is_num)
            return static_cast<int32_t>(int_val);
        else
            return static_cast<double>(luaL_checknumber(L, index));
    }

    static bool isInstance(lua_State *L, int index) {
        return lua_type(L, index) == LUA_TNUMBER;
    }
};

LuaRef Load(const std::string &path, lua_State *L) {
    AddInObjectFactory factory(path);
    return {L, factory};
}

LuaRef VariantToLua(Variant *v, lua_State *L) {
    switch (v->Index()) {
        case VTYPE_EMPTY:
            return L;
        case VTYPE_I4:
            return {L, static_cast<int32_t>(*v)};
        case VTYPE_R8:
            return {L, static_cast<double>(*v)};
        case VTYPE_BOOL:
            return {L, static_cast<bool>(*v)};
        case VTYPE_PWSTR:
            return {L, utf16_to_utf8(static_cast<std::basic_string_view<WCHAR_T>>(*v))};
        default:
            throw std::bad_cast();
    }
}

Variant LuaToVariant(const LuaRef &val) {
    Variant v;

    if (val.isNil()) {
    } else if (val.isBool()) {
        v = val.cast<bool>();
    } else if (val.isNumber()) {
        auto tmp = val.cast<LuaNumber>();
        if (std::holds_alternative<int32_t>(tmp))
            v = std::get<int32_t>(tmp);
        else if (std::holds_alternative<double>(tmp))
            v = std::get<double>(tmp);
    } else if (val.isString()) {
        auto str = val.cast<std::string>();
        v = utf8_to_utf16(str);
    } else {
        throw std::bad_cast();
    }

    return v;
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
            .addFunction("GetNProps", &AddInObject::GetNProps)
            .addFunction("FindProp", &AddInObject::FindProp)
            .addFunction("GetPropName", &AddInObject::GetPropName)
            .addFunction("GetPropVal", &AddInObject::GetPropVal)
            .addFunction("SetPropVal", &AddInObject::SetPropVal)
            .addFunction("IsPropReadable", &AddInObject::IsPropReadable)
            .addFunction("IsPropWritable", &AddInObject::IsPropWritable)
            .addFunction("GetNMethods", &AddInObject::GetNMethods)
            .addFunction("FindMethod", &AddInObject::FindMethod)
            .addFunction("GetMethodName", &AddInObject::GetMethodName)
            .addFunction("GetNParams", &AddInObject::GetNParams)
            .addFunction("GetParamDefValue", &AddInObject::GetParamDefValue)
            .addFunction("HasRetVal", &AddInObject::HasRetVal)
            // CallAsProc
            // CallAsFunc
            .endClass();

    getGlobalNamespace(L)
            .beginClass<Variant>("v")
            .endClass();

    getGlobalNamespace(L)
            .beginClass<Variant>("Variant")
            .addFunction("Value", &VariantToLua)
            .endClass();

    getGlobalNamespace(L)
            .addFunction("Variant", &LuaToVariant)
            .addFunction("Load", &Load);
}

ScriptEngine::~ScriptEngine() {
    lua_close(L);
}

void ScriptEngine::Run(std::string_view path) {
    if (luaL_dofile(L, path.data()) != LUA_OK)
        throw std::runtime_error(lua_tostring(L, -1));
}
