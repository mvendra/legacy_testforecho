
.PHONY : all clean compile link 

APPNAME=testforecho_testapp

BASE_SRC=../../src
BASE_OBJ=../../build
RUN=../../run

SRC=main.cpp test_testforecho.cpp
#SRC_FULL=$(addprefix $(BASE_SRC)/, $(SRC))
#OBJ=$(SRC:.cpp=.o) 
#OBJ_FULL=$(addprefix $(BASE_OBJ)/, $(OBJ))
COMPILER=g++

ARCH := $(shell getconf LONG_BIT)
PLAT=linux

ifeq ($(MODE),)
	MODE=debug
endif

ifeq ($(MODE),debug)
BASE_OBJ_FULL=$(BASE_OBJ_FULL)_
INTFLAGS = \
	-g \
	-Wall \
	-Wextra \
	-pedantic \
	-Weffc++ \
	-Werror \
	-fPIC \
	-pthread \
	-D_GLIBCXX_DEBUG \
	-std=c++14
POSTBUILD=
#DEFINES= -D _DEBUG -D _LOG 
endif

ifeq ($(MODE),release)
INTFLAGS = \
 	-O2 \
	-Wall \
	-Wextra \
	-pedantic \
	-Weffc++ \
	-Werror \
	-fPIC \
	-std=c++14
POSTBUILD= strip $(FULL_APP_NAME)
#DEFINES= -D _LOG 
endif

ifeq ($(ARCH),64)
CPPFLAGS = $(INTFLAGS) -m64
else 
CPPFLAGSS = $(INTFLAGS)
endif

INCLUDES=-I$(BASE_SRC)
LDFLAGS=

BASE_OBJ_FULL=$(BASE_OBJ)/$(PLAT)_x$(ARCH)_$(MODE)
RUN_FULL=$(RUN)/$(PLAT)_x$(ARCH)_$(MODE)
ALL_OBJS=$(foreach src,$(SRC),$(BASE_OBJ_FULL)/$(src:.cpp=.o))
FULL_APP_NAME=$(RUN_FULL)/$(APPNAME)

all: compile link 

compile:
	$(foreach src,$(SRC),$(COMPILER) $(INCLUDES) $(CPPFLAGS) -c $(BASE_SRC)/$(src) -o $(BASE_OBJ_FULL)/$(src:.cpp=.o);)

link:
	$(COMPILER) -o $(FULL_APP_NAME) $(ALL_OBJS) $(LDFLAGS)
	$(POSTBUILD)

clean:
	$(foreach objs,$(ALL_OBJS),rm -rf $(objs);)
	rm -rf $(FULL_APP_NAME)

