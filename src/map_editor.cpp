#include "map_editor.h"
#include "object_type.h"
#include "tiles.h"
#include "math2.h"

#include <vector>

using namespace std;

int MapToScreen(int y) {
    return SCREEN_H - (y - (int)camera.GetY());
}

class ContextMenu {
    public:
        class Item {
            public:
                virtual ~Item() { }
                virtual void Draw(BITMAP *dest, int x, int y) = 0;
                virtual int GetHeight() = 0;
        };

        class TextItem : public Item {
            public:
                TextItem(char *_text) : text(_text) { }
                void Draw(BITMAP *dest, int x, int y) {
                    textout_ex(dest, font, text, x, y + 4, makecol(0, 0, 0), -1);
                }
                int GetHeight() { return 18; }
            private:
                char *text;
        };

        class IconItem : public Item {
            public:
                IconItem(BITMAP *_icon) : icon(_icon) { }
                void Draw(BITMAP *dest, int x, int y) {
                    draw_sprite(dest, icon, x, y);
                }
                int GetHeight() { return icon->h; }
            private:
                BITMAP *icon;
        };

        ContextMenu(int _x, int _y) {
            x = _x;
            y = _y;
            w = 50;
            selected = -1;
            selectedY = 0;
        }

        ~ContextMenu() {
            for (vector<Item *>::iterator i = itemList.begin(); i != itemList.end(); ++ i) {
                delete *i;
            }
        }
        
        void Place(int _x, int _y) {
            x = _x;
            y = _y;
        }

        void Draw(BITMAP *dest) {
            int cy = 0;
            if (selected > -1) {
                rectfill(dest, x, y + selectedY, x + w - 1, y + selectedY + itemList[selected]->GetHeight() - 1, makecol(255, 200, 120));
            }
            for (vector<Item *>::iterator i = itemList.begin(); i != itemList.end(); ++ i) {
                Item *item = *i;
                item->Draw(dest, x, y + cy);
                cy += item->GetHeight();
            }
            rect(dest, x, y, x + w - 1, y + cy - 1, makecol(0, 0, 0));
        }
        void Update() {
            int cy = 0, n = 0;
            if (mouse_x < x || mouse_x > x+ w) {
                selected = -1;
                return;
            }
            for (vector<Item *>::iterator i = itemList.begin(); i != itemList.end(); ++ i, ++ n) {
                Item *item = *i;
                int h = item->GetHeight();
                if (mouse_y > y + cy && mouse_y < y + cy + h) {
                    selected = n;
                    selectedY = cy;
                    return;
                }
                cy += h;
            }
            selected = -1;
        }
        void AddItem(Item *item) { itemList.push_back(item); }
        int GetSelection() const { return selected; }
    private:
        std::vector<Item *> itemList;
        int selected, selectedY;
        int x, y;
        int w;
};

MapEditor::MapEditor() {
    mousePressed = false;
    editMode = TILE;
    map = 0;
    objectType = -1;
    menuOpen = false;
    tileIndex = 0;
    tileSolid = false;
    selectedObject = -1;
    objectMenu = new ContextMenu(0, 0);
    for (int i = 0; i < NUM_OBJECT; ++ i) {
        objectMenu->AddItem(new ContextMenu::TextItem(GetObjectName(i)));
    }
    tileMenu = new ContextMenu(0, 0);
    for (int i = 0; i < ZEOF; ++ i) {
        tileMenu->AddItem(new ContextMenu::IconItem(Map::GetTileImage(i)));
    }
    backupTimer = 0;
}

MapEditor::~MapEditor() {
    //map->Save("map001.map");
    //SaveObjects("map001.obj");
    delete tileMenu;
    delete objectMenu;
    for (int i = 0; i < objectList.size(); ++ i) {
        delete objectList[i].extra;
    }
}

void MapEditor::SetMap(Map *_map) {
    map = _map;
    camera.SetRange(0, (map->GetH() << 5) - SCREEN_H);
}

