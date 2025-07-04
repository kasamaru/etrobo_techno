mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_CXXOBJS += \
	Walker.o \
	LineWalker.o \
	Starter.o \
	ColorMonitor.o \
	GyroMonitor.o \
	SonarMonitor.o \
	PidControl.o \
	TimerWalker.o \
	ScenarioWalker.o \
	SelectPlayer.o

SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile

endif

APPL_DIRS += $(mkfile_path)app $(mkfile_path)unit

INCLUDES += \
	-I$(mkfile_path)right \
	-I$(mkfile_path)right/app \
	-I$(mkfile_path)right/mid \
	-I$(mkfile_path)left \
	-I$(mkfile_path)left/app \
	-I$(mkfile_path)left/mid \
	-I$(mkfile_path)common
	-I$(mkfile_path)common/app \
	-I$(mkfile_path)common/mid \