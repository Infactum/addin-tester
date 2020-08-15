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

#ifndef MEMORYMANAGERIMPL_H
#define MEMORYMANAGERIMPL_H

#include <types.h>
#include <IMemoryManager.h>

class MemoryManagerImpl : public IMemoryManager {
public:
    MemoryManagerImpl(const MemoryManagerImpl &) = delete;

    MemoryManagerImpl &operator=(const MemoryManagerImpl &) = delete;

    static MemoryManagerImpl &Instance() {
        static MemoryManagerImpl instance;
        return instance;
    }

    inline bool ADDIN_API AllocMemory(void **pMemory, unsigned long ulCountByte) override {
        *pMemory = malloc(ulCountByte);
        return *pMemory != nullptr;
    };

    inline void ADDIN_API FreeMemory(void **pMemory) override {
        free(*pMemory);
    };

private:
    MemoryManagerImpl() = default;

    ~MemoryManagerImpl() override = default;
};


#endif //MEMORYMANAGERIMPL_H
