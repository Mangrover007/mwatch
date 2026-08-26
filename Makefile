OBJECTS=src/main.cpp src/debug.cpp include/debug.h

CFLAGS=
BUILDDIR=

DEBUG ?= 1
ifeq ($(DEBUG), 1)
	CFLAGS = -DDEBUG
	BUILDDIR = build/debug/mwatch.out
else
	CFLAGS = -DNDEBUG
	BUILDDIR = build/release/mwatch.out
endif

default: $(OBJECTS)
	g++ $(CFLAGS) $(OBJECTS) -o $(BUILDDIR)

