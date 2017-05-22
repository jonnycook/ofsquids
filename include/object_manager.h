#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include <list>
#include "object.h"

#define objManager ObjectManager::GetInstance()

class ObjectManager {
    public:
        typedef std::list<Object *> ObjectList;
        ~ObjectManager();
        void AddObject(Object *object, bool back = true);
        void Update(Map &map);
        void Draw(BITMAP *dest);
        void Free();
        bool LoadObjects(char *file);
        static ObjectManager &GetInstance();
    private:
        ObjectManager();
        ObjectList objectList;
};

#endif
