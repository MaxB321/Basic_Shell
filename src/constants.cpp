#include "constants.h"


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
const std::string_view* commands_start{std::begin(commands)};
const std::string_view* commands_end{std::end(commands)};

