add_library(mcp23s17Lib
        mcp23s17.cpp
        )

if(BUILD_TESTING)
        add_executable(mcp23s17PathTest
                ${PROJECT_SOURCE_DIR}/test/lib/mcp23s17/MCP23S17PathTest.cpp
                mcp23s17.cpp
                )
        target_compile_definitions(mcp23s17PathTest PRIVATE MCP23S17_TESTING)
        add_test(NAME MCP23S17PathTest COMMAND mcp23s17PathTest)
endif()
