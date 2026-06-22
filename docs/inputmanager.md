# Input Manager

## Functions

> Mouse functions are still buggy and being tested
### MouseRec(Rectangle Rec)
- the function checks collision between the mouse position and the given rectangle <br>
- pair it with Lclick() to detect clicks inside that rectangle, useful for menus and other clickable UI elements <br>
- MouseRec() is a member function of Mpoint class. accessed through the mousepoint object inside the Engine struct <br>
- Lclick() is a free function in the Input namespace <br>
- to call these functions: <br>
EWE.mousepoint.MouseRec(Rec) <br>
Input::Lclick()

- example:
```` cpp
if(EWE.mousepoint.MouseRec(buttonRec) && Input::Lclick()) 
{
    // button function
}
````

### Input Namespace
- Functions in the Input namespace are simple boolean wrappers around Raylib's input functions.
- example:
````cpp
inline bool Lclick() { return IsMouseButtonPressed(MOUSE_BUTTON_LEFT); }

inline bool pressX()
    {return IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT);
    }
````
- Default controller keybindings assume an  Xbox-layout controller for face buttons: 
    - face down = A;
    - face right = B;
    - face left = X;
    - face up = Y;
Change the keybinds as needed

> WIP: MadokaScript configs will auto-assign buttons from a .mad config file instead of using hardcoded keybinds.

[previous](displaymanager.md) <br>
[next](assetmanager.md)