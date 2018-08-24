################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_16.9.8.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./F28069_Common_Source/F2806x_Adc.obj" \
"./F28069_Common_Source/F2806x_CodeStartBranch.obj" \
"./F28069_Common_Source/F2806x_Comp.obj" \
"./F28069_Common_Source/F2806x_CpuTimers.obj" \
"./F28069_Common_Source/F2806x_DBGIER.obj" \
"./F28069_Common_Source/F2806x_DefaultIsr.obj" \
"./F28069_Common_Source/F2806x_DisInt.obj" \
"./F28069_Common_Source/F2806x_Dma.obj" \
"./F28069_Common_Source/F2806x_ECan.obj" \
"./F28069_Common_Source/F2806x_ECap.obj" \
"./F28069_Common_Source/F2806x_EPwm.obj" \
"./F28069_Common_Source/F2806x_EQep.obj" \
"./F28069_Common_Source/F2806x_GlobalVariableDefs.obj" \
"./F28069_Common_Source/F2806x_Gpio.obj" \
"./F28069_Common_Source/F2806x_HRCap.obj" \
"./F28069_Common_Source/F2806x_I2C.obj" \
"./F28069_Common_Source/F2806x_Mcbsp.obj" \
"./F28069_Common_Source/F2806x_OscComp.obj" \
"./F28069_Common_Source/F2806x_PieCtrl.obj" \
"./F28069_Common_Source/F2806x_PieVect.obj" \
"./F28069_Common_Source/F2806x_Sci.obj" \
"./F28069_Common_Source/F2806x_Spi.obj" \
"./F28069_Common_Source/F2806x_SysCtrl.obj" \
"./F28069_Common_Source/F2806x_TempSensorConv.obj" \
"./F28069_Common_Source/F2806x_usDelay.obj" \
"./User Source/LLC.obj" \
"./User Source/control.obj" \
"./User Source/main.obj" \
"../F28069.cmd" \
"../F2806x_Headers_nonBIOS.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include F28069_Common_Source/subdir_vars.mk
-include User\ Source/subdir_vars.mk
-include subdir_rules.mk
-include F28069_Common_Source/subdir_rules.mk
-include User\ Source/subdir_rules.mk
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
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
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
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
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
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
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
ModPwr_LLC_20180803.out \

EXE_OUTPUTS__QUOTED += \
"ModPwr_LLC_20180803.out" \

BIN_OUTPUTS += \
ModPwr_LLC_20180803.hex \

BIN_OUTPUTS__QUOTED += \
"ModPwr_LLC_20180803.hex" \


# All Target
all: ModPwr_LLC_20180803.out

# Tool invocations
ModPwr_LLC_20180803.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C2000 Linker'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_16.9.8.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 -g --diag_warning=225 --diag_wrap=off --display_error_number -z -m"ModPwr_LLC_20180803.map" --stack_size=0x300 --warn_sections -i"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_16.9.8.LTS/lib" -i"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_16.9.8.LTS/include" --reread_libs --diag_wrap=off --display_error_number --xml_link_info="ModPwr_LLC_20180803_linkInfo.xml" --rom_model -o "ModPwr_LLC_20180803.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

ModPwr_LLC_20180803.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: C2000 Hex Utility'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_16.9.8.LTS/bin/hex2000"  -o "ModPwr_LLC_20180803.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "F28069_Common_Source\F2806x_Adc.d" "F28069_Common_Source\F2806x_Comp.d" "F28069_Common_Source\F2806x_CpuTimers.d" "F28069_Common_Source\F2806x_DefaultIsr.d" "F28069_Common_Source\F2806x_Dma.d" "F28069_Common_Source\F2806x_ECan.d" "F28069_Common_Source\F2806x_ECap.d" "F28069_Common_Source\F2806x_EPwm.d" "F28069_Common_Source\F2806x_EQep.d" "F28069_Common_Source\F2806x_GlobalVariableDefs.d" "F28069_Common_Source\F2806x_Gpio.d" "F28069_Common_Source\F2806x_HRCap.d" "F28069_Common_Source\F2806x_I2C.d" "F28069_Common_Source\F2806x_Mcbsp.d" "F28069_Common_Source\F2806x_OscComp.d" "F28069_Common_Source\F2806x_PieCtrl.d" "F28069_Common_Source\F2806x_PieVect.d" "F28069_Common_Source\F2806x_Sci.d" "F28069_Common_Source\F2806x_Spi.d" "F28069_Common_Source\F2806x_SysCtrl.d" "F28069_Common_Source\F2806x_TempSensorConv.d" "User Source\LLC.d" "User Source\control.d" "User Source\main.d" 
	-$(RM) "F28069_Common_Source\F2806x_Adc.obj" "F28069_Common_Source\F2806x_CodeStartBranch.obj" "F28069_Common_Source\F2806x_Comp.obj" "F28069_Common_Source\F2806x_CpuTimers.obj" "F28069_Common_Source\F2806x_DBGIER.obj" "F28069_Common_Source\F2806x_DefaultIsr.obj" "F28069_Common_Source\F2806x_DisInt.obj" "F28069_Common_Source\F2806x_Dma.obj" "F28069_Common_Source\F2806x_ECan.obj" "F28069_Common_Source\F2806x_ECap.obj" "F28069_Common_Source\F2806x_EPwm.obj" "F28069_Common_Source\F2806x_EQep.obj" "F28069_Common_Source\F2806x_GlobalVariableDefs.obj" "F28069_Common_Source\F2806x_Gpio.obj" "F28069_Common_Source\F2806x_HRCap.obj" "F28069_Common_Source\F2806x_I2C.obj" "F28069_Common_Source\F2806x_Mcbsp.obj" "F28069_Common_Source\F2806x_OscComp.obj" "F28069_Common_Source\F2806x_PieCtrl.obj" "F28069_Common_Source\F2806x_PieVect.obj" "F28069_Common_Source\F2806x_Sci.obj" "F28069_Common_Source\F2806x_Spi.obj" "F28069_Common_Source\F2806x_SysCtrl.obj" "F28069_Common_Source\F2806x_TempSensorConv.obj" "F28069_Common_Source\F2806x_usDelay.obj" 
	-$(RM) "User Source\LLC.obj" "User Source\control.obj" "User Source\main.obj" 
	-$(RM) "F28069_Common_Source\F2806x_CodeStartBranch.d" "F28069_Common_Source\F2806x_DBGIER.d" "F28069_Common_Source\F2806x_DisInt.d" "F28069_Common_Source\F2806x_usDelay.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

