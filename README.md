# My-Emulator

This is a simplistic implementation of an ARMv6 processor in C.

## Components

### Emulator
This component contains everything related to the boot process of the system.
This includes initializing the emulator, loading the emulated program, initializing PC and SP, configuring Flags and cPU state as well as starting program execution by entering the emulator main loop.
Additionally, this component implements a bunch of API functions that wrap around functions implemented in other components, i.e. only functions defined in this component should be used to interact with the emulator.

### CPU
This component contains everything related to the state of the CPU.
This is reflected by the state of the register file.
It implements a multitude of register access functions, as well as access functions for dedicated register fields


### Memory
This component contains everything related to memory management.
In a memory area allocated in this component the stacks reside (main stack and process stack).
Furthermore, it contains data and BSS memory sections.

### Instructions
This component contains everything related to instruction execution.
This includes fetching (via CPU component), decoding and execution.
This logic is implemented using a 3-stage pipeline.

## Usage
The project is built using CMake. 
The build pipeline can be invoked by calling:

```bash
cd My-Emulator
mkdir build
cd build
cmake ..
make
./src/Emulator path/to/objfile.o
```

