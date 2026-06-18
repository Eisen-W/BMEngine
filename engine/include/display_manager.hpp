#pragma once
#include<raylib.h>

inline constexpr bool PIXEL_PERFECT = false;

class displayManager{
    private:
    float scale = 1.0f;
    Vector2 fit = {0,0};
    int offsetX = 0;
    int offsetY = 0;

    static constexpr int windowWidth = 640; // initial window
    static constexpr int windowHeight = 480;

    static constexpr int canvasWidth = 640; // canvas dimensions
    static constexpr int canvasHeight = 480;

    RenderTexture2D canvas;

    public:
    displayManager();
    ~displayManager();

    void initCanvas();
    void unloadCanvas();
    void scaleWindow();
    void drawCanvasOnScreen() const;

    int getOffsetX() const {return offsetX;}
    int getOffsetY() const {return offsetY;}
    float getScale() const {return scale;}
    Vector2 getFit() const {return fit;}

    int getCanvasWidth() const {return canvasWidth;}
    int getCanvasHeight() const {return canvasHeight;}

    int getWHeight() const {return windowHeight;}
    int getWWidth() const {return windowWidth;}

    const RenderTexture2D& getCanvas() const {return canvas;}
};
//inline displayManager DM;