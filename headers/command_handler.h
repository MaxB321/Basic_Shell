#include "pch.h"

extern std::string currentPath;

extern void catExec(std::istringstream& argsString);
extern void cdExec(uint32_t& commandIndex, std::istringstream& argsString);
extern void commandHandler(uint32_t commandIndex, std::vector<std::string>& inputArgs, std::istringstream& argsString); 
extern void cpExec();
extern void echoExec(std::istringstream& argsString);
extern void grepExec(uint32_t commandIndex, std::vector<std::string>& inputArgs, std::istringstream& argsString);
extern bool isValidArgs(uint32_t& commandIndex, std::string& argsString);
extern bool isValidPath(std::string& path);
extern void lsExec();
extern void mkdirExec(std::istringstream& argsString);
extern void mvExec();
extern void rmExec();
extern void setArgVec(uint32_t commandIndex, std::vector<std::string>& inputArgs, std::istringstream& argsString);
extern void touchExec(std::istringstream& argsString);
