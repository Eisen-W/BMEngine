# Display Manager

## PIXEL PERFECT FLAG
Set the flag to true or false in [display_manager.hpp](../engine/include/display_manager.hpp); default is false. <br>
Setting the flag to true uses integer scaling, however the monitor needs enough resolution to support that scale factor. <br>
For instance, if the canvas resolution is 640x480 then monitor needs at least 1280x960 to scale up to 2x. <br>
Default value 'false' uses float-based scaling, so it will scale up or down regardless of the monitor's resolution.

## Functions

### initCanvas()
- initializes canvas using TEXTURE_FILTER_POINT
- Change texture filters as needed

### unloadCanvas()
- unloads canvas

### scaleWindow()
- calculates scaling math

### drawCanvasOnScreen()
- draws canvas on window display

[previous](EWEngine.md) <br>
[next](inputmanager.md)