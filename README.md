# santer's legacysploit (gay name)

## what's this?
mega pro level 0 luacapi exploit (idk how do i make level 6) for 2019M Roblox. get client in [RBLXHub](https://discord.gg/PjaBNuMsRC)

doesnt use shitty retarded ass methods for execution like scanning scriptcontext in memory

this thing is getting job **WaitingScriptJob** from **TaskScheduler** jobs and then getting **DataModel** and then getting **ScriptContext** using **DataModel** (basically ScriptContext is a child of DataModel)!!!

and yuh after getting **ScriptContext** this baby gets global lua state and creating new lua thread for more rizz (so this gives full access to lua_state)

this method is so **OP** that takes **less than 1/4 second** for execution if **WaitingScriptJob** is active

if you inject like right after roblox is started then you will be able to execute luacapi **before client sided scripts will start**
> ^ (2 seconds difference)

relative new to C++ so enjoy this dog shit code (look at WaitingScriptJob getter code for braincells loss)

also this project is pretty beginner friendly

## whats working and not

- [ ] finished
    - [x] getting WaitingScriptJob
    - [x] getting datamodel
	- [x] getting script context
    - [x] getting WaitingScriptJob has poor implementation
	- [ ] set identity >>> broken idk
	- [ ] lua wrapper

## how to build?
### vscode
open Visual Studio 2022 Developer Command Prompt

cd folder that contains this project

```bash
code .
```

done

CTRL + SHIFT + B for build

### visual studio
idk theres no .sln file good luck