#pragma once

struct cmd_function_s
{
	cmd_function_s* next;
	const char* name;
	const char* autoCompleteDir;
	const char* autoCompleteExt;
	void(__cdecl* function)();
};


struct XModelLodInfo
{
	float dist;
	unsigned __int16 numsurfs;
	unsigned __int16 surfIndex;
	int partBits[4];
	char lod;
	char smcIndexPlusOne;
	char smcAllocBits;
	char unused;
};
struct XModelHighMipBounds
{
	float mins[3];
	float maxs[3];
};

struct XModelStreamInfo
{
	XModelHighMipBounds* highMipBounds;
};
struct XModel
{
	const char* name;
	char numBones;
	char numRootBones;
	unsigned char numsurfs;
	char lodRampType;
	unsigned __int16* boneNames;
	char* parentList;
	__int16* quats;
	float* trans;
	char* partClassification;
	struct DObjAnimMat* baseMat;
	struct XSurface* surfs;
	struct Material** materialHandles;
	XModelLodInfo lodInfo[4];
	struct XModelCollSurf_s* collSurfs;
	int numCollSurfs;
	int contents;
	struct XBoneInfo* boneInfo;
	float radius;
	float mins[3];
	float maxs[3];
	__int16 numLods;
	__int16 collLod;
	XModelStreamInfo streamInfo;
	int memUsage;
	char flags;
	bool bad;
	struct PhysPreset* physPreset;
	struct PhysGeomList* physGeoms;
};

struct GfxPackedPlacement
{
	float origin[3];
	float axis[3][3];
	float scale;
};

struct __declspec(align(4)) GfxStaticModelDrawInst
{
	float cullDist;
	GfxPackedPlacement placement;
	XModel* model;
	unsigned __int16 smodelCacheIndex[4];
	char reflectionProbeIndex;
	char primaryLightIndex;
	unsigned __int16 lightingHandle;
	char flags;
	char pad[18];
};
struct GfxPointVertex
{
	float xyz[3];
	unsigned char color[4];
};

union PackedTexCoords
{
	unsigned int packed;
};
struct SimplePlaneIntersection
{
	float xyz[3];
	int planeIndex[3];
};
struct adjacencyWinding_t
{
	int numsides;
	int sides[12];
};
// fucking namespaces
union PackedUnitVec
{
	unsigned int packed;
	char array[4];
};

// fucking namespaces
union GfxColor
{
	unsigned int packed;
	unsigned char array[4];
};
struct cplane_s
{
	float normal[3];
	float dist;
	char type;  // for fast side tests: 0,1,2 = axial, 3 = nonaxial
	char signbits;  // signx + (signy<<1) + (signz<<2), used as lookup during collision
	char pad[2];
};

#pragma pack(push, 2)
struct cbrushside_t
{
	cplane_s* plane;
	unsigned int materialNum;
	__int16 firstAdjacentSideOffset;
	char edgeCount;
};
#pragma pack(pop)

#pragma pack(push, 16)
struct cbrush_t
{
	float mins[3];
	int contents;
	float maxs[3];
	unsigned int numsides;
	cbrushside_t* sides;
	__int16 axialMaterialNum[2][3];
	char* baseAdjacentSide;
	__int16 firstAdjacentSideOffsets[2][3];
	char edgeCount[2][3];
	__int16 colorCounter;
	__int16 cmBrushIndex;
	__int16 cmSubmodelIndex;
	bool isSubmodel;
	bool pad;
};
#pragma pack(pop)

struct dmaterial_t
{
	char material[64];
	int surfaceFlags;
	int contentFlags;
};
struct CollisionBorder
{
	float distEq[3];
	float zBase;
	float zSlope;
	float start;
	float length;
};

struct CollisionPartition
{
	char triCount;
	char borderCount;
	int firstTri;
	int hmm;
	int hmm2;
	CollisionBorder* borders;
};


union CollisionAabbTreeIndex
{
	int firstChildIndex;
	int partitionIndex;
};

struct CollisionAabbTree
{
	float origin[3];
	unsigned __int16 materialIndex;
	unsigned __int16 childCount;
	float halfSize[3];
	CollisionAabbTreeIndex u;
};

