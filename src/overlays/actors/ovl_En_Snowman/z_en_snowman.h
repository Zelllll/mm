#ifndef Z_EN_SNOWMAN_H
#define Z_EN_SNOWMAN_H

#include <global.h>

struct EnSnowman;

typedef void (*EnSnowmanActionFunc)(struct EnSnowman*, struct GlobalContext*);

typedef struct EnSnowman {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ SkelAnime skelAnime2;
    /* 0x1CC */ Vec3s jointTable[12];
    /* 0x214 */ Vec3s morphTable[12];
    /* 0x25C */ Vec3s jointTable2[3];
    /* 0x26E */ Vec3s morphTable2[3];
    /* 0x280 */ EnSnowmanActionFunc actionFunc;
    /* 0x284 */ EnSnowmanActionFunc prevActionFunc;
    /* 0x288 */ u8 unk_288;
    /* 0x289 */ u8 unk_289;
    /* 0x28A */ u8 unk_28A;
    /* 0x28B */ u8 effType;
    /* 0x28C */ s16 timer;
    /* 0x28E */ s16 aimAngleY;
    /* 0x290 */ s16 timer2;
    /* 0x294 */ f32 unk_294;
    /* 0x298 */ f32 unk_298;
    /* 0x29C */ f32 unk_29C;
    /* 0x2A0 */ f32 effAlpha;
    /* 0x2A4 */ f32 effScale;
    /* 0x2A8 */ Vec3f aimPos;
    /* 0x2B4 */ Vec3f snowballPos;
    /* 0x2C0 */ Vec3f unk_2C0[9];
    /* 0x32C */ ColliderCylinder collider;
} EnSnowman; // size = 0x378

extern const ActorInit En_Snowman_InitVars;

#endif // Z_EN_SNOWMAN_H
