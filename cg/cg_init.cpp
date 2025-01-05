#include "cg/cg_hooks.hpp"
#include "cg_init.hpp"
#include "global_macros.hpp"

#include <chrono>
#include <thread>
#include <windows.h>
#include <array>

#include "cg/cg_local.hpp"
#include "cg/cg_offsets.hpp"
#include <cm/cm_brush.hpp>
#include <cm/cm_export.hpp>
#include <cm/cm_typedefs.hpp>

#include "cmd/cmd.hpp"

#include "dvar/dvar.hpp"
#include "utils/engine.hpp"

using namespace std::chrono_literals;

const unsigned char completeVersion[] =
{
    BUILD_YEAR_CH0, BUILD_YEAR_CH1, BUILD_YEAR_CH2, BUILD_YEAR_CH3,
    '-',
    BUILD_MONTH_CH0, BUILD_MONTH_CH1,
    '-',
    BUILD_DAY_CH0, BUILD_DAY_CH1,
    'T',
    BUILD_HOUR_CH0, BUILD_HOUR_CH1,
    ':',
    BUILD_MIN_CH0, BUILD_MIN_CH1,
    ':',
    BUILD_SEC_CH0, BUILD_SEC_CH1,
    '\0'
};

void CG_Init()
{
    std::this_thread::sleep_for(300ms);
    CG_CreatePermaHooks();
    CG_MemoryTweaks();

    Cmd_AddCommand("cm_mapexport", CM_MapExport);
    Cmd_AddCommand("cm_showCollisionFilter", CM_ShowCollisionFilter);

    dvar_limits l{};
    dvar_value v{};

    v.integer = 0;

    static const char* poly_types[] = { "Edges", "Polygons" };
    static const char* showCollisionNames[] = { "Disabled", "Brushes", "Terrain", "Both" };
    static const char* elevator_types[] = { "Disabled", "Enabled", "Include Corners" };

    l.enumeration.stringCount = 4;
    l.enumeration.strings = showCollisionNames;


    Dvar_RegisterNew("cm_showCollision", dvar_type::enumeration, dvar_flags::saved,
        "Select whether to show the terrain, brush or all collision surface groups", v, l);

    l.enumeration.stringCount = 2;
    l.enumeration.strings = poly_types;

    Dvar_RegisterNew("cm_showCollisionPolyType", dvar_type::enumeration, dvar_flags::saved,
        "Select whether to display the collision surfaces as wireframe or poly interiors", v, l);

    v.value = 2000;
    l.value.max = FLT_MAX;
    l.value.min = 0.f;

    Dvar_RegisterNew("cm_showCollisionDist", dvar_type::value, dvar_flags::saved, "Maximum distance to show collision surfaces", v, l);

    v.value = 0.5f;
    l.value.max = 1.f;
    l.value.min = 0.f;
    Dvar_RegisterNew("cm_showCollisionPolyAlpha", dvar_type::value, dvar_flags::saved, "Collision transparency", v, l);

    v.enabled = true;
    Dvar_RegisterNew("cm_showCollisionDepthTest", dvar_type::boolean, dvar_flags::saved, "Select whether to use depth test in collision surfaces display", v, l);

    v.enabled = false;

    Dvar_RegisterNew("cm_onlyBounces", dvar_type::boolean, dvar_flags::none, "Only display surfaces which can be bounced", v, l);

    l.enumeration.stringCount = 3;
    l.enumeration.strings = elevator_types;
    v.integer = 0;

    Dvar_RegisterNew("cm_onlyElevators", dvar_type::enumeration, dvar_flags::none, "Only display surfaces which can be elevated", v, l);

    v.enabled = true;

    Dvar_RegisterNew("cm_ignoreNonColliding", dvar_type::boolean, dvar_flags::saved, "Don't display surfaces which don't have collisions", v, l);
    
    static std::string date = std::string(__DATE__) + " - " + std::string(__TIME__) + " ^1by ^2xkejj";

    v.string = date.c_str();
    Dvar_RegisterNew("tool_version", dvar_type::string, dvar_flags::write_protected, date.c_str(), v, l);
}

template<MemoryAddress_t Mem>
struct CGameMemoryTweak
{
    Mem address{};
    std::string tweaked{};
    std::string original{};

};


constexpr std::array<CGameMemoryTweak<std::int32_t>, 1> tweaks = {
    CGameMemoryTweak{.address = 0x6E6528, .tweaked = std::string("\xEB\x00\xBA\xF0\xF5", 5), .original = "\x74\x14" }, //jmp -> jnz in RB_EndSceneRendering
};

void CG_MemoryTweaks()
{

    for (const auto& tweak : tweaks) {
        Engine::Tools::write_bytes(tweak.address, tweak.tweaked);
    }
}