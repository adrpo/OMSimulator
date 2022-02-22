detected_OS ?= $(shell uname -s)

ifeq ($(detected_OS),Darwin)
	BUILD_DIR := ../../build/mac
	INSTALL_DIR := ../../install/mac
	FEXT=.dylib
else ifeq (MINGW,$(findstring MINGW,$(detected_OS)))
	BUILD_DIR := ../../build/mingw
	INSTALL_DIR := ../../install/mingw
	FEXT=.dll
	EEXT=.exe
else
	BUILD_DIR := ../../build/linux
	INSTALL_DIR := ../../install/linux
	FEXT=.so
endif

# Should we install everything into the OMBUILDDIR?
ifeq ($(OMBUILDDIR),)
	TOP_INSTALL_DIR=$(INSTALL_DIR)
else
	TOP_INSTALL_DIR=$(OMBUILDDIR)
	HOST_SHORT_OMC=$(host_short)/omc
endif

ifeq (MINGW,$(findstring MINGW,$(detected_OS)))
	EXTRALIBS=-L../../3rdParty/FMIL/install/mingw/lib -lfmilib \
	-L../../3rdParty/cvode/install/mingw/lib -lsundials_cvode \
	-L../../3rdParty/kinsol/install/mingw/lib -lsundials_kinsol \
	-L../../3rdParty/minizip/install/mingw/lib -lminizip \
	-L../../3rdParty/Lua/install/mingw/ -llua \
	-lws2_32 -lshlwapi
endif

LINKFLAGS=-L$(TOP_INSTALL_DIR)/lib/$(HOST_SHORT_OMC) -static-libstdc++ -Wl,-Bstatic -lOMSimulator -Wl,-Bdynamic -L$(TOP_INSTALL_DIR)/bin -lomtlmsimulator $(EXTRALIBS)
COMPFLAGS=-g -I. -I$(TOP_INSTALL_DIR)/include/

all:
	g++ $(COMPFLAGS) -shared -o glue$(FEXT) glue.cpp glue_model_cs.c $(LINKFLAGS)

