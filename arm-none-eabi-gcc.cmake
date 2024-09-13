
# File: toolchain-arm-cortex-m4f.cmake
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Define the cross-compiler for ARM Cortex-M4F
set(toolchainPrifix "arm-none-eabi-")
set(CMAKE_C_COMPILER ${toolchainPrifix}gcc)
set(CMAKE_CXX_COMPILER ${toolchainPrifix}g++)
set(CMAKE_ASM_COMPILER ${toolchainPrifix}gcc)


# Specify the target architecture (Cortex-M4 with FPU)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(CPU_FLAGS "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard")

# Compiler and linker flags
set(CMAKE_C_FLAGS "${CPU_FLAGS} -Wall -Wextra -O2")
set(CMAKE_CXX_FLAGS "${CPU_FLAGS} -Wall -Wextra -O2")
# set(CMAKE_ASM_FLAGS "${CPU_FLAGS}")
SET(CMAKE_ASM_FLAGS " ${CPU_FLAGS} -ffunction-sections -fdata-sections -x assembler-with-cpp -Wa,-mimplicit-it=thumb  -gdwarf-2")
set(CMAKE_EXE_LINKER_FLAGS "${CPU_FLAGS} -cref,-u,Reset_Handler -Wl,--gc-sections -Wl,-Map=${CMAKE_PROJECT_NAME}.map")

# Specify the linker script for your specific MCU (replace with your own)
set(LINKER_SCRIPT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/link.ld")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T${LINKER_SCRIPT_PATH}")

# Specify the path to the ARM toolchain (modify to match your system's setup)
set(CMAKE_FIND_ROOT_PATH "d:/msys64/ucrt64/bin")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# Disable shared libraries (embedded targets usually use static linking)
set(BUILD_SHARED_LIBS OFF)

# For debugging
set(CMAKE_DEBUG_POSTFIX "_d")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
