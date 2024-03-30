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
    "duck-helper: duck <function> <label>\n \
\t --help or -h \t Outputs all possible commands \
\n                                      \
\t add  <programname> \t Add to /usr/bin, able to call normally on terminal.\
\t remove <programname> \t Remove the program from /usr/bin \n\
\t Any doubt about usage, see readme for more details.\n\
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

        puts("duck-quack: Invalid function... see --help :) ! ");
        break;
    case 3:
        if (strcmp("add", CLI_FUNCTION) == 0)
        {
            verifyValidString(CLI_PROGRAM);
            add_program(CLI_PROGRAM);
            return EXIT_SUCCESS;
        }
        if (strcmp("remove", CLI_FUNCTION) == 0)
        {
            verifyValidString(CLI_PROGRAM);
            remove_program(CLI_PROGRAM);
            return EXIT_SUCCESS;
        }

        break;
    default:
        puts("duck-quack: invalid usage of duck, see --help.");
        break;
    }
    return EXIT_FAILURE;
}
void sudoStatus()
{
    if (geteuid() != 0)
    {
        puts("duck-quack: you must run duck with sudo previlegies ;-;");
        exit(EXIT_FAILURE);
    }
}

void add_program(char *binname)
{
    verifyValidString(binname);
    static struct stat stat_buffer;
    // char filepath[FILENAME_MAX];
    //  char directory[256];
    //  if (getcwd(directory, sizeof(directory)) == NULL)
    //  {
    //      perror("duck-error: Failed to get current directory.");
    //      exit(EXIT_FAILURE);
    //  }
    //  snprintf(filepath, (size_t)sizeof(filepath), "%s/%s", directory, binname);
    //  puts(filepath);

    char buffer[(size_t)strlen("/usr/bin/") + strlen(binname) + 1];
    sprintf(buffer, "/usr/bin/%s", binname);
    if (access(buffer, F_OK) != -1)
    {
        puts("duck-quack: the file already exists in the default path");
        exit(EXIT_FAILURE);
    }

    char cmd[126];
    snprintf(cmd, sizeof(cmd), "mv %s %s", binname, buffer);
    puts(cmd);

    if (rename(binname, buffer) == 0)
    {
        perror("duck-quack-> cannot move file.");
        exit(EXIT_FAILURE);
    }

    puts("duck-success: process complete, program, now is installed your machine.");
}

void remove_program(char *binname)
{
    verifyValidString(binname);
}

void invalid_usage()
{
    puts("duck-quack: Invalid command for 2 arguments.");
    help(helpMessage);
}

void verifyValidString(char *string)
{
    if (string == NULL || string[0] == '\0')
    {
        puts("duck-quack: Invalid string passed as argument.");
        exit(EXIT_FAILURE);
    }
}
