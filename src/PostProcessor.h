#ifndef POST_PROCESSOR_H
#define POST_PROCESSOR_H

#include <memory>
#include "Types.h"
#include "Textures.h"
#include "Graphics/ObjectHandle.h"

namespace graphics {
	class ShaderProgram;
}

class PostProcessor {
public:
	void init();
	void destroy();
#ifndef PANDORA
	FrameBuffer * doBlur(FrameBuffer * _pBuffer);
#endif
	FrameBuffer * doGammaCorrection(FrameBuffer * _pBuffer);
	FrameBuffer * doOrientationCorrection(FrameBuffer * _pBuffer);

	static PostProcessor & get();

private:
	PostProcessor();
	PostProcessor(const PostProcessor & _other);

	void _initCommon();
	void _destroyCommon();
	void _initGammaCorrection();
	void _destroyGammaCorrection();
	void _initOrientationCorrection();
	void _destroyOrientationCorrection();
#ifndef PANDORA
	void _initBlur();
	void _destroyBlur();
#endif
	void _preDraw(FrameBuffer * _pBuffer);
	void _postDraw();

	std::unique_ptr<graphics::ShaderProgram> m_gammaCorrectionProgram;
	std::unique_ptr<graphics::ShaderProgram> m_orientationCorrectionProgram;

	FrameBuffer * m_pResultBuffer;
#ifndef PANDORA
	graphics::ObjectHandle m_FBO_glowMap;
	graphics::ObjectHandle m_FBO_blur;
#endif
	CachedTexture * m_pTextureOriginal;
#ifndef PANDORA
	CachedTexture * m_pTextureGlowMap;
	CachedTexture * m_pTextureBlur;
#endif
#ifdef OS_ANDROID
	static PostProcessor processor;
#endif
};

#endif // POST_PROCESSOR_H
