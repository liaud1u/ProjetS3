################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cmake-build-debug/CMakeFiles/3.12.3/CompilerIdC/CMakeCCompilerId.c 

OBJS += \
./cmake-build-debug/CMakeFiles/3.12.3/CompilerIdC/CMakeCCompilerId.o 

C_DEPS += \
./cmake-build-debug/CMakeFiles/3.12.3/CompilerIdC/CMakeCCompilerId.d 


# Each subdirectory must supply rules for building sources it contributes
cmake-build-debug/CMakeFiles/3.12.3/CompilerIdC/%.o: ../cmake-build-debug/CMakeFiles/3.12.3/CompilerIdC/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


