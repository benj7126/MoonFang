cmake_minimum_required(VERSION 3.12)
project(MoonFang VERSION 0.1.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(FetchContent)

option (FORCE_COLORED_OUTPUT "Always produce ANSI-colored output (GNU/Clang only)." TRUE)

if (${FORCE_COLORED_OUTPUT})
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
       add_compile_options (-fdiagnostics-color=always)
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
       add_compile_options (-fcolor-diagnostics)
    endif ()
endif ()

find_package(X11 REQUIRED)
# find_package(GLib REQUIRED)
# find_package(GObject REQUIRED)
# find_package(HarfBuzz REQUIRED)
find_package(Freetype REQUIRED)

file(GLOB_RECURSE MoonFang_src
  "src/*.cpp"
)

add_executable(MoonFang
  ${MoonFang_src}
)

set_target_properties(MoonFang PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF)

target_include_directories(MoonFang PRIVATE include ${X11_INCLUDE_DIR} ${X11_Xft_INCLUDE_PATH} ${FREETYPE_INCLUDE_DIRS})

target_link_libraries(MoonFang ${X11_LIBRARIES} ${X11_Xft_LIB} ${FREETYPE_LIBRARIES} Xrender)
