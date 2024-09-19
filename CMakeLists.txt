cmake_minimum_required(VERSION 3.25)
project(gd32 VERSION 0.1.0 LANGUAGES C ASM)
add_library(gd32F4FirmWare STATIC )

set(Peripheral_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/GD32F4xx_standard_peripheral)
set(CMSIS_GD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/GD/GD32F4xx)
set(CMSIS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS)

set(CMSIS_SRC_DIR ${CMSIS_GD_DIR}/Source)
set(CMSIS_INC_DIR ${CMSIS_GD_DIR}/Include)
set(startup_file ${CMSIS_SRC_DIR}/GCC/startup_gd32f4xx.s)

set(Peripheral_SRC_DIR ${Peripheral_DIR}/Source)
set(Peripheral_INC_DIR ${Peripheral_DIR}/Include)

file(GLOB Peripheral_SrcFiles CONFIGURE_DEPENDS ${Peripheral_SRC_DIR}/*.c)

target_sources(gd32F4FirmWare PRIVATE
    ${startup_file}
    ${CMSIS_SRC_DIR}/system_gd32f4xx.c
    ${Peripheral_SrcFiles}
)
target_include_directories(gd32F4FirmWare PUBLIC
    ${Peripheral_INC_DIR}
    ${CMSIS_DIR}
    ${CMSIS_INC_DIR}
    .
)
target_compile_definitions(gd32F4FirmWare PUBLIC
    -DGD32F425
    -DUSE_STDPERIPH_DRIVER
)

# add_executable(mydemo.elf main.c)
# target_link_libraries(mydemo.elf PRIVATE gd32F4FirmWare )
# set_target_properties(mydemo PROPERTIES 
#     OUTPUT_NAME mydemo
#     SUFFIX ".elf"
# )

# ADD_CUSTOM_COMMAND(TARGET mydemo.elf POST_BUILD 
# COMMAND ${CMAKE_OBJCOPY} -O binary mydemo.elf mydemo.bin
# COMMAND ${CMAKE_SIZE} mydemo.elf)