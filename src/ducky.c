#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <locale.h>
#include <ctype.h>
#include <sys/stat.h>
#include <errno.h>

#define setUTF() setlocale(LC_ALL, "")
#define clear() system("clear")
#define DEFAULT_PATH / usr / bin /

#define CLI_FUNCTION argv[1]
#define CLI_PROGRAM argv[2]
#define MV_SCRIPT "\
mv %s /usr/bin/%s"

#define help(message) puts(helpMessage)
// program add <program_name>
// program remove <program_name>
// program --help

char *helpMessage =
    "ducky-helper: sudo ducky <function> <label>\n \
    Remember, some functions require sudo privilegies!\n\
\t --help or -h                     Outputs all possible commands\n \
\t add, install <programname>       Add to /usr/bin, able to call normally on terminal.\n\
\t remove <programname>             Remove the program from /usr/bin \n\n\
    Any doubt about usage, see readme for more details.\n\
";

void sudoStatus();
void add_program(char *binname);
void remove_program(char *binname);
void invalid_usage();
void verifyValidString(char *string);
int main(int argc, char **argv)
{
    setUTF();
    sudoStatus();

    switch (argc)
    {
    case 2:
        if (strcmp("--help", CLI_FUNCTION) == 0 || strcmp("-h", CLI_FUNCTION) == 0)
        {
            help(helpMessage);
            exit(EXIT_SUCCESS);
        }

        puts("ducky-quack: Invalid function... see --help :) ! ");
        break;
    case 3:
        if (strcmp("add", CLI_FUNCTION) == 0 || strcmp("install", CLI_FUNCTION) == 0)
        {
            verifyValidString(CLI_PROGRAM);
            add_program(CLI_PROGRAM);
            return EXIT_SUCCESS;
        }
        if (strcmp("remove", CLI_FUNCTION) == 0 || strcmp("delete", CLI_FUNCTION))
        {
            verifyValidString(CLI_PROGRAM);
            remove_program(CLI_PROGRAM);
            return EXIT_SUCCESS;
        }

        puts("ducky-quack: not a recongnized command ;-;");

        break;
    default:
        puts("ducky-quack: invalid usage of ducky, see --help.");
        break;
    }
    return EXIT_FAILURE;
}
void sudoStatus()
{
    if (geteuid() != 0)
    {
        puts("ducky-quack: you must run ducky with sudo previlegies ;-;");
        exit(EXIT_FAILURE);
    }
}

void add_program(char *binname)
{
    verifyValidString(binname);
    static struct stat stat_buffer;
    char buffer[(size_t)strlen("/usr/bin/") + strlen(binname) + 1];
    sprintf(buffer, "/usr/bin/%s", binname);
    if (stat(buffer, &stat_buffer) == 0)
    {
        puts("ducky-quack: the program already exists in the default path.");
        exit(EXIT_FAILURE);
    }

    char cmd[128];
    snprintf(cmd, sizeof(cmd) - 1, "mv %s %s > /dev/null 2>&1", binname, buffer);
    puts(cmd);

    if (system(cmd) != 0)
    {
        perror("ducky-quack-> cannot move file.");
        exit(EXIT_FAILURE);
    }

    puts("ducky-success: process complete, program, now is installed your machine.");
}

void remove_program(char *binname)
{
    verifyValidString(binname);

    static struct stat stat_buffer;

    char buffer[128];

    snprintf(buffer, 127, "/usr/bin/%s", binname);

    if (stat(buffer, &stat_buffer) != 0)
    {
        puts("ducky-quack: program doesn't installed.");
        exit(EXIT_FAILURE);
    }

    char cmd[128];
    snprintf(cmd, 127, "rm %s /usr/bin/%s > /dev/null 2>&1", binname, binname);

    if (system(cmd) == -1)
    {
        puts("ducky-quack: program couldn't be removed.");
        exit(EXIT_FAILURE);
    }
    puts("ducky-success: Your program has been removed.");
}

void invalid_usage()
{
    puts("ducky-quack: Invalid command for 2 arguments.");
    help(helpMessage);
}

void verifyValidString(char *string)
{
    if (string == NULL || string[0] == '\0')
    {
        puts("ducky-quack: Invalid string passed as argument.");
        exit(EXIT_FAILURE);
    }
}
