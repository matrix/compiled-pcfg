##
## Author......: Matt Weir
## Note........: Parts of this Makefile were copied from Hashcat and other sources
## License.....: GPL-2
##

DEBUG                   := 0
PRODUCTION              := 0
ENABLE_LTO              ?= 1

##
## Detect Operating System
##

UNAME                   := $(shell uname -s)

# we need to strip the windows version number to be able to build hashcat on cygwin hosts
UNAME                   := $(patsubst CYGWIN_NT-%,CYGWIN,$(UNAME))

# same for msys
UNAME                   := $(patsubst MSYS_NT-%,MSYS2,$(UNAME))
UNAME                   := $(patsubst MINGW32_NT-%,MSYS2,$(UNAME))
UNAME                   := $(patsubst MINGW64_NT-%,MSYS2,$(UNAME))

ifeq (,$(filter $(UNAME),Linux OpenBSD FreeBSD NetBSD DragonFly Darwin CYGWIN MSYS2))
$(error "! Your Operating System ($(UNAME)) is not supported by this Makefile")
endif

# force disable LTO if DEBUG > 0
ifeq ($(shell [ $(DEBUG) -gt 0 ] && echo true),true)
override ENABLE_LTO := 0
endif

ifneq (,$(filter $(UNAME),NetBSD DragonFly))
override ENABLE_LTO := 0
endif

ifeq ($(ENABLE_LTO),1)
CFLAGS                  += -flto=auto
endif

##
## Native compiler paths
##
CC                      := gcc

ifeq ($(UNAME),Darwin)
CC                      := clang
DARWIN_VERSION          := $(shell uname -r | cut -d. -f1)
endif

ifneq (,$(filter $(UNAME),OpenBSD FreeBSD NetBSD DragonFly))
CC                      := cc
endif

ifeq ($(UNAME),NetBSD)
CC                      := gcc
endif

ifeq ($(shell [ $(DEBUG) -gt 0 ] && echo true),true)
$(info "## Detected Operating System : $(UNAME)")
$(info "## Detected ENABLE_LTO : $(ENABLE_LTO)")
$(info "## Detected CC : $(CC)")
endif

ifeq ($(DEBUG),0)
CFLAGS                  += -O3 -fomit-frame-pointer
else
ifeq ($(DEBUG),1)
ifneq ($(UNAME),Darwin)
CFLAGS                  += -DDEBUG -Og -ggdb
else
CFLAGS                  += -DDEBUG -O0 -ggdb
endif
else
ifeq ($(DEBUG),2)
ifneq ($(UNAME),Darwin)
CFLAGS                  += -DDEBUG -Og -ggdb
else
CFLAGS                  += -DDEBUG -O0 -ggdb
endif
CFLAGS                  += -fsanitize=address -fno-omit-frame-pointer
endif
endif
endif

CFLAGS                  += -pipe -std=gnu99

ifeq ($(UNAME),Darwin)
export MACOSX_DEPLOYMENT_TARGET=15.0

ifeq ($(shell test $(DARWIN_VERSION) -le 11; echo $$?), 0)
CFLAGS                  += -DMISSING_CLOCK_GETTIME
endif
endif # Darwin

##
## target
##

pcfg_guesser: src/pcfg_guesser.o src/tty.o src/banner_info.o src/command_line.o src/grammar_io.o src/config_parser.o src/helper_io.o src/base_structure_io.o src/pqueue.o src/pcfg_pqueue.o
	$(CC) $(CFLAGS) src/pcfg_guesser.o src/tty.o src/banner_info.o src/command_line.o src/config_parser.o src/grammar_io.o src/helper_io.o src/base_structure_io.o src/pqueue.o src/pcfg_pqueue.o -o pcfg_guesser

pcfg_guesser.o: src/pcfg_guesser.c src/pcfg_guesser.h src/grammar.h
	$(CC) $(CFLAGS) -c src/pcfg_guesser.c

tty.o: src/tty.c src/tty.h
	$(CC) $(CFLAGS) -c src/tty.c

banner_info.o: src/banner_info.c src/bannar_info.h
	$(CC) $(CFLAGS) -c src/banner_info.c

command_line.o: src/command_line.c src/command_line.h
	$(CC) $(CFLAGS) -c src/command_line.c

grammar_io.o: src/grammar_io.c src/grammar_io.h src/grammar.h
	$(CC) $(CFLAGS) -c src/grammar_io.c

config_parser.o: src/config_parser.c src/config_parser.h
	$(CC) $(CFLAGS) -c src/config_parser.c

helper_io.o: src/helper_io.c src/helper_io.h
	$(CC) $(CFLAGS) -c src/helper_io.c

base_structure_io.o: src/base_structure_io.c src/base_structure_io.h
	$(CC) $(CFLAGS) -c src/base_structure_io.c

pqueue.o: src/pqueue.c src/pqueue.h
	$(CC) $(CFLAGS) -c src/pqueue.c

pcfg_pqueue.o: src/pcfg_pqueue.c src/pcfg_pqueue.h
	$(CC) $(CFLAGS) -c src/pcfg_pqueue.c

main: pcfg_guesser

clean:
	rm -f pcfg_guesser
	rm -f pcfg_guesser.exe
	rm -f src/*.o
	rm -f src/*.a
