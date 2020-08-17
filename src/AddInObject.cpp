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

long AddInObject::FindProp(const std::string &name) {
    auto name_ = utf8_to_utf16(name);
    return obj_->FindProp(name_.c_str());
}

std::string AddInObject::GetPropName(long num, long alias) {
    auto name = obj_->GetPropName(num, alias);
    return utf16_to_utf8(name);
}

Variant AddInObject::GetPropVal(long num) {
    Variant result;
    if (!obj_->GetPropVal(num, result.Get()))
        throw std::runtime_error("GetPropVal() call failed!");

    return result;
}

void AddInObject::SetPropVal(long num, Variant &v) {
    if (!obj_->SetPropVal(num, v.Get()))
        throw std::runtime_error("SetPropVal() call failed!");
}

long AddInObject::FindMethod(const std::string &name) {
    auto name_ = utf8_to_utf16(name);
    return obj_->FindMethod(name_.c_str());
}

std::string AddInObject::GetMethodName(long num, long alias) {
    auto name = obj_->GetMethodName(num, alias);
    return utf16_to_utf8(name);
}

Variant AddInObject::GetParamDefValue(long meth_num, long param_num) {
    // FIXME: it might be good idea to return pair of has_param / value
    Variant result;
    obj_->GetParamDefValue(meth_num, param_num, result.Get());
    return result;
}
