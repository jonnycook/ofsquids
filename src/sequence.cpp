#include "sequence.h"

Sequence::Sequence(bool _loop) {
    current = 0;
    tick = 0;
    loop = _loop;
    play = true;
}

bool Sequence::Update() {
    if (!play || frame.empty()) {
        return false;
    }
    if (++ tick >= frame[current]) {
        tick = 0;
        if (++ current >= frame.size()) {
            if (loop) {
                current = 0;
            }
            else {
                -- current;
                play = false;
            }
            return true;
        }
    }
    return false;
}
