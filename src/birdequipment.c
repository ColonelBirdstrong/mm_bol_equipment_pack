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

// Kokiri Sword

// Razor Sword

// Gilded Sword

// Great Fairy's Sword
#include "gBoLDS1Claymore.h"
#include "gBoLMoonlightGreatsword.h"

DECLARE_ROM_SEGMENT(object_link_child);
DECLARE_ROM_SEGMENT(gameplay_keep);
DECLARE_ROM_SEGMENT(icon_item_static_yar);
DECLARE_ROM_SEGMENT(object_mir_ray);

// Shields
extern Gfx* gPlayerShields[];
extern Gfx gLinkHumanHerosShieldDL[];
extern Mtx gLinkHumanHerosShieldMtx;
extern Gfx gLinkHumanMirrorShieldDL[];
extern Mtx gLinkHumanMirrorShieldMtx;
extern Gfx object_mir_ray_DL_0004B0[];

// Swords
extern Gfx* gPlayerSwords[];
extern Gfx gLinkHumanKokiriSwordDL[];
extern Gfx gLinkHumanKokiriSwordMtx;
extern Gfx gLinkHumanRazorSwordDL[];
extern Gfx gLinkHumanRazorSwordMtx;
extern Gfx gLinkHumanGildedSwordDL[];
extern Gfx gLinkHumanGildedSwordMtx;
extern Gfx gLinkHumanGreatFairysSwordDL[];
extern Gfx gLinkHumanGreatFairysSwordMtx;

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
        Gfx* to_patch = Lib_SegmentedToVirtual(gLinkHumanHerosShieldDL);
        switch (recomp_get_config_u32("bird_heroshield_model"))
        {
        case HERO_SHIELD_OFF:
            ;
            break;
        case HERO_SHIELD_MM3D_GI:
        gSPBranchList(to_patch , gBoLMM3DHeroShield);
            break;
        case HERO_SHIELD_KITESHIELD:
        gSPBranchList(to_patch , gBoLKiteShield);
            break;
        case HERO_SHIELD_OOT3D:
        gSPBranchList(to_patch , gBoLOoT3DHyShield);
            break;
        case HERO_SHIELD_STSHIELD:
        gSPBranchList(to_patch , gBoLSTShield);
            break;
        case HERO_SHIELD_ALTTPFIGHTERSHIELD:
        gSPBranchList(to_patch , gBoLFighterShield);
            break;
        case HERO_SHIELD_ALTTPREDSHIELD:
        gSPBranchList(to_patch , gBoLRedShield);
            break;
        }
        Gfx* to_patch_2 = Lib_SegmentedToVirtual(gLinkHumanGreatFairysSwordDL);
        switch (recomp_get_config_u32("bird_greatfairysword_model"))
        {
        case GREATFAIRYSWORD_OFF:
            ;
            break;
        case GREATFAIRYSWORD_DS1CLAYMORE:
        gSPBranchList(to_patch_2 , gBoLDS1Claymore);
            break;
        case GREATFAIRYSWORD_MOONLIGHTGREATSWORD:
        gSPBranchList(to_patch_2 , gBoLMoonlightGreatsword);
            break;
        }
        gSegments[0x06] = old_segment_6;
    }
    gVrom = 0;
    gRam = NULL;
}