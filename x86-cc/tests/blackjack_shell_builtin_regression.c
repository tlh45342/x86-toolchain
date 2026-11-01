/* Regression: Blackjack shell builtin requires stdlib getenv and stdio perror. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
static char cwd[128];
static int builtin(char **argv, int in_child)
{
    if (!argv[0]) return 1;
    if (strcmp(argv[0], "exit") == 0) return in_child ? 1 : -1;
    if (strcmp(argv[0], "pwd") == 0) { puts(cwd); return 1; }
    if (strcmp(argv[0], "cd") == 0) {
        const char *dest = argv[1] ? argv[1] : getenv("HOME");
        if (!dest) dest = "/";
        if (chdir(dest) < 0) {
            perror("cd");
        } else if (!getcwd(cwd, sizeof(cwd))) {
            strncpy(cwd, dest, sizeof(cwd) - 1);
            cwd[sizeof(cwd) - 1] = 0;
        }
        return 1;
    }
    return 0;
}
int main(void)
{
    char *argv[2];
    argv[0] = "pwd";
    argv[1] = 0;
    return builtin(argv, 0);
}
