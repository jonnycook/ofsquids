#include "object_type.h"
#include "object.h"

// Object includes
#include "player.h"
#include "stalker.h"
#include "pacer.h"
#include "turret.h"
#include "flyer.h"
#include "comet.h"
#include "puddle.h"
#include "evil_squid.h"
#include "checkpoint.h"

const char *objectName[] = {
    "player",
    "stalker",
    "turret",
    "comet",
    "pacer",
    "flyer",
    "puddle",
    "evil squid",
    "checkpoint",
};

Object *GetObjectByType(int type) {
    switch (type) {
        case PLAYER_OBJECT:
            return new Player;
        case PACER_OBJECT:
            return new Pacer;
        case STALKER_OBJECT:
            return new Stalker;
        case TURRET_OBJECT:
            return new Turret;
        case FLYER_OBJECT:
            return new Flyer;
        case COMET_OBJECT:
            return new Comet;
        case PUDDLE_OBJECT:
            return new Puddle;
        case EVIL_SQUID_OBJECT:
            return new EvilSquid;
        case CHECKPOINT_OBJECT:
            return new Checkpoint;
    }
    return 0;
}

char *GetObjectName(int type) {
    return (char *)objectName[(int)type];
}
