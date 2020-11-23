cmake_minimum_required(VERSION 3.17)
project(adv_qck_srt C)

set(CMAKE_C_STANDARD 11)

add_executable(adv_qck_srt main.c quick_sort.c quick_sort.h)