#pragma pack(push, 4)
struct cLeaf_t
{
	unsigned __int16 firstCollAabbIndex;
	unsigned __int16 collAabbCount;
	int brushContents;
	int terrainContents;
	float mins[3];
	float maxs[3];
	int leafBrushNode;
	__int16 cluster;
};
#pragma pack(pop)
struct clipMap_t
{
	char* name;
	int isInUse;
	int planeCount;
	void* cplane_s___planes;
	unsigned int numStaticModels;
	struct cStaticModel_s* staticModelList;
	unsigned int numMaterials;
	dmaterial_t* materials;
	unsigned int numBrushSides;
	void* cbrushside_t___brushsides;
	unsigned int numBrushEdges;
	unsigned __int8* brushEdges;
	unsigned int numNodes;
	void* cNode_t___nodes;
	unsigned int numLeafs;
	cLeaf_t* leafs;
	unsigned int leafbrushNodesCount;
	void* cLeafBrushNode_s___leafbrushNodes;
	unsigned int numLeafBrushes;
	unsigned __int16* leafbrushes;
	unsigned int numLeafSurfaces;
	unsigned int* leafsurfaces;
	unsigned int vertCount;
	float(*verts)[3];
	unsigned int numBrushVerts;
	float(*brushVerts)[3];
	unsigned int nuinds;
	unsigned __int16* uinds;
	int triCount;
	unsigned __int16* triIndices;
	unsigned __int8* triEdgeIsWalkable;
	int borderCount;
	void* CollisionBorder___borders;
	int partitionCount;
	CollisionPartition* partitions;
	int aabbTreeCount;
	CollisionAabbTree* aabbTrees;
	unsigned int numSubModels;
	void* cmodel_t___cmodels;
	unsigned __int16 numBrushes;
	cbrush_t* brushes;
	int numClusters;
	int clusterBytes;
	unsigned __int8* visibility;
	int vised;
	struct MapEnts* mapEnts;
	void* cbrush_t___box_brush;
};
enum class MaterialTechniqueType : int
{
	TECHNIQUE_DEPTH_PREPASS = 0x0,
	TECHNIQUE_BUILD_FLOAT_Z = 0x1,
	TECHNIQUE_BUILD_SHADOWMAP_DEPTH = 0x2,
	TECHNIQUE_BUILD_SHADOWMAP_COLOR = 0x3,
	TECHNIQUE_UNLIT = 0x4,
	TECHNIQUE_EMISSIVE = 0x5,
	TECHNIQUE_EMISSIVE_SHADOW = 0x6,
	TECHNIQUE_EMISSIVE_REFLECTED = 0x7,
	TECHNIQUE_LIT = 0x8,
	TECHNIQUE_LIT_FADE = 0x9,
	TECHNIQUE_LIT_SUN = 0xA,
	TECHNIQUE_LIT_SUN_FADE = 0xB,
	TECHNIQUE_LIT_SUN_SHADOW = 0xC,
	TECHNIQUE_LIT_SUN_SHADOW_FADE = 0xD,
	TECHNIQUE_LIT_SPOT = 0xE,
	TECHNIQUE_LIT_SPOT_FADE = 0xF,
	TECHNIQUE_LIT_SPOT_SHADOW = 0x10,
	TECHNIQUE_LIT_SPOT_SHADOW_FADE = 0x11,
	TECHNIQUE_LIT_OMNI = 0x12,
	TECHNIQUE_LIT_OMNI_FADE = 0x13,
	TECHNIQUE_LIT_OMNI_SHADOW = 0x14,
	TECHNIQUE_LIT_OMNI_SHADOW_FADE = 0x15,
	TECHNIQUE_LIT_CHARRED = 0x16,
	TECHNIQUE_LIT_FADE_CHARRED = 0x17,
	TECHNIQUE_LIT_SUN_CHARRED = 0x18,
	TECHNIQUE_LIT_SUN_FADE_CHARRED = 0x19,
	TECHNIQUE_LIT_SUN_SHADOW_CHARRED = 0x1A,
	TECHNIQUE_LIT_SUN_SHADOW_FADE_CHARRED = 0x1B,
	TECHNIQUE_LIT_SPOT_CHARRED = 0x1C,
	TECHNIQUE_LIT_SPOT_FADE_CHARRED = 0x1D,
	TECHNIQUE_LIT_SPOT_SHADOW_CHARRED = 0x1E,
	TECHNIQUE_LIT_SPOT_SHADOW_FADE_CHARRED = 0x1F,
	TECHNIQUE_LIT_OMNI_CHARRED = 0x20,
	TECHNIQUE_LIT_OMNI_FADE_CHARRED = 0x21,
	TECHNIQUE_LIT_OMNI_SHADOW_CHARRED = 0x22,
	TECHNIQUE_LIT_OMNI_SHADOW_FADE_CHARRED = 0x23,
	TECHNIQUE_LIT_INSTANCED = 0x24,
	TECHNIQUE_LIT_INSTANCED_SUN = 0x25,
	TECHNIQUE_LIT_INSTANCED_SUN_SHADOW = 0x26,
	TECHNIQUE_LIT_INSTANCED_SPOT = 0x27,
	TECHNIQUE_LIT_INSTANCED_SPOT_SHADOW = 0x28,
	TECHNIQUE_LIT_INSTANCED_OMNI = 0x29,
	TECHNIQUE_LIT_INSTANCED_OMNI_SHADOW = 0x2A,
	TECHNIQUE_LIGHT_SPOT = 0x2B,
	TECHNIQUE_LIGHT_OMNI = 0x2C,
	TECHNIQUE_LIGHT_SPOT_SHADOW = 0x2D,
	TECHNIQUE_LIGHT_SPOT_CHARRED = 0x2E,
	TECHNIQUE_LIGHT_OMNI_CHARRED = 0x2F,
	TECHNIQUE_LIGHT_SPOT_SHADOW_CHARRED = 0x30,
	TECHNIQUE_FAKELIGHT_NORMAL = 0x31,
	TECHNIQUE_FAKELIGHT_VIEW = 0x32,
	TECHNIQUE_SUNLIGHT_PREVIEW = 0x33,
	TECHNIQUE_CASE_TEXTURE = 0x34,
	TECHNIQUE_WIREFRAME_SOLID = 0x35,
	TECHNIQUE_WIREFRAME_SHADED = 0x36,
	TECHNIQUE_SHADOWCOOKIE_CASTER = 0x37,
	TECHNIQUE_SHADOWCOOKIE_RECEIVER = 0x38,
	TECHNIQUE_DEBUG_BUMPMAP = 0x39,
	TECHNIQUE_DEBUG_BUMPMAP_INSTANCED = 0x3A,
	TECHNIQUE_COUNT = 0x3B,
};
struct GfxImageLoadDef
{
	char levelCount; //OFS: 0x0 SIZE: 0x1
	char flags; //OFS: 0x1 SIZE: 0x1
	__int16 dimensions[3]; //OFS: 0x2 SIZE: 0x6
	int format; //OFS: 0x8 SIZE: 0x4
	int resourceSize; //OFS: 0xC SIZE: 0x4
	char data[1]; //OFS: 0x10 SIZE: 0x1
};

union GfxTexture
{
	struct IDirect3DBaseTexture9* basemap; //OFS: 0x0 SIZE: 0x4
	struct IDirect3DTexture9* map; //OFS: 0x1 SIZE: 0x4
	struct IDirect3DVolumeTexture9* volmap; //OFS: 0x2 SIZE: 0x4
	struct IDirect3DCubeTexture9* cubemap; //OFS: 0x3 SIZE: 0x4
	GfxImageLoadDef* loadDef; //OFS: 0x4 SIZE: 0x4
};

