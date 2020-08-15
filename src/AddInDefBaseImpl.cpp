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

#include "AddInDefBaseImpl.h"

#include <stdexcept>

bool AddInDefBaseImpl::AddError(unsigned short wcode, const WCHAR_T *source, const WCHAR_T *descr, long scode) {
    throw std::runtime_error("AddInDefBase::AddError not implemented!");
}

bool AddInDefBaseImpl::Read(WCHAR_T *wszPropName, tVariant *pVal, long *pErrCode, WCHAR_T **errDescriptor) {
    throw std::runtime_error("AddInDefBase::Read not implemented!");
}

bool AddInDefBaseImpl::Write(WCHAR_T *wszPropName, tVariant *pVar) {
    throw std::runtime_error("AddInDefBase::Write not implemented!");
}

bool AddInDefBaseImpl::RegisterProfileAs(WCHAR_T *wszProfileName) {
    throw std::runtime_error("AddInDefBase::RegisterProfileAs not implemented!");
}

bool AddInDefBaseImpl::SetEventBufferDepth(long lDepth) {
    throw std::runtime_error("AddInDefBase::SetEventBufferDepth not implemented!");
}

long AddInDefBaseImpl::GetEventBufferDepth() {
    throw std::runtime_error("AddInDefBase::GetEventBufferDepth not implemented!");
}

bool AddInDefBaseImpl::ExternalEvent(WCHAR_T *wszSource, WCHAR_T *wszMessage, WCHAR_T *wszData) {
    throw std::runtime_error("AddInDefBase::ExternalEvent not implemented!");
}

void AddInDefBaseImpl::CleanEventBuffer() {
    throw std::runtime_error("AddInDefBase::CleanEventBuffer not implemented!");
}

bool AddInDefBaseImpl::SetStatusLine(WCHAR_T *wszStatusLine) {
    throw std::runtime_error("AddInDefBase::SetStatusLine not implemented!");
}

void AddInDefBaseImpl::ResetStatusLine() {
    throw std::runtime_error("AddInDefBase::ResetStatusLine not implemented!");
}


