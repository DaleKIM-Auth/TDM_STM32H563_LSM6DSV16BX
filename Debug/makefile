################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32H5xx_HAL_Driver/Src/subdir.mk
-include Drivers/BSP/STM32H5xx_Nucleo/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
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

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := TDM_STM32H563_LSM6DSV16BX
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
TDM_STM32H563_LSM6DSV16BX.elf \

MAP_FILES += \
TDM_STM32H563_LSM6DSV16BX.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
TDM_STM32H563_LSM6DSV16BX.list \


# All Target
all: main-build

# Main-build Target
main-build: TDM_STM32H563_LSM6DSV16BX.elf secondary-outputs

# Tool invocations
TDM_STM32H563_LSM6DSV16BX.elf TDM_STM32H563_LSM6DSV16BX.map: $(OBJS) $(USER_OBJS) C:\WorkSpace\TDM_STM32H563_LSM6DSV16BX\STM32H563ZITX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "TDM_STM32H563_LSM6DSV16BX.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m33 -T"C:\WorkSpace\TDM_STM32H563_LSM6DSV16BX\STM32H563ZITX_FLASH.ld" --specs=nosys.specs -Wl,-Map="TDM_STM32H563_LSM6DSV16BX.map" -Wl,--gc-sections -static -L"C:\WorkSpace\TDM_STM32H563_LSM6DSV16BX\NanoEdgeAI" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

TDM_STM32H563_LSM6DSV16BX.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "TDM_STM32H563_LSM6DSV16BX.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) TDM_STM32H563_LSM6DSV16BX.elf TDM_STM32H563_LSM6DSV16BX.list TDM_STM32H563_LSM6DSV16BX.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
