#pragma once

#include "global_macros.hpp"
#include <vector>

template<typename T>
struct vec3;

using fvec3 = vec3<float>;
using ivec3 = vec3<int>;

struct Poly;
struct GfxViewParms;
struct GfxPointVertex;
enum class MaterialTechniqueType : int;
struct Material;
struct DebugGlobals;

using BYTE = unsigned char;

//Overwrite me if you want!
void RB_DrawDebug(void* viewParms);

int RB_BeginSurface(MaterialTechniqueType tech, Material* material);
void RB_EndTessSurface();
void RB_SetPolyVertice(const vec3_t pos, const BYTE* col, const int vert, const int index);
void RB_DrawPolyInteriors(const std::vector<fvec3>& points, const float* color, bool two_sided = false, bool depthTest = false);
char RB_DrawLines3D(int count, int width, const GfxPointVertex* verts, char depthTest);
int RB_AddDebugLine(GfxPointVertex* verts, char depthTest, const vec_t* start, const vec_t* end, const float* color, int vertCount);

void RB_DrawLine(const fvec3& start, const fvec3& end, bool depthtest, const float* color);

void RB_DrawPoly(const std::vector<fvec3>& points, bool depthtest, vec4_t color = vec4_t{ 1,1,1,1 });
void R_ConvertColorToBytes(const vec4_t in, uint8_t* out);