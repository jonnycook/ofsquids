#include "map.h"

DATAFILE *Map::tileImages;

Map::Map() {

}

BITMAP *Map::GetTileImage(int index) {
    return (BITMAP *)tileImages[index].dat;
}

bool Map::LoadTileImages() {
    if (!(tileImages = load_datafile("media/tiles.dat"))) {
        return false;
    }
    return true;
}

void Map::FreeTileImages() {
    unload_datafile(tileImages);
}

void Map::TileToScreen(int tx, int ty, int &x, int &y) {
    x = tx << 5;
    y = SCREEN_H - (ty << 5) - 32 + (int)camera.GetY();
}

void Map::Create(int _w, int _h) {
    w = _w;
    h = _h;
    tile.resize(w * h);
}

bool Map::Load(char *file) {
    PACKFILE *pf = pack_fopen(file, "r");
    if (!pf) {
        return false;
    }
    
    // Read dimensions
    w = pack_igetl(pf);
    h = pack_igetl(pf);
    tile.resize(w * h);
    
    // Read tile data
    for (int i = 0; i < w * h; ++ i) {
        // Solid flag
        tile[i].solid = pack_getc(pf);
        // Tile index
        tile[i].index = pack_igetl(pf);
    }
    
    pack_fclose(pf);
}

void Map::Save(char *file) {
    PACKFILE *pf = pack_fopen(file, "w");
    
    // Write dimensions
    pack_iputl(w, pf);
    pack_iputl(h, pf);
    
    // Tile data
    for (int i = 0; i < w * h; ++ i) {
        // Solid flag
        pack_putc(tile[i].solid, pf);
        // Tile index
        pack_iputl(tile[i].index, pf);
    }

    pack_fclose(pf);
}

void Map::Draw(BITMAP *dest, int flags) {
    int camY = ((int)camera.GetY()) >> 5;
    for (int y = 0; y < (SCREEN_H >> 5) + 1; ++ y) {
        int ty = camY + y;
        if (ty >= h) {
            break;
        }
        for (int x = 0; x < w; ++ x) {
            int sx, sy;
            TileToScreen(x, ty, sx, sy);
            draw_sprite(dest, GetTileImage(GetTile(x, ty).index), sx, sy);
            if (GetTile(x, ty).solid) {
                if (flags & DEBUG_INFO) {
                    circle(dest, sx + 15, sy + 15, 5, makecol(0, 0, 0));
                }
            }
        }
    }
    if (flags & DEBUG_INFO) {
        textprintf_centre_ex(dest, font, SCREEN_W >> 1, 0, makecol(0, 0, 0), -1, "%i, %i", w, h);
        textprintf_right_ex(dest, font, SCREEN_W, 0, makecol(0, 0, 0), -1, "%i", MIN(camY + (SCREEN_H >> 5) - 1, h - 1));
        textprintf_right_ex(dest, font, SCREEN_W, SCREEN_H - 10, makecol(0, 0, 0), -1, "%i", (int)camera.GetY() >> 5);
        textprintf_ex(dest, font, 0, SCREEN_H - 10, makecol(0, 0, 0), -1, "%.2f", camera.GetY());
    }
}

void Map::Update() {

}

void Map::AddRows(int num) {
    for (int i = 0; i < w * num; ++ i) {
        tile.push_back(Tile());
    }
    h += num;
}

void Map::RemoveRows(int num) {
    for (int i = 0; i < w * num; ++ i) {
        tile.pop_back();
    }
    h -= num;
}
