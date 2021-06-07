################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include Drivers/STM32F7xx_HAL_Driver/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Regulacja_swiatla.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Regulacja_swiatla.list \

OBJCOPY_BIN += \
Regulacja_swiatla.bin \


# All Target
all: Regulacja_swiatla.elf secondary-outputs

# Tool invocations
Regulacja_swiatla.elf: $(OBJS) $(USER_OBJS) C:\Users\skibi\OneDrive\Pulpit\regulacja_swiatla\STM32F746ZGTX_FLASH.ld
	arm-none-eabi-gcc -o "Regulacja_swiatla.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"C:\Users\skibi\OneDrive\Pulpit\regulacja_swiatla\STM32F746ZGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Regulacja_swiatla.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Regulacja_swiatla.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Regulacja_swiatla.list"
	@echo 'Finished building: $@'
	@echo ' '

Regulacja_swiatla.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Regulacja_swiatla.bin"
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
