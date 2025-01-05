#include "cg/cg_local.hpp"
#include "cg/cg_offsets.hpp"
#include "cm_brush.hpp"
#include "cm_renderer.hpp"
#include "cm_typedefs.hpp"
#include "com/com_vector.hpp"
#include "dvar/dvar.hpp"
#include "r/backend/rb_endscene.hpp"
#include "utils/hook.hpp"
#include "utils/typedefs.hpp"

using namespace std::string_literals;

#include <ranges>


void RB_DrawDebug(void* viewParms)
{
	CM_ShowCollision(viewParms);

	return hooktable::find<void, void*>("RB_DrawDebug"s)->call(viewParms);
}


void CM_DrawCollisionPoly(const std::vector<fvec3>& points, const float* colorFloat, bool depthtest)
{
	RB_DrawPolyInteriors(points, colorFloat, true, depthtest);
}

GfxPointVertex verts[2075];
void CM_DrawCollisionEdges(const std::vector<fvec3>& points, const float* colorFloat, bool depthtest)
{
	const auto numPoints = points.size();
	auto vert_count = 0;
	auto vert_index_prev = numPoints - 1u;


	for (auto i : std::views::iota(0u, numPoints)) {
		vert_count = RB_AddDebugLine(verts, depthtest, points[i].As<vec_t*>(), points[vert_index_prev].As<vec_t*>(), colorFloat, vert_count);
		vert_index_prev = i;
	}

	RB_DrawLines3D(vert_count / 2, 1, verts, depthtest);
}

void CM_ShowCollision([[maybe_unused]]void* v)
{

	if (CClipMap::Size() == 0)
		return;

	cplane_s frustum_planes[6];
	CreateFrustumPlanes(frustum_planes);

	showCollisionType collisionType = static_cast<showCollisionType>(Dvar_FindMalleableVar("cm_showCollision")->current.integer);

	cm_renderinfo render_info =
	{
		.frustum_planes = frustum_planes,
		.num_planes = 5,
		.draw_dist = Dvar_FindMalleableVar("cm_showCollisionDist")->current.value,
		.depth_test = Dvar_FindMalleableVar("cm_showCollisionDepthTest")->current.enabled,
		.as_polygons = static_cast<polyType>(Dvar_FindMalleableVar("cm_showCollisionPolyType")->current.integer) == polyType::POLYS,
		.only_colliding = Dvar_FindMalleableVar("cm_ignoreNonColliding")->current.enabled,
		.only_bounces = Dvar_FindMalleableVar("cm_onlyBounces")->current.enabled,
		.only_elevators = Dvar_FindMalleableVar("cm_onlyElevators")->current.integer,
		.alpha = Dvar_FindMalleableVar("cm_showCollisionPolyAlpha")->current.value
	};

	const bool brush_allowed = collisionType == showCollisionType::BRUSHES || collisionType == showCollisionType::BOTH;
	const bool terrain_allowed = collisionType == showCollisionType::TERRAIN || collisionType == showCollisionType::BOTH;

	std::unique_lock<std::mutex> lock(CClipMap::GetLock());
	CClipMap::ForEach([&](const GeometryPtr_t& geom) {
		if (geom->type() == cm_geomtype::brush && brush_allowed || geom->type() == cm_geomtype::terrain && terrain_allowed)
			geom->render(render_info);
	});

}
