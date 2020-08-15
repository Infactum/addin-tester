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

#ifndef SCRIPTENGINE_H
#define SCRIPTENGINE_H

#include <boost/core/noncopyable.hpp>

#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>
#include <LuaBridge/Vector.h>

#include "AddInObjectFactory.h"

class ScriptEngine : private boost::noncopyable {
public:
    ScriptEngine();

    virtual ~ScriptEngine();

    void Run(std::string_view path);

private:
    lua_State *L;
};


#endif //SCRIPTENGINE_H
