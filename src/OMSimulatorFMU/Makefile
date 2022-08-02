detected_OS ?= $(shell uname -s)

ifeq ($(detected_OS),Darwin)
	BUILD_DIR := ../../build/mac
	INSTALL_DIR := ../../install/mac
	FEXT=.dylib
	TLMLIB=-lomtlmsimulator
	OMSIMULATORLIB=-l:libOMSimulator.a
else ifeq (MINGW,$(findstring MINGW,$(detected_OS)))
	BUILD_DIR := ../../build/mingw
	INSTALL_DIR := ../../install/mingw
	FEXT=.dll
	EEXT=.exe
	OMSIMULATORLIB=-lOMSimulator
else
	BUILD_DIR := ../../build/linux
	INSTALL_DIR := ../../install/linux
	FEXT=.so
	EXTRA_LD_FLAGS=-fPIC
	TLMLIB=-lomtlmsimulator
	OMSIMULATORLIB=-l:libOMSimulator.a
endif

# Should we install everything into the OMBUILDDIR?
ifeq ($(OMBUILDDIR),)
	TOP_INSTALL_DIR=$(INSTALL_DIR)
else
	TOP_INSTALL_DIR=$(OMBUILDDIR)
	HOST_SHORT_OMC=$(host_short)/omc
endif

ifeq (MINGW,$(findstring MINGW,$(detected_OS)))
	EXTRALIBS=-L../../3rdParty/FMIL/install/mingw/lib \
	-L../../3rdParty/cvode/install/mingw/lib -lsundials_cvode \
	-L../../3rdParty/kinsol/install/mingw/lib -lsundials_kinsol \
	-L../../3rdParty/minizip/install/mingw/lib -lminizip -lfmilib \
	-L../../3rdParty/Lua/install/mingw/ -llua \
	-lws2_32 -lshlwapi
	TLMLIB=$(TOP_INSTALL_DIR)/bin/libomtlmsimulator.dll
endif

LINKFLAGS=-L$(TOP_INSTALL_DIR)/lib/$(HOST_SHORT_OMC) $(OMSIMULATORLIB) $(TLMLIB) $(EXTRALIBS) $(EXTRA_LD_FLAGS)
COMPFLAGS=-g -I. -I$(TOP_INSTALL_DIR)/include/ -I../../3rdParty/FMIL/install/mingw/include -static-libgcc -static-libstdc++

all:
	g++ -shared -o omsglue$(FEXT) omsglue.cpp omsglue_model_cs.c $(COMPFLAGS) $(LINKFLAGS)

