#ifndef DATA_H
#define DATA_H

#include <allegro.h>
#include "dat.h"

#define data Data::GetInstance()

class Data {
    public:
        bool Load();
        void Unload();
        void *operator[](int i) const { return dat[i].dat; }
        static Data &GetInstance();
    private:
        Data();
        DATAFILE *dat;
};

#endif
