#pragma once
#include "../../Plugins/OpenGLRendering/OGLRenderer.h"
#include "../../Plugins/OpenGLRendering/OGLShader.h"
#include "../../Plugins/OpenGLRendering/OGLTexture.h"
#include "../../Plugins/OpenGLRendering/OGLMesh.h"

#include "RenderObject.h"
#include "../../Common/Vector2.h"

namespace NCL {
	namespace CSC3223 {

		class Renderer : public OGLRenderer
		{
		public:
			Renderer(Window& w);
			~Renderer();

			void AddRenderObject(RenderObject* ro) {
				renderObjects.emplace_back(ro);
			}

			void DeleteAllRenderObjects() {
				for (const RenderObject* object : renderObjects) {
					delete object;
				}
				renderObjects.clear();
			}
			
			void SetProjectionMatrix(const Matrix4&m) {
				projMatrix = m;
			}

			void SetViewMatrix(const Matrix4&m) {
				viewMatrix = m;
			}

			void EnableDepthBuffer(bool state) {
				if (state) {
					glEnable(GL_DEPTH_TEST);
				}
				else {
					glDisable(GL_DEPTH_TEST);
				}
			}

			void EnableBlending(bool state) {
				state ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
			}

			void EnableBilinearFiltering(OGLTexture& t);
			void EnableMipMapFiltering(OGLTexture& t);

			void SetBlendToLinear();
			void SetBlendToAdditive();
			void SetBlendToInvert();

			void SetDepthTestToGreater();
			void SetDepthTestToAlways();
			void SetDepthTestToLEqual();

			void EnableTextureRepeating(OGLTexture& t, bool  uRepeat, bool  vRepeat);

		protected:
			void RenderNode(RenderObject* root);
	
			void OnWindowResize(int w, int h)	override;

			void RenderFrame()	override;
			OGLShader*		defaultShader;

			Matrix4		projMatrix;
			Matrix4		viewMatrix;

			vector<RenderObject*> renderObjects;
		};
	}
}

