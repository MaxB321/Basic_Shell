#include "threading.h"


namespace
{
    std::mutex queueMutex{};
    std::mutex outputMutex{};
    bool targetFound{false};

    DWORD WINAPI mtParseFuncCi(LPVOID lpParam);
    DWORD WINAPI mtParseFuncCs(LPVOID lpParam);
}


std::queue<std::filesystem::directory_entry> threadingFuncs::mkEntryQueue(std::string& directory)
{
    std::queue<std::filesystem::directory_entry> dirEntries{};
    for (const std::filesystem::directory_entry& entry : std::filesystem::recursive_directory_iterator(directory))
    {
        dirEntries.push(entry);
    }
    return dirEntries;
}

void threadingFuncs::mtParseDirStringRec(std::queue<std::filesystem::directory_entry>& dirEntries, std::string& target, bool caseSensitive)
{
    std::atomic<bool> threadFailedCreation{false};

    ThreadData* data1 = new ThreadData{
        &dirEntries,
        target,
        &threadFailedCreation
    };

    ThreadData* data2 = new ThreadData{
        &dirEntries,
        target,
        &threadFailedCreation
    };

    HANDLE thread1{};
    HANDLE thread2{};

    if (caseSensitive)
    {
        thread1 = CreateThread(
            nullptr,
            0,
            mtParseFuncCs,
            data1,
            0,
            nullptr
        );

        thread2 = CreateThread(
            nullptr,
            0,
            mtParseFuncCs,
            data2,
            0,
            nullptr
        );
    }
    else
    {
        thread1 = CreateThread(
            nullptr,
            0,
            mtParseFuncCi,
            data1,
            0,
            nullptr
        );

        thread2 = CreateThread(
            nullptr,
            0,
            mtParseFuncCi,
            data2,
            0,
            nullptr
        );
    }
    
    if (!thread1 || !thread2)
    {
        threadFailedCreation = true;
        if (thread1)
        {
            WaitForSingleObject(thread1, INFINITE);
            CloseHandle(thread1);
        }
        else
        {
            delete data1;
        }
        if (thread2)
        {
            WaitForSingleObject(thread2, INFINITE);
            CloseHandle(thread2);
        }
        else
        {
            delete data2;
        }

        std::cerr << "Failed to create thread(s)." << std::endl;
        targetFound = false;
        return;
    }

    WaitForSingleObject(thread1, INFINITE);
    WaitForSingleObject(thread2, INFINITE);
    CloseHandle(thread1);
    CloseHandle(thread2);

    if (!targetFound)
        std::cerr << target << " not found." << std::endl;

    targetFound = false;
}

namespace
{

// case insensitive
    DWORD WINAPI mtParseFuncCi(LPVOID lpParam)
    {
        ThreadData* data = static_cast<ThreadData*>(lpParam);
        std::queue<std::filesystem::directory_entry>& dirEntries = *data->dirEntries;
        std::string& target = data->target;

        delete data;
        return 0;
    }

    // case sensitive
    DWORD WINAPI mtParseFuncCs(LPVOID lpParam)
    {
        ThreadData* data = static_cast<ThreadData*>(lpParam);
        std::queue<std::filesystem::directory_entry>& dirEntries = *data->dirEntries;
        uint32_t lineNumber{0};
        std::ifstream file{};
        std::string line{};
        std::filesystem::directory_entry entry{};

        std::vector<Match> outputBuffer{};

        while (true)
        {
            if (*data->threadFailedCreation)
                break;

            {
                std::lock_guard<std::mutex> lock(queueMutex);

                if (dirEntries.empty())
                    break;
                
                entry = dirEntries.front();
                dirEntries.pop(); 
            }

            lineNumber = 0;
            file.open(entry.path());
            while (std::getline(file, line))
            {
                ++lineNumber;

                if (line.find(data->target) != std::string::npos) 
                {
                    utility::trimString(line);
                    outputBuffer.push_back({line, lineNumber, entry.path().filename().string()});
                }
            }
            file.close();
            file.clear();

            if (COMMAND_INTERRUPTED)
            {
                break;
            }

            if (outputBuffer.empty())
                continue;

            {
                std::lock_guard<std::mutex> lock(outputMutex);

                for (Match& targetMatch : outputBuffer)
                {
                    std::cout << targetMatch.text << "\tline: " << targetMatch.line <<  "; File: [" << targetMatch.fileName << "]" << '\n';
                }
            }
            outputBuffer.clear();
            targetFound = true;
        }

        delete data;
        return 0;
    }
}
