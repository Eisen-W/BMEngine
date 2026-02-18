#pragma once
#include<raylib.h>
#include "display_manager.hpp"

class Mpoint{
    public:
    bool MouseRec(Rectangle Rec);
    Vector2 CMouse;
    float scale = 1;
    displayManager DM;
};


namespace Input{
    //MOUSE INPUT
    inline bool Lclick() { return IsMouseButtonPressed(MOUSE_BUTTON_LEFT); }

    //--------------------------------------------------------------
    //KEYBOARD INPUT

    //constant input
    // -0.25f <= deadzone <= 0.25f
    constexpr float DEADZONE = 0.25f;

    inline bool moveUp() 
    {return IsKeyDown(KEY_W) 
        || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_UP)
        || GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) < -DEADZONE;
    }

    inline bool moveDown() 
    {return IsKeyDown(KEY_S) 
        || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN)
        || GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) > DEADZONE;
    }

    inline bool moveRight() 
    {return IsKeyDown(KEY_D) 
        || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)
        || GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) > DEADZONE;
    }
    inline bool moveLeft() 
    {return IsKeyDown(KEY_A) 
        || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT) 
        || GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) < -DEADZONE;
    }

    //Action keys
    inline bool fire()
    {return IsKeyDown(KEY_SPACE)
        || IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT);
    }

    //input per frame
    inline bool pressUp() 
    {return IsKeyPressed(KEY_W) 
        || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_UP);
    }

    inline bool pressDown() 
    {return IsKeyPressed(KEY_S) 
        || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN);
    }

    inline bool pressLeft() 
    {return IsKeyPressed(KEY_A) 
        || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT);
    }

    inline bool pressRight() 
    {return IsKeyPressed(KEY_D) 
        || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT);
    }

    inline bool confirm() 
    {return IsKeyPressed(KEY_SPACE) 
        || IsKeyPressed(KEY_ENTER) 
        || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN);
    }

    inline bool back() 
    {return IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT);
    }
}