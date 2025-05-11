ifeq ($(PLATFORM),mingw64)
  BINEXT := .exe
  CC := x86_64-w64-mingw32-gcc
else
  BINEXT :=
  CC := gcc
endif

TOOLS_CFLAGS := -O2 -Wall -fno-strict-aliasing

all: makebuild build/asm$(BINEXT) build/lcc$(BINEXT) build/cpp$(BINEXT) build/rcc$(BINEXT)

makebuild:
	mkdir -p build

build/asm$(BINEXT): code/asm/asm.c code/asm/cmdlib.c
	$(CC) $(TOOLS_CFLAGS) -o $@ $^

build/lcc$(BINEXT): code/lcc/bytecode.c code/lcc/lcc.c
	$(CC) $(TOOLS_CFLAGS) -o $@ $^

build/cpp$(BINEXT): code/cpp/cpp.c code/cpp/eval.c code/cpp/getopt.c code/cpp/hideset.c code/cpp/include.c code/cpp/lex.c code/cpp/macro.c code/cpp/nlist.c code/cpp/tokens.c code/cpp/unix.c
	$(CC) $(TOOLS_CFLAGS) -o $@ $^

build/rcc$(BINEXT): code/rcc/alloc.c code/rcc/bind.c code/rcc/bytecode.c code/rcc/dag.c code/rcc/decl.c code/rcc/enode.c code/rcc/error.c code/rcc/event.c code/rcc/expr.c code/rcc/gen.c code/rcc/init.c code/rcc/inits.c code/rcc/input.c code/rcc/lex.c code/rcc/list.c code/rcc/main.c code/rcc/null.c code/rcc/output.c code/rcc/prof.c code/rcc/profio.c code/rcc/simp.c code/rcc/stmt.c code/rcc/string.c code/rcc/sym.c code/rcc/symbolic.c code/rcc/trace.c code/rcc/tree.c code/rcc/types.c
	$(CC) $(TOOLS_CFLAGS) -o $@ $^
