
#include <utils/typedefs.hpp>

#include <unordered_set>
#include <string>

struct cm_geometry;
struct cbrush_t;
struct SimplePlaneIntersection;
struct adjacencyWinding_t;
struct cbrushside_t;

void CM_ShowCollisionFilter();

void CM_LoadAllBrushWindingsToClipMapWithFilter(const std::unordered_set<std::string>& filters);


void CM_LoadBrushWindingsToClipMap(const cbrush_t* brush);
std::unique_ptr<cm_geometry> CM_GetBrushPoints(const cbrush_t* brush, const fvec3& poly_col);

void CM_BuildAxialPlanes(float(*planes)[6][4], const cbrush_t* brush);
void CM_GetPlaneVec4Form(const cbrushside_t* sides, const float(*axialPlanes)[4], int index, float* expandedPlane);
int GetPlaneIntersections(const float** planes, int planeCount, SimplePlaneIntersection* OutPts);
int BrushToPlanes(const cbrush_t* brush, float(*outPlanes)[4]);
adjacencyWinding_t* BuildBrushAdjacencyWindingForSide(int ptCount, char* collMap, float* normals, int planeIndex, SimplePlaneIntersection* pts, adjacencyWinding_t* optionalOutWinding);
char* CM_MaterialForNormal(const cbrush_t* target, const fvec3& normals);
std::vector<std::string> CM_GetBrushMaterials(const cbrush_t* brush);

bool CM_BrushHasCollision(const cbrush_t* brush);
bool CM_BrushInView(const cbrush_t* brush, struct cplane_s* frustumPlanes, int numPlanes = 5);

namespace __brush
{
	void __asm_adjacency_winding();
}