struct __declspec(align(1)) Picmip
{
	char platform[2]; //OFS: 0x0 SIZE: 0x2
};
struct CardMemory
{
	int platform[2]; //OFS: 0x0 SIZE: 0x8
};
enum MapType : __int32
{
	MAPTYPE_NONE = 0x0,
	MAPTYPE_INVALID1 = 0x1,
	MAPTYPE_INVALID2 = 0x2,
	MAPTYPE_2D = 0x3,
	MAPTYPE_3D = 0x4,
	MAPTYPE_CUBE = 0x5,
	MAPTYPE_COUNT = 0x6,
};
struct GfxImage
{
	MapType mapType; //OFS: 0x0 SIZE: 0x4
	GfxTexture texture; //OFS: 0x4 SIZE: 0x4
	Picmip picmip; //OFS: 0x8 SIZE: 0x2
	bool noPicmip; //OFS: 0xA SIZE: 0x1
	char semantic; //OFS: 0xB SIZE: 0x1
	char track; //OFS: 0xC SIZE: 0x1
	CardMemory cardMemory; //OFS: 0x10 SIZE: 0x8
	unsigned __int16 width; //OFS: 0x18 SIZE: 0x2
	unsigned __int16 height; //OFS: 0x1A SIZE: 0x2
	unsigned __int16 depth; //OFS: 0x1C SIZE: 0x2
	char category; //OFS: 0x1E SIZE: 0x1
	bool delayLoadPixels; //OFS: 0x1F SIZE: 0x1
	const char* name; //OFS: 0x20 SIZE: 0x4
};
struct __declspec(align(1)) MaterialStreamRouting
{
	char source; //OFS: 0x0 SIZE: 0x1
	char dest; //OFS: 0x1 SIZE: 0x1
};

struct MaterialVertexStreamRouting
{
	MaterialStreamRouting data[16]; //OFS: 0x0 SIZE: 0x20
	struct IDirect3DVertexDeclaration9* decl[17]; //OFS: 0x20 SIZE: 0x44
};

struct MaterialVertexDeclaration
{
	char streamCount; //OFS: 0x0 SIZE: 0x1
	bool hasOptionalSource; //OFS: 0x1 SIZE: 0x1
	bool isLoaded; //OFS: 0x2 SIZE: 0x1
	MaterialVertexStreamRouting routing; //OFS: 0x4 SIZE: 0x64
};

struct GfxVertexShaderLoadDef
{
	unsigned int* program; //OFS: 0x0 SIZE: 0x4
	unsigned __int16 programSize; //OFS: 0x4 SIZE: 0x2
	unsigned __int16 loadForRenderer; //OFS: 0x6 SIZE: 0x2
};

struct MaterialVertexShaderProgram
{
	struct IDirect3DVertexShader9* vs; //OFS: 0x0 SIZE: 0x4
	GfxVertexShaderLoadDef loadDef; //OFS: 0x4 SIZE: 0x8
};

struct MaterialVertexShader
{
	const char* name; //OFS: 0x0 SIZE: 0x4
	MaterialVertexShaderProgram prog; //OFS: 0x4 SIZE: 0xC
};

struct GfxPixelShaderLoadDef
{
	unsigned int* program; //OFS: 0x0 SIZE: 0x4
	unsigned __int16 programSize; //OFS: 0x4 SIZE: 0x2
	unsigned __int16 loadForRenderer; //OFS: 0x6 SIZE: 0x2
};
struct MaterialPixelShaderProgram
{
	struct IDirect3DPixelShader9* ps; //OFS: 0x0 SIZE: 0x4
	GfxPixelShaderLoadDef loadDef; //OFS: 0x4 SIZE: 0x8
};

struct MaterialPixelShader
{
	const char* name; //OFS: 0x0 SIZE: 0x4
	MaterialPixelShaderProgram prog; //OFS: 0x4 SIZE: 0xC
};

struct __declspec(align(2)) MaterialArgumentCodeConst
{
	unsigned __int16 index; //OFS: 0x0 SIZE: 0x2
	char firstRow; //OFS: 0x2 SIZE: 0x1
	char rowCount; //OFS: 0x3 SIZE: 0x1
};

union MaterialArgumentDef
{
	const float* literalConst; //OFS: 0x0 SIZE: 0x4
	MaterialArgumentCodeConst codeConst; //OFS: 0x1 SIZE: 0x4
	unsigned int codeSampler; //OFS: 0x2 SIZE: 0x4
	unsigned int nameHash; //OFS: 0x3 SIZE: 0x4
};

struct MaterialShaderArgument
{
	unsigned __int16 type; //OFS: 0x0 SIZE: 0x2
	unsigned __int16 dest; //OFS: 0x2 SIZE: 0x2
	MaterialArgumentDef u; //OFS: 0x4 SIZE: 0x4
};

struct MaterialPass
{
	MaterialVertexDeclaration* vertexDecl; //OFS: 0x0 SIZE: 0x4
	MaterialVertexShader* vertexShader; //OFS: 0x4 SIZE: 0x4
	MaterialPixelShader* pixelShader; //OFS: 0x8 SIZE: 0x4
	char perPrimArgCount; //OFS: 0xC SIZE: 0x1
	char perObjArgCount; //OFS: 0xD SIZE: 0x1
	char stableArgCount; //OFS: 0xE SIZE: 0x1
	char customSamplerFlags; //OFS: 0xF SIZE: 0x1
	MaterialShaderArgument* args; //OFS: 0x10 SIZE: 0x4
};
struct MaterialTechnique
{
	const char* name; //OFS: 0x0 SIZE: 0x4
	unsigned __int16 flags; //OFS: 0x4 SIZE: 0x2
	unsigned __int16 passCount; //OFS: 0x6 SIZE: 0x2
	MaterialPass passArray[1]; //OFS: 0x8 SIZE: 0x14
};

struct MaterialTechniqueSet
{
	const char* name; //OFS: 0x0 SIZE: 0x4
	char worldVertFormat; //OFS: 0x4 SIZE: 0x1
	bool hasBeenUploaded; //OFS: 0x5 SIZE: 0x1
	char unused[1]; //OFS: 0x6 SIZE: 0x1
	MaterialTechniqueSet* remappedTechniqueSet; //OFS: 0x8 SIZE: 0x4
	MaterialTechnique* techniques[59]; //OFS: 0xC SIZE: 0xEC
};
union MaterialTextureDefInfo
{
	GfxImage* image; //OFS: 0x0 SIZE: 0x4
	struct water_t* water; //OFS: 0x1 SIZE: 0x4
};

