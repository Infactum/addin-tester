local inspect = require('inspect')

local lib = Load("SampleAddIn.dll")
local names = lib:GetClassNames()
print("Class names: " .. inspect(names))

local obj = lib:GetClassObject(names[1])
print("GetInfo(): " .. obj:GetInfo())
print("RegisterExtensionAs(): " .. obj:RegisterExtensionAs())