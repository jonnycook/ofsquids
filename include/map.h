#ifndef MAP_H
#define MAP_H

#include <allegro.h>
#include <vector>
#include "camera.h"
#include "tiles.h"

class Map {
    public:
        enum {
            DEBUG_INFO = 1
        };
        struct Tile {
            Tile() : solid(false), index(TILE002) { }
            bool solid;
            int index;
        };
        Map();
        bool Load(char *file);
        void Save(char *file);
        void Create(int w, int h);
        void Draw(BITMAP *dest, int flags = 0);
        void Update();
        Tile &GetTile(int x, int y) { return tile[y * w + x]; }
        int GetW() const { return w; }
        int GetH() const { return h; }
        void AddRows(int num);
        void RemoveRows(int num);
        static void TileToScreen(int tx, int ty, int &x, int &y);
        static BITMAP *GetTileImage(int index);
        static bool LoadTileImages();
        static void FreeTileImages();
    private:
        static DATAFILE *tileImages;
        int w, h;
        std::vector<Tile> tile;
};

#endif
