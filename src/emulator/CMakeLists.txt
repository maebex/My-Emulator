
add_library(EmulatorLogic emulator.c)

add_subdirectory(config)
add_subdirectory(cpu)
add_subdirectory(instructions)
add_subdirectory(io)
add_subdirectory(memory)
add_subdirectory(utils)
