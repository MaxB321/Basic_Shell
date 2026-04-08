#include "pch.h"

extern std::string currentPath;

extern void catExec(std::istringstream& argsStringStream);
extern void cdExec(const uint32_t& commandIndex, std::istringstream& argsStringStream);
extern void commandHandler(const uint32_t& commandIndex, std::vector<std::string>& inputArgs, std::istringstream& argsStringStream); 
extern void cpExec();
extern void echoExec(std::istringstream& argsStringStream);
extern void grepExec(const uint32_t& commandIndex, std::vector<std::string>& inputArgs, std::istringstream& argsStringStream);
extern void handleRelativePathing(std::string& path);
extern bool isValidArgs(const uint32_t& commandIndex, std::string& argsString);
extern bool isValidArgs(const uint32_t& commandIndex, std::vector<std::string>& inputArgs);
extern bool isValidPath(std::string& path);
extern void lsExec();
extern void mkdirExec(std::istringstream& argsStringStream);
extern void mvExec();
extern uint32_t parseFileString(const std::string& fileName, const std::string& target);
extern void rmExec(const uint32_t& commandIndex, std::vector<std::string>& inputArgs, std::istringstream& argsStringStream);
extern void setArgVec(std::string& argsString, std::vector<std::string>& inputArgs);
extern void touchExec(std::istringstream& argsStringStream);
