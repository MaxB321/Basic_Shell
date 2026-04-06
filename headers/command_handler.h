#include "pch.h"

extern std::string currentPath;

extern void catExec(std::istringstream& argsStringStream);
extern void cdExec(uint32_t& commandIndex, std::istringstream& argsStringStream);
extern void commandHandler(uint32_t commandIndex, std::vector<std::string>& inputArgs, std::istringstream& argsStringStream); 
extern void cpExec();
extern void echoExec(std::istringstream& argsStringStream);
extern void grepExec(uint32_t& commandIndex, std::vector<std::string>& inputArgs, std::istringstream& argsStringStream);
extern bool isValidArgs(uint32_t& commandIndex, std::string& argsString);
extern bool isValidPath(std::string& path);
extern void lsExec();
extern void mkdirExec(std::istringstream& argsStringStream);
extern void mvExec();
extern void rmExec();
extern void setArgVec(uint32_t commandIndex, std::vector<std::string>& inputArgs, std::string& argsString);
extern void touchExec(std::istringstream& argsStringStream);
