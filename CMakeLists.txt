cmake_minimum_required(VERSION 3.0.0)
project(fileSystem VERSION 0.1.0)

include(CTest)
enable_testing()


# 添加头文件
include_directories(./fileSystem ./lib ./shellUtil)
# 查找当前目录下的所有源文件，并将名称保存到DIR_SRCS变量
aux_source_directory(./fileSystem DIR_SRCS)
aux_source_directory(./lib LIB_SRCS)
aux_source_directory(./shellUtil UTIL_SRCS)
# 指定生成目标
add_executable(main ${DIR_SRCS} ${LIB_SRCS} ${UTIL_SRCS})
# 添加链接库
target_link_libraries(main)