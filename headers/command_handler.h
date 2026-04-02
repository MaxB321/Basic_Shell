#include "pch.h"

extern void catExec();
extern void cdExec();
extern void clearExec();
extern void commandHandler(uint32_t commandIndex, std::vector<std::string>& inputArgs, std::istringstream& argsString); 
extern void cpExec();
extern void echoExec(std::istringstream& argsString);
extern void grepExec();
extern void lsExec();
extern void mkdirExec();
extern void mvExec();
extern void pwdExec();
extern void rmExec();
extern void setArgVec(std::vector<std::string>& inputArgs, std::istringstream& argsString);
extern void touchExec();
extern bool validateArgs();