#ifndef MAP_EDITOR_H
#define MAP_EDITOR_H

#include "map.h"
#include <vector>
#include <iostream>

class ContextMenu;

class MapEditor {
    struct ObjectInfo {
        ObjectInfo(int _type = 0, int _x = 0, int _y = 0, int *_extra = 0) : type(_type), x(_x), y(_y), extra(_extra) { }
        int type;
        int x, y;
        int *extra;
    };
    typedef std::vector<ObjectInfo> ObjectList;
    public:
        MapEditor();
        ~MapEditor();
        void SetMap(Map *map);
        void Draw(BITMAP *dest);
        void Update();
    private:
        void SaveObjects(char *file);
        bool LoadObjects(char *file);
        void FilterPosition(int type, int &x, int &y);
        void UpdateTileEditor();
        void UpdateObjectEditor();
        void DrawTileEditor(BITMAP *dest);
        void DrawObjectEditor(BITMAP *dest);
        enum { TILE, OBJECT } editMode;
        bool menuOpen;
        int objectType;
        int selectedObject;
        int tileIndex;
        bool tileSolid;
        int tileX, tileY;
        int cursorX, cursorY;
        int keycode;
        bool mousePressed;
        bool objectDragging;
        ObjectList objectList;
        Map *map;
        ContextMenu *tileMenu;
        ContextMenu *objectMenu;
        int backupTimer;
};

#endif
