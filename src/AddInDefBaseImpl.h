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

#ifndef ADDINDEFBASEIMPL_H
#define ADDINDEFBASEIMPL_H

#include <types.h>
#include <AddInDefBase.h>

class AddInDefBaseImpl : public IAddInDefBase {
public:
    AddInDefBaseImpl(const AddInDefBaseImpl &) = delete;

    AddInDefBaseImpl &operator=(const AddInDefBaseImpl &) = delete;

    static AddInDefBaseImpl &Instance() {
        static AddInDefBaseImpl instance;
        return instance;
    }

    bool ADDIN_API AddError(unsigned short wcode, const WCHAR_T *source, const WCHAR_T *descr, long scode) override;

    bool ADDIN_API Read(WCHAR_T *wszPropName, tVariant *pVal, long *pErrCode, WCHAR_T **errDescriptor) override;

    bool ADDIN_API Write(WCHAR_T *wszPropName, tVariant *pVar) override;

    bool ADDIN_API RegisterProfileAs(WCHAR_T *wszProfileName) override;

    bool ADDIN_API SetEventBufferDepth(long lDepth) override;

    long ADDIN_API GetEventBufferDepth() override;

    bool ADDIN_API ExternalEvent(WCHAR_T *wszSource, WCHAR_T *wszMessage, WCHAR_T *wszData) override;

    void ADDIN_API CleanEventBuffer() override;

    bool ADDIN_API SetStatusLine(WCHAR_T *wszStatusLine) override;

    void ADDIN_API ResetStatusLine() override;

private:
    AddInDefBaseImpl() = default;

    ~AddInDefBaseImpl() override = default;
};


#endif //ADDINDEFBASEIMPL_H
