
# Compiler emulator into library
add_subdirectory(emulator)


add_executable(${CMAKE_PROJECT_NAME} 
               "main.c")
target_link_directories(${CMAKE_PROJECT_NAME} 
                        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../build/src/Emulator")
target_link_libraries(${CMAKE_PROJECT_NAME} 
                      EmulatorLogic)
                      