void MapEditor::SaveObjects(char *file) {
    PACKFILE *pf = pack_fopen(file, "w");
    pack_fputs("<objs>", pf);
    pack_iputl(objectList.size(), pf);
    for (int i = 0; i < objectList.size(); ++ i) {
        pack_iputl(objectList[i].type, pf);
        pack_iputl(objectList[i].x, pf);
        pack_iputl(objectList[i].y, pf);
        switch (objectList[i].type) {
            case PACER_OBJECT:
                pack_iputl(objectList[i].extra[0], pf);
                pack_iputl(objectList[i].extra[1], pf);
                pack_iputl(objectList[i].extra[2], pf);
                pack_iputl(objectList[i].extra[3], pf);
                break;
            case FLYER_OBJECT:
                pack_iputl(objectList[i].extra[0], pf);
                pack_iputl(objectList[i].extra[1], pf);
                break;
            case COMET_OBJECT:
                pack_iputl(*objectList[i].extra, pf);
                break;
        }
    }
    pack_fclose(pf);
}

bool MapEditor::LoadObjects(char *file) {
    PACKFILE *pf = pack_fopen(file, "r");
    if (!pf) {
        return false;
    }
    char buf[7]; buf[6] = 0;
    pack_fread(buf, 6, pf);
    if (!strcmp(buf, "<objs>")) {
        int size = pack_igetl(pf);
        objectList.resize(size);
        for (int i = 0; i < size; ++ i) {
            objectList[i].type = pack_igetl(pf);
            objectList[i].x = pack_igetl(pf);
            objectList[i].y = pack_igetl(pf);
            switch (objectList[i].type) {
                case PACER_OBJECT:
                    objectList[i].extra = new int[4];
                    objectList[i].extra[0] = pack_igetl(pf);
                    objectList[i].extra[1] = pack_igetl(pf);
                    objectList[i].extra[2] = pack_igetl(pf);
                    objectList[i].extra[3] = pack_igetl(pf);
                    break;
                case FLYER_OBJECT:
                    objectList[i].extra = new int[2];
                    objectList[i].extra[0] = pack_igetl(pf);
                    objectList[i].extra[1] = pack_igetl(pf);
                    break;
                case COMET_OBJECT:
                    objectList[i].extra = new int;
                    *objectList[i].extra = pack_igetl(pf);
                    break;
            }
        }
    }
    pack_fclose(pf);
    return true;
}

void MapEditor::FilterPosition(int type, int &x, int &y) {
    x = (x / 4) * 4;
    y = (y / 4) * 4;
    switch (type) {
        case TURRET_OBJECT:
            x = (x >> 5) << 5;
            y = (y >> 5) << 5;
            break;
        case PACER_OBJECT:
            if (objectType < 0) {
                if (objectList[selectedObject].extra[0] == objectList[selectedObject].extra[2]) {
                    x = objectList[selectedObject].extra[0];
                    
                    y = MID(objectList[selectedObject].extra[1], y, objectList[selectedObject].extra[3]);
                }
                else {
                    x = MID(objectList[selectedObject].extra[0], x, objectList[selectedObject].extra[2]);
                    y = objectList[selectedObject].extra[1];
                }
            }
            break;
    }
}

void MapEditor::UpdateTileEditor() {
    if (key[KEY_SPACE]) {
        int x = 0, y = 0;
        for (int i = 0; i < ZEOF; ++ i) {
            if (mouse_x > x && mouse_x < x + 31 &&
                mouse_y > y && mouse_y < y + 31) {
                tileIndex = i;
                break;
            }
            y += 32;
            if (y == SCREEN_H) {
                y = 0;
                x += 32;
            }
        }
    }
    else {
        if (mouse_b & 1) {
            map->GetTile(tileX, tileY).solid = tileSolid;
            map->GetTile(tileX, tileY).index = tileIndex;
        }
        else if (mouse_b & 2) {
            map->GetTile(tileX, tileY).solid = false;
            map->GetTile(tileX, tileY).index = TILE002;
        }
    }
}

