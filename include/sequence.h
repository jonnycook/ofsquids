#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <vector>
#include "allegro.h"

class Sequence {
    public:
        Sequence(bool loop = false);
        bool Update();
        void AddFrame(int delay) { frame.push_back(delay); }
        int GetFrame() const { return current; }
        void Reset() { current = 0; tick = 0; play = true; }
        void JumpToFrame(int f) { current = MID(0, f, frame.size()); }
        void SetLoop(int _loop) { loop = _loop; }
    private:
        int current;
        int tick;
        bool loop;
        bool play;
        std::vector<int> frame;
};

#endif

        
