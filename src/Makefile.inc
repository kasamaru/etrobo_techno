mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

# C++オブジェクトファイルの定義
APPL_CXXOBJS += \
	right/rightMain.o \
	right/app/scenarioTrace.o \
	common/mid/timer.o \
	common/mid/walker.o

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
	$(mkfile_path)common/mid

# インクルードパスの設定
INCLUDES += \
	-I$(mkfile_path) \
	-I$(mkfile_path)right \
	-I$(mkfile_path)right/app \
	-I$(mkfile_path)common \
	-I$(mkfile_path)common/mid