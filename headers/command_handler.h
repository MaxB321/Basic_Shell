#include "pch.h"

extern void catExec();
extern void cdExec();
extern void clearExec();
extern void commandHandler(uint32_t commandIndex, std::vector<std::string>& inputArgs); 
extern void cpExec();
extern void echoExec();
extern void grepExec();
extern void lsExec();
extern void mkdirExec();
extern void mvExec();
extern void pwdExec();
extern void rmExec();
extern void touchExec(std::string& userInput);
extern bool validateArgs();