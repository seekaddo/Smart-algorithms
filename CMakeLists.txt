cmake_minimum_required(VERSION 3.6)


project(ProjektabgabeBICSS)

#[[set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")]]
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -g -std=gnu11")   #optimise Os,Ofast,O1-2-3 -Wall -Werror

set( $MyName = "Dennis Addo" )
set(SOURCE_FILES hash.c ../BluePrint/logging.c main.c)
#set(SOURCE_FILES Test.c)
add_executable(ProjektabgabeBICSS ${SOURCE_FILES})