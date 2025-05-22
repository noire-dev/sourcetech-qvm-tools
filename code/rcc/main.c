#include "c.h"

static char rcsid[] = "main.c - faked rcsid";

Interface *IR = NULL;

int Aflag;		/* >= 0 if -A specified */

int main(int argc, char *argv[]) {
	int i, j;
	for (i = argc - 1; i > 0; i--)
		if (strncmp(argv[i], "-target=", 8) == 0)
			break;
	if (i > 0) {
		char *s = strchr(argv[i], '\\');
		if (s != NULL)
			*s = '/';
		for (j = 0; bindings[j].name && bindings[j].ir; j++)
			if (strcmp(&argv[i][8], bindings[j].name) == 0) {
				IR = bindings[j].ir;
				break;
			}
		if (s != NULL)
			*s = '\\';
	}
	if (!IR) {
		fprint(stderr, "%s: unknown target", argv[0]);
		if (i > 0)
			fprint(stderr, " `%s'", &argv[i][8]);
		fprint(stderr, "; must specify one of\n");
		for (i = 0; bindings[i].name; i++)
			fprint(stderr, "\t-target=%s\n", bindings[i].name);
		exit(EXIT_FAILURE);
	}
	init(argc, argv);
	t = gettok();
	(*IR->progbeg)(argc, argv);
	program();
	if (events.end)
		apply(events.end, NULL, NULL);
	memset(&events, 0, sizeof events);
	finalize();
	(*IR->progend)();
	deallocate(PERM);
	return errcnt > 0;
}
/* main_init - process program arguments */
void main_init(int argc, char *argv[]) {
	char *infile = NULL, *outfile = NULL;
	int i;
	static int inited;

	if (inited)
		return;
	inited = 1;
	type_init(argc, argv);
	for (i = 1; i < argc; i++)
		if (strcmp(argv[i], "-A") == 0)
			++Aflag;
		else if (strcmp(argv[i], "-w") == 0)
			wflag++;
		else if (strcmp(argv[i], "-v") == 0)
			fprint(stderr, "%s %s\n", argv[0], rcsid);
		else if (strncmp(argv[i], "-s", 2) == 0)
			density = strtod(&argv[i][2], NULL);
		else if (strncmp(argv[i], "-errout=", 8) == 0) {
			FILE *f = fopen(argv[i]+8, "w");
			if (f == NULL) {
				fprint(stderr, "%s: can't write errors to `%s'\n", argv[0], argv[i]+8);
				exit(EXIT_FAILURE);
			}
			fclose(f);
			f = freopen(argv[i]+8, "w", stderr);
			assert(f);
		} else if (strncmp(argv[i], "-e", 2) == 0) {
			int x;
			if ((x = strtol(&argv[i][2], NULL, 0)) > 0)
				errlimit = x;
		} else if (strncmp(argv[i], "-little_endian=", 15) == 0)
			IR->little_endian = argv[i][15] - '0';
		else if (strncmp(argv[i], "-mulops_calls=", 18) == 0)
			IR->mulops_calls = argv[i][18] - '0';
		else if (strncmp(argv[i], "-wants_callb=", 13) == 0)
			IR->wants_callb = argv[i][13] - '0';
		else if (strncmp(argv[i], "-wants_argb=", 12) == 0)
			IR->wants_argb = argv[i][12] - '0';
		else if (strncmp(argv[i], "-left_to_right=", 15) == 0)
			IR->left_to_right = argv[i][15] - '0';
		else if (strncmp(argv[i], "-wants_dag=", 11) == 0)
			IR->wants_dag = argv[i][11] - '0';
		else if (*argv[i] != '-' || strcmp(argv[i], "-") == 0) {
			if (infile == NULL)
				infile = argv[i];
			else if (outfile == NULL)
				outfile = argv[i];
		}

	if (infile != NULL && strcmp(infile, "-") != 0
	&& freopen(infile, "r", stdin) == NULL) {
		fprint(stderr, "%s: can't read `%s'\n", argv[0], infile);
		exit(EXIT_FAILURE);
	}
	if (outfile != NULL && strcmp(outfile, "-") != 0
	&& freopen(outfile, "w", stdout) == NULL) {
		fprint(stderr, "%s: can't write `%s'\n", argv[0], outfile);
		exit(EXIT_FAILURE);
	}
}
