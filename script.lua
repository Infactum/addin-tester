local inspect = require('inspect')

local lib = Load("SampleAddIn.dll")
local names = lib:GetClassNames()
print("Class names: " .. inspect(names))

local obj = lib:GetClassObject(names[1])

print("GetInfo(): " .. obj:GetInfo())
print("RegisterExtensionAs(): " .. obj:RegisterExtensionAs())

local num_props = obj:GetNProps()
print("GetNProps(): " .. num_props)
for i = 0, num_props - 1 do
    local prop_en = obj:GetPropName(i, 0)
    local prop_ru = obj:GetPropName(i, 1)
    assert(i == obj:FindProp(prop_en))
    assert(i == obj:FindProp(prop_ru))
    local attr = (obj:IsPropReadable(i) and "R" or "") .. (obj:IsPropWritable(i) and "W" or "")
    print(string.format(" [%d]: %s - %s - %s", i, prop_en, prop_ru, attr))
end

local num_meth = obj:GetNMethods()
print("GetNMethods(): " .. num_meth)
for i = 0, num_meth - 1 do
    local meth_en = obj:GetMethodName(i, 0)
    local meth_ru = obj:GetMethodName(i, 1)
    assert(i == obj:FindMethod(meth_en))
    assert(i == obj:FindMethod(meth_ru))
    local num_params = obj:GetNParams(i)
    local type = obj:HasRetVal(i) and "func" or "proc"
    print(string.format(" [%d]: %s - %s - %s - %d", i, type, meth_en, meth_ru, num_params))
end