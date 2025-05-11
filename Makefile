ifeq ($(PLATFORM),mingw64)
  BINEXT := .exe
  CC := x86_64-w64-mingw32-gcc
else
  BINEXT :=
  CC := gcc
endif

TOOLS_CFLAGS := -O2 -Wall -Werror -fno-strict-aliasing

all: makebuild build/asm$(BINEXT) build/lcc$(BINEXT) build/cpp$(BINEXT)

makebuild:
	mkdir -p build

build/asm$(BINEXT): code/asm/asm.c code/asm/cmdlib.c
	$(CC) $(TOOLS_CFLAGS) -o $@ $^

build/lcc$(BINEXT): code/lcc/bytecode.c code/lcc/lcc.c
	$(CC) $(TOOLS_CFLAGS) -o $@ $^

build/cpp$(BINEXT): code/cpp/cpp.c code/cpp/eval.c code/cpp/getopt.c code/cpp/hideset.c code/cpp/include.c code/cpp/lex.c code/cpp/macro.c code/cpp/nlist.c code/cpp/tokens.c code/cpp/unix.c
	$(CC) $(TOOLS_CFLAGS) -o $@ $^
