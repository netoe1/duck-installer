#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <locale.h>
#define setUTF() setlocale(LC_ALL, "")
#define clear() system("clear")
#define DEFAULT_PATH "/usr/bin/%s"

#define CLI_FUNCTION argv[1]
#define CLI_PROGRAM argv[2]

// program add <program_name>
// program remove <program_name>
// program --help

bool validString(char *ptr);
bool sudoStatus();
void add(char *binname);
void remove(char *binname);
int main(int argc, char **argv)
{
    setUTF();
    clear();
    printf("Welcome to the duck, a linux binary installer.");
    sudoStatus();

    switch (argc)
    {
    case 2:
        if (strcmp("--help", CLI_FUNCTION) == 0 || strcmp("-h", CLI_FUNCTION) == 0)
        {
        }
        break;
    case 3:
        if (strcmp("add", CLI_FUNCTION) == 0)
        {
        }
        else if (strcmp("remove", CLI_FUNCTION) == 0)
        {
        }
        break;
    default:
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

bool sudoStatus()
{
    if (getuid() == 0)
    {
        puts("duck-quack: you must run this program as a sudo.");
        return true;
    }

    return false;
}