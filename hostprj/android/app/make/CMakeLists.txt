cmake_minimum_required(VERSION 3.22.1)

project("main")

list(APPEND src_dirs ../../../../api)
list(APPEND src_dirs ../../../../host/android/cpp)
list(APPEND src_dirs ../../../../vm)

list(APPEND ref_libs android)
list(APPEND ref_libs log)

set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 17)

foreach (dir ${src_dirs})
    file(GLOB_RECURSE list LIST_DIRECTORIES true "${dir}/*")
    foreach (item ${list})
        if (IS_DIRECTORY ${item})
            list(APPEND inc_list ${item})
        endif ()
    endforeach ()

    file(GLOB_RECURSE list "${dir}/*.cpp")
    list(APPEND src_list ${list})

endforeach ()

include_directories(
    ${inc_list}
)
add_library(
    ${CMAKE_PROJECT_NAME}
    SHARED
    ${src_list}
)
target_link_libraries(
    ${CMAKE_PROJECT_NAME}
    ${ref_libs}
)
