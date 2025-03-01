#pragma once
#include <windows.h>
#include <string>
#include <iostream>
#include "retcheck.h"

#define x(x) (x - 0x400000 + ((DWORD)GetModuleHandleA(0)))
typedef DWORD _DWORD;

namespace RLua
{
    using Rlua_gettop = int(__cdecl *)(int);
    Rlua_gettop lua_gettop = (Rlua_gettop)x(0x826550);

    using Rlua_getfield = int(__fastcall *)(int, int, const char *);
    Rlua_getfield lua_getfield = (Rlua_getfield)unprotect(x(0x825F20));

    using Rlua_setfield = int(__fastcall *)(int, int, const char *);
    Rlua_setfield lua_setfield = (Rlua_setfield)unprotect(x(0x8280D0));

    using Rlua_pushstring = void(__fastcall *)(int, const char *);
    Rlua_pushstring lua_pushstring = (Rlua_pushstring)unprotect(x(0x8274A0));

    using Rlua_pushvalue = void(__stdcall *)(int, int);
    Rlua_pushvalue lua_pushvalue = (Rlua_pushvalue)unprotect(x(0x8275F0));

    using Rlua_call = int(__cdecl *)(int, int, int);
    Rlua_call lua_call = (Rlua_call)unprotect(x(0x825910));

    using Rlua_newthread = int(__cdecl *)(int);
    Rlua_newthread lua_newthread = (Rlua_newthread)unprotect(x(0x826B90));

    using Rlua_tolstring = char *(__stdcall *)(int, int, int);
    Rlua_tolstring lua_tolstring = (Rlua_tolstring)unprotect(x(0x828960));

    using Rlua_type = int(__cdecl *)(int, int);
    Rlua_type lua_type = (Rlua_type)x(0x828E20);

    using Rlua_pop = int(__cdecl *)(int, int);
    Rlua_pop lua_pop = (Rlua_pop)unprotect(x(0x8286A0));
}

namespace RBX
{
    enum MessageType : __int32
    {
        MESSAGE_OUTPUT = 0x0,
        MESSAGE_INFO = 0x1,
        MESSAGE_WARNING = 0x2,
        MESSAGE_ERROR = 0x3,
        MESSAGE_SENSITIVE = 0x4,
        MESSAGE_TYPE_MAX = 0x5,
    };

    using Rprintf = void(__cdecl *)(MessageType, const char *, ...);
    Rprintf printf = (Rprintf)x(0x5FB540);

    class Instance
    {
    public:
        Instance(int *ptr)
        {
            pointer = ptr;
        };

        std::string *getName()
        {
            return *((std::string **)(((char *)pointer) + 0x2C));
        };

        char *getChildren()
        {
            return *(char **)(*(void **)(((char *)pointer) + 0x30));
        };

        char *getFirstChild()
        {
            return *(char **)getChildren();
        };

        Instance *findFirstChild(const char *name)
        {
            char *children = getChildren();
            int currentoffset = 0;
            char *currentchild;
            std::string stdname(name);

            for (int i = 0; i < 100; i++)
            {
                currentchild = *(char **)(children + currentoffset);
                Instance *instance = new Instance((int *)currentchild);
                char *instance_name = *((char **)(currentchild + 0x2C));

                if (strcmp(instance_name, name) == 0)
                {
                    return instance;
                }
                else
                {
                    delete instance;
                    currentoffset += 8;
                }
            }

            return this;
        };

        int *pointer = nullptr;
    };

    namespace TaskScheduler
    {
        using Rscheduler = int(*)();
        Rscheduler scheduler = (Rscheduler)x(0x578210);

        struct DataModelJob
        {
            char pad_0000[16]; // 0x0000
            std::string *name; // 0x0010
            char pad_0014[20]; // 0x0014
            int *dm;           // 0x0028
            char pad_002C[20]; // 0x002C
        };
    }

    namespace ScriptContext
    {
        using RsetThreadIdentityAndSandbox = int(__cdecl *)(int, int, int);
        RsetThreadIdentityAndSandbox setThreadIdentityAndSandbox = (RsetThreadIdentityAndSandbox)x(0x80CC80);
    }
}