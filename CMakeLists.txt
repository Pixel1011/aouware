# CMakeList.txt : CMake project for aouware, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.16)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("aouware")

# Point CMake to your Qt root (contains bin/, lib/, include/)
set(QT_ROOT "D:/c++libs/Qt/6.10.0/msvc2022_64")
set(CMAKE_PREFIX_PATH "${QT_ROOT}")

find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Collect sources from src/ (recursive). CONFIGURE_DEPENDS makes CMake
# re-run when files are added/removed (requires CMake >= 3.12).
file(GLOB_RECURSE AOU_SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.c"
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.cc"
    "${CMAKE_SOURCE_DIR}/src/*.cxx"
    "${CMAKE_SOURCE_DIR}/src/*.m"
    "${CMAKE_SOURCE_DIR}/src/*.mm"
)

# Optionally include headers (not required for build, but nice for IDEs)
file(GLOB_RECURSE AOU_HEADERS
    "${CMAKE_SOURCE_DIR}/src/*.h"
    "${CMAKE_SOURCE_DIR}/src/*.hpp"
)

# Collect all files in resources/ (e.g., your .gif)
file(GLOB_RECURSE AOU_RESOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/resources/*"
)

add_executable(aouware ${AOU_SOURCES} ${AOU_HEADERS})

# C++20
set_property(TARGET aouware PROPERTY CXX_STANDARD 20)

target_link_libraries(aouware PRIVATE Qt6::Widgets)

# Embed resources into the executable (Qt 6) - use BASE to avoid absolute-path alias error
if (AOU_RESOURCES)
  qt_add_resources(aouware "app_resources"
    PREFIX "/"
    BASE "${CMAKE_SOURCE_DIR}/resources"
    FILES ${AOU_RESOURCES}
  )
endif()

# Deploy Qt runtime after build (Windows)
if (WIN32)
  find_program(WINDEPLOYQT_EXECUTABLE NAMES windeployqt HINTS "${QT_ROOT}/bin")
  if (WINDEPLOYQT_EXECUTABLE)
    add_custom_command(TARGET aouware POST_BUILD
      COMMAND "${WINDEPLOYQT_EXECUTABLE}" $<TARGET_FILE:aouware>
      COMMENT "Deploying Qt runtime with windeployqt"
    )
  else()
    message(WARNING "windeployqt not found; Qt DLLs will not be deployed automatically.")
  endif()
endif()

# Enable automatic MOC/UIC/RCC for Qt
set_target_properties(aouware PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
)

# TODO: Add tests and install targets if needed.