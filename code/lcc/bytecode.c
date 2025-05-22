/* quake3 bytecode target */

#include <string.h>
#include <stdio.h>

#ifdef _WIN32
#define BINEXT ".exe"
#else
#define BINEXT ""
#endif

char *suffixes[] = { ".c", ".i", ".asm", ".o", ".out", 0 };
char inputs[256] = "";
char *cpp[] = { "cpp" BINEXT,
	"-D__STDC__=1", "-D__STRICT_ANSI__", "-D__signed__=signed", "-DQ3_VM",
	"$1", "$2", "$3", 0 };
char *include[] = { 0 };
char *com[] = { "rcc" BINEXT, "-target=bytecode", "$1", "$2", "$3", 0 };
char *ld[] = { 0 };
char *as[] = { 0 };

extern char *concat(char *, char *);

/*
===============
UpdatePaths

Updates the paths to cpp and rcc based on
the directory that contains lcc
===============
*/
void UpdatePaths( const char *lccBinary )
{
	char basepath[ 1024 ];
	char *p;
	size_t basepathsz = sizeof( basepath ) - 1;

	strncpy( basepath, lccBinary, basepathsz );
	basepath[basepathsz] = 0;
	p = strrchr( basepath, '/' );

	if( !p )
		p = strrchr( basepath, '\\' );

	if( p )
	{
		*( p + 1 ) = '\0';

		cpp[ 0 ] = concat( basepath, "cpp" BINEXT );
		com[ 0 ] = concat( basepath, "rcc" BINEXT );
	}
}

int option(char *arg) {
	if (strncmp(arg, "-lccdir=", 8) == 0) {
		cpp[0] = concat(&arg[8], "/cpp" BINEXT);
		include[0] = concat("-I", concat(&arg[8], "/include"));
		com[0] = concat(&arg[8], "/rcc" BINEXT);
	} else if (strncmp(arg, "-lcppdir=", 9) == 0) {
		cpp[0] = concat(&arg[9], "/cpp" BINEXT);
	} else if (strncmp(arg, "-lrccdir=", 9) == 0) {
		com[0] = concat(&arg[9], "/rcc" BINEXT);
	} else if (strcmp(arg, "-p") == 0 || strcmp(arg, "-pg") == 0) {
		fprintf( stderr, "no profiling supported, %s ignored.\n", arg);
	} else if (strcmp(arg, "-b") == 0);
	else if (strncmp(arg, "-ld=", 4) == 0 || strcmp(arg, "-static") == 0) {
		fprintf( stderr, "no linking supported, %s ignored.\n", arg);
	} else
		return 0;
	return 1;
}
