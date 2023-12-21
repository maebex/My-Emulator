
# Compiler emulator into library
add_subdirectory(emulator)

add_executable(${CMAKE_PROJECT_NAME} 
               "main.c")
target_link_directories(${CMAKE_PROJECT_NAME} 
                        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../build/src/Emulator")
target_link_libraries(${CMAKE_PROJECT_NAME} 
                      EmulatorLogic)

link_directories("${CMAKE_CURRENT_SOURCE_DIR}/../submodules/Unity/build")
link_libraries(unity)
include_directories("${PROJECT_SOURCE_DIR}/submodules")
          


#-------------------------------------------------
# TESTING
#-------------------------------------------------
#
# Unity
# Cmake and Unity example: https://www.poisel.info/posts/2019-07-15-cmake-unity-integration/
include(CTest)
add_subdirectory(${PROJECT_SOURCE_DIR}/test/cpu ${PROJECT_SOURCE_DIR}/build/utst/cpu)
add_subdirectory(${PROJECT_SOURCE_DIR}/test/memory ${PROJECT_SOURCE_DIR}/build/utst/memory)