struct MaterialTextureDef
{
	unsigned int nameHash; //OFS: 0x0 SIZE: 0x4
	char nameStart; //OFS: 0x4 SIZE: 0x1
	char nameEnd; //OFS: 0x5 SIZE: 0x1
	char samplerState; //OFS: 0x6 SIZE: 0x1
	char semantic; //OFS: 0x7 SIZE: 0x1
	char isMatureContent; //OFS: 0x8 SIZE: 0x1
	MaterialTextureDefInfo u; //OFS: 0xC SIZE: 0x4
};

struct MaterialConstantDef
{
	unsigned int nameHash; //OFS: 0x0 SIZE: 0x4
	char name[12]; //OFS: 0x4 SIZE: 0xC
	float literal[4]; //OFS: 0x10 SIZE: 0x10
};

struct GfxStateBits
{
	unsigned int loadBits[2]; //OFS: 0x0 SIZE: 0x8
};
struct GfxDrawSurfFields
{
	unsigned __int64 objectId : 16;
	unsigned __int64 reflectionProbeIndex : 8;
	unsigned __int64 customIndex : 5;
	unsigned __int64 materialSortedIndex : 11;
	unsigned __int64 prepass : 2;
	unsigned __int64 primaryLightIndex : 8;
	unsigned __int64 surfType : 4;
	unsigned __int64 primarySortKey : 6;
	unsigned __int64 unused : 4;
};

union GfxDrawSurf
{
	GfxDrawSurfFields fields;
	unsigned __int64 packed;
};

struct __declspec(align(8)) MaterialInfo
{
	const char* name; //OFS: 0x0 SIZE: 0x4
	char gameFlags; //OFS: 0x4 SIZE: 0x1
	char sortKey; //OFS: 0x5 SIZE: 0x1
	char textureAtlasRowCount; //OFS: 0x6 SIZE: 0x1
	char textureAtlasColumnCount; //OFS: 0x7 SIZE: 0x1
	GfxDrawSurf drawSurf; //OFS: 0x8 SIZE: 0x8
	unsigned int surfaceTypeBits; //OFS: 0x10 SIZE: 0x4
	unsigned __int16 hashIndex; //OFS: 0x14 SIZE: 0x2
};
struct Material
{
	MaterialInfo info; //OFS: 0x0 SIZE: 0x18
	char stateBitsEntry[67]; //OFS: 0x18 SIZE: 0x43
	char textureCount; //OFS: 0x5B SIZE: 0x1
	char constantCount; //OFS: 0x5C SIZE: 0x1
	char stateBitsCount; //OFS: 0x5D SIZE: 0x1
	char stateFlags; //OFS: 0x5E SIZE: 0x1
	char cameraRegion; //OFS: 0x5F SIZE: 0x1
	MaterialTechniqueSet* techniqueSet; //OFS: 0x60 SIZE: 0x4
	MaterialTextureDef* textureTable; //OFS: 0x64 SIZE: 0x4
	MaterialConstantDef* constantTable; //OFS: 0x68 SIZE: 0x4
	GfxStateBits* stateBitsTable; //OFS: 0x6C SIZE: 0x4
};
struct GfxLightImage
{
	GfxImage* image; //OFS: 0x0 SIZE: 0x4
	unsigned __int8 samplerState; //OFS: 0x4 SIZE: 0x1
};

struct GfxLightDef
{
	char* name; //OFS: 0x0 SIZE: 0x4
	GfxLightImage attenuation; //OFS: 0x4 SIZE: 0x8
	int lmapLookupStart; //OFS: 0xC SIZE: 0x4
};
struct SavedScreenParams
{
	float s0; //OFS: 0x0 SIZE: 0x4
	float t0; //OFS: 0x4 SIZE: 0x4
	float _ds; //OFS: 0x8 SIZE: 0x4
	float dt; //OFS: 0xC SIZE: 0x4
	int isSet; //OFS: 0x10 SIZE: 0x4
};
struct GfxLightRegionAxis
{
	float dir[3]; //OFS: 0x0 SIZE: 0xC
	float midPoint; //OFS: 0xC SIZE: 0x4
	float halfSize; //OFS: 0x10 SIZE: 0x4
};

struct GfxLightRegionHull
{
	float kdopMidPoint[9]; //OFS: 0x0 SIZE: 0x24
	float kdopHalfSize[9]; //OFS: 0x24 SIZE: 0x24
	unsigned int axisCount; //OFS: 0x48 SIZE: 0x4
	GfxLightRegionAxis* axis; //OFS: 0x4C SIZE: 0x4
};

struct GfxLightRegion
{
	unsigned int hullCount; //OFS: 0x0 SIZE: 0x4
	GfxLightRegionHull* hulls; //OFS: 0x4 SIZE: 0x4
};

struct GfxWorldDpvsDynamic
{
	unsigned int dynEntClientWordCount[2]; //OFS: 0x0 SIZE: 0x8
	unsigned int dynEntClientCount[2]; //OFS: 0x8 SIZE: 0x8
	unsigned int* dynEntCellBits[2]; //OFS: 0x10 SIZE: 0x8
	unsigned __int8* dynEntVisData[2][3]; //OFS: 0x18 SIZE: 0x18
};

struct GfxWorldLodChain
{
	float origin[3]; //OFS: 0x0 SIZE: 0xC
	float lastDist; //OFS: 0xC SIZE: 0x4
	unsigned int firstLodInfo; //OFS: 0x10 SIZE: 0x4
	unsigned __int16 lodInfoCount; //OFS: 0x14 SIZE: 0x2
};

struct GfxWorldLodInfo
{
	float dist; //OFS: 0x0 SIZE: 0x4
	unsigned int firstSurf; //OFS: 0x4 SIZE: 0x4
	unsigned __int16 surfCount; //OFS: 0x8 SIZE: 0x2
};

