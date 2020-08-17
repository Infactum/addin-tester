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

#ifndef ADDINOBJECT_H
#define ADDINOBJECT_H

#include <memory>
#include <string>

#include "ComponentBase.h"
#include "Variant.h"

class AddInObject {
public:
    explicit AddInObject(std::shared_ptr<IComponentBase> obj);

    virtual ~AddInObject();

    inline long GetInfo() { return obj_->GetInfo(); }

    std::string RegisterExtensionAs();

    inline long GetNProps() { return obj_->GetNProps(); }

    long FindProp(const std::string &name);

    std::string GetPropName(long num, long alias);

    Variant GetPropVal(long num);

    void SetPropVal(long num, Variant &v);

    inline bool IsPropReadable(long num) { return obj_->IsPropReadable(num); }

    inline bool IsPropWritable(long num) { return obj_->IsPropWritable(num); }

    inline long GetNMethods() { return obj_->GetNMethods(); }

    long FindMethod(const std::string &name);

    std::string GetMethodName(long num, long alias);

    inline long GetNParams(long num) { return obj_->GetNParams(num); }

    // GetParamDefValue

    inline bool HasRetVal(long num) { return obj_->HasRetVal(num); }

    // CallAsProc

    // CallAsFunc

private:
    std::shared_ptr<IComponentBase> obj_;
};

#endif //ADDINOBJECT_H
