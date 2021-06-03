#include "z_en_snowman.h"

#define FLAGS 0x00000005

#define THIS ((EnSnowman*)thisx)

void EnSnowman_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSnowman_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSnowman_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSnowman_Draw(Actor* thisx, GlobalContext* globalCtx);

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

InitChainEntry sInitChain[] = {
    ICHAIN_S8(hintId, 20, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 3000, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -1000, ICHAIN_STOP),
};

Vec3f accel0 = { 0.0f, -1.0f, 0.0f };

Vec3f accel1 = { 0.0f, -0.5f, 0.0f };

s8 D_80B19AD0[] = { -1, -1, -1, -1, -1, -1, 0, 1, -1, 2, 3, 4 };

Vec3f D_80B19ADC[] = {
    { 2000.0f, 3000.0f, 0.0f }, { 2000.0f, -2000.0f, 0.0f }, { 3000.0f, 0.0f, 0.0f },
    { 1000.0f, 0.0f, 3000.0f }, { 1000.0f, 0.0f, -3000.0f },
};

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/EnSnowman_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/EnSnowman_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Snowman_0x80B16B00/func_80B16FC0.asm")

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