struct GfxWaterBuffer
{
	unsigned int bufferSize; //OFS: 0x0 SIZE: 0x4
	float(*buffer)[4]; //OFS: 0x4 SIZE: 0x4
};
struct GfxVertexBuffer
{
	struct IDirect3DVertexBuffer9* data; //OFS: 0x0 SIZE: 0x4
};
struct GfxWorldVertex
{
	float xyz[3]; //OFS: 0x0 SIZE: 0xC
	float binormalSign; //OFS: 0xC SIZE: 0x4
	GfxColor color; //OFS: 0x10 SIZE: 0x4
	float texCoord[2]; //OFS: 0x14 SIZE: 0x8
	float lmapCoord[2]; //OFS: 0x1C SIZE: 0x8
	PackedUnitVec normal; //OFS: 0x24 SIZE: 0x4
	PackedUnitVec tangent; //OFS: 0x28 SIZE: 0x4
};
struct GfxWorldVertexData
{
	GfxWorldVertex* vertices; //OFS: 0x0 SIZE: 0x4
	GfxVertexBuffer worldVb; //OFS: 0x4 SIZE: 0x4
};
struct GfxWorldVertexLayerData
{
	unsigned __int8* data; //OFS: 0x0 SIZE: 0x4
	GfxVertexBuffer layerVb; //OFS: 0x4 SIZE: 0x4
};
struct SunLightParseParams
{
	char name[64]; //OFS: 0x0 SIZE: 0x40
	float ambientScale; //OFS: 0x40 SIZE: 0x4
	float ambientColor[3]; //OFS: 0x44 SIZE: 0xC
	float diffuseFraction; //OFS: 0x50 SIZE: 0x4
	float sunLight; //OFS: 0x54 SIZE: 0x4
	float sunColor[3]; //OFS: 0x58 SIZE: 0xC
	float diffuseColor[3]; //OFS: 0x64 SIZE: 0xC
	bool diffuseColorHasBeenSet; //OFS: 0x70 SIZE: 0x1
	float angles[3]; //OFS: 0x74 SIZE: 0xC
	float treeScatterIntensity; //OFS: 0x80 SIZE: 0x4
	float treeScatterAmount; //OFS: 0x84 SIZE: 0x4
};
struct GfxWorldDpvsPlanes
{
	int cellCount; //OFS: 0x0 SIZE: 0x4
	cplane_s* planes; //OFS: 0x4 SIZE: 0x4
	unsigned __int16* nodes; //OFS: 0x8 SIZE: 0x4
	unsigned int* sceneEntCellBits; //OFS: 0xC SIZE: 0x4
};
struct __declspec(align(2)) GfxLightGridEntry
{
	unsigned __int16 colorsIndex; //OFS: 0x0 SIZE: 0x2
	unsigned __int8 primaryLightIndex; //OFS: 0x2 SIZE: 0x1
	unsigned __int8 needsTrace; //OFS: 0x3 SIZE: 0x1
};

struct __declspec(align(1)) GfxLightGridColors
{
	unsigned __int8 rgb[56][3]; //OFS: 0x0 SIZE: 0xA8
};

