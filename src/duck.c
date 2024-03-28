#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <locale.h>
#include <ctype.h>

#define setUTF() setlocale(LC_ALL, "")
#define clear() system("clear")
#define DEFAULT_PATH "/usr/bin/%s"

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

bool validString(char *ptr);
void sudoStatus();
void add_program(char *binname);
void remove_program(char *binname);
void invalid_usage();
int main(int argc, char **argv)
{
    setUTF();
    printf("\t\tDUCK DUCK DUCK DUCK\nWelcome to the duck, a linux binary installer.\n");
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
            validString(CLI_PROGRAM);
            add_program(CLI_PROGRAM);
            return EXIT_SUCCESS;
        }
        if (strcmp("remove", CLI_FUNCTION) == 0)
        {
            validString(CLI_PROGRAM);
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

bool validString(char *ptr)
{
    if (ptr == NULL || ptr[0] == '\0')
    {
        puts("duck-quack: invalid string format for CLI.");
        return false;
    }

    return true;
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
    if (validString(binname))
    {
        // FILE *p = fopen("r", binname);

        // if (p == NULL)
        // {
        //     puts("duck-quack: Cannot find program to add.");
        //     exit(EXIT_FAILURE);
        // }
        char buffer[100];
        snprintf(buffer, 99, MV_SCRIPT, binname, binname);
        system(buffer);
    }
}

void remove_program(char *binname)
{
    FILE *p = fopen("r", binname);

    if (!p)
    {
        puts("duck-quack: Cannot find program to remove.");
        exit(EXIT_FAILURE);
    }
    char choice = 'a';

    do
    {
        printf("\nSure you want to delete the program:%s[Y/N]?", binname);
        setbuf(stdin, NULL);
        scanf("%c", &choice);
        choice = tolower(choice);
    } while (choice != 's' && choice != 'n');

    if (choice == 's')
    {
        char buffer[100];
        snprintf(buffer, 99, "rm -rf ./usr/bin/%s", binname);
        system(buffer);
    }
    else if (choice == 'n')
    {
        puts("duck-status: Aborting removing.");
    }
    fclose(p);
}

void invalid_usage()
{
    puts("duck-quack: Invalid command for 2 arguments.");
    help(helpMessage);
}