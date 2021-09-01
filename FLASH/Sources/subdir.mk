################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/adc.c" \
"../Sources/buttons.c" \
"../Sources/common.c" \
"../Sources/dac.c" \
"../Sources/lptmr.c" \
"../Sources/main.c" \
"../Sources/sa_mtb.c" \
"../Sources/uart.c" \

C_SRCS += \
../Sources/adc.c \
../Sources/buttons.c \
../Sources/common.c \
../Sources/dac.c \
../Sources/lptmr.c \
../Sources/main.c \
../Sources/sa_mtb.c \
../Sources/uart.c \

OBJS += \
./Sources/adc.o \
./Sources/buttons.o \
./Sources/common.o \
./Sources/dac.o \
./Sources/lptmr.o \
./Sources/main.o \
./Sources/sa_mtb.o \
./Sources/uart.o \

C_DEPS += \
./Sources/adc.d \
./Sources/buttons.d \
./Sources/common.d \
./Sources/dac.d \
./Sources/lptmr.d \
./Sources/main.d \
./Sources/sa_mtb.d \
./Sources/uart.d \

OBJS_QUOTED += \
"./Sources/adc.o" \
"./Sources/buttons.o" \
"./Sources/common.o" \
"./Sources/dac.o" \
"./Sources/lptmr.o" \
"./Sources/main.o" \
"./Sources/sa_mtb.o" \
"./Sources/uart.o" \

C_DEPS_QUOTED += \
"./Sources/adc.d" \
"./Sources/buttons.d" \
"./Sources/common.d" \
"./Sources/dac.d" \
"./Sources/lptmr.d" \
"./Sources/main.d" \
"./Sources/sa_mtb.d" \
"./Sources/uart.d" \

OBJS_OS_FORMAT += \
./Sources/adc.o \
./Sources/buttons.o \
./Sources/common.o \
./Sources/dac.o \
./Sources/lptmr.o \
./Sources/main.o \
./Sources/sa_mtb.o \
./Sources/uart.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/adc.o: ../Sources/adc.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/adc.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/adc.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/buttons.o: ../Sources/buttons.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/buttons.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/buttons.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/common.o: ../Sources/common.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/common.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/common.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/dac.o: ../Sources/dac.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/dac.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/dac.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/lptmr.o: ../Sources/lptmr.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/lptmr.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/lptmr.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/main.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/sa_mtb.o: ../Sources/sa_mtb.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/sa_mtb.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/sa_mtb.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/uart.o: ../Sources/uart.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/uart.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/uart.o"
	@echo 'Finished building: $<'
	@echo ' '


