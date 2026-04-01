#include "constants.h"

const char* defaultPath{std::getenv("USERPROFILE")};

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
    "rm -r",
    "cat",
    "grep",
    "cp",
    "mv"
};
const std::string_view* commands_start{std::begin(commands)};
const std::string_view* commands_end{std::end(commands)};

