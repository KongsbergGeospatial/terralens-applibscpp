#include "TerraLens/QTextureViewport3D.h"
#include "Viewport3D.h"
#include "Camera3D.h"

TerraLens::QTextureViewport3D::QTextureViewport3D(QWidget* widget, int msUpdateTimeout)
    : QTextureViewport(widget, msUpdateTimeout)
{
    camera = std::make_unique<InterMAPhics::Camera3D>();
}

TerraLens::QTextureViewport3D::~QTextureViewport3D()
{
}

InterMAPhics::Viewport3D* TerraLens::QTextureViewport3D::getViewport()
{
	return viewport3D;
}

InterMAPhics::Camera3D* TerraLens::QTextureViewport3D::getCamera()
{
    return camera.get();
}

InterMAPhics::Viewport* TerraLens::QTextureViewport3D::buildViewport(InterMAPhics::OpenGLTextureRenderer* renderer)
{
	if (!viewport3D)
	{
		viewport3D = new InterMAPhics::Viewport3D(renderer);
		viewport3D->setCamera(*camera);
	}
	return viewport3D;
}
