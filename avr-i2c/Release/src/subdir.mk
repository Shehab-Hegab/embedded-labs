################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/I2c.c \
../src/Rtc.c \
../src/Usart.c \
../src/main.c 

OBJS += \
./src/I2c.o \
./src/Rtc.o \
./src/Usart.o \
./src/main.o 

C_DEPS += \
./src/I2c.d \
./src/Rtc.d \
./src/Usart.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\SD\Eclipse-Workspaces\eclipse-cpp\avr\avr-i2c\include" -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32a -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


