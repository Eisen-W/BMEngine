# Blue Maniac Engine Documentation

## A
### anim_manager
``` cpp
enum struct anim_Type{REPEATING, ONESHOT};

struct anim_values{int first; int last; int curr; float speed; float duration_left; anim_Type type;};

void anim_Update(anim_values *self);
Rectangle anim_frame(anim_values *self, int frames_per_row, int tileset_px);
```
### asset_manager
``` cpp
Texture2D&  getTexture(const std::string& path);    
Font&       getFont(const std::string& path);
Font&       getFontEx(const std::string& path, int FontSize, std::vector<int> codepoints);
Sound&      getSound(const std::string& path);
Music&      getMusic(const std::string& path);
Model&      getModel(const std::string& path);
```

## D

### display_manager
``` cpp
struct CanvasEntry{ RenderTexture2D texture; std::string id; int width; int height; };

// main canvas - index 0
void initCanvas();
void unloadCanvas();

// multi canvas
int     addCanvas(const std::string& id, int w, int h);
void    removeCanvas(int index);
const   RenderTexture2D& getCanvas(int index = 0) const;
const   RenderTexture2D& getCanvas(const std::string& id) const;
int     getCanvasIndex(const std::string& id) const;
int     getCanvasCount() const { return (int)canvases.size(); }
void    scaleWindow();
void    drawCanvasOnScreen(int index = 0) const;
void    drawCanvasAt(int index, Rectangle dest) const;

// getters
int     getOffsetX()        const {return offsetX;}
int     getOffsetY()        const {return offsetY;}
float   getScale()          const {return scale;}
Vector2 getFit()            const {return fit;}
int     getCanvasWidth()    const {return canvasWidth;}
int     getCanvasHeight()   const {return canvasHeight;}
int     getWHeight()        const {return windowHeight;}
int     getWWidth()         const {return windowWidth;}
```

## E

### engine_utils
``` cpp
void startMessageBox(const DialogueData& data);

void checkInteractDialogue(Rectangle playerRec, Direction playerDir);    //call on input
void checkAutoDialogue(Rectangle playerRec);        //call every frame
```

### engine
``` cpp
struct Engine{
    AssetManager    AM;
    DisplayManager  DM;
    Debug           dbg;
    Mpoint          mousepoint;
    Intro           intro;
    Tilemap         TM;
    Animation       Anim;
    TextBox         TB;
    MadLoader       madloader;
    EngineUtils     EUtils;
    FacesetManager  FaceSM;
    SaveManager     SAVE;
    BlockManager    moveblock;
    ScreenManager   screens;
    Raycaster       raycast; // just for fun because why not
};
```
## F

### faceset_manager
``` cpp
void registerFace(const std::string& name, Rectangle rect);
bool getFace(const std::string& name, Rectangle& out) const;
```

## G

### globalfont
``` cpp
// edit or add in the header per your requirements
namespace JPFont { inline std::vector<int> GetCodePoints() }
namespace GlobalFont{ inline Font EngineFont(AssetManager& AM) }
```

## I

### [input_manager](engine/include/input_manager.hpp)
``` cpp
bool MouseRec(Rectangle Rec); // for mouse point and rectangle collision

inline bool NavTick(float& timer, float delay = 0.15f) // experimental function
```

## L

### loader
``` cpp
void FLoad(const char* madfile); // File Load

// dialogue passthrough
const std::vector<DialogueData>& getDialogueBlocks() const;
void startDialogue(int id, int rectIndex = -1);
void advanceDialogue();
const DialogueData* currentDialogue() const;
bool dialogueRunning() const;
std::string buildRaw(const DialogueData& data) const;
bool hasFiredRect(int id, int rectIndex) const;

void saveDialogueState(FILE* f) const;
void loadDialogueState(FILE* f);

// interactable passthroughs
const std::vector<SwitcherData>& getSwitchers() const;
bool getSwitcherState(int id) const;
void setSwitcherState(int id, bool value);
const std::vector<MoveableData>& getMoveables() const;
int getMoveableDestIndex(int id) const;
void setMoveableDestIndex(int id, int destIndex);
bool isMoveableSolved(int id) const;

void saveInteractableState(FILE* f) const;
void loadInteractableState(FILE* f);
```

## M

### messagebox 
``` cpp
// textbox
void Start(const std::string& raw, const std::string& speakerName, bool hasFace_ = false, Texture2D faceTex_ = {}, Rectangle faceRect_ = {});
void Update(float dt);
void Draw();
void HandleTB();
bool isActive() const { return active; }
```

## R

## raycaster
``` cpp
void Init(Texture2D& sheet);
void Update(const Vector2& playerCenter, const std::vector<std::vector<int>>& visMap, int mapW, int mapH);
void Draw() const;
```

## S

### save_manager
``` cpp
bool openSave(const char* path);
bool openLoad(const char* path);
void close();

//write functions
void writeInt(int val);
void writeFloat(float val);
void writeBool(bool val);
void writeString(const std::string& val);

//read functions
int readInt();
float readFloat();
bool readBool();
std::string readString();

FILE* getFile() const { return f; }

bool fileExists(const char* path) const;
```

### screen_manager
``` cpp
void add(const std::string& id, IScreen* screen);
void switchTo(const std::string& id);
void InitAll();
```

## T

### tilemap
```cpp
void Load(const char* collisionFile, const char* visualFile, const char* objectFile, const char* TsPath, int width, int height);
void Draw();

void destroyTile(int x, int y);
void setCollisionTile(int x, int y, int val) { collisionMap[y][x] = val; }
void setVisualTile(int x, int y, int val) {visualMap[y][x] = val; }
void setObjectTile(int x, int y, int val) { objectMap[y][x] = val; }

int getMapWidth()   const { return mapWidth; }
int getMapHeight()  const { return mapHeight; }
```