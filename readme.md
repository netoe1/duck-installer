# Ducky

Installer for binary programs.

# Why?

When we want to install new programs to the default path of terminal linux handler (/usr/bin/programname), we should know about terminal commands to do that. I think is great, because knowledge isn't only for do things, but sometimes, it's became repetitive and boring. So, for fix this problem, **I created _Ducky_**, a CLI program that make all the dirty stuff for you.

Ducky is simple to use, all you have to do is: **run as sudo**, because we going to install in a strict directory, if you don't use sudo, we can't add programs to that directory.

Set the flag, if the flag is valid and type the name of program that you want. All support is going to be made by ducky.

## About commands structure:

```console
foo@system$: sudo ducky function flag
```
## Available functions
- ***--help or -h*** : Show available commands to use.
- ***add or install***: Add program to /usr/bin, to be called as a native program in terminal.
- ***remove, delete, uninstall*** : Remove the program from /usr/bin, if exists in te current directory.

Examples will be available in files.
<br>
<br>

# Enjoy, by NEWCORP.team




