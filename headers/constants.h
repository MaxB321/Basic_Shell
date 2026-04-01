#pragma once 

#include "pch.h"

#define GREEN_TEXT    "\033[92m"
#define NORMAL_TEXT "\033[0m"
#define RED_TEXT    "\033[91m"


extern const char* defaultPath;
extern const std::string_view commands[];
extern const std::string_view* commands_start;
extern const std::string_view* commands_end;
