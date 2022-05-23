#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <bits/types/siginfo_t.h>
#include <signal.h>
#include <bits/sigaction.h>

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

int ind = 1;
char *names[] = {"aa", "ab", "ac", "ad", "ae", "af", "ag", "ah", "ai", "aj", "ak", "al", "am", "an", "ao",
                 "ap", "aq", "ar", "as", "at", "au", "av", "aw", "ax", "ay", "az", "ba", "bb", "bc", "bd",
                 "be", "bf", "bg", "bh", "bi", "bj", "bk", "bl", "bm", "bn", "bo", "bp", "bq", "br", "bs",
                 "bt", "bu", "bv", "bw", "bx", "by", "bz", "ca", "cb", "cc", "cd", "ce", "cf", "cg", "ch",
                 "ci", "cj", "ck", "cl", "cm", "cn", "co", "cp", "cq", "cr", "cs", "ct", "cu", "cv", "cw",
                 "cx", "cy", "cz", "da", "db", "dc", "dd", "de", "df", "dg", "dh", "di", "dj", "dk", "dl",
                 "dm", "dn", "do", "dp", "dq", "dr", "ds", "dt", "du", "dv", "dw", "dx", "dy", "dz", "ea",
                 "eb", "ec", "ed", "ee", "ef", "eg", "eh", "ei", "ej", "ek", "el", "em", "en", "eo", "ep",
                 "eq", "er", "es", "et", "eu", "ev", "ew", "ex", "ey", "ez", "fa", "fb", "fc", "fd", "fe",
                 "ff", "fg", "fh", "fi", "fj", "fk", "fl", "fm", "fn", "fo", "fp", "fq", "fr", "fs", "ft",
                 "fu", "fv", "fw", "fx", "fy", "fz", "ga", "gb", "gc", "gd", "ge", "gf", "gg", "gh", "gi",
                 "gj", "gk", "gl", "gm", "gn", "go", "gp", "gq", "gr", "gs", "gt", "gu", "gv", "gw", "gx",
                 "gy", "gz", "ha", "hb", "hc", "hd", "he", "hf", "hg", "hh", "hi", "hj", "hk", "hl", "hm",
                 "hn", "ho", "hp", "hq", "hr", "hs", "ht", "hu", "hv", "hw", "hx", "hy", "hz", "ia", "ib",
                 "ic", "id", "ie", "if", "ig", "ih", "ii", "ij", "ik", "il", "im", "in", "io", "ip", "iq",
                 "ir", "is", "it", "iu", "iv", "iw", "ix", "iy", "iz", "ja", "jb", "jc", "jd", "je", "jf",
                 "jg", "jh", "ji", "jj", "jk", "jl", "jm", "jn", "jo", "jp", "jq", "jr", "js", "jt", "ju",
                 "jv", "jw", "jx", "jy", "jz", "ka", "kb", "kc", "kd", "ke", "kf", "kg", "kh", "ki", "kj",
                 "kk", "kl", "km", "kn", "ko", "kp", "kq", "kr", "ks", "kt", "ku", "kv", "kw", "kx", "ky",
                 "kz", "la", "lb", "lc", "ld", "le", "lf", "lg", "lh", "li", "lj", "lk", "ll", "lm", "ln",
                 "lo", "lp", "lq", "lr", "ls", "lt", "lu", "lv", "lw", "lx", "ly", "lz", "ma", "mb", "mc",
                 "md", "me", "mf", "mg", "mh", "mi", "mj", "mk", "ml", "mm", "mn", "mo", "mp", "mq", "mr",
                 "ms", "mt", "mu", "mv", "mw", "mx", "my", "mz", "na", "nb", "nc", "nd", "ne", "nf", "ng",
                 "nh", "ni", "nj", "nk", "nl", "nm", "nn", "no", "np", "nq", "nr", "ns", "nt", "nu", "nv",
                 "nw", "nx", "ny", "nz", "oa", "ob", "oc", "od", "oe", "of", "og", "oh", "oi", "oj", "ok",
                 "ol", "om", "on", "oo", "op", "oq", "or", "os", "ot", "ou", "ov", "ow", "ox", "oy", "oz",
                 "pa", "pb", "pc", "pd", "pe", "pf", "pg", "ph", "pi", "pj", "pk", "pl", "pm", "pn", "po",
                 "pp", "pq", "pr", "ps", "pt", "pu", "pv", "pw", "px", "py", "pz", "qa", "qb", "qc", "qd",
                 "qe", "qf", "qg", "qh", "qi", "qj", "qk"};

static void handler(int sig, siginfo_t *si, void *unused) {
    printf("Cant open link file with %d depth\n", ind - 1);
    while(ind != -1) {
        if (remove(names[ind]) != 0) {
            printf("Cant delete files\nSorry:((((((((\n");
        }
        ind--;
    }
    printf("Deleting link files...\n");
    exit(EXIT_FAILURE);
}

int main() {
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = handler;
    if (sigaction(SIGSEGV, &sa, NULL) == -1)
        handle_error("sigaction");

    FILE *fp;
    fp = fopen("aa", "w");
    if (access("aa", F_OK) != 0) {
        printf("Cant create dummy file");
        exit(EXIT_FAILURE);
    }
    fclose(fp);

    printf("Creating link files...\n");
    symlink("aa", names[ind]);

    while (ind < 427) {
        int error = symlink(names[ind], names[ind + 1]);
        ind++;
        if (error == -1) {
            printf("An error occurred\nShutting down");
            printf("%d", ind - 1);
            exit(EXIT_FAILURE);
        }

        fp = fopen(names[ind], "r");
        fclose(fp);
    }
    printf("Lol\n427 links was not enough!");
    exit(EXIT_SUCCESS);
}
