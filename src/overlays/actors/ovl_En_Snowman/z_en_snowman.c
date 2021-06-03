#include "z_en_snowman.h"

#define FLAGS 0x00000005

#define THIS ((EnSnowman*)thisx)

void EnSnowman_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSnowman_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSnowman_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSnowman_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B173D0(EnSnowman* this);
void func_80B18908(EnSnowman* this);

void func_80B19474(Actor* thisx, GlobalContext* globalCtx); // update?
void func_80B19998(Actor* thisx, GlobalContext* globalCtx); // draw?

const ActorInit En_Snowman_InitVars = {
    ACTOR_EN_SNOWMAN,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_SNOWMAN,
    sizeof(EnSnowman),
    (ActorFunc)EnSnowman_Init,
    (ActorFunc)EnSnowman_Destroy,
    (ActorFunc)EnSnowman_Update,
    (ActorFunc)EnSnowman_Draw,
};

u32 sCylinderInit[] = {
    0x04000939, 0x10010000, 0x00000000, 0x00000000, 0x00000000, 0xF7CFFFFF,
    0x00000000, 0x00050100, 0x003C0050, 0x00000000, 0x00000000,
};

u32 sSnowballCylinderInit[] = {
    0x0A110938, 0x10010000, 0x00000000, 0xF7CFFFFF, 0x00040000, 0xF7CFFFFF,
    0x00000000, 0x19010100, 0x003C0050, 0x00000000, 0x00000000,
};

DamageTable sDamageTable[] = {
    0x10, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0xF1, 0x02, 0x01, 0x01, 0x22, 0x01, 0x42, 0x01, 0x10,
    0x01, 0x02, 0x10, 0x50, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
};

CollisionCheckInfoInit sColChkInfoInit = { 2, 60, 80, 150 };

Color_RGBA8 sPrimColor = { 250, 250, 250, 255 };

Color_RGBA8 sEnvColor = { 180, 180, 180, 255 };

Vec3f sSnowVec = { 0.0f, 1.5f, 0.0f };

Gfx* D_80B19A94[] = { 0x06004400, 0x060010B0, 0x06004400 };

Gfx* D_80B19AA0[] = { 0x06005CB0, 0x06006190, 0x06006620 };

static InitChainEntry sInitChain[] = {
    ICHAIN_S8(hintId, 20, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 3000, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -1000, ICHAIN_STOP),
};

extern FlexSkeletonHeader D_060045A0;
extern FlexSkeletonHeader D_06004A90;
extern AnimationHeader D_0600554C;
extern AnimationHeader D_060046D8;

void EnSnowman_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnSnowman* this = THIS;
    s32 pad;
    s32 type;

    Actor_ProcessInitChain(&this->actor, sInitChain);

    type = (this->actor.params >> 8) & 0xFF;

    if (type == 0xFF) {
        type = 0;
    }

    this->actor.params &= 7;

    if (this->actor.params < 3) {
        SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_060045A0, &D_0600554C, &this->jointTable, &this->morphTable,
                         12);
        SkelAnime_InitSV(globalCtx, &this->skelAnime2, &D_06004A90, &D_060046D8, &this->jointTable2, &this->morphTable2,
                         3);
        CollisionCheck_SetInfo(&this->actor.colChkInfo, sDamageTable, &sColChkInfoInit);
        Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, sCylinderInit);

        if (this->actor.params == 1) {
            this->actor.flags |= 0x400;

            Actor_SpawnWithParent(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_SNOWMAN,
                                  this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0,
                                  2);
            this->actor.parent = Actor_SpawnWithParentAndCutscene(
                &globalCtx->actorCtx, globalCtx, ACTOR_EN_SNOWMAN, this->actor.world.pos.x, this->actor.world.pos.y,
                this->actor.world.pos.z, 0, 0, 0, 2, -1, (s16)this->actor.unk20, 0);

            if ((this->actor.child == NULL) || (this->actor.parent == NULL)) {
                if (this->actor.child != NULL) {
                    Actor_MarkForDeath(this->actor.child);
                }

                if (this->actor.parent != NULL) {
                    Actor_MarkForDeath(this->actor.parent);
                }

                Actor_MarkForDeath(&this->actor);
                return;
            }

            this->actor.parent->child = &this->actor;
            if (1) {}
            this->actor.child->child = this->actor.parent;
            this->actor.parent->parent = this->actor.child;
            Actor_SetScale(&this->actor, 0.02f);
        }

        do {
            this->unk_294 = this->actor.scale.x * 100.0f;
        } while (0);

        this->unk_29C = (this->unk_294 * 240.0f) + (type * 0.1f * 40.0f);

        if (this->actor.params == 2) {
            func_80B18908(this);
        } else {
            func_80B173D0(this);
        }
    } else {
        ActorPlayer* player = PLAYER;

        this->actor.flags &= -2;
        Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, sSnowballCylinderInit);
        this->actor.world.rot.y = Actor_YawBetweenActors(&this->actor, &player->base);

        this->actor.velocity.y = -5.0f + (Actor_XZDistanceBetweenActors(&this->actor, &player->base) * 0.035f);
        this->actor.velocity.y = CLAMP_MAX(this->actor.velocity.y, 3.5f);

        if (this->actor.params == 3) {
            this->actor.speedXZ = 15.0f;
        } else {
            this->actor.speedXZ = 22.5f;
            this->actor.velocity.y *= 1.5f;
        }

        this->actor.world.pos.x += this->actor.speedXZ * Math_SinS(this->actor.world.rot.y);
        this->actor.world.pos.y += this->actor.velocity.y;
        this->actor.world.pos.z += this->actor.speedXZ * Math_CosS(this->actor.world.rot.y);

        if (this->actor.params == 3) {
            this->collider.dim.radius = 8;
            this->collider.dim.height = 12;
            this->collider.dim.yShift = -6;
            ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 10.0f);
        } else {
            this->collider.dim.radius = 50;
            this->collider.dim.height = 122;
            this->collider.dim.yShift = -8;
            this->collider.info.toucher.damage = 16;
            this->actor.world.pos.y -= 32.0f;
            Actor_SetScale(&this->actor, 0.006f);
            ActorShape_Init(&this->actor.shape, 5333.3335f, func_800B3FC0, 170.0f);
            this->actor.gravity = -1.5f;
        }

        this->actor.flags |= 0x10;
        this->actor.update = func_80B19474;
        this->actor.draw = func_80B19998;
        this->timer = 5;
    }
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/EnSnowman_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B16FC0.asm")

Vec3f accel0 = { 0.0f, -1.0f, 0.0f };

Vec3f accel1 = { 0.0f, -0.5f, 0.0f };

s8 D_80B19AD0[] = { -1, -1, -1, -1, -1, -1, 0, 1, -1, 2, 3, 4 };

Vec3f D_80B19ADC[] = {
    { 2000.0f, 3000.0f, 0.0f }, { 2000.0f, -2000.0f, 0.0f }, { 3000.0f, 0.0f, 0.0f },
    { 1000.0f, 0.0f, 3000.0f }, { 1000.0f, 0.0f, -3000.0f },
};

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B17144.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B173D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B1746C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B177EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B178B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B179D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B17A58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B17CE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B17D78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B17EB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B17EFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B17F4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B17FE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B180A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B18124.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B18380.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B183A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B183C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B1848C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B18600.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B1861C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B18908.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B189C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B189D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B18A04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B18A28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B18B30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B18BB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B18C7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B18F50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/EnSnowman_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B19474.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B19718.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/EnSnowman_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B19948.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B19998.asm")
