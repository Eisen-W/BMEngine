#pragma once
#include<raylib.h>
#include <string>
#include <vector>

inline constexpr bool PIXEL_PERFECT = false;

struct CanvasEntry{
    RenderTexture2D texture;
    std::string id;
    int width;
    int height;
};

class DisplayManager{
    private:
    float scale = 1.0f;
    Vector2 fit = {0,0};
    int offsetX = 0;
    int offsetY = 0;

    static constexpr int windowWidth = 640; // initial window size
    static constexpr int windowHeight = 480;

    static constexpr int canvasWidth = 640; // canvas dimensions
    static constexpr int canvasHeight = 480;

    std::vector<CanvasEntry> canvases;

    public:
    DisplayManager();
    ~DisplayManager();

    //main canvas - index 0
    void initCanvas();
    void unloadCanvas();

    // multi canvas
    int addCanvas(const std::string& id, int w, int h);
    void removeCanvas(int index);

    const RenderTexture2D& getCanvas(int index = 0) const;
    const RenderTexture2D& getCanvas(const std::string& id) const;
    int getCanvasIndex(const std::string& id) const;
    int getCanvasCount() const { return (int)canvases.size(); }

    void scaleWindow();
    void drawCanvasOnScreen(int index = 0) const;
    void drawCanvasAt(int index, Rectangle dest) const;

    int     getOffsetX()        const {return offsetX;}
    int     getOffsetY()        const {return offsetY;}
    float   getScale()          const {return scale;}
    Vector2 getFit()            const {return fit;}
    int     getCanvasWidth()    const {return canvasWidth;}
    int     getCanvasHeight()   const {return canvasHeight;}
    int     getWHeight()        const {return windowHeight;}
    int     getWWidth()         const {return windowWidth;}
};