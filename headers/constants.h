#pragma once 

#include "pch.h"

#define NORMAL_TEXT "\033[0m"
#define RED_TEXT    "\033[91m"
#define GREEN_TEXT  "\033[92m"
#define BLUE_TEXT  "\033[94m"
#define PURPLE_TEXT  "\033[95m"
#define CYAN_TEXT  "\033[96m"



extern const std::string_view commands[];
extern const std::string_view* commands_start;
extern const std::string_view* commands_end;
