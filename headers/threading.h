#pragma once

#include "pch.h"
#include "flags.h"
#include "utility.h"

namespace threadingFuncs
{
    extern std::queue<std::filesystem::directory_entry> mkEntryQueue(std::string& directory);
    extern void mtParseDirStringRec(std::queue<std::filesystem::directory_entry>& dirEntries, std::string& target, bool caseSensitive);
    extern DWORD WINAPI mtParseFuncCi(LPVOID lpParam);
    extern DWORD WINAPI mtParseFuncCs(LPVOID lpParam);
}

struct Match
{
    std::string text{};
    std::uint32_t line{};
    std::string fileName{};
};

struct ThreadData
{
    std::queue<std::filesystem::directory_entry>* dirEntries{};
    std::string target{};
    std::atomic<bool>* threadFailedCreation{};
};
