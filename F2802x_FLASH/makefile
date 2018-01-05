################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := c:/ti/ccsv6/tools/compiler/c2000_6.2.7

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./source/DSP2803x_Sci.obj" \
"./source/F2802x_EPwm.obj" \
"./source/F2802x_GlobalVariableDefs.obj" \
"./source/F2802x_Gpio.obj" \
"./source/SCICommu_Ctrl.obj" \
"./source/Timer.obj" \
"./source/control_loop.obj" \
"./source/f2802x_adc.obj" \
"./source/f2802x_codestartbranch.obj" \
"./source/f2802x_cputimers.obj" \
"./source/f2802x_defaultisr.obj" \
"./source/f2802x_piectrl.obj" \
"./source/f2802x_pievect.obj" \
"./source/f2802x_sysctrl.obj" \
"./source/f2802x_usdelay.obj" \
"./source/input_control.obj" \
"./source/main.obj" \
"./source/state.obj" \
"../F28027_FLASH_LED-ColorMix.cmd" \
"../F2802x_Headers_nonBIOS.cmd" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include source/subdir_vars.mk
-include subdir_rules.mk
-include source/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
28027.out \

EXE_OUTPUTS__QUOTED += \
"28027.out" \


# All Target
all: 28027.out

# Tool invocations
28027.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C2000 Linker'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.7/bin/cl2000" -v28 -ml -mt -g --define="_DEBUG" --define="LARGE_MODEL" --define="FLASH" --diag_warning=225 --gen_func_subsections=on -z --stack_size=0x300 -m"28027.map" --warn_sections -i"c:/ti/ccsv6/tools/compiler/c2000_6.2.7/lib" -i"c:/ti/ccsv6/tools/compiler/c2000_6.2.7/include" -i"D:/CCS_workspace_v6_0/28027" --reread_libs --xml_link_info="LED-ColorMix_linkInfo.xml" --rom_model -o "28027.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)
	-$(RM) "source\DSP2803x_Sci.pp" "source\F2802x_EPwm.pp" "source\F2802x_GlobalVariableDefs.pp" "source\F2802x_Gpio.pp" "source\SCICommu_Ctrl.pp" "source\Timer.pp" "source\control_loop.pp" "source\f2802x_adc.pp" "source\f2802x_cputimers.pp" "source\f2802x_defaultisr.pp" "source\f2802x_piectrl.pp" "source\f2802x_pievect.pp" "source\f2802x_sysctrl.pp" "source\input_control.pp" "source\main.pp" "source\state.pp" 
	-$(RM) "source\DSP2803x_Sci.obj" "source\F2802x_EPwm.obj" "source\F2802x_GlobalVariableDefs.obj" "source\F2802x_Gpio.obj" "source\SCICommu_Ctrl.obj" "source\Timer.obj" "source\control_loop.obj" "source\f2802x_adc.obj" "source\f2802x_codestartbranch.obj" "source\f2802x_cputimers.obj" "source\f2802x_defaultisr.obj" "source\f2802x_piectrl.obj" "source\f2802x_pievect.obj" "source\f2802x_sysctrl.obj" "source\f2802x_usdelay.obj" "source\input_control.obj" "source\main.obj" "source\state.obj" 
	-$(RM) "source\f2802x_codestartbranch.pp" "source\f2802x_usdelay.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

