# Set minimun required version of CMake
cmake_minimum_required(VERSION 3.12)

# Set name of project (as PROJECT_NAME)
project(telnet_sim VERSION 1.0 LANGUAGES C)

# Habilitar soporte para estándares de C
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# specify the C++ standard
#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD_REQUIRED True)

# Agregar el archivo fuente
add_executable(telnet_server telnet_server.c)
# Tell CMake where to find the executable source file
#add_executable(${PROJECT_NAME}
#    main.cpp
#)


# Enlazar la librería ws2_32
target_link_libraries(telnet_server ws2_32)


#In windows, use the next command to generate de MakeFile: cmake .. -G "MinGW Makefiles"
