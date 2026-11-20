# Features

### Generalized Textbox
``` cpp
// in Update function
if(IsKeyPressed(KEY_ENTER))
{
    TextBoxConfig cfg;

    cfg.box = {50,50,300, 100};
    cfg.padding = 18;

    cfg.slice.texture = BME.AM.getTexture("../assets/textboxnslice.png");
    cfg.slice.active = true;
    float sliceW = cfg.slice.texture.width;
    float sliceH = cfg.slice.texture.height;
    cfg.slice.npatch.source = {0,0,sliceW,sliceH};
    int npx = 16;
    cfg.slice.npatch.left = cfg.slice.npatch.bottom = cfg.slice.npatch.right = cfg.slice.npatch.top = npx;
    cfg.slice.npatch.layout = NPATCH_NINE_PATCH;
   
    std::string customMSG = "hello <nick>";
    BME.TB.Start(BME.EUtils.processString(customMSG), "Sugma",
    false, {}, {}, cfg
    );
}
```