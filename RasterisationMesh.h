#include "../../Plugins/OpenGLRendering/OGLMesh.h"

using namespace NCL;
using namespace NCL::Rendering;

class RasterisationMesh : public OGLMesh {
public:
	RasterisationMesh();
	~RasterisationMesh();

	static RasterisationMesh* CreateTriangleFromPoints(const std::vector<Vector3>& verticies, const std::vector<Vector4>& colours, int type = false);
	static RasterisationMesh* CreateLineFromPoints(const std::vector<Vector3>& verticies, const std::vector<Vector4>& colours, bool bresenham = false);

protected:
	void RasterLineEquationTriange(const Vector3& p0, const Vector3& p1, const Vector3& p2,
									const Vector4& c0, const Vector4& c1, const Vector4& c2);

	void RasterBasicLine(const Vector3& p0, const Vector3& p1, const Vector4& c0, const Vector4& c1);
	void RasterBresenhamLine(const Vector3& p0, const Vector3& p1, const Vector4& c0, const Vector4& c1);

	void RasterBarycentricTriangle(const Vector3& p0, const Vector3& p1, const Vector3& p2,
		const Vector4& c0, const Vector4& c1, const Vector4& c2);
};

