MODULE:=gcommon
VERSION:=1.0.0
TARGET:=lib$(MODULE)
PRE_DEFINED:= 
BUILD_PATH:=$(shell pwd)

SUBDIRS:= \
	filesys \
	function \
	mapreduce \
	network \
#	iostream    

INCLUDES:=$(foreach dir, $(SUBDIRS), $(BUILD_PATH)/$(dir)) \
	$(foreach dir, $(SUBDIRS), $(BUILD_PATH)/$(dir)/inc) \
	$(GOHOOP_INC_PATH)/gsystem \
	$(GOHOOP_INC_PATH)/gutils \
	$(GOHOOP_INC_PATH)/glogger

SRCDIRS:=$(foreach dir, $(SUBDIRS), $(BUILD_PATH)/$(dir)/src)

LIBS_PATH:=$(GOHOOP_LIB_PATH)

LIBS:=gsystem glogger gutils  

SLIBS:=

OUT_HEADS:=$(wildcard $(BUILD_PATH)/*.h) \
	$(foreach dir, $(SUBDIRS), $(wildcard $(BUILD_PATH)/$(dir)/*.h)) \
	$(foreach dir, $(SUBDIRS), $(wildcard $(BUILD_PATH)/$(dir)/inc/*.h))

include $(GOHOOP_TOP)/shared.mk
