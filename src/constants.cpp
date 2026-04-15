#include "constants.h"

const std::string_view cdArgs[] {
    ".",
    "..",
    "/"
};
const std::string_view commands[] {
    "exit",
    "echo",
    "pwd",
    "cd", 
    "ls",
    "clear",
    "touch",
    "mkdir",
    "rm",
    "cat",
    "grep",
    "cp",
    "mv"
};
const std::string_view grepArgs[] {
    "-i",
    "-r",
};
const std::string_view rmRecFlag{"-r"};
