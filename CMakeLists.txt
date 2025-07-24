cmake_minimum_required(VERSION 3.27)
project(DA_Project_2)

set(CMAKE_CXX_STANDARD 26)

add_executable(DA_Project_2 main.cpp
        src/DeliveryManager.cpp
        data_structures/Heap.cpp
        data_structures/UFDS.cpp)
