#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <unistd.h>

#define MAX_SUBST_LEN 4096
#define MAX_GROUPS 10
#define MAX_REFS 100

const char* colors[MAX_GROUPS] = {
    "",
	"\033[31m",
	"\033[32m",
	"\033[33m",
	"\033[34m",
    "\033[35m",
	"\033[36m",
	"\033[91m",
	"\033[92m",
	"\033[93m"
};
const char* reset_color = "\033[0m";

void usage(const char* progname) {
    fprintf(stderr, "Usage: %s [-c] <regexp> <substitution> <string>\n", progname);
}

int main(int argc, char *argv[]) {
    int colorize = 0;
    int opt;
    optind = 0; 
    while ((opt = getopt(argc, argv, "c")) != -1) {
        switch (opt) {
            case 'c':
                colorize = 1;
                break;
            default:
                usage(argv[0]);
                return -1;
        }
    }

    if (optind + 3 != argc) {
        usage(argv[0]);
        return -1;
    }

    const char *pattern = argv[optind];
    const char *subst   = argv[optind + 1];
    const char *input   = argv[optind + 2];

    regex_t reg;
    int ret = regcomp(&reg, pattern, REG_EXTENDED);
    if (ret != 0) {
        size_t errlen = regerror(ret, &reg, NULL, 0);
        char *errmsg = malloc(errlen);
        if (!errmsg) {
            perror("malloc");
            regfree(&reg);
            return -1;
        }
        regerror(ret, &reg, errmsg, errlen);
        fprintf(stderr, "Invalid regex: %s\n", errmsg);
        free(errmsg);
        regfree(&reg);
        return -1;
    }

    regmatch_t pmatch[MAX_GROUPS];
    ret = regexec(&reg, input, MAX_GROUPS, pmatch, 0);
    if (ret == REG_NOMATCH) {
        puts(input);
        regfree(&reg);
        return 0;
    } else if (ret != 0) {
        size_t errlen = regerror(ret, &reg, NULL, 0);
        char *errmsg = malloc(errlen);
        if (!errmsg) {
            perror("malloc");
            regfree(&reg);
            return -1;
        }
        regerror(ret, &reg, errmsg, errlen);
        fprintf(stderr, "Regex execution error: %s\n", errmsg);
        free(errmsg);
        regfree(&reg);
        return -1;
    }

    int ngroups = 0;
    for (int i = 0; i < MAX_GROUPS; i++) {
        if (pmatch[i].rm_so != -1) ngroups = i + 1;
    }

    char result[MAX_SUBST_LEN] = {0};
    char *out = result;
    const char *s = subst;
    int ref_count = 0;

    while (*s && (out - result) < (int)sizeof(result) - 20) {
        if (*s == '\\') {
            s++;
            if (*s == '\\') {
                *out++ = '\\';
                s++;
            } else if (*s >= '1' && *s <= '9') {
                int grp = *s - '0';
                if (grp >= ngroups) {
                    fprintf(stderr, "Invalid backreference: \\%d (only %d groups captured)\n", grp, ngroups - 1);
                    regfree(&reg);
                    return -1;
                }
                if (++ref_count > MAX_REFS) {
                    fprintf(stderr, "Too many backreferences (max %d)\n", MAX_REFS);
                    regfree(&reg);
                    return -1;
                }

                regmatch_t *m = &pmatch[grp];
                int len = m->rm_eo - m->rm_so;
                if (len > 0) {
                    if (colorize && grp > 0) {
                        const char *col = colors[grp];
                        strcpy(out, col);
                        out += strlen(col);
                    }
                    memcpy(out, input + m->rm_so, len);
                    out += len;
                    if (colorize && grp > 0) {
                        strcpy(out, reset_color);
                        out += strlen(reset_color);
                    }
                }
                s++;
            } else {
                *out++ = '\\';
                if (*s) *out++ = *s++;
            }
        } else {
            *out++ = *s++;
        }
    }
    *out = '\0';
	
    regfree(&reg);
	regmatch_t *whole = &pmatch[0];
	fwrite(input, 1, whole->rm_so, stdout);
	fputs(result, stdout);
	fwrite(input + whole->rm_eo, 1, strlen(input) - whole->rm_eo, stdout);
	putchar('\n');
    return 0;
}
