#ifndef CONSOLE_H
#define CONSOLE_H

#include <allegro.h>
#include <string>

#define console Console::GetInstance()

class Console {
    class Window {
        public:
            Window();
            void Setup(int x, int y, int w, int h);
            void Draw(BITMAP *buffer, std::string &text);
            void Update();
        private:
            int x, y;
            int w, h;
            int letterHeight, letterWidth;
            int maxRows;
    };
    
    class Input {
        public:
            Input();
            void Setup(int x, int y, int w, int h);
            void Draw(BITMAP *buffer);
            bool Update();
            std::string GetText() const { return lastText; }
        private:
            int x, y;
            int w, h;
            std::string text, lastText;
    };
        
    public:
        Console();
        static Console &GetInstance();
        void Update();
        void Draw(BITMAP *buffer);
        void Setup(int x, int y, int w, int h);
        Console &operator<<(const char *str) { text += str; return *this; }
    private:
        Window window;
        Input input;
        std::string text;
        int x, y;
        int w, h;
};

#endif
