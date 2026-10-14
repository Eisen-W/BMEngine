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
. engine-add.sh
```

``` shell
sh engine-update.sh
```
directly use the above command to update if you've already added subtree

### MadokaScript Integration
MadokaScript is my custom scripting language now integrated with BMEngine <br>
For now it creates dialogue triggers without hardcoding it in code, simply create a file with '.mad' extension and load it in the game code corresponding to levels. <br>
To modify the triggers or dialogues just edit the .mad file without worrying about recompiling the game <br>
check out [madokascript-BME documentation](madokascript-BME-docs.md) for more help.

### Pull madokascript updates from subtree
```shell
sh engine-update-mad.sh
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
- [x] Renderer
- [x] MadokaScript: Options
- [x] Image and image pixels loading and caching in AssetManager
- [x] Pixel Collision against point(Vector2) and Rectangle

### TO-DO
- [ ] WRITE DOCS ASAP