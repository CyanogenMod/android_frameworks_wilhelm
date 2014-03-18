LOCAL_PATH:= $(call my-dir)

# slesTest_recBuffQueue

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := tests

LOCAL_C_INCLUDES:= \
	$(call include-path-for, wilhelm)

LOCAL_SRC_FILES:= \
	slesTestRecBuffQueue.cpp

LOCAL_SHARED_LIBRARIES := \
	libutils \
	libOpenSLES

ifeq ($(TARGET_OS),linux)
	LOCAL_CFLAGS += -DXP_UNIX
endif

LOCAL_MODULE:= slesTest_recBuffQueue

LOCAL_32_BIT_ONLY := true

include $(BUILD_EXECUTABLE)

# slesTest_playFdPath

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := tests

LOCAL_C_INCLUDES:= \
	$(call include-path-for, wilhelm)

LOCAL_SRC_FILES:= \
	slesTestPlayFdPath.cpp

LOCAL_SHARED_LIBRARIES := \
	libutils \
	libOpenSLES

ifeq ($(TARGET_OS),linux)
	LOCAL_CFLAGS += -DXP_UNIX
endif

LOCAL_MODULE:= slesTest_playFdPath

LOCAL_32_BIT_ONLY := true

include $(BUILD_EXECUTABLE)

# slesTest_feedback

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := tests

LOCAL_C_INCLUDES:= \
	$(call include-path-for, wilhelm)

LOCAL_SRC_FILES:= \
    slesTestFeedback.cpp

LOCAL_SHARED_LIBRARIES := \
	libutils \
	libOpenSLES

ifeq ($(TARGET_OS),linux)
	LOCAL_CFLAGS += -DXP_UNIX
	#LOCAL_SHARED_LIBRARIES += librt
endif

LOCAL_CFLAGS += -UNDEBUG

LOCAL_MODULE:= slesTest_feedback

LOCAL_32_BIT_ONLY := true

include $(BUILD_EXECUTABLE)

# slesTest_sawtoothBufferQueue

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := tests

LOCAL_C_INCLUDES:= \
	$(call include-path-for, wilhelm)

LOCAL_SRC_FILES:= \
	slesTestSawtoothBufferQueue.cpp

LOCAL_SHARED_LIBRARIES := \
	libutils \
	libOpenSLES

ifeq ($(TARGET_OS),linux)
	LOCAL_CFLAGS += -DXP_UNIX
	#LOCAL_SHARED_LIBRARIES += librt
endif

LOCAL_MODULE:= slesTest_sawtoothBufferQueue

LOCAL_32_BIT_ONLY := true

include $(BUILD_EXECUTABLE)

# slesTest_eqFdPath

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := tests

LOCAL_C_INCLUDES:= \
	$(call include-path-for, wilhelm)

LOCAL_SRC_FILES:= \
	slesTestEqFdPath.cpp

LOCAL_SHARED_LIBRARIES := \
	libutils \
	libOpenSLES

ifeq ($(TARGET_OS),linux)
	LOCAL_CFLAGS += -DXP_UNIX
endif

LOCAL_32_BIT_ONLY := true

LOCAL_MODULE:= slesTest_eqFdPath

include $(BUILD_EXECUTABLE)

# slesTest_eqOutputPath

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := tests

LOCAL_C_INCLUDES:= \
	$(call include-path-for, wilhelm)

LOCAL_SRC_FILES:= \
	slesTestEqOutputPath.cpp

LOCAL_SHARED_LIBRARIES := \
	libutils \
	libOpenSLES

ifeq ($(TARGET_OS),linux)
	LOCAL_CFLAGS += -DXP_UNIX
endif

LOCAL_MODULE:= slesTest_eqOutputPath

LOCAL_32_BIT_ONLY := true

include $(BUILD_EXECUTABLE)

# slesTest_bassboostPath

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := tests

LOCAL_C_INCLUDES:= \
	$(call include-path-for, wilhelm)

LOCAL_SRC_FILES:= \
	slesTestBassBoostPath.cpp

