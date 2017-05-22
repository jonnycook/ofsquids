#ifndef TIMER_H
#define TIMER_H

#define timer Timer::GetInstance()

class Timer {
    public:
        bool Install();
        int GetTicks() const { return ticks; }
        static Timer &GetInstance();
    private:
        Timer();
        unsigned int ticks;
};

#endif
