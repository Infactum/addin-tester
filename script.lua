--[[
    Attention!
    AddInObjectFactory (Load call result) and AddInObject (GetClassObject call result) cannot be copied.
    Even if you make a copy of such objects with Lua they'll still share internal C++ object reference.
-- ]]

local function describe(obj)
    local header = [[
  API Version: %d
  Registers as: %s]]
    print(string.format(header, obj:GetInfo(), obj:RegisterExtensionAs()))

    local prop_header = [[
  Properties (%d):]]
    local num_props = obj:GetNProps()
    print(string.format(prop_header, num_props))

    local prop_desc = [[
    - Alias: %s / %s
      Access: %s
      Default: %s]]

    for i = 0, num_props - 1 do
        local prop_en = obj:GetPropName(i, 0)
        local prop_ru = obj:GetPropName(i, 1)
        assert(i == obj:FindProp(prop_en))
        assert(i == obj:FindProp(prop_ru))
        local attr = (obj:IsPropReadable(i) and "R" or "") .. (obj:IsPropWritable(i) and "W" or "")
        local def_val = obj:GetPropVal(i):Value()
        print(string.format(prop_desc, prop_en, prop_ru, attr, tostring(def_val)))
    end

    local meth_header = [[
  Methods (%d):]]

    local num_meth = obj:GetNMethods()
    print(string.format(meth_header, num_meth))

    local meth_desc = [[
    - Alias: %s / %s
      Type: %s
      Params: %d
      Defaults:]]
    local meth_desc_def_i = [[
        [%d]: %s]]

    for i = 0, num_meth - 1 do
        local meth_en = obj:GetMethodName(i, 0)
        local meth_ru = obj:GetMethodName(i, 1)
        assert(i == obj:FindMethod(meth_en))
        assert(i == obj:FindMethod(meth_ru))
        local num_params = obj:GetNParams(i)
        local type = obj:HasRetVal(i) and "func" or "proc"
        print(string.format(meth_desc, meth_en, meth_ru, type, num_params))

        for j = 0, num_params - 1 do
            local def_val = obj:GetParamDefValue(i, j):Value()
            print(string.format(meth_desc_def_i, j, tostring(def_val)))
        end
    end

end

local lib = Load("SampleAddIn.dll")
local names = lib:GetClassNames()
for i = 1, #names do
    print(string.format("Class %s:", names[i]))
    local obj = lib:GetClassObject(names[1])
    describe(obj)
    print()
end
