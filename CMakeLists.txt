cmake_minimum_required(VERSION 3.24)
project(SDIZOproject2)

set(CMAKE_CXX_STANDARD 17)

add_executable(SDIZOproject2 main.cpp Menu.cpp Menu.h MST/MST.cpp MST/MST.h PriorityQueue.cpp PriorityQueue.h FSP/FSP.cpp FSP/FSP.h FSP/MinHeap.cpp FSP/MinHeap.h Timer.cpp Timer.h)
