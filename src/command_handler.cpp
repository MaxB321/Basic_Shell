#include "command_handler.h"
#include "enums.h"
#include "flags.h"


void catExec(){} 
void cdExec(){}

void commandHandler(uint32_t commandIndex, std::vector<std::string>& inputArgs)
{
    if (!validateArgs())
        return;

    switch (commandIndex)
    {
        case static_cast<uint32_t>(commandsEnum::Exit):
            PROGRAM_RUNNING = false;
            break;
        case static_cast<uint32_t>(commandsEnum::Echo):
            std::cout << inputArgs[0] << '\n';
            break;
        case static_cast<uint32_t>(commandsEnum::Pwd):
            break;
        case static_cast<uint32_t>(commandsEnum::Cd):
            break;
        case static_cast<uint32_t>(commandsEnum::Ls):
            break;
        case static_cast<uint32_t>(commandsEnum::Clear):
            system("CLS");
            break;
        case static_cast<uint32_t>(commandsEnum::Touch):
            break;
        case static_cast<uint32_t>(commandsEnum::Mkdir):
            break;
        case static_cast<uint32_t>(commandsEnum::Rm):
            break;
        case static_cast<uint32_t>(commandsEnum::Cat):
            break;
        case static_cast<uint32_t>(commandsEnum::Grep):
            break;
        case static_cast<uint32_t>(commandsEnum::Cp):
            break;
        case static_cast<uint32_t>(commandsEnum::Mv):
            break;
    }
}

void cpExec(){}

void echoExec()
{

}

void grepExec(){}
void lsExec(){}
void mkdirExec(){}
void mvExec(){}
void pwdExec(){}
void rmExec(){}

void touchExec(std::string& userInput)
{
    
}

bool validateArgs()
{
    return true;
}
