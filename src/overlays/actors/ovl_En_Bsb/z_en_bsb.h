#ifndef Z_EN_BSB_H
#define Z_EN_BSB_H

#include "global.h"
#include "assets/objects/object_bsb/object_bsb.h"

struct EnBsb;

typedef void (*EnBsbActionFunc)(struct EnBsb*, PlayState*);

typedef struct {
    /* 0x00 */ u8 type;
    /* 0x04 */ Vec3f pos;
    /* 0x10 */ Vec3f velocity;
    /* 0x1C */ Vec3f accel;
    /* 0x28 */ Vec3s workAngle;
    /* 0x30 */ f32 scale;
    /* 0x34 */ s16 timer;
} CaptainKeetaEffect;

typedef struct EnBsb {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ Vec3s jointTable[OBJECT_BSB_LIMB_MAX];
    /* 0x0206 */ Vec3s morphTable[OBJECT_BSB_LIMB_MAX];
    /* 0x0284 */ EnBsbActionFunc actionFunc;
    /* 0x0288 */ Path* path;
    /* 0x028C */ s32 pathCount;
    /* 0x0290 */ u8 hint_sound_flag;
    /* 0x0292 */ s16 moveTimer;
    /* 0x0294 */ s16 waitTimer;
    /* 0x0296 */ s16 unk_296;
    /* 0x0298 */ Vec3f damage_spd;
    /* 0x02A4 */ s32 sundry_count;
    /* 0x02A8 */ s32 sundry_flag;
    /* 0x02AC */ s16 sundry_angle;
    /* 0x02AE */ u8 dust_flag;
    /* 0x02AF */ u8 dush_bgm_flag;
    /* 0x02B0 */ s32 index;
    /* 0x02B4 */ s16 stat_mode;
    /* 0x02B6 */ s16 rail_index;
    /* 0x02B8 */ s16 start_bit;
    /* 0x02BA */ s16 end_bit;
    /* 0x02BC */ s16 angle_bak;
    /* 0x02C0 */ f32 part_break_pos;
    /* 0x02C4 */ f32 end_frame;
    /* 0x02C8 */ s16 talk_count;
    /* 0x02CA */ s16 body_alpha;
    /* 0x02CC */ s16 Event_now[5];
    /* 0x02D8 */ s32 c_change_flag;
    /* 0x02DC */ s32 type_flag;
    /* 0x02E0 */ Vec3f headPos;
    /* 0x02EC */ Vec3f move_pos;
    /* 0x02F8 */ Vec3f rightFootPos;
    /* 0x0304 */ Vec3f leftFootPos;
    /* 0x0310 */ Vec3s right_hand_angle;
    /* 0x0316 */ Vec3s leftHandRot;
    /* 0x031C */ Vec3s break_rot_angle;
    /* 0x0322 */ s16 special_damage_timer;
    /* 0x0324 */ s16 special_index;
    /* 0x0328 */ f32 special_scale;
    /* 0x032C */ f32 special_scale2;
    /* 0x0330 */ Vec3f shape_pos[17];
    /* 0x03FC */ s32 shape_jyoint_no[17];
    /* 0x0440 */ s16 shape_count;
    /* 0x0444 */ CaptainKeetaEffect effects[50];
    /* 0x0F34 */ ColliderJntSph collider;
    /* 0x0F54 */ ColliderJntSphElement colliderElements[7];
    /* 0x1114 */ u32 demo_time;
    /* 0x1118 */ s16 demo_stat;
    /* 0x111A */ s16 camNum;
    /* 0x111C */ s16 demo_count;
    /* 0x1120 */ f32 fovy;
    /* 0x1124 */ f32 fovy_max;
    /* 0x1128 */ Vec3f eye;
    /* 0x1134 */ Vec3f way;
    /* 0x1140 */ Vec3f eye_max;
    /* 0x114C */ Vec3f way_max;
} EnBsb; // size = 0x1158

#endif // Z_EN_BSB_H
