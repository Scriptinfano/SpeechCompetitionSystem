cmake_minimum_required(VERSION 3.22)
project(speechCompetitionManageSystem)

set(CMAKE_CXX_STANDARD 23)

add_executable(speechCompetitionManageSystem speechCompetition.cpp speechManager.h speechManager.cpp speechPlayer.h)
