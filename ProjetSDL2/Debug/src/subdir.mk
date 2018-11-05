################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ECS.cpp \
../src/GameManager.cpp \
../src/GameObject.cpp \
../src/Map.cpp \
../src/ProjetSDL.cpp \
../src/TextureManager.cpp 

OBJS += \
./src/ECS.o \
./src/GameManager.o \
./src/GameObject.o \
./src/Map.o \
./src/ProjetSDL.o \
./src/TextureManager.o 

CPP_DEPS += \
./src/ECS.d \
./src/GameManager.d \
./src/GameObject.d \
./src/Map.d \
./src/ProjetSDL.d \
./src/TextureManager.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


