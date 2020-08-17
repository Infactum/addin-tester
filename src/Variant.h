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

#ifndef SMARTVARIANT_H
#define SMARTVARIANT_H

#include <utility>
#include <string_view>

#include "types.h"

class Variant {
public:
    Variant();

    template<class T>
    explicit Variant(T from) : Variant() { *this = from; };

    virtual ~Variant();

    Variant(const Variant &rhs);

    Variant &operator=(const Variant &rhs);

    Variant &operator=(const int32_t &rhs);

    Variant &operator=(const double &rhs);

    Variant &operator=(const bool &rhs);

    Variant &operator=(const std::basic_string_view<WCHAR_T> &rhs);

    explicit operator int32_t();

    explicit operator double();

    explicit operator bool();

    explicit operator std::basic_string_view<WCHAR_T>();

    void Swap(Variant &rhs);

    inline tVariant *Get() { return content; }

    inline int Index() { return content->vt; }

private:
    void implementedCheck();

    void init();

    void free();

    tVariant *content{nullptr};
};


#endif //SMARTVARIANT_H
