################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include FreeRTOS_src/subdir.mk
-include FreeRTOS_portable/MemMang/subdir.mk
-include FreeRTOS_portable/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: TP1_ghostbuster_etu.axf

# Tool invocations
TP1_ghostbuster_etu.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"/Users/gaetan/Hepia_MEGA/temps_reel/ghost-buster/Debug" -L"/Users/gaetan/MEGAsync/workspace_lpcexpresso/Temps_Reel/CMSISv2p00_LPC17xx/Debug" -Xlinker -Map="TP1_ghostbuster_etu.map" -Xlinker --defsym=__user_heap_base=__end_bss_RAM2 -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "TP1_ghostbuster_Debug.ld" -o "TP1_ghostbuster_etu.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) TP1_ghostbuster_etu.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "TP1_ghostbuster_etu.axf"; # arm-none-eabi-objcopy -O binary "TP1_ghostbuster_etu.axf" "TP1_ghostbuster_etu.bin" ; checksum -p LPC1769 -d "TP1_ghostbuster_etu.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