struct GfxLightGrid
{
	bool hasLightRegions; //OFS: 0x0 SIZE: 0x1
	unsigned int sunPrimaryLightIndex; //OFS: 0x4 SIZE: 0x4
	unsigned __int16 mins[3]; //OFS: 0x8 SIZE: 0x6
	unsigned __int16 maxs[3]; //OFS: 0xE SIZE: 0x6
	unsigned int rowAxis; //OFS: 0x14 SIZE: 0x4
	unsigned int colAxis; //OFS: 0x18 SIZE: 0x4
	unsigned __int16* rowDataStart; //OFS: 0x1C SIZE: 0x4
	unsigned int rawRowDataSize; //OFS: 0x20 SIZE: 0x4
	unsigned __int8* rawRowData; //OFS: 0x24 SIZE: 0x4
	unsigned int entryCount; //OFS: 0x28 SIZE: 0x4
	GfxLightGridEntry* entries; //OFS: 0x2C SIZE: 0x4
	unsigned int colorCount; //OFS: 0x30 SIZE: 0x4
	GfxLightGridColors* colors; //OFS: 0x34 SIZE: 0x4
};
struct sunflare_t
{
	bool hasValidData; //OFS: 0x0 SIZE: 0x1
	Material* spriteMaterial; //OFS: 0x4 SIZE: 0x4
	Material* flareMaterial; //OFS: 0x8 SIZE: 0x4
	float spriteSize; //OFS: 0xC SIZE: 0x4
	float flareMinSize; //OFS: 0x10 SIZE: 0x4
	float flareMinDot; //OFS: 0x14 SIZE: 0x4
	float flareMaxSize; //OFS: 0x18 SIZE: 0x4
	float flareMaxDot; //OFS: 0x1C SIZE: 0x4
	float flareMaxAlpha; //OFS: 0x20 SIZE: 0x4
	int flareFadeInTime; //OFS: 0x24 SIZE: 0x4
	int flareFadeOutTime; //OFS: 0x28 SIZE: 0x4
	float blindMinDot; //OFS: 0x2C SIZE: 0x4
	float blindMaxDot; //OFS: 0x30 SIZE: 0x4
	float blindMaxDarken; //OFS: 0x34 SIZE: 0x4
	int blindFadeInTime; //OFS: 0x38 SIZE: 0x4
	int blindFadeOutTime; //OFS: 0x3C SIZE: 0x4
	float glareMinDot; //OFS: 0x40 SIZE: 0x4
	float glareMaxDot; //OFS: 0x44 SIZE: 0x4
	float glareMaxLighten; //OFS: 0x48 SIZE: 0x4
	int glareFadeInTime; //OFS: 0x4C SIZE: 0x4
	int glareFadeOutTime; //OFS: 0x50 SIZE: 0x4
	float sunFxPosition[3]; //OFS: 0x54 SIZE: 0xC
};
struct GfxWorldDpvsStatic
{
	unsigned int smodelCount; //OFS: 0x0 SIZE: 0x4
	unsigned int staticSurfaceCount; //OFS: 0x4 SIZE: 0x4
	unsigned int litSurfsBegin; //OFS: 0x8 SIZE: 0x4
	unsigned int litSurfsEnd; //OFS: 0xC SIZE: 0x4
	unsigned int decalSurfsBegin; //OFS: 0x10 SIZE: 0x4
	unsigned int decalSurfsEnd; //OFS: 0x14 SIZE: 0x4
	unsigned int emissiveSurfsBegin; //OFS: 0x18 SIZE: 0x4
	unsigned int emissiveSurfsEnd; //OFS: 0x1C SIZE: 0x4
	unsigned int smodelVisDataCount; //OFS: 0x20 SIZE: 0x4
	unsigned int surfaceVisDataCount; //OFS: 0x24 SIZE: 0x4
	unsigned __int8* smodelVisData[3]; //OFS: 0x28 SIZE: 0xC
	unsigned __int8* surfaceVisData[3]; //OFS: 0x34 SIZE: 0xC
	unsigned int* lodData; //OFS: 0x40 SIZE: 0x4
	unsigned __int16* sortedSurfIndex; //OFS: 0x44 SIZE: 0x4
	struct GfxStaticModelInst* smodelInsts; //OFS: 0x48 SIZE: 0x4
	struct GfxSurface* surfaces; //OFS: 0x4C SIZE: 0x4
	struct GfxCullGroup* cullGroups; //OFS: 0x50 SIZE: 0x4
	GfxStaticModelDrawInst* smodelDrawInsts; //OFS: 0x54 SIZE: 0x4
	GfxDrawSurf* surfaceMaterials; //OFS: 0x58 SIZE: 0x4
	unsigned int* surfaceCastsSunShadow; //OFS: 0x5C SIZE: 0x4
	int usageCount; //OFS: 0x60 SIZE: 0x4
};
struct GfxWorld
{
	const char* name; //OFS: 0x0 SIZE: 0x4
	const char* baseName; //OFS: 0x4 SIZE: 0x4
	int planeCount; //OFS: 0x8 SIZE: 0x4
	int nodeCount; //OFS: 0xC SIZE: 0x4
	int indexCount; //OFS: 0x10 SIZE: 0x4
	unsigned __int16* indices; //OFS: 0x14 SIZE: 0x4
	int surfaceCount; //OFS: 0x18 SIZE: 0x4
	int streamInfo; //OFS: 0x1C SIZE: 0x4
	int skySurfCount; //OFS: 0x20 SIZE: 0x4
	int* skyStartSurfs; //OFS: 0x24 SIZE: 0x4
	GfxImage* skyImage; //OFS: 0x28 SIZE: 0x4
	unsigned __int8 skySamplerState; //OFS: 0x2C SIZE: 0x1
	char* skyBoxModel; //OFS: 0x30 SIZE: 0x4
	unsigned int vertexCount; //OFS: 0x34 SIZE: 0x4
	GfxWorldVertexData vd; //OFS: 0x38 SIZE: 0x8
	unsigned int vertexLayerDataSize; //OFS: 0x40 SIZE: 0x4
	GfxWorldVertexLayerData vld; //OFS: 0x44 SIZE: 0x8
	unsigned int vertexStream2DataSize; //OFS: 0x4C SIZE: 0x4
	SunLightParseParams sunParse; //OFS: 0x50 SIZE: 0x88
	struct GfxLight* sunLight; //OFS: 0xD8 SIZE: 0x4
	float sunColorFromBsp[3]; //OFS: 0xDC SIZE: 0xC
	unsigned int sunPrimaryLightIndex; //OFS: 0xE8 SIZE: 0x4
	unsigned int primaryLightCount; //OFS: 0xEC SIZE: 0x4
	int cullGroupCount; //OFS: 0xF0 SIZE: 0x4
	unsigned int reflectionProbeCount; //OFS: 0xF4 SIZE: 0x4
	struct GfxReflectionProbe* reflectionProbes; //OFS: 0xF8 SIZE: 0x4
	GfxTexture* reflectionProbeTextures; //OFS: 0xFC SIZE: 0x4
	unsigned int coronaCount; //OFS: 0x100 SIZE: 0x4
	struct GfxLightCorona* coronas; //OFS: 0x104 SIZE: 0x4
	GfxWorldDpvsPlanes dpvsPlanes; //OFS: 0x108 SIZE: 0x10
	int cellBitsCount; //OFS: 0x118 SIZE: 0x4
	struct GfxCell* cells; //OFS: 0x11C SIZE: 0x4
	int lightmapCount; //OFS: 0x120 SIZE: 0x4
	GfxImage** lightmaps; //OFS: 0x124 SIZE: 0x4
	GfxLightGrid lightGrid; //OFS: 0x128 SIZE: 0x38
	struct gpuTexture* lightmapPrimaryTextures; //OFS: 0x160 SIZE: 0x4
	struct gpuTexture* lightmapSecondaryTextures; //OFS: 0x164 SIZE: 0x4
	int modelCount; //OFS: 0x168 SIZE: 0x4
	struct GfxBrushModel* models; //OFS: 0x16C SIZE: 0x4
	float mins[3]; //OFS: 0x170 SIZE: 0xC
	float maxs[3]; //OFS: 0x17C SIZE: 0xC
	unsigned int checksum; //OFS: 0x188 SIZE: 0x4
	int materialMemoryCount; //OFS: 0x18C SIZE: 0x4
	struct MaterialMemory* materialMemory; //OFS: 0x190 SIZE: 0x4
	sunflare_t sun; //OFS: 0x194 SIZE: 0x60
	float outdoorLookupMatrix[4][4]; //OFS: 0x1F4 SIZE: 0x40
	GfxImage* outdoorImage; //OFS: 0x234 SIZE: 0x4
	unsigned int* cellCasterBits; //OFS: 0x238 SIZE: 0x4
	struct GfxSceneDynModel* sceneDynModel; //OFS: 0x23C SIZE: 0x4
	struct GfxSceneDynBrush* sceneDynBrush; //OFS: 0x240 SIZE: 0x4
	unsigned int* primaryLightEntityShadowVis; //OFS: 0x244 SIZE: 0x4
	unsigned int* primaryLightDynEntShadowVis[2]; //OFS: 0x248 SIZE: 0x8
	char* nonSunPrimaryLightForModelDynEnt; //OFS: 0x250 SIZE: 0x4
	struct GfxShadowGeometry* shadowGeom; //OFS: 0x254 SIZE: 0x4
	GfxLightRegion* lightRegion; //OFS: 0x258 SIZE: 0x4
	GfxWorldDpvsStatic dpvs; //OFS: 0x25C SIZE: 0x64
	GfxWorldDpvsDynamic dpvsDyn; //OFS: 0x2C0 SIZE: 0x30
	unsigned int worldLodChainCount; //OFS: 0x2F0 SIZE: 0x4
	GfxWorldLodChain* worldLodChains; //OFS: 0x2F4 SIZE: 0x4
	unsigned int worldLodInfoCount; //OFS: 0x2F8 SIZE: 0x4
	GfxWorldLodInfo* worldLodInfos; //OFS: 0x2FC SIZE: 0x4
	unsigned int worldLodSurfaceCount; //OFS: 0x300 SIZE: 0x4
	unsigned int* worldLodSurfaces; //OFS: 0x304 SIZE: 0x4
	float waterDirection; //OFS: 0x308 SIZE: 0x4
	GfxWaterBuffer waterBuffers[2]; //OFS: 0x30C SIZE: 0x10
	Material* waterMaterial; //OFS: 0x31C SIZE: 0x4
};

