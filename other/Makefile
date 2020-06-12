CC = g++
LFLAGS = -m64
CFLAGS += -c --std=c++0x
	
ifdef RELEASE
	CFLAGS += -O3
	LFLAGS += -O3
else
	CFLAGS += -g -DDEBUG 
	LFLAGS += -g -lpthread 
endif

TARGET = ./memory_pool
SOURCES += \
	main.cc \
	memory_pool.cc \


OBJS = $(SOURCES:%.cc=objs/%.o) 
DEPS = $(SOURCES:%.cc=objs/%.d)

default : $(TARGET)
rebuild : clean default

objs/%.d: %.cc
	@$(CC) -MM $(CFLAGS) $< | sed 's, \($*\)\.o[ :]*,obj/\1.o $@ : ,g' > $@
	
objs/%.o: %.cc
	@$(CC) $(CFLAGS) -o $@ $<
	
-include $(DEPS)

clean :
	rm -f $(TARGET) objs/*

$(TARGET) : $(OBJS)
	$(CC) $(LFLAGS) -o $@ $(OBJS)
