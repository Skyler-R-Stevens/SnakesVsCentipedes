# CMakeList.txt : CMake project for Snakes Vs Centipedes, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("SnakesVsCentipedes")

find_package(SFML COMPONENTS Graphics REQUIRED)

# Add source to this project's executable.
add_executable (
    SnakesVsCentipedes
    Main.cpp
    Game.cpp
    Game.h
    Menu.cpp
    Menu.h
    Snake.cpp
    Snake.h
    GameOverScreen.cpp
    GameOverScreen.h
    Map.cpp
    Map.h
    GameMode.h
    RoundSettings.h
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SnakesVsCentipedes PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
target_link_libraries(
    SnakesVsCentipedes
    PRIVATE
    SFML::Graphics
)

add_custom_command(
    TARGET SnakesVsCentipedes
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/assets"
            "$<TARGET_FILE_DIR:SnakesVsCentipedes>/assets"
)