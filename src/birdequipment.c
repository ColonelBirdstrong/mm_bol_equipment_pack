#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "ultra64.h"
#include "segment_symbols.h"

// Hero's Shield
#include "gBoLMM3DHeroShield.h"
#include "gBoLKiteShield.h"
#include "gBoLOoT3DHyShield.h"
#include "gBoLSTShield.h"
#include "gBoLFighterShield.h"
#include "gBoLRedShield.h"

// Mirror Shield
#include "gBoLImprovedMirrorShield.h"
#include "gBoLALTTPMirrorShield.h"
#include "gBoLMagicShield.h"

// Kokiri Sword

// Razor Sword

// Gilded Sword
#include "gBoLMagicSwordHilt.h"
#include "gBoLMagicSwordBlade.h"
#include "gBoLValentine.h"


// Great Fairy's Sword
#include "gBoLDS1Claymore.h"
#include "gBoLMoonlightGreatsword.h"
#include "gBoLPursuerUGS.h"
#include "gBoLUltimaWeapon.h"
#include "gBoLBurningDragonsword.h"

// Masks
#include "gJoJoStoneMask.h"

DECLARE_ROM_SEGMENT(object_link_child);
DECLARE_ROM_SEGMENT(gameplay_keep);
DECLARE_ROM_SEGMENT(icon_item_static_yar);
DECLARE_ROM_SEGMENT(object_mir_ray);
DECLARE_ROM_SEGMENT(object_mask_stone);

// Shields
extern Gfx* gPlayerShields[];
extern Gfx gLinkHumanHerosShieldDL[];
extern Mtx gLinkHumanHerosShieldMtx;
extern Gfx gLinkHumanMirrorShieldDL[];
extern Mtx gLinkHumanMirrorShieldMtx;
extern Gfx object_mir_ray_DL_0004B0[];

// Swords
extern Gfx* gPlayerSwords[];

// Kokiri Sword
extern Gfx* gKokiriSwordBladeDL[];
extern Gfx* gKokiriSwordHandleDL[];

// Razor Sword
extern Gfx* gRazorSwordBladeDL[];
extern Gfx* gRazorSwordHandleDL[];

// Gilded Sword
extern Gfx* gLinkHumanGildedSwordHandleDL[];
extern Gfx* gLinkHumanGildedSwordBladeDL[];
extern Gfx* gLinkHumanGildedSwordSheathDL[];
extern Gfx gLinkHumanGreatFairysSwordDL[];
extern Gfx gLinkHumanGreatFairysSwordMtx;

// Masks
extern Gfx* D_801C0B20[];
extern Gfx object_mask_stone_DL_000820[];

enum BirdHeroShieldModel {
    HERO_SHIELD_OFF,
    HERO_SHIELD_MM3D_GI,
    HERO_SHIELD_KITESHIELD,
    HERO_SHIELD_OOT3D,
    HERO_SHIELD_STSHIELD,
    HERO_SHIELD_ALTTPFIGHTERSHIELD,
    HERO_SHIELD_ALTTPREDSHIELD,
};

enum BirdGreatFairySwordModel {
    GREATFAIRYSWORD_OFF,
    GREATFAIRYSWORD_DS1CLAYMORE,
    GREATFAIRYSWORD_MOONLIGHTGREATSWORD,
    GREATFAIRYSWORD_PURSUERUGS,
    GREATFAIRYSWORD_ULTIMAWEAPON,
    GREATFAITYSWORD_BURNINGDRAGONSWORD,
};

enum BirdStoneMaskModel {
    STONEMASK_OFF,
    STONEMASK_JOJO,
};

enum BirdMirrorShieldModel {
    MIRRORSHIELD_OFF,
    MIRRORSHIELD_OOTIMPROVED,
    MIRRORSHIELD_ALTTP,
    MIRRORSHIELD_MAGIC,
};

enum BirdGildedSwordModel {
    GILDEDSWORD_OFF,
    GILDEDSWORD_MAGICSWORD,
    GILDEDSWORD_VALENTINE,
};

void* gRam;
uintptr_t gVrom;
size_t gSize;
RECOMP_HOOK("DmaMgr_ProcessRequest") void on_DmaMgr_RequestSync(DmaRequest* req) {
    gRam = req->dramAddr;
    gVrom = req->vromAddr;
    gSize = req->size;
}

