################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
TIM1_8_V1.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
TIM1_8_V1.list \

OBJCOPY_BIN += \
TIM1_8_V1.bin \


# All Target
all: TIM1_8_V1.elf secondary-outputs

# Tool invocations
TIM1_8_V1.elf: $(OBJS) $(USER_OBJS) D:\CAT\ Reloaded\ARM\ARM_PROJECTS_new\TIM1_8_V1\STM32F103C8TX_FLASH.ld
	arm-none-eabi-gcc -o "TIM1_8_V1.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\CAT Reloaded\ARM\ARM_PROJECTS_new\TIM1_8_V1\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="TIM1_8_V1.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

TIM1_8_V1.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "TIM1_8_V1.list"
	@echo 'Finished building: $@'
	@echo ' '

TIM1_8_V1.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "TIM1_8_V1.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
