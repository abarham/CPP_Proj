################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Bandit.cpp \
../Cleric.cpp \
../Dragon.cpp \
../Enemy.cpp \
../Hero.cpp \
../Mage.cpp \
../Ogre.cpp \
../Program.cpp \
../RPGDisplay.cpp \
../Warrior.cpp 

OBJS += \
./Bandit.o \
./Cleric.o \
./Dragon.o \
./Enemy.o \
./Hero.o \
./Mage.o \
./Ogre.o \
./Program.o \
./RPGDisplay.o \
./Warrior.o 

CPP_DEPS += \
./Bandit.d \
./Cleric.d \
./Dragon.d \
./Enemy.d \
./Hero.d \
./Mage.d \
./Ogre.d \
./Program.d \
./RPGDisplay.d \
./Warrior.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -pedantic -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


