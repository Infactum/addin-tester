set(TARGET engine)

include(FindLua)
find_package(Lua REQUIRED)
find_package(Boost REQUIRED COMPONENTS system filesystem)

find_path(LUABRIDGE_INCLUDE_DIRS "LuaBridge/List.h")

add_executable(${TARGET}
        AddInDefBaseImpl.cpp
        AddInDefBaseImpl.h
        AddInObject.cpp
        AddInObject.h
        AddInObjectFactory.cpp
        AddInObjectFactory.h
        MemoryManagerImpl.h
        str_convert.cpp
        str_convert.h
        main.cpp)

target_include_directories(${TARGET} PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${LUA_INCLUDE_DIR}
        ${LUABRIDGE_INCLUDE_DIRS}
        ${Boost_INCLUDE_DIRS})

target_link_libraries(${TARGET} PRIVATE
        ${Boost_LIBRARIES}
        ${LUA_LIBRARIES})

if (MSVC)
    target_compile_definitions(${TARGET} PRIVATE
            _WINDOWS
            _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING)
endif ()

add_custom_command(TARGET ${TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/script.lua $<TARGET_FILE_DIR:${TARGET}>)