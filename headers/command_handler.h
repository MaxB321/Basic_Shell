#include "pch.h"

extern std::string currentPath;

extern void catExec();
extern void cdExec(std::istringstream& argsString);
extern void commandHandler(uint32_t commandIndex, std::vector<std::string>& inputArgs, std::istringstream& argsString); 
extern void cpExec();
extern void echoExec(std::istringstream& argsString);
extern void grepExec();
extern bool isValidArgs(std::istringstream& argsString);
extern bool isValidPath(std::string& path);
extern void lsExec();
extern void mkdirExec();
extern void mvExec();
extern void rmExec();
extern void setArgVec(std::vector<std::string>& inputArgs, std::istringstream& argsString);
extern void touchExec();
