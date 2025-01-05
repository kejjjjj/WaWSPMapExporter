#include "utils/hook.hpp"
#include "cm/cm_brush.hpp"
#include "r/backend/rb_endscene.hpp"

#include <chrono>
#include <thread>
using namespace std::chrono_literals;

static void CG_CreateHooks();

void CG_CreatePermaHooks()
{
	hooktable::initialize();

	CG_CreateHooks();

}
void CG_CreateHooks()
{
	hooktable::preserver<void>("__asm_adjacency_winding", 0x608AEC, __brush::__asm_adjacency_winding);
	hooktable::preserver<void, void*>("RB_DrawDebug", 0x73B1E0, RB_DrawDebug);


}