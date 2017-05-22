#ifndef OBJECT_TYPE_H
#define OBJECT_TYPE_H

class Object;

enum {
    PLAYER_OBJECT,
    STALKER_OBJECT,
    TURRET_OBJECT,
    COMET_OBJECT,
    PACER_OBJECT,
    FLYER_OBJECT,
    PUDDLE_OBJECT,
    EVIL_SQUID_OBJECT,
    CHECKPOINT_OBJECT,
    NUM_OBJECT
};

Object *GetObjectByType(int type);
char *GetObjectName(int type);

#endif
