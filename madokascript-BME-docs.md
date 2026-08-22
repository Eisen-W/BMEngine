# MadokaScript BME Documentation

## Syntax

### Dialogue Block
``` cpp
DIALOGUES {
// AUTO DIALOGUES
    auto {
        id = 1;
        next = 0;
        once = false/true;
        rect = [(x,y,w,h, dir),(rect2)];
        speaker = "speaker name";
        sprite = "sprite name";
        lines = ["page 1", "next page, page 2"];
    }

// INTERACTABLE DIALOGUES
    interact {
        id = 1;
        next = 0;
        once = false;
        rect = [(x,y,w,h, dir)];
        speaker = "speaker name";
        sprite = "sprite name"
        lines = ["Hello World", "Next Page"];
    }
}
```

### Interactable Block
``` cpp
INTERACTABLES{
// MOVEABLE BLOCKS
    moveable {
        id = 1;
        name = "pushing block puzzle";
        start = (single_rect);
        dest = [(rect1), (rect2)];
    }
// SWITCHER BLOCKS
    switcher {
        id = 1;
        name = "lever or switch";
        rect = [(rect1), (rect2)];
    }
}
```