// Replace Models
// num OnOffToggles {
//    TOGGLE_OFF,
//    TOGGLE_ON,
// ;
RECOMP_HOOK_RETURN("DmaMgr_ProcessRequest") void after_dma() {
    if (gVrom == SEGMENT_ROM_START(object_link_child)) {
        uintptr_t old_segment_6 = gSegments[0x06];
        gSegments[0x06] = OS_K0_TO_PHYSICAL(gRam);
        Gfx* to_patch_heroshield = Lib_SegmentedToVirtual(gLinkHumanHerosShieldDL);
        switch (recomp_get_config_u32("bird_heroshield_model"))
        {
        case HERO_SHIELD_OFF:
            ;
            break;
        case HERO_SHIELD_MM3D_GI:
        gSPBranchList(to_patch_heroshield , gBoLMM3DHeroShield);
            break;
        case HERO_SHIELD_KITESHIELD:
        gSPBranchList(to_patch_heroshield , gBoLKiteShield);
            break;
        case HERO_SHIELD_OOT3D:
        gSPBranchList(to_patch_heroshield , gBoLOoT3DHyShield);
            break;
        case HERO_SHIELD_STSHIELD:
        gSPBranchList(to_patch_heroshield , gBoLSTShield);
            break;
        case HERO_SHIELD_ALTTPFIGHTERSHIELD:
        gSPBranchList(to_patch_heroshield , gBoLFighterShield);
            break;
        case HERO_SHIELD_ALTTPREDSHIELD:
        gSPBranchList(to_patch_heroshield , gBoLRedShield);
            break;
        }
        
        Gfx* to_patch_gfs = Lib_SegmentedToVirtual(gLinkHumanGreatFairysSwordDL);
        switch (recomp_get_config_u32("bird_greatfairysword_model"))
        {
        case GREATFAIRYSWORD_OFF:
            ;
            break;
        case GREATFAIRYSWORD_DS1CLAYMORE:
        gSPBranchList(to_patch_gfs , gBoLDS1Claymore);
            break;
        case GREATFAIRYSWORD_MOONLIGHTGREATSWORD:
        gSPBranchList(to_patch_gfs , gBoLMoonlightGreatsword);
            break;
        case GREATFAIRYSWORD_PURSUERUGS:
        gSPBranchList(to_patch_gfs , gBoLPursuerUGS);
            break;
        case GREATFAIRYSWORD_ULTIMAWEAPON:
        gSPBranchList(to_patch_gfs , gBoLUltimaWeapon);
            break;
        case GREATFAITYSWORD_BURNINGDRAGONSWORD:
        gSPBranchList(to_patch_gfs , gBoLBurningDragonsword);
            break;
        }
        switch (recomp_get_config_u32("bird_stonemask_model"))
            {
        case STONEMASK_OFF:
        D_801C0B20[PLAYER_MASK_STONE - 1] = object_mask_stone_DL_000820;
            break;
        case STONEMASK_JOJO: //Credit to Xenthos for the original model!
        D_801C0B20[PLAYER_MASK_STONE - 1] = gJoJoStoneMask;
            break;
        }
        Gfx* to_patch_mirrorshield = Lib_SegmentedToVirtual(gLinkHumanMirrorShieldDL);
        switch (recomp_get_config_u32("bird_mirrorshield_model"))
        {
        case MIRRORSHIELD_OFF:
            ;
            break;
        case MIRRORSHIELD_OOTIMPROVED:
        gSPBranchList(to_patch_mirrorshield , gBoLImprovedMirrorShield);
            break;
        case MIRRORSHIELD_ALTTP:
        gSPBranchList(to_patch_mirrorshield , gBoLALTTPMirrorShield);
            break;
        case MIRRORSHIELD_MAGIC:
        gSPBranchList(to_patch_mirrorshield , gBoLMagicShield);
            break;
        }
        Gfx* to_patch_gildedswordblade = Lib_SegmentedToVirtual(gLinkHumanGildedSwordBladeDL);
        switch (recomp_get_config_u32("bird_gildedsword_model"))
        {
        case GILDEDSWORD_OFF:
            ;
            break;
        case GILDEDSWORD_MAGICSWORD:
        gSPBranchList(to_patch_gildedswordblade , gBoLMagicSwordBlade);
            break;
        case GILDEDSWORD_VALENTINE:
        gSPBranchList(to_patch_gildedswordblade , gEmptyDL);
            break;
        }
        Gfx* to_patch_gildedswordhilt = Lib_SegmentedToVirtual(gLinkHumanGildedSwordHandleDL);
        switch (recomp_get_config_u32("bird_gildedsword_model"))
        {
        case GILDEDSWORD_OFF:
            ;
            break;
        case GILDEDSWORD_MAGICSWORD:
        gSPBranchList(to_patch_gildedswordhilt , gBoLMagicSwordHilt);
            break;
        case GILDEDSWORD_VALENTINE:
        gSPBranchList(to_patch_gildedswordhilt , gBoLValentine);
            break;
        }
        Gfx* to_patch_gildedswordsheath = Lib_SegmentedToVirtual(gLinkHumanGildedSwordSheathDL);
        switch (recomp_get_config_u32("bird_gildedsword_model"))
        {
        case GILDEDSWORD_OFF:
            ;
            break;
        case GILDEDSWORD_MAGICSWORD:
            ;
            break;
        case GILDEDSWORD_VALENTINE:
        gSPBranchList(to_patch_gildedswordsheath , gEmptyDL);
            break;
        }
        gSegments[0x06] = old_segment_6;
    }
    gVrom = 0;
    gRam = NULL;
}

// RECOMP_HOOK("Player_Init") void on_Player_Init() {
//     
// }