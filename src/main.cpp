#include "RBX.h"
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <string.h>

void main()
{
    AllocConsole();
    FILE *fDummy;
    freopen_s(&fDummy, "CONOUT$", "w", stdout);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONIN$", "r", stdin);

    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    printf("wow bro lemme break roblox fro you\n");

    int *begin_jobs;
    int *end_jobs;
    _DWORD *job_name;
    int iterating_job;
    int scheduler = RBX::TaskScheduler::scheduler();
    const char *findingJob = "WaitingScriptJob"; // couldv just do strcmp((char *)job_name, "WaitingScriptJob") but im WAY too pro!
    bool STOP_JOB_SEARCHING = false;
    RBX::TaskScheduler::DataModelJob *WaitingScriptJob = nullptr;

    // searching WaitingScriptJob (method is very good but i coded it like a ass shit)
    std::cout << "waiting until WaitingScriptJob will get online.." << std::endl;
    do
    {
        if (STOP_JOB_SEARCHING)
            break;
        // Sleep(1);
        begin_jobs = (int *)*((_DWORD *)scheduler + 147);
        end_jobs = (int *)*((_DWORD *)scheduler + 148);
        if (begin_jobs != end_jobs)
        {
            do
            {
                iterating_job = *begin_jobs;
                if (iterating_job == NULL) // finally i found reason why my shit crashes sometimes on finding job
                {
                    begin_jobs = (int *)*((_DWORD *)scheduler + 147);
                    end_jobs = (int *)*((_DWORD *)scheduler + 148);
                    continue;
                }
                job_name = (_DWORD *)(iterating_job + 16);
                if (*(_DWORD *)(iterating_job + 36) >= 0x10u)
                    job_name = (_DWORD *)*job_name;

                begin_jobs += 2;
                if (strcmp((char *)job_name, findingJob) == 0)
                {
                    std::cout << "Found job WaitingScriptJob. It's time to hack now!" << std::endl;
                    WaitingScriptJob = (RBX::TaskScheduler::DataModelJob *)iterating_job;
                    STOP_JOB_SEARCHING = true;
                    break;
                }
            } while (begin_jobs != end_jobs);
        }
    } while (!STOP_JOB_SEARCHING);

    std::cout << "Job address: " << WaitingScriptJob << std::endl;

    RBX::Instance *dm = new RBX::Instance((WaitingScriptJob->dm) + 1); // 0x4
    std::cout << "DataModel address: " << dm->pointer << std::endl;
    std::cout << "DataModel name: " << *dm->getName() << std::endl;
    *dm->getName() = "better dm name";

    RBX::Instance *ScriptContext = dm->findFirstChild("Script Context");
    std::cout << "ScriptContext address: " << (void *)ScriptContext->pointer << std::endl;

    /*
    ida pro RBX::ScriptContext::createThreadFromSource


    isInRole = RBX::Security::Context::isInRole(4, 5);
    v18 = &ScriptContext[14 * isInRole + 43] - ScriptContext[14 * isInRole + 43];

    43 and 14 for int length (4) so char will be
    172 and 56
    */

    int *scriptcontextptr = ScriptContext->pointer;
    int L;
    int isInRole = 1;

    L = (int)&scriptcontextptr[14 * isInRole + 43] - scriptcontextptr[14 * isInRole + 43];
    std::cout << "roblox global lua state: " << (void *)L << std::endl;
    L = RLua::lua_newthread(L); // lua_newthread one love
    std::cout << "roblox thread lua state: " << (void *)L << std::endl;
    
    /*int unktable[2];
    unktable[0] = 0;
    unktable[1] = 0;
    int identity = 6;
    RBX::ScriptContext::setThreadIdentityAndSandbox(L, identity, (int)unktable); // infinity yields idk why*/

    DWORD* w = (DWORD *)(L - 10);
    printf("identity before %u\n", *w);
    *w ^= (6 ^ (unsigned __int8)*w) & 0x1F;
    DWORD* w2 = (DWORD *)(L - 10);
    printf("identity after %u\n", *w2);
    printf("increased identity!!! rob house\n");

    RLua::lua_getfield(L, -10002, "printidentity");
    printf("calling printidentity\n");
    RLua::lua_call(L, 0, 0);

    RLua::lua_getfield(L, -10002, "game");
    printf("global type: %d\n", RLua::lua_type(L, -1));
    RLua::lua_pushstring(L, "nigger");
    RLua::lua_setfield(L, -2, "Name");
    RLua::lua_pop(L, 1);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0x1000, (LPTHREAD_START_ROUTINE)main, nullptr, 0, nullptr);
    }
    return TRUE;
}