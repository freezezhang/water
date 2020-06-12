TARGET = libwater.a

CC := g++
AR := ar rcs
RM := rm -rf 

SOURCE_EXTENSION = cc

TARGET_TYPE = $(CC) -shared
#TARGET_TYPE = $(CC)
#TARGET_TYPE = $(AR)

COMPILE_TYPE = Debug
#COMPILE_TYPE = Release

OBJECT_OUTPUT := bin
SOURCE_DIRECTORY:= 

LIBRARYS := #-lpthread
LIBRARY_PATH := #-Lpath1 -Lpath2 -Lpath3
INCLUDE_PATH := -I.

TARGET_OUTPUT := $(OBJECT_OUTPUT)/$(COMPILE_TYPE)/
SUBDIRECTORY := $(shell find $(SOURCE_DIRECTORY) -type d)
DEBUG_FLAG = -O0 -g3 -Wall -c -fmessage-length=0
RELEASE_FLAG = -O3 -Wall -c -fmessage-length=0

ifeq ($(COMPILE_TYPE), Debug)
    CFLAGS := $(DEBUG_FLAG)
else
    CFLAGS := $(RELEASE_FLAG)
endif

SOURCE_FILES := $(shell find $(SOURCE_DIRECTORY) -name *.$(SOURCE_EXTENSION))
OBJECTS := $(SOURCE_FILES:%.$(SOURCE_EXTENSION)=$(TARGET_OUTPUT)%.o)

#all target
all: dir $(TARGET_OUTPUT)$(TARGET)

dir:
	mkdir -p $(TARGET_OUTPUT);
	for val in $(SUBDIRECTORY);do \
	  mkdir -p $(TARGET_OUTPUT)$${val}; \
	done; \
	$(RM) $(TARGET_OUTPUT)/$(OBJECT_OUTPUT); \

$(TARGET_OUTPUT)$(TARGET):$(OBJECTS)
	@echo 'Building target: $@'
	@echo 'Invoking:GCC C++ Linker'
	$(TARGET_TYPE) -o $@ $^ $(LIBRARY_PATH) $(LIBRARYS)
	@echo 'Finished building target: $@'
	@echo ' '

$(TARGET_OUTPUT)%o:./%$(SOURCE_EXTENSION)
	@echo 'Building file: $<'
	@echo 'Invoking:GCC C++ Compiler'
	$(CC) $(CFLAGS) $(INCLUDE_PATH) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<" -fPIC
	@echo 'Finished building: $<'
	@echo ' '

clean:
	-$(RM) $(OBJECT_OUTPUT)/*
	-@echo ' '
.PHONY:all clean
.SECONDARY:

