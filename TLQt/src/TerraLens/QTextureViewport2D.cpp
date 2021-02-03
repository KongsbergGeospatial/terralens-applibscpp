#include "TerraLens/QTextureViewport2D.h"
#include "Viewport2D.h"
#include "Camera2D.h"

TerraLens::QTextureViewport2D::QTextureViewport2D(QWidget* widget, int msUpdateTimeout)
    : QTextureViewport(widget, msUpdateTimeout)
{
    camera = std::make_unique<InterMAPhics::Camera2D>();
}

TerraLens::QTextureViewport2D::~QTextureViewport2D()
{
}

InterMAPhics::Viewport2D* TerraLens::QTextureViewport2D::getViewport()
{
	return viewport2D;
}

InterMAPhics::Camera2D* TerraLens::QTextureViewport2D::getCamera()
{
    return camera.get();
}

InterMAPhics::Viewport* TerraLens::QTextureViewport2D::buildViewport(InterMAPhics::OpenGLTextureRenderer* renderer)
{
	if (!viewport2D)
	{
		viewport2D = new InterMAPhics::Viewport2D(renderer);
		viewport2D->setCamera(*camera);
	}
	return viewport2D;
}
