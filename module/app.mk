INCLUDES+=$(GOHOOP_TOP)/gcommon/inc 	

SLIBS+= 

LIBS+= 

LIBS_PATH+= 

#create dir
OUTPUT:=$(BUILD_PATH)/output
$(shell mkdir -p $(OUTPUT)/bin)
$(shell mkdir -p $(OUTPUT)/obj)

OBJDIR:=$(BUILD_PATH)/output/obj
SRCDIR:=$(BUILD_PATH)/src

PS:=cpp
CC:=g++
CPPFLAGS:=-Wall -g -O0 -march=i686
CPPFLAGS+=$(addprefix -I, $(INCLUDES))
CPPFLAGS+=$(addprefix -D, $(PRE_DEFINED))

SOURCE:=$(wildcard $(BUILD_PATH)/src/*.$(PS))
CPPSRCS:=$(notdir $(SOURCE))
OBJS:=$(patsubst %.$(PS), $(OBJDIR)/%.o, $(CPPSRCS))

LIB_FLAGS:=$(addprefix -l, $(LIBS)) $(addprefix -L, $(LIBS_PATH))
SLIB_FLAGS:=-Wl,--whole-archive $(SLIBS) -Wl,--no-whole-archive
TARGET_FILE:=$(OUTPUT)/bin/$(TARGET).$(VERSION)

$(TARGET) : $(OBJS)
	$(CC) $(CPPFLAGS) $(OBJS) -o $(TARGET_FILE) $(SLIB_FLAGS) $(LIB_FLAGS)
	@echo "++++++++++Build $(TARGET_FILE) Success++++++++++"

$(OBJDIR)/%.o:$(SRCDIR)/%.cpp
	@echo $<, `more $<|wc -l` lines
	$(CC) -c $(CPPFLAGS) -o $@ $< 

.PHONY : all install clean 

install :
	@echo "start install $(TARGET_FILE) ..."
	@echo 'install $(TARGET_FILE) complete ...'

clean :
	@rm $(OUTPUT)/obj -rf

cleanall :
	@rm $(OUTPUT) -rf