struct r_global_permanent_t
{
	Material* sortedMaterials[2048]; //OFS: 0x0 SIZE: 0x2000
	int needSortMaterials; //OFS: 0x2000 SIZE: 0x4
	int materialCount; //OFS: 0x2004 SIZE: 0x4
	int needMaterialPreload; //OFS: 0x2008 SIZE: 0x4
	GfxImage* whiteImage; //OFS: 0x200C SIZE: 0x4
	GfxImage* blackImage; //OFS: 0x2010 SIZE: 0x4
	GfxImage* blankImage; //OFS: 0x2014 SIZE: 0x4
	GfxImage* grayImage; //OFS: 0x2018 SIZE: 0x4
	GfxImage* identityNormalMapImage; //OFS: 0x201C SIZE: 0x4
	GfxImage* specularityImage; //OFS: 0x2020 SIZE: 0x4
	GfxImage* outdoorImage; //OFS: 0x2024 SIZE: 0x4
	GfxImage* pixelCostColorCode; //OFS: 0x2028 SIZE: 0x4
	GfxLightDef* dlightDef; //OFS: 0x202C SIZE: 0x4
	Material* defaultMaterial; //OFS: 0x2030 SIZE: 0x4
	Material* whiteMaterial; //OFS: 0x2034 SIZE: 0x4
	Material* additiveMaterial; //OFS: 0x2038 SIZE: 0x4
	Material* additiveMaterialNoDepth; //OFS: 0x203C SIZE: 0x4
	Material* pointMaterial; //OFS: 0x2040 SIZE: 0x4
	Material* lineMaterial; //OFS: 0x2044 SIZE: 0x4
	Material* lineMaterialNoDepth; //OFS: 0x2048 SIZE: 0x4
	Material* clearAlphaMaterial; //OFS: 0x204C SIZE: 0x4
	Material* clearAlphaStencilMaterial; //OFS: 0x2050 SIZE: 0x4
	Material* shadowClearMaterial; //OFS: 0x2054 SIZE: 0x4
	Material* shadowCookieOverlayMaterial; //OFS: 0x2058 SIZE: 0x4
	Material* shadowCookieBlurMaterial; //OFS: 0x205C SIZE: 0x4
	Material* shadowCasterMaterial; //OFS: 0x2060 SIZE: 0x4
	Material* shadowOverlayMaterial; //OFS: 0x2064 SIZE: 0x4
	Material* depthPrepassMaterial; //OFS: 0x2068 SIZE: 0x4
	Material* glareBlindMaterial; //OFS: 0x206C SIZE: 0x4
	Material* lightCoronaMaterial; //OFS: 0x2070 SIZE: 0x4
	Material* pixelCostAddDepthAlwaysMaterial; //OFS: 0x2074 SIZE: 0x4
	Material* pixelCostAddDepthDisableMaterial; //OFS: 0x2078 SIZE: 0x4
	Material* pixelCostAddDepthEqualMaterial; //OFS: 0x207C SIZE: 0x4
	Material* pixelCostAddDepthLessMaterial; //OFS: 0x2080 SIZE: 0x4
	Material* pixelCostAddDepthWriteMaterial; //OFS: 0x2084 SIZE: 0x4
	Material* pixelCostAddNoDepthWriteMaterial; //OFS: 0x2088 SIZE: 0x4
	Material* pixelCostColorCodeMaterial; //OFS: 0x208C SIZE: 0x4
	Material* stencilShadowMaterial; //OFS: 0x2090 SIZE: 0x4
	Material* stencilDisplayMaterial; //OFS: 0x2094 SIZE: 0x4
	Material* floatZDisplayMaterial; //OFS: 0x2098 SIZE: 0x4
	Material* colorChannelMixerMaterial; //OFS: 0x209C SIZE: 0x4
	Material* frameColorDebugMaterial; //OFS: 0x20A0 SIZE: 0x4
	Material* frameAlphaDebugMaterial; //OFS: 0x20A4 SIZE: 0x4
	GfxImage* rawImage; //OFS: 0x20A8 SIZE: 0x4
	struct GfxWorld* world; //OFS: 0x20AC SIZE: 0x4
	Material* feedbackReplaceMaterial; //OFS: 0x20B0 SIZE: 0x4
	Material* feedbackBlendMaterial; //OFS: 0x20B4 SIZE: 0x4
	Material* feedbackFilmBlendMaterial; //OFS: 0x20B8 SIZE: 0x4
	Material* cinematicMaterial; //OFS: 0x20BC SIZE: 0x4
	Material* flameThrowerFXMaterial; //OFS: 0x20C0 SIZE: 0x4
	Material* waterSheetingFXMaterial; //OFS: 0x20C4 SIZE: 0x4
	Material* waterDropletMaterial; //OFS: 0x20C8 SIZE: 0x4
	Material* reviveFXMaterial; //OFS: 0x20CC SIZE: 0x4
	Material* postFxColorMaterial; //OFS: 0x20D0 SIZE: 0x4
	Material* postFxMaterial; //OFS: 0x20D4 SIZE: 0x4
	Material* poisonFXMaterial; //OFS: 0x20D8 SIZE: 0x4
	Material* symmetricFilterMaterial[8]; //OFS: 0x20DC SIZE: 0x20
	Material* godRaysFilterMaterial; //OFS: 0x20FC SIZE: 0x4
	Material* shellShockBlurredMaterial; //OFS: 0x2100 SIZE: 0x4
	Material* shellShockFlashedMaterial; //OFS: 0x2104 SIZE: 0x4
	Material* glowConsistentSetupMaterial; //OFS: 0x2108 SIZE: 0x4
	Material* glowApplyBloomMaterial; //OFS: 0x210C SIZE: 0x4
	Material* ropeMaterial; //OFS: 0x2110 SIZE: 0x4
	int savedScreenTimes[4]; //OFS: 0x2114 SIZE: 0x10
	SavedScreenParams savedScreenParams[4]; //OFS: 0x2124 SIZE: 0x50
	GfxImage* terrain_scorch_images[31]; //OFS: 0x2174 SIZE: 0x7C
	GfxImage* splitscreen_sidebars; //OFS: 0x21F0 SIZE: 0x4
	char pad[140]; //OFS: 0x21F4 SIZE: 0x8C
};
enum MaterialVertexDeclType
{
	VERTDECL_GENERIC = 0x0,
	VERTDECL_PACKED = 0x1,
	VERTDECL_WORLD = 0x2,
	VERTDECL_WORLD_T1N0 = 0x3,
	VERTDECL_WORLD_T1N1 = 0x4,
	VERTDECL_WORLD_T2N0 = 0x5,
	VERTDECL_WORLD_T2N1 = 0x6,
	VERTDECL_WORLD_T2N2 = 0x7,
	VERTDECL_WORLD_T3N0 = 0x8,
	VERTDECL_WORLD_T3N1 = 0x9,
	VERTDECL_WORLD_T3N2 = 0xA,
	VERTDECL_WORLD_T4N0 = 0xB,
	VERTDECL_WORLD_T4N1 = 0xC,
	VERTDECL_WORLD_T4N2 = 0xD,
	VERTDECL_POS_TEX = 0xE,
	VERTDECL_STATICMODELCACHE = 0xF,
	VERTDECL_WATER = 0x10,
	VERTDECL_PARTICLECLOUD = 0x11,
	VERTDECL_COUNT = 0x12,
};
struct gfxVertexSteamsUnk
{
	unsigned int stride;
	struct IDirect3DVertexBuffer9* vb;
	unsigned int offset;
};
struct GfxCmdBufPrimState
{
	struct IDirect3DDevice9* device;
	struct IDirect3DIndexBuffer9* indexBuffer;
	MaterialVertexDeclType vertDeclType;
	int pad;
	gfxVertexSteamsUnk streams[3];
	struct IDirect3DVertexDeclaration9* vertexDecl;
};

