DEPEND_FILE = depend_file

.SUFFIXES : .c .o
.SUFFIXES : .cpp .o

CSRCS = json_parser.c \
		daemonLog.c \
		becomeDaemon.c

CXXSRCS = main.cpp \
#	  filemanager.cpp

SRCS = $(CSRCS) $(CXXSRCS)

OBJC = $(CSRCS:%.c=%.o) 
OBJCXX = $(CXXSRCS:%.cpp=%.o)
OBJS = $(OBJC) $(OBJCXX)

CXX = g++
CXXFLAGS = -O2 -g -Wall -I.
LIBS = -ljson-c -lpthread
CLIBS = -Wno-write-strings
CXXLIBS = -Wno-write-strings

TARGET = ShareBerry

all : $(TARGET)

$(TARGET) : $(OBJS)
		$(CXX) $(OBJS) -o $(TARGET) $(LIBS)
.cpp.o :
	$(CXX) $(CXXFLAGS) -c $< $(CXXLIBS)
.c.o :
	$(CXX) $(CXXFLAGS) -c $< $(CLIBS)
depend:
	$(CXX) -MM $(SRCS) > $(DEPEND_FILE)

clean:
	rm -f $(OBJS) $(TARGET) $(DEPEND_FILE) core

ifneq ($(MAKECMDGOALS), clean)
ifneq ($(MAKECMDGOALS), depend)
ifneq ($(SRCS),)
-include $(DEPEND_FILE)
endif
endif
endif

