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

#include "AddInObjectFactory.h"

#include "str_convert.h"

std::vector<std::string> split(std::string s, const std::string &delimiter) {
    std::vector<std::string> result;

    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        result.emplace_back(token);
        s.erase(0, pos + delimiter.length());
    }
    result.emplace_back(s);

    return result;
}

std::vector<std::string> AddInObjectFactory::GetClassNames() {
    auto getClassNames = lib.get<WCHAR_T *()>("GetClassNames");
    auto names = utf16_to_utf8(getClassNames());
    return split(names, "|");
}

AddInObject AddInObjectFactory::GetClassObject(const std::string &name) {
    auto getClassObject = lib.get<long(const WCHAR_T *, IComponentBase **)>("GetClassObject");

    IComponentBase *ptr{nullptr};
    auto name_ = utf8_to_utf16(name);
    if (getClassObject(name_.c_str(), &ptr) == 0)
        throw std::runtime_error("Failed to create object!");

    auto obj = std::shared_ptr<IComponentBase>(ptr, [lib = lib](IComponentBase *obj) {
        auto destroyObject = lib.get<long(IComponentBase **)>("DestroyObject");
        destroyObject(&obj);
    });

    return AddInObject(obj);
}