enum GfxDepthRangeType
{
	GFX_DEPTH_RANGE_SCENE = 0x0,
	GFX_DEPTH_RANGE_VIEWMODEL = 0x2,
	GFX_DEPTH_RANGE_FULL = 0xFFFFFFFF,
};

struct GfxViewport
{
	int x;
	int y;
	int width;
	int height;
};

struct GfxDrawPrimArgs
{
	int vertexCount;
	int triCount;
	int baseIndex;
};
struct GfxCmdBufState
{
	char refSamplerState[16];
	unsigned int samplerState[16];
	GfxTexture* samplerTexture[16];
	GfxCmdBufPrimState prim;
	Material* material;
	MaterialTechniqueType techType;
	MaterialTechnique* technique;
	MaterialPass* pass;
	unsigned int passIndex;
	GfxDepthRangeType depthRangeType;
	float depthRangeNear;
	float depthRangeFar;
	char pad1[4116];
	void* pixelShader;
	void* vertexShader;
	GfxViewport viewport;
	int renderTargetId;
	Material* origMaterial;
	MaterialTechniqueType origTechType;
};


struct GfxVertex
{
	float xyzw[4];
	GfxColor color;
	float texCoord[2];
	PackedUnitVec normal;
};
#pragma pack(push)
#pragma warning(disable : 4324)
struct __declspec(align(8)) materialCommands_t
{
	GfxVertex verts[5450];
	unsigned __int16 indices[1048576];
	MaterialVertexDeclType vertDeclType;
	unsigned int vertexSize;
	int indexCount;
	int vertexCount;
	int firstVertex;
	int lastVertex;
	bool finishedFilling;
};
#pragma pack(pop)
struct GfxMatrix
{
	float m[4][4];
};

struct DpvsPlane
{
	float coeffs[4]; //OFS: 0x0 SIZE: 0x10
	unsigned __int8 side[3]; //OFS: 0x10 SIZE: 0x3
	unsigned __int8 pad; //OFS: 0x13 SIZE: 0x1
};
struct DpvsView
{
	unsigned int renderFxFlagsCull;
	DpvsPlane frustumPlanes[14];
	int frustumPlaneCount;
};
struct DpvsGlob
{
	DpvsPlane viewPlane;
	DpvsPlane fogPlane;
	DpvsPlane* nearPlane;
	DpvsPlane* farPlane;
	GfxMatrix* viewProjMtx;
	GfxMatrix* invViewProjMtx;
	int pad;
	float viewOrg[4];
	int viewOrgIsDir;
	int queuedCount;
	void* PortalHeapNode___portalQueue;
	void* GfxHullPointsPool___nextFreeHullPoints;
	float cullDist;
	DpvsPlane childPlanes[2048];
	DpvsView views[4][3];
	unsigned int cameraCellIndex;
	DpvsPlane* sideFrustumPlanes;
	unsigned int* entVisBits[4];
	unsigned int* cellBits;
	unsigned int cellVisibleBits[32];
};

struct CmdArgs
{
	int nesting; //OFS: 0x0 SIZE: 0x4
	int localClientNum[8]; //OFS: 0x4 SIZE: 0x20
	int controllerIndex[8]; //OFS: 0x24 SIZE: 0x20
	int argc[8]; //OFS: 0x44 SIZE: 0x20
	char** argv[8]; //OFS: 0x64 SIZE: 0x20
};