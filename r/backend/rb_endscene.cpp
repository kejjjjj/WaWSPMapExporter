#include <ranges>
#include <array>

#include "rb_endscene.hpp"
#include "cg/cg_local.hpp"
#include "cg/cg_offsets.hpp"
#include "utils/typedefs.hpp"
#include "utils/resolution.hpp"

#include <iostream>



void RB_DrawPolyInteriors(const std::vector<fvec3>& points, const float* c, bool two_sided, bool depthTest)
{
	auto n_points = points.size();

	//partly copied from iw3xo :)
	if (n_points < 3u)
		return;
	
	BYTE color[4];
	R_ConvertColorToBytes(c, color);


	Material material = *rgp->whiteMaterial;

	static unsigned int loadBits[2] = { material.stateBitsTable->loadBits[0], material.stateBitsTable->loadBits[1] };
	static GfxStateBits bits = { .loadBits = { material.stateBitsTable->loadBits[0], material.stateBitsTable->loadBits[1] } };

	memcpy(material.stateBitsTable, rgp->whiteMaterial->stateBitsTable, sizeof(GfxStateBits));
	material.stateBitsTable = &bits;
	constexpr MaterialTechniqueType tech = MaterialTechniqueType::TECHNIQUE_UNLIT;
	static uint32_t ogBits = material.stateBitsTable->loadBits[1];

	if (gfxCmdBufState->origMaterial != &material || gfxCmdBufState->origTechType != tech) {
		if (tess->indexCount)
			RB_EndTessSurface();

		if (depthTest)
			material.stateBitsTable->loadBits[1] = 44;
		else
			material.stateBitsTable->loadBits[1] = ogBits;

		if (two_sided)
			material.stateBitsTable->loadBits[0] = 422072677;
		else
			material.stateBitsTable->loadBits[0] = 422089061;

		//material.stateBitsTable->loadBits[1] = 44;

		RB_BeginSurface(tech, &material);

	}
	if (n_points + tess->vertexCount > 5450 || tess->indexCount + 2 * (n_points - 2) > 1048576)// RB_CheckTessOverflow
	{
		RB_EndTessSurface();
		RB_BeginSurface(gfxCmdBufState->origTechType, gfxCmdBufState->origMaterial);
	}
	size_t idx = 0u;

	for (; idx < n_points; ++idx) {
		vec3_t p = { points[idx].x, points[idx].y, points[idx].z };
		RB_SetPolyVertice(p, color, tess->vertexCount + idx, idx);
	}

	for (idx = 2u; idx < n_points; ++idx)
	{
		tess->indices[tess->indexCount + 0] = static_cast<std::uint16_t>(tess->vertexCount);
		tess->indices[tess->indexCount + 1] = static_cast<std::uint16_t>(idx + tess->vertexCount);
		tess->indices[tess->indexCount + 2] = static_cast<std::uint16_t>(idx + tess->vertexCount - 1);
		tess->indexCount += 3;
	}

	tess->vertexCount += n_points;

	RB_EndTessSurface();

}
int RB_AddDebugLine(GfxPointVertex* verts, char depthTest, const vec_t* start, const vec_t* end, const float* color, int vertCount)
{
	int _vc = vertCount;
	if (vertCount + 2 > 2725)
	{
		RB_DrawLines3D(vertCount / 2, 1, verts, depthTest);
		_vc = 0;
	}

	GfxPointVertex* vert = &verts[_vc];
	if (color) {
		R_ConvertColorToBytes(color, vert->color);
	}

	verts[_vc + 1].color[0] = vert->color[0];
	verts[_vc + 1].color[1] = vert->color[1];
	verts[_vc + 1].color[2] = vert->color[2];
	verts[_vc + 1].color[3] = vert->color[3];

	VectorCopy(start, vert->xyz);

	vert = &verts[_vc + 1];
	VectorCopy(end, vert->xyz);

	return _vc + 2;

}

void R_ConvertColorToBytes(const vec4_t in, uint8_t* out)
{
	((char(__fastcall*)(const float* in, uint8_t * out))0x49E900)(in, out);
}
char RB_DrawLines3D(int count, int width, const GfxPointVertex* verts, char depthTest)
{
	((char(__cdecl*)(int, int, const GfxPointVertex*, char))0x6F9920)(count, width, verts, depthTest);
	return 1;

}
int RB_BeginSurface(MaterialTechniqueType tech, Material* material)
{
	int rval = 0;
	const static auto fnc = 0x710F80;
	__asm
	{
		mov edi, tech;
		mov esi, material;
		call fnc;
		mov rval, eax;
	}
	return rval;
}
void RB_EndTessSurface()
{
	((void(*)())0x711050)();

}
void RB_SetPolyVertice(const vec3_t pos, const BYTE* col, const int vert, const int index)
{
	VectorCopy(pos, tess->verts[vert].xyzw);
	tess->verts[vert].color.array[0] = col[0];
	tess->verts[vert].color.array[1] = col[1];
	tess->verts[vert].color.array[2] = col[2];
	tess->verts[vert].color.array[3] = col[3];

	switch (index)
	{
	case 0:
		tess->verts[vert].texCoord[0] = 0.0f;
		tess->verts[vert].texCoord[1] = 0.0f;
		break;

	case 1:
		tess->verts[vert].texCoord[0] = 0.0f;
		tess->verts[vert].texCoord[1] = 1.0f;
		break;
	case 2:
		tess->verts[vert].texCoord[0] = 1.0f;
		tess->verts[vert].texCoord[1] = 1.0f;
		break;
	case 3:
		tess->verts[vert].texCoord[0] = 1.0f;
		tess->verts[vert].texCoord[1] = 0.0f;
		break;

	default:
		tess->verts[vert].texCoord[0] = 0.0f;
		tess->verts[vert].texCoord[1] = 0.0f;
		break;
	}

	tess->verts[vert].normal.packed = 1073643391;
}

GfxPointVertex lineVerts[2];
void RB_DrawLine(const fvec3& start, const fvec3& end, bool depthtest, const float* color)
{

	const auto verts = RB_AddDebugLine(lineVerts, depthtest, start.As<vec_t*>(), end.As<vec_t*>(), color, 2);
	RB_DrawLines3D(verts / 2, 1, lineVerts, depthtest);
}

GfxPointVertex poly_verts[2725];
void RB_DrawPoly(const std::vector<fvec3>& points, bool depthtest, vec4_t color)
{

	std::int32_t vert_count = 0;
	size_t vert_index_prev = 0;

	for (auto i : std::views::iota(1u, points.size())) {
		vert_count = RB_AddDebugLine(poly_verts, depthtest, (float*)&points[i], (float*)&points[vert_index_prev], color, vert_count);
		vert_index_prev = i;
	}

	RB_DrawLines3D(vert_count / 2, 1, poly_verts, depthtest);
}