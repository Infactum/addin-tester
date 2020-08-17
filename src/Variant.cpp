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

#include "Variant.h"

#include <iostream>

#include "MemoryManagerImpl.h"

Variant::Variant() {
    init();
}

Variant::~Variant() {
    implementedCheck();
    free();
    MemoryManagerImpl::Instance().FreeMemory(reinterpret_cast<void **>(&content));
}

Variant::Variant(const Variant &rhs) {
    init();

    *content = *rhs.content;
    implementedCheck();

    if (content->vt == VTYPE_PWSTR && content->pwstrVal != nullptr) {
        auto size = sizeof(*content->pwstrVal) * content->wstrLen;
        MemoryManagerImpl::Instance().AllocMemory(reinterpret_cast<void **>(&content->pwstrVal), size);
        std::memcpy(content->pwstrVal, rhs.content->pwstrVal, size);
    } else if (content->vt == VTYPE_BLOB && content->pstrVal != nullptr) {
        auto size = sizeof(*content->pstrVal) * content->strLen;
        MemoryManagerImpl::Instance().AllocMemory(reinterpret_cast<void **>(&content->pstrVal), size);
        std::memcpy(content->pstrVal, rhs.content->pstrVal, size);
    }

}

Variant &Variant::operator=(const Variant &rhs) {
    Variant(rhs).Swap(*this);
    return *this;
}

void Variant::Swap(Variant &rhs) {
    std::swap(content, rhs.content);
}

void Variant::implementedCheck() {
    // TODO: Implement support of all tVariant types and remove this check
    switch (content->vt) {
        case VTYPE_EMPTY:
        case VTYPE_I4:
        case VTYPE_R8:
        case VTYPE_BOOL:
        case VTYPE_BLOB:
        case VTYPE_PWSTR:
            break;
        default:
            std::cerr << "Cannot handle variant type of " << content->vt << std::endl;
            exit(1);
    }
}

Variant &Variant::operator=(const int32_t &rhs) {
    free();
    tVarInit(content);
    content->vt = VTYPE_I4;
    content->lVal = rhs;
    return *this;
}

Variant &Variant::operator=(const double &rhs) {
    free();
    tVarInit(content);
    content->vt = VTYPE_R8;
    content->dblVal = rhs;
    return *this;
}

Variant &Variant::operator=(const bool &rhs) {
    free();
    tVarInit(content);
    content->vt = VTYPE_BOOL;
    content->bVal = rhs;
    return *this;
}

Variant &Variant::operator=(const std::basic_string_view<WCHAR_T> &rhs) {
    free();
    tVarInit(content);
    content->vt = VTYPE_PWSTR;
    content->wstrLen = rhs.size();

    auto size = sizeof(*content->pwstrVal) * rhs.length();
    MemoryManagerImpl::Instance().AllocMemory(reinterpret_cast<void **>(&content->pwstrVal), size);
    std::memcpy(content->pwstrVal, rhs.data(), size);

    return *this;
}

void Variant::init() {
    MemoryManagerImpl::Instance().AllocMemory(reinterpret_cast<void **>(&content), sizeof(*content));
    tVarInit(content);
}

void Variant::free() {
    if (content->vt == VTYPE_PWSTR && content->pwstrVal != nullptr) {
        MemoryManagerImpl::Instance().FreeMemory(reinterpret_cast<void **>(&content->pwstrVal));
    } else if (content->vt == VTYPE_BLOB && content->pstrVal != nullptr) {
        MemoryManagerImpl::Instance().FreeMemory(reinterpret_cast<void **>(&content->pstrVal));
    }
}

Variant::operator int32_t() {
    if (content->vt != VTYPE_I4)
        throw std::bad_cast();

    return content->lVal;
}

Variant::operator double() {
    if (content->vt != VTYPE_R8)
        throw std::bad_cast();

    return content->dblVal;
}

Variant::operator bool() {
    if (content->vt != VTYPE_BOOL)
        throw std::bad_cast();

    return content->bVal;
}

Variant::operator std::basic_string_view<WCHAR_T>() {
    if (content->vt != VTYPE_PWSTR)
        throw std::bad_cast();

    return {content->pwstrVal, content->wstrLen};
}
