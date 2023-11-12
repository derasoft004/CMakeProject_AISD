# CMakeList.txt: файл проекта CMake верхнего уровня; проведите глобальную конфигурацию
# и включите сюда подпроекты.
#
cmake_minimum_required (VERSION 3.8)

project ("CMakeProject_AISD")

# Включите подпроекты.
add_subdirectory ("CMakeProject_AISD")

add_executable(console "CMakeProject_AISD/console.cpp")