LOCAL_SHARED_LIBRARIES := \
	libutils \
	libOpenSLES

ifeq ($(TARGET_OS),linux)
	LOCAL_CFLAGS += -DXP_UNIX
endif

LOCAL_MODULE:= slesTest_bassboostPath

LOCAL_32_BIT_ONLY := true

include $(BUILD_EXECUTABLE)

# slesTest_virtualizer

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := tests

LOCAL_C_INCLUDES:= \
	$(call include-path-for, wilhelm)

LOCAL_SRC_FILES:= \
	slesTestVirtualizerPath.cpp

LOCAL_SHARED_LIBRARIES := \
	libutils \
	libOpenSLES

ifeq ($(TARGET_OS),linux)
	LOCAL_CFLAGS += -DXP_UNIX
endif

LOCAL_32_BIT_ONLY := true

LOCAL_MODULE:= slesTest_virtualizer

include $(BUILD_EXECUTABLE)

# slesTest_effectCapabilities

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := tests

LOCAL_C_INCLUDES:= \
	$(call include-path-for, wilhelm)

LOCAL_SRC_FILES:= \
	slesTestEffectCapabilities.cpp

LOCAL_SHARED_LIBRARIES := \
	libutils \
	libOpenSLES

ifeq ($(TARGET_OS),linux)
	LOCAL_CFLAGS += -DXP_UNIX
endif

LOCAL_MODULE:= slesTest_effectCapabilities

LOCAL_32_BIT_ONLY := true

include $(BUILD_EXECUTABLE)

# slesTest_sendToPresetReverb

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := tests

LOCAL_C_INCLUDES:= \
	$(call include-path-for, wilhelm)

LOCAL_SRC_FILES:= \
	slesTestSendToPresetReverb.cpp

LOCAL_SHARED_LIBRARIES := \
	libutils \
	libOpenSLES

ifeq ($(TARGET_OS),linux)
	LOCAL_CFLAGS += -DXP_UNIX
endif

LOCAL_MODULE:= slesTest_sendToPresetReverb

LOCAL_32_BIT_ONLY := true

include $(BUILD_EXECUTABLE)

# slesTest_decodeToBuffQueue

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := tests

LOCAL_C_INCLUDES:= \
	$(call include-path-for, wilhelm)

LOCAL_SRC_FILES:= \
	slesTestDecodeToBuffQueue.cpp

LOCAL_SHARED_LIBRARIES := \
	libutils \
	libOpenSLES

ifeq ($(TARGET_OS),linux)
	LOCAL_CFLAGS += -DXP_UNIX
endif

LOCAL_MODULE:= slesTest_decodeToBuffQueue

LOCAL_32_BIT_ONLY := true

include $(BUILD_EXECUTABLE)

###################
# slesTestDecodeAac

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := tests

LOCAL_C_INCLUDES:= \
	$(call include-path-for, wilhelm)

LOCAL_SRC_FILES:= \
	slesTestDecodeAac.cpp

LOCAL_SHARED_LIBRARIES := \
	libutils \
	libOpenSLES

LOCAL_STATIC_LIBRARIES := libcpustats

ifeq ($(TARGET_OS),linux)
	LOCAL_CFLAGS += -DXP_UNIX
endif

LOCAL_CFLAGS += -UNDEBUG

LOCAL_MODULE:= slesTest_decodeAac

LOCAL_32_BIT_ONLY := true

include $(BUILD_EXECUTABLE)

#######################################
# OpenMAX AL example code

# xaVideoDecoderCapabilities

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := tests

LOCAL_C_INCLUDES:= \
	$(call include-path-for, wilhelm)

LOCAL_SRC_FILES:= \
	xaVideoDecoderCapabilities.cpp

LOCAL_SHARED_LIBRARIES := \
	libutils \
	libOpenMAXAL

ifeq ($(TARGET_OS),linux)
	LOCAL_CFLAGS += -DXP_UNIX
endif

LOCAL_MODULE:= xaVideoDecoderCapabilities

LOCAL_32_BIT_ONLY := true

include $(BUILD_EXECUTABLE)
