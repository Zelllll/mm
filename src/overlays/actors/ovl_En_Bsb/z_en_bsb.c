/*
 * File: z_en_bsb.c
 * Overlay: ovl_En_Bsb
 * Description: Captain Keeta
 */

#include "z_en_bsb.h"
#include "z64rumble.h"
#include "z64shrink_window.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_UNFRIENDLY | ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_2000000)

#define THIS ((EnBsb*)thisx)

void EnBsb_Init(Actor* thisx, PlayState* play);
void EnBsb_Destroy(Actor* thisx, PlayState* play);
void EnBsb_Update(Actor* thisx, PlayState* play);
void EnBsb_Draw(Actor* thisx, PlayState* play);

static f32 D_80C0F8D0 = 0.0f;

// static ColliderJntSphElementInit sJntSphElementsInit[7] = {
static ColliderJntSphElementInit D_80C0F8D4[7] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 10, { { 1000, 400, 0 }, 40 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x04, 0x08 },
            { 0x00000000, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 9, { { 0, 700, 200 }, 35 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 6, { { 100, 600, 0 }, 35 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { 3, { { 400, 200, 0 }, 40 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 13, { { 700, -100, 0 }, 35 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 16, { { 200, 300, 0 }, 30 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 19, { { 200, 300, 0 }, 30 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80C0F9D0 = {
    {
        COLTYPE_HIT6,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_PLAYER,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    ARRAY_COUNT(D_80C0F8D4),
    D_80C0F8D4, // sJntSphElementsInit,
};

// static DamageTable sDamageTable = {
static DamageTable D_80C0F9E0 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0xD),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xE),
    /* Zora boomerang */ DMG_ENTRY(0, 0xF),
    /* Normal arrow   */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xF),
    /* Goron punch    */ DMG_ENTRY(1, 0xD),
    /* Sword          */ DMG_ENTRY(1, 0xD),
    /* Goron pound    */ DMG_ENTRY(1, 0xD),
    /* Fire arrow     */ DMG_ENTRY(0, 0x2),
    /* Ice arrow      */ DMG_ENTRY(0, 0x3),
    /* Light arrow    */ DMG_ENTRY(0, 0x4),
    /* Goron spikes   */ DMG_ENTRY(0, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0xC),
    /* Deku bubble    */ DMG_ENTRY(0, 0xF),
    /* Deku launch    */ DMG_ENTRY(1, 0xE),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(1, 0x5),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(0, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xD),
    /* Spin attack    */ DMG_ENTRY(1, 0xD),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xD),
};

ActorInit En_Bsb_InitVars = {
    /**/ ACTOR_EN_BSB,
    /**/ ACTORCAT_PROP,
    /**/ FLAGS,
    /**/ OBJECT_BSB,
    /**/ sizeof(EnBsb),
    /**/ EnBsb_Init,
    /**/ EnBsb_Destroy,
    /**/ EnBsb_Update,
    /**/ EnBsb_Draw,
};

extern UNK_TYPE D_06000C50;
extern UNK_TYPE D_06004894;

// void mode_anime_set(EnBsb* this, int i);
void func_80C0B290(EnBsb* this, s32 arg1) {
    static AnimationHeader* D_80C0FA20[] = {
        (AnimationHeader*)0x060086BC, (AnimationHeader*)0x0600CD88, (AnimationHeader*)0x06000400,
        (AnimationHeader*)0x060065D8, (AnimationHeader*)0x06000FF0, (AnimationHeader*)0x06000C50,
        (AnimationHeader*)0x06006C48, (AnimationHeader*)0x06001390, (AnimationHeader*)0x06002AF4,
        (AnimationHeader*)0x06002590, (AnimationHeader*)0x06007120, (AnimationHeader*)0x060043A4,
        (AnimationHeader*)0x06007B18, (AnimationHeader*)0x06001CD8, (AnimationHeader*)0x06003E1C,
        (AnimationHeader*)0x06003238, (AnimationHeader*)0x0600606C, (AnimationHeader*)0x06005440,
        (AnimationHeader*)0x06004E2C, (AnimationHeader*)0x06004894, (AnimationHeader*)0x06004208,
        (AnimationHeader*)0x0600D3CC, (AnimationHeader*)0x06004510, (AnimationHeader*)0x06001F90,
        (AnimationHeader*)0x0600C790,
    };
    static u8 D_80C0FA84[] = {
        0x02, 0x00, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x02, 0x02, 0x00, 0x02, 0x00, 0x00,
        0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00,
    };

    this->c_change_flag = arg1;
    this->end_frame = Animation_GetLastFrame((void*)D_80C0FA20[arg1]);
    Animation_Change(&this->skelAnime, D_80C0FA20[this->c_change_flag], 1.0f, 0.0f, this->end_frame,
                     D_80C0FA84[this->c_change_flag], -2.0f);
}

u32 D_80C0FAA0[] = {
    0x00000000,
    0x41000000,
    0x00000000,
};

u32 D_80C0FAAC[] = {
    0x00000000,
    0xBFC00000,
    0x00000000,
};

u32 D_80C0FAB8[] = {
    0x2EE0D8F0,
    0xB5C80000,
};

u32 D_80C0FAC0[] = {
    0xD8F02710,
    0xD8F00000,
};

u32 D_80C0FAC8[] = {
    0xC2A00000, 0x43ED8000, 0xC511A000, 0x00000000, 0x00000000, 0x00000000,
};

// void dust_ground_setx(PlayState* play, EnBsb* this, xyz_t* pos);
void func_80C0B31C(PlayState* play, EnBsb* this, Vec3f* pos);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0B31C.s")

// void En_Bsb_actor_ct(ACTOR* thisx, game_t* game);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/EnBsb_Init.s")

// void En_Bsb_actor_dt(ACTOR* thisx, game_t* game);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/EnBsb_Destroy.s")

// int mode_attack_check(EnBsb* this, PlayState* play);
s32 func_80C0B888(EnBsb* this, PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0B888.s")

// void mode_doshin_check(EnBsb* this, PlayState* play);
void func_80C0B970(EnBsb* this, PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0B970.s")

// void mode_attack_doshin_check(EnBsb* this, PlayState* play);
void func_80C0BA58(EnBsb* this, PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0BA58.s")

// int mode_hand_check(EnBsb* this);
s32 func_80C0BC30(EnBsb* this);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0BC30.s")

// void camera_move(EnBsb* this, PlayState* play);
void func_80C0BE1C(EnBsb* this, PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0BE1C.s")

// void mode_ocarina_check_wait_init(EnBsb* this);
void func_80C0BF2C(EnBsb* this);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0BF2C.s")

// void mode_ocarina_check_wait(EnBsb* this, PlayState* play);
void func_80C0BFE8(EnBsb* this, PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0BFE8.s")

// void mode_event_start_init(EnBsb* this, PlayState* play);
void func_80C0C0F4(EnBsb* this, PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0C0F4.s")

// void mode_event_start(EnBsb* this, PlayState* play);
void func_80C0C238(EnBsb* this, PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0C238.s")

// void mode_demo_stand_up_init(EnBsb* this);
void func_80C0C32C(EnBsb* this);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0C32C.s")

// void mode_demo_stand_up(EnBsb* this, PlayState* play);
void func_80C0C364(EnBsb* this, PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0C364.s")

// void mode_rail_walk_init(EnBsb* this);
void func_80C0C430(EnBsb* this);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0C430.s")

// void mode_rail_walk(EnBsb* this, PlayState* play);
void func_80C0C484(EnBsb* this, PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0C484.s")

// void mode_ouch_init(EnBsb* this);
void func_80C0C610(EnBsb* this);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0C610.s")

// void mode_ouch(EnBsb* this, PlayState* play);
void func_80C0C6A8(EnBsb* this, PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0C6A8.s")

// void mode_attack_move_init(EnBsb* this);
void func_80C0C86C(EnBsb* this);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0C86C.s")

// void mode_attack_move(EnBsb* this, PlayState* play);
void func_80C0C8EC(EnBsb* this, PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0C8EC.s")

// void mode_attack_jump_init(EnBsb* this, PlayState* play);
void func_80C0CA28(EnBsb* this, PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0CA28.s")

// void mode_attack_jump(EnBsb* this, PlayState* play);
void func_80C0CB3C(EnBsb* this, PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0CB3C.s")

// void mode_attack_jump_wait_init(EnBsb* this);
void func_80C0CCCC(EnBsb* this);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0CCCC.s")

// void mode_attack_jump_wait(EnBsb* this, PlayState* play);
void func_80C0CD04(EnBsb* this, PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0CD04.s")

// void mode_attack_init(EnBsb* this);
void func_80C0CD90(EnBsb* this);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0CD90.s")

// void mode_attack(EnBsb* this, PlayState* play);
void func_80C0CDE4(EnBsb* this, PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0CDE4.s")

// void mode_hirumu_init(EnBsb* this);
void func_80C0CF4C(EnBsb* this);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0CF4C.s")

// void mode_hirumu(EnBsb* this, PlayState* play);
void func_80C0CFDC(EnBsb* this, PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0CFDC.s")

// void mode_damage_init(EnBsb* this);
void func_80C0D00C(EnBsb* this);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0D00C.s")

// void mode_damage(EnBsb* this, PlayState* play);
void func_80C0D10C(EnBsb* this, PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0D10C.s")

// void mode_paralyze_init(EnBsb* this);
void func_80C0D214(EnBsb* this);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0D214.s")

// void mode_paralyze(EnBsb* this, PlayState* play);
void func_80C0D27C(EnBsb* this, PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0D27C.s")

// void mode_laugh_init(EnBsb* this);
void func_80C0D334(EnBsb* this);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0D334.s")

// void mode_laugh(EnBsb* this, PlayState* play);
void func_80C0D384(EnBsb* this, PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0D384.s")

// void mode_dead_init(EnBsb* this, PlayState* play);
void func_80C0D3C0(EnBsb* this, PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0D3C0.s")

// void mode_dead(EnBsb* this, PlayState* play);
void func_80C0D51C(EnBsb* this, PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0D51C.s")

// void mode_dosun_init(EnBsb* this, PlayState* play);
void func_80C0D964(EnBsb* this, PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0D964.s")

// void mode_dosun(EnBsb* this, PlayState* play);
void func_80C0D9B4(EnBsb* this, PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0D9B4.s")

// void mode_goal_down_init(EnBsb* this);
void func_80C0DA58(EnBsb* this);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0DA58.s")

// void mode_goal_down(EnBsb* this, PlayState* play);
void func_80C0DB18(EnBsb* this, PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0DB18.s")

// void mode_demo01_init(EnBsb* this);
void func_80C0E178(EnBsb* this);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0E178.s")

// void mode_demo01(EnBsb* this, PlayState* play);
void func_80C0E1C0(EnBsb* this, PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0E1C0.s")

// void mode_demo02_init(EnBsb* this);
void func_80C0E3B8(EnBsb* this);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0E3B8.s")

// void mode_demo02(EnBsb* this, PlayState* play);
void func_80C0E480(EnBsb* this, PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0E480.s")

// void mode_demo03(EnBsb* this, PlayState* play);
void func_80C0E4FC(EnBsb* this, PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0E4FC.s")

// void damage_proc(EnBsb* this, PlayState* play);
void func_80C0E618(EnBsb* this, PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0E618.s")

// int move_demoproc(EnBsb* this, PlayState* play);
s32 func_80C0E9CC(EnBsb* this, PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0E9CC.s")

// void En_Bsb_actor_move(ACTOR* thisx, game_t* game);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/EnBsb_Update.s")

// int bsb_display1(game_t* game, int jyoint_no, Gfx** shape, xyz_t* t, s_xyz* r, void* p);
s32 func_80C0EEA0(GameState* gameState, s32 arg1, Gfx** arg2, Vec3f* arg3, Vec3s* arg4, void* arg5);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0EEA0.s")

// int bsb_display3(game_t* game, int jyoint_no, Gfx** shape, xyz_t* t, s_xyz* r, void* p, Gfx** next_disp);
s32 func_80C0F078(GameState* gameState, s32 arg1, Gfx** arg2, Vec3f* arg3, Vec3s* arg4, void* arg5, Gfx** arg6);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0F078.s")

// void bsb_display2(game_t* game, int jyoint_no, Gfx** shape, s_xyz* r, void* p);
void func_80C0F170(GameState* gameState, s32 arg1, Gfx** arg2, Vec3s* arg3, void* arg4);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0F170.s")

// void En_Bsb_actor_draw(ACTOR* thisx, game_t* game);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/EnBsb_Draw.s")

// void en_bsb_eff_set(EnBsb* this, xyz_t* pos, xyz_t* vec, xyz_t* acc, float scale, short timer);
void func_80C0F544(EnBsb* this, Vec3f* pos, Vec3f* velocity, Vec3f* accel, f32 scale, s16 timer);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0F544.s")

// void en_bsb_eff_move(EnBsb* this, PlayState* play);
void func_80C0F640(EnBsb* this, PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0F640.s")

// void en_bsb_eff_disp(EnBsb* this, PlayState* play);
void func_80C0F758(EnBsb* this, PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bsb/func_80C0F758.s")
