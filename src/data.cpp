#include "data.h"

Data::Data() {
    dat = 0;
}

bool Data::Load() {
    dat = load_datafile("media/data.dat");
    return (bool)dat;
}

void Data::Unload() {
    unload_datafile(dat);
}

Data &Data::GetInstance() {
    static Data instance;
    return instance;
}