void MapEditor::UpdateObjectEditor() {
    if (key[KEY_SPACE]) {
        if (!menuOpen) {
            menuOpen = true;
            objectMenu->Place(mouse_x, mouse_y);
        }
    }
    else {
        if (menuOpen) {
            menuOpen = false;
            objectType = objectMenu->GetSelection();
        }
    }

    if (menuOpen) {
        objectMenu->Update();
    }
    
    if (keycode) {
        switch (keycode >> 8) {
            case KEY_DEL:
                if (selectedObject < objectList.size() && selectedObject >= 0) {
                    objectList.erase(objectList.begin() + selectedObject);
                    selectedObject = MIN(selectedObject, objectList.size() - 1);
                }
                break;
        }
    }
    
    if (mouse_b & 1) {
        if (!mousePressed) {
            mousePressed = true;
            if (objectType > -1) {
                selectedObject = objectList.size();
                int x = cursorX - 15, y = cursorY + 15;
                FilterPosition(objectType, x, y);
                int *extra = 0;
                
                // Extra object info
                switch (objectType) {
                    case PACER_OBJECT:
                        extra = new int[4];
                        extra[0] = x;
                        extra[1] = y;
                        extra[2] = x;
                        extra[3] = y;
                        break;
                    case FLYER_OBJECT:
                        extra = new int[2];
                        extra[0] = 0;
                        extra[1] = 0;
                        break;
                    case COMET_OBJECT:
                        extra = new int;
                        *extra = 0;
                        break;
                }

                objectList.push_back(ObjectInfo(objectType, x, y, extra));
            }
            else {
                bool mouseCaught = false;
                for (int i = 0; i < objectList.size(); ++ i) {
                    int v1 = cursorX - (objectList[i].x + 15);
                    int v2 = cursorY - (objectList[i].y - 15);
                    if (v1*v1 + v2*v2 < 16*16) {
                        if (selectedObject == i) {
                            objectDragging = true;
                        }
                        selectedObject = i;
                        mouseCaught = true;
                        break;
                    }
                }
                if (!mouseCaught) {
                    if (selectedObject > -1) {
                        switch (objectList[selectedObject].type) {
                            case PACER_OBJECT:
                                if (ABS(cursorX - objectList[selectedObject].extra[0]) > ABS(cursorY - objectList[selectedObject].extra[1])) {
                                    objectList[selectedObject].extra[2] = MAX(cursorX, objectList[selectedObject].extra[0]);
                                    objectList[selectedObject].extra[3] = objectList[selectedObject].extra[1];
                                }
                                else {
                                    objectList[selectedObject].extra[2] = objectList[selectedObject].extra[0];
                                    objectList[selectedObject].extra[3] = MAX(cursorY, objectList[selectedObject].extra[1]);
                                }
                                break;
                            case FLYER_OBJECT:
                                objectList[selectedObject].extra[0] = mouse_x - objectList[selectedObject].x;
                                objectList[selectedObject].extra[1] = mouse_y - MapToScreen(objectList[selectedObject].y);
                                break;
                                
                            case COMET_OBJECT:
                                *objectList[selectedObject].extra = MAX(0, objectList[selectedObject].y - cursorY);
                                break;
                        }
                    }
                }
            }
        }
    }
    else {
        objectDragging = false;
        mousePressed = false;
    }
    
    if (objectDragging) {
        objectList[selectedObject].x = cursorX - 15;
        objectList[selectedObject].y = cursorY + 15;
        FilterPosition(objectList[selectedObject].type, objectList[selectedObject].x, objectList[selectedObject].y);
    }
}

void MapEditor::Update() {
    cursorX = mouse_x;
    cursorY = SCREEN_H - mouse_y + (int)camera.GetY();
    tileX = cursorX >> 5;
    tileY = cursorY >> 5;
    
    if (keypressed()) {
        keycode = readkey();
    }
    else {
        keycode = 0;
    }
    
    if (keycode) {
        switch (keycode >> 8) {
            case KEY_TAB:
                editMode = (editMode == TILE ? OBJECT : TILE);
                keycode = 0;
                break;
            case KEY_UP:
                camera.Scroll(1.0f);
                keycode = 0;
                break;
            case KEY_DOWN:
                camera.Scroll(-1.0f);
                keycode = 0;
                break;
            case KEY_PGUP:
                camera.Scroll(32.0f);
                keycode = 0;
                break;
            case KEY_PGDN:
                camera.Scroll(-32.0f);
                keycode = 0;
                break;
            case KEY_HOME:
                camera.Jump(0);
                keycode = 0;
                break;
            case KEY_F5:
                map->Save("map001.map");
                SaveObjects("map001.obj");
                keycode = 0;
                break;
            case KEY_F9:
                map->Load("map001.map");
                LoadObjects("map001.obj");
                keycode = 0;
                break;
            case KEY_S:
                tileSolid = !tileSolid;
                keycode = 0;
                break;
            case KEY_EQUALS:
                map->AddRows(1);
                SetMap(map);
                keycode = 0;
                break;
            case KEY_MINUS:
                map->RemoveRows(1);
                SetMap(map);
                keycode = 0;
                break;
        }
    }
    
    if (editMode == TILE) {
        UpdateTileEditor();
    }
    else {
        UpdateObjectEditor();
    }
    
    if (++ backupTimer > 60 * 60) {
        map->Save("map001.map.bak");
        SaveObjects("map001.obj.bak");
        backupTimer = 0;
    }
}

