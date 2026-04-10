#include "pch.h"

extern std::string currentPath;

extern void catExec(std::istringstream& argsStringStream);
extern void cdExec(const uint32_t& commandIndex, std::istringstream& argsStringStream);
extern void commandHandler(const uint32_t& commandIndex, std::vector<std::string>& inputArgs, std::istringstream& argsStringStream); 
extern void cpExec(std::vector<std::string>& inputArgs, std::istringstream& argsStringStream);
extern void echoExec(std::istringstream& argsStringStream);
extern void grepWithArgs(const std::string& flag, std::string& targetString, const std::string& fileName);
extern void grepWithArgs(std::string& targetString, const std::string& fileName);
extern void grepExec(const uint32_t& commandIndex, std::vector<std::string>& inputArgs, std::istringstream& argsStringStream);
extern void handleRelativePathing(std::string& path);
extern bool isValidArgs(const uint32_t& commandIndex, std::string& argsString);
extern bool isValidArgs(const uint32_t& commandIndex, std::vector<std::string>& inputArgs);
extern bool isValidPath(std::string& path);
extern void lsExec();
extern void mkdirExec(std::istringstream& argsStringStream);
extern void mvExec(std::vector<std::string>& inputArgs, std::istringstream& argsStringStream);
extern void parseFileString(const std::string& fileName, std::string& target, const bool caseSensitive);
extern void parseFileStringRec(const std::string& fileName, std::string& target, const bool caseSensitive);
extern void parseDirStringRec(const std::string& fileName, std::string& target, const bool caseSensitive);
extern void rmExec(const uint32_t& commandIndex, std::vector<std::string>& inputArgs, std::istringstream& argsStringStream);
extern void setArgVec(std::string& argsString, std::vector<std::string>& inputArgs);
extern void touchExec(std::istringstream& argsStringStream);
