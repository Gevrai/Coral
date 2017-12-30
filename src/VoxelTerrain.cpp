#include "VoxelTerrain.h"

VoxelTerrain::VoxelTerrain(WindowRenderer* renderer, std::string mapname)
{
	if(!loadMap(mapname))
		throw InitializationException();
}

bool VoxelTerrain::loadMap(std::string mapname)
{
	std::string heightmapPath = "../res/heightmaps/";
	std::string colormapPath = "../res/colormaps/";

	Surface heightmapSurface = Surface(heightmapPath.append(mapname).c_str());
	Surface colormapSurface = Surface(colormapPath.append(mapname).c_str());
	if (!heightmapSurface.isValid()  || !colormapSurface.isValid()) {
		return false;
	}

	if (heightmap) delete heightmap;
	if (colormap) delete colormap;

	colormapW = colormapSurface.width();
	colormapH = colormapSurface.height();
	heightmapW = heightmapSurface.width();
	heightmapH = heightmapSurface.height();

	colormap = new RGBA[colormapW * colormapH];
	heightmap = new Uint8[heightmapW * heightmapH];


	if (colormap == nullptr || heightmap == nullptr) {
		ERROR("OUT OF MEMORY TO ALLOCATE MAPS");
		exit(-1);
	}

	for (uint i = 0; i < colormapW ; i++)
		for (uint j = 0; j < colormapH; j++){
			colormap[i*colormapW + j] = colormapSurface.GetRGBA(i,j);
		}


	for (uint i = 0; i < heightmapW; i++)
		for (uint j = 0; j < heightmapH; j++)
			heightmap[i*heightmapW + j] = heightmapSurface.GetRGBA(i,j).r;

	heightmap_scalex = (double) heightmapW / colormapW;
	heightmap_scaley = (double) heightmapH / colormapH;
	return true;
}


VoxelTerrain::~VoxelTerrain()
{
	delete heightmap;
	delete colormap;
}

inline RGBA VoxelTerrain::colormapPixelAt(double x, double y) const {
	int i = (int) x; i = MOD(i, colormapW);
	int j = (int) y; j = MOD(j, colormapH);
	return colormap[i*colormapW + j];
}

inline Uint8 VoxelTerrain::heightmapPixelAt(double x, double y) const {
	int i = x * heightmap_scalex; i = MOD(i, heightmapW);
	int j = y * heightmap_scaley; j = MOD(j, heightmapH);
	return heightmap[i*heightmapW + j];
}

void VoxelTerrain::render(WindowRenderer* renderer, const Camera* camera) const {

	// Get screen width and height
	int screenwidth, screenheight;
	SDL_RenderGetLogicalSize(renderer->getRenderer(), &screenwidth, &screenheight);

	double xl,yl,xr,yr,dx,dy;
	double posx = camera->getPos().x;
	double posy = camera->getPos().y;
	double posz = camera->getPos().z;
	double fowx = camera->getFoward().x;
	double fowy = camera->getFoward().y;

	double horizon = camera->getFoward().z + screenheight/2;
	horizon = 0;

	RGBA color;

	int heightOnScreen;
	double heightOnMap;
	int* yCurrentHeight = new int[screenwidth];
	for (int i=0;i<screenwidth;i++)
		yCurrentHeight[i] = screenheight;

	// Draw from front to back with occlusion
	double z = 1.0;
	double dz = 1.0;
	while ( z < drawDistance ) {
		// Line on map for this distance (fov of 45 degrees)
		xr = ( fowx + fowy) * z;
		yr = ( fowy - fowx) * z;
		xl = ( fowx - fowy) * z;
		yl = ( fowy + fowx) * z;
		// Segment line
		dx = (xr - xl)/(double) screenwidth;
		dy = (yr - yl)/(double) screenwidth;
		// Center camera
		xl += posx;
		yl += posy;

		// Draw line for each segment
		for (int i = 0; i < screenwidth ; i++) {
			// Get heightmap pixel
			heightOnMap = heightmapPixelAt(xl,yl);
			heightOnScreen = ((posz - heightOnMap) / z * scaleHeight + horizon);
			if (heightOnScreen < 0)
				heightOnScreen = 0;
			if (heightOnScreen < yCurrentHeight[i]) {
				color = colormapPixelAt(xl,yl);
				renderer->DrawLine(color, i, heightOnScreen, i, yCurrentHeight[i]);
				yCurrentHeight[i] = heightOnScreen;
			}
			xl += dx;
			yl += dy;
		}

		// Less and less resolution
		dz *= resolutionDelta;
		z += dz;
	}

	delete yCurrentHeight;
}

double VoxelTerrain::getHeightAt(double x, double y) const {
	return (double) heightmapPixelAt(x,y);
}
