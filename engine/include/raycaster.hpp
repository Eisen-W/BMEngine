#pragma once

#include<raylib.h>
#include<vector>

enum struct TileFace{
    FACE_F, FACE_LF, FACE_RF, FACE_T, FACE_BT, FACE_BK
};

struct RaySlice{
    float screenX;
    float screenH;
    float dist;
    TileFace face;
};

class Raycaster{
    public:
    void Init(Texture2D& sheet);
    void Update(const Vector2& playerCenter, const std::vector<std::vector<int>>& visMap, int mapW, int mapH);
    void Draw() const;

    Vector2 crossHairPoint;
    private:
    Texture2D facesheet;
    std::vector<RaySlice> slices;

    TileFace getFace(const Vector2& pos, const Rectangle& tile) const;
    bool inFOV(Vector2 toTile, float dist, Vector2 dir) const;

    static constexpr float FOV_RAD = 1.0f;
};