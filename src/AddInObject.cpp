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

#include "AddInObject.h"

#include <locale>
#include <stdexcept>

#include "AddInDefBaseImpl.h"
#include "MemoryManagerImpl.h"
#include "str_convert.h"

AddInObject::AddInObject(std::shared_ptr<IComponentBase> obj)
        : obj_(std::move(obj)) {
    auto &base = AddInDefBaseImpl::Instance();
    if (!obj_->Init(&base))
        throw std::runtime_error("Init() call failed!");

    auto &mem_mgr = MemoryManagerImpl::Instance();
    if (!obj_->setMemManager(&mem_mgr))
        throw std::runtime_error("setMemManager() call failed!");

    auto locale_ = utf8_to_utf16(std::locale().name());
    obj_->SetLocale(locale_.c_str());
}

AddInObject::~AddInObject() {
    obj_->Done();
}

std::string AddInObject::RegisterExtensionAs() {
    WCHAR_T *extension_name;
    if (!obj_->RegisterExtensionAs(&extension_name))
        throw std::runtime_error("RegisterExtensionAs() call failed!");

    auto result = utf16_to_utf8(extension_name);
    MemoryManagerImpl::Instance().FreeMemory(reinterpret_cast<void **>(&extension_name));

    return result;
}
