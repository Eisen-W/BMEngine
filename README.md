# Blue Maniac Engine
drag and drop engine files and template for my games. <br>
Visual tools and editor not included.
---
Raylib version: Raylib v6.*


### Docs
- [Documentation](docs.md) <br>

### How to Update From Previous Version
If you're on old engine version and haven't added engine-upstream in remote
``` shell
cd <yourclonedrepo>
git remote add engine-upstream  https://github.com/Eisen-W/BMengine.git
git subtree add --prefix=engine/ engine-upstream main --squash
```
After adding subtree, delete everything from 'parent engine' directory and copy contents of 'engine subdirectory' in 'parent engine' directory
commit changes and use command below to update/pull changes from remote

``` shell
git subtree pull --prefix=engine/ engine-upstream main --squash
```
directly use the above command to update if you've already added subtree

### MadokaScript Integration
MadokaScript is my custom scripting language now integrated with BMEngine <br>
For now it creates dialogue triggers without hardcoding it in code, simply create a file with '.mad' extension and load it in the game code corresponding to levels. <br>
To modify the triggers or dialogues just edit the .mad file without worrying about recompiling the game <br>
check out [madokascript-BME documentation]() for more help.

### Pull madokascript updates from subtree
```shell
git subtree pull --prefix=engine/madokascript-engine/base/ mad-base main --squash
```

### Features
- [x] Asset Manager (to load and cache assets such as texture, font, sound, music)
- [x] Display Manager (to handle window, canvas, and scaling)
- [x] Input Manager (to handle keyboard, mouse and gamepad input)
- [x] Debug view (for DEV BUILDS, it just shows stats like FPS, Time, memory usage etc.)
- [x] Intro
- [x] Animation Manager (to handle animations)
- [x] Basic save system
- [x] Tilemap Parser
- [x] Message Box
- [x] Interactable tiles
- [x] Madokascript Integration (for dialogues and interactables)
- [x] Screen Manager

### ChangeLog
- v0.5: Generalized screen manager 
- v0.4: Generalized display manager and added MadokaScript features such as Dialogue scripting and moveable block puzzle scripting
- v0.3: Interactable tiles and messagebox
- v0.2: Tilemap parser and default game file structure
- v0.1: Asset manager, Display manager, Input manager, Animation manager, Debug view, Engine intro

### TO-DO
- [ ] WRITE DOCS ASAP