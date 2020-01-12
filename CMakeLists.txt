cmake_minimum_required(VERSION 3.15)
project(flightsimulatorgal)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(flightsimulatorgal main.cpp lexer.h command.h Expression.h Expression.cpp server.h ClientHandler.h MySerialServer.cpp MyTestClientHandler.cpp Solver.h CacheManager.h FileCacheManager.cpp stringReverser.cpp)