void MapEditor::DrawTileEditor(BITMAP *dest) {
    if (key[KEY_SPACE]) {
        int x = 0, y = 0;
        for (int i = 0; i < ZEOF; ++ i) {
            draw_sprite(dest, Map::GetTileImage(i), x, y);
            if (tileIndex == i) {
                rect(dest, x, y, x + 31, y + 31, makecol(255, 0, 0));
            }
            y += 32;
            if (y == SCREEN_H) {
                y = 0;
                x += 32;
            }
        }
    }
    else {
        int sx, sy;
        Map::TileToScreen(tileX, tileY, sx, sy);
        rect(dest, sx, sy, sx + 31, sy + 31, makecol(0, 0, 0));
        if (tileSolid) {
            circle(dest, sx + 15, sy + 15, 10, makecol(255, 100, 100));
        }
    }
}

void MapEditor::DrawObjectEditor(BITMAP *dest) {
    if (menuOpen) {
        objectMenu->Draw(dest);
    }
    else {
        if (objectType > -1) {
            textout_ex(dest, font, GetObjectName(objectType), mouse_x, mouse_y, -1, 0);
        }
    }
}

void MapEditor::Draw(BITMAP *dest) {
    map->Draw(dest, Map::DEBUG_INFO);
    for (int i = 0; i < objectList.size(); ++ i) {
        int sx = objectList[i].x;
        int sy = SCREEN_H - (int)(objectList[i].y - camera.GetY());
        textout_ex(dest, font, GetObjectName(objectList[i].type), sx, sy, 0, -1);
        circle(dest, sx + 15, sy + 15, 16, (selectedObject == i ? makecol(255, 0, 0) : makecol(0, 0, 0)));
        putpixel(dest, sx, sy, makecol(0, 0, 0));
        switch (objectList[i].type) {
            case PACER_OBJECT: {
                int *extra = objectList[i].extra;
                line(dest, extra[0], MapToScreen(extra[1]), extra[2], MapToScreen(extra[3]), makecol(0, 0, 0));
                break;
            }
            case FLYER_OBJECT: {
                textprintf_ex(dest, font, sx, sy + 32, 0, -1, "%.2f", (1/180.0f)*objectList[i].extra[1]);
                float x = 0;
                float y = 0;
                for (int j = 0; j < 180; ++ j) {
                    putpixel(dest, objectList[i].x + x, MapToScreen(objectList[i].y) + y , 0);
                    x += ((float)objectList[i].extra[0]/90.0f)*Sin(j);
                    y += (1/180.0f)*objectList[i].extra[1];
                }
                break;
            }
            case COMET_OBJECT: {
                int y = MapToScreen(objectList[i].y - *objectList[i].extra);
                vline(dest, sx, sy, y, 0);
                hline(dest, sx - 10, y, sx + 10, 0);
                break;
            }
        }
    }
    if (editMode == TILE) {
        DrawTileEditor(dest);
    }
    else {
        DrawObjectEditor(dest);
    }
    textprintf_ex(dest, font, 0, 0, makecol(0, 0, 0), -1, "%i, %i", tileX, tileY);
    textprintf_ex(dest, font, 0, 10, makecol(0, 0, 0), -1, "%i, %i", cursorX, cursorY);
    circle(dest, mouse_x, mouse_y, 3, makecol(255, 0, 0));
    putpixel(dest, mouse_x, mouse_y, 0);
}
