#include "object_manager.h"
#include "object_type.h"
#include "pacer.h"
#include "player.h"
#include "flyer.h"
#include "comet.h"
#include <vector>

using namespace std;

ObjectManager::ObjectManager() {

}

ObjectManager::~ObjectManager() {
    Free();
}

ObjectManager &ObjectManager::GetInstance() {
    static ObjectManager instance;
    return instance;
}

void ObjectManager::AddObject(Object *object, bool back) {
    if (back) {
        objectList.push_back(object);
    }
    else {
        objectList.push_front(object);
    }
}

void ObjectManager::Update(Map &map) {
    std::list<ObjectList::iterator> deadList;
    ObjectList collisionList;
    
    for (ObjectList::iterator i = objectList.begin(); i != objectList.end(); ++ i) {
        Object *object = *i;
        if (object->GetY() - camera.GetY() > object->GetTriggerRange()) {
            continue;
        }
        if (object->GetY() - camera.GetY() < -SCREEN_H) {
            deadList.push_back(i);
            continue;
        }
        object->BackupCoords();
        object->Update();
        if (object->TestFlag(Object::F_TILE_COLLISION)) {
            object->CheckTileCollision(map);
        }
        if (object->TestFlag(Object::F_OBJECT_COLLISION)) {
            collisionList.push_back(object);
        }
        if (object->TestFlag(Object::F_DEAD)) {
            deadList.push_back(i);
        }
    }
    
    ObjectList::iterator end = collisionList.end();
    -- end;
    for (ObjectList::iterator i = collisionList.begin(); i != end; ++ i) {
        ObjectList::iterator j = i;
        ++ j;
        
        for (; j != collisionList.end(); ++ j) {
            if (Object::Collides(*j, *i)) {
                (*i)->HandleCollision(Object::OBJECT_COLLISION, (void *)*j);
                (*j)->HandleCollision(Object::OBJECT_COLLISION, (void *)*i);
            }
        }
    }

    for (std::list<ObjectList::iterator>::iterator i = deadList.begin(); i != deadList.end(); ++ i) {
        delete **i;
        objectList.erase(*i);
    }
}

void ObjectManager::Draw(BITMAP *dest) {
    for (ObjectList::iterator i = objectList.begin(); i != objectList.end(); ++ i) {
        (*i)->Draw(dest);
        //(*i)->DrawInfo(dest);
    }
}

bool ObjectManager::LoadObjects(char *file) {
    PACKFILE *pf = pack_fopen(file, "r");
    if (!pf) {
        return false;
    }
    char buf[7]; buf[6] = 0;
    pack_fread(buf, 6, pf);
    if (!strcmp(buf, "<objs>")) {
        int p = 0;
        int size = pack_igetl(pf);
        for (int i = 0; i < size; ++ i) {
            int type = pack_igetl(pf);
            int x = pack_igetl(pf);
            int y = pack_igetl(pf);
            Object *object = GetObjectByType(type);
            if (object) {
                switch (type) {
                    case PACER_OBJECT: {
                        int x1 = pack_igetl(pf);
                        int y1 = pack_igetl(pf);
                        int x2 = pack_igetl(pf);
                        int y2 = pack_igetl(pf);
                        Pacer *pacer = dynamic_cast<Pacer *>(object);
                        pacer->SetPath(x1, y1, x2, y2);
                        AddObject(object);
                        break;
                    }
                    case PUDDLE_OBJECT:
                        AddObject(object, false);
                        break;
                    case PLAYER_OBJECT:
                        ++ p;
                        if (p == 1) {
                            Player::one = dynamic_cast<Player *>(object);
                            Player::one->SetPlayer(1);
                            AddObject(object);
                        }
                        else if (p == 2) {
                            Player::two = dynamic_cast<Player *>(object);
                            Player::two->SetPlayer(2);
                            AddObject(object);
                        }
                        break;
                    case FLYER_OBJECT: {
                        int x = pack_igetl(pf);
                        int y = pack_igetl(pf);
                        Flyer *flyer = dynamic_cast<Flyer *>(object);
                        flyer->SetPath(x, y);
                        AddObject(object);
                        break;
                    }
                    case COMET_OBJECT: {
                        int trigger = pack_igetl(pf);
                        object->SetTriggerRange(trigger);
                        AddObject(object);
                        break;
                    }
                    default:
                        AddObject(object);
                }
                object->MoveTo(x, y);
            }
        }
    }
    pack_fclose(pf);
    return true;
}

void ObjectManager::Free() {
    for (ObjectList::iterator i = objectList.begin(); i != objectList.end(); ++ i) {
        delete *i;
    }
    objectList.clear();
}
