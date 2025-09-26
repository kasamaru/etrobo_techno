mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

# C++オブジェクトファイルの定義
APPL_CXXOBJS += \
	rightMain.o \
	pidCtrl.o \
	scenarioTrace.o \
	lineTrace.o\
	timer.o \
	walker.o \
	starter.o \
	lineMonitor.o 

# 言語設定
SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-spike/Makefile

endif

# アプリケーションディレクトリの追加
APPL_DIRS += \
	$(mkfile_path) \
	$(mkfile_path)right \
	$(mkfile_path)right/app \
	$(mkfile_path)common/mid \
	$(mkfile_path)common/app

# インクルードパスの設定
INCLUDES += \
	-I$(mkfile_path) \
	-I$(mkfile_path)right \
	-I$(mkfile_path)right/app \
	-I$(mkfile_path)common \
	-I$(mkfile_path)common/mid \
	-I$(mkfile_path)common/app