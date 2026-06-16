# EWEngine-2D
drag and drop engine files and template for my 2D games

### How to Use
Just drag and drop include, lib and src folders into engine directory \
edit the CMakeLists.txt and main according to game after copying and change target paths in that file
if you're not using the current template/file structure 

Raylib v6 update: in cmakelists target_link_libraries, move X11 after raylib

### How to Update From Previous Version
If you're on old engine version, After using the template
``` shell
cd <yourclonedrepo>
git remote add engine-upstream  https://github.com/Eisen-W/EWEngine-2D.git
git subtree pull --prefix=engine/ engine-upstream main --squash 
```
DO NOT USE "git subtree add" as it copies entire ewengine repo inside the engine directory if the project doesnt already have the engine directory, in that case just copy 
the engine files

### MadokaScript Integration
MadokaScript is my custom scripting language now integrated with EWEngine-2D <br>
For now it creates dialogue triggers without hardcoding it in code, simply create a file with '.mad' extension and load it in the game code corresponding to levels. <br>
To modify the triggers or dialogues just edit the .mad file without worrying about recompiling the game <br>
check out [madokascript-EWE documentation]() for more help.

### Pull madokascript updates from subtree
```shell
git subtree pull --prefix=engine/madokascript-engine/ mad-upstream main --squash 
```

### Features
- [x] Asset Manager (to load and cache assets such as texture, font, sound, music)
- [x] Display Manager (to handle window, canvas, and scaling)
- [x] Input Manager (to handle keyboard, mouse and gamepad input)
- [x] Debug view (for DEV BUILDS, it just shows stats like FPS, Time, memory usage etc.)
- [x] Intro
- [x] Animation Manager (to handle animations)
- [ ] Basic save system
- [x] Tilemap Parser
- [x] Message Box
- [x] Interactable tiles
- [x] Madokascript Integration (for dialogues and interactables)

### ChangeLog
- v0.3: interactable tiles and messagebox
- v0.2: tilemap parser and default game file structure
- v0.1: asset manager, display manager, input manager, animation manager, debug view, intro