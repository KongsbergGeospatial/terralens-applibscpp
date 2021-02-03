#include "TerraLens/QWidgetViewport3D.h"
#include "Viewport3D.h"
#include "Camera3D.h"

TerraLens::QWidgetViewport3D::QWidgetViewport3D(QWidget* widget, int msUpdateTimeout)
    : QWidgetViewport(widget, msUpdateTimeout)
{
    camera = std::make_unique<InterMAPhics::Camera3D>();
}

TerraLens::QWidgetViewport3D::~QWidgetViewport3D()
{
}

InterMAPhics::Viewport3D* TerraLens::QWidgetViewport3D::getViewport()
{
	return viewport3D;
}

InterMAPhics::Camera3D* TerraLens::QWidgetViewport3D::getCamera()
{
    return camera.get();
}

InterMAPhics::Viewport* TerraLens::QWidgetViewport3D::buildViewport(InterMAPhics::OpenGLWindowRenderer* renderer)
{
	if (!viewport3D)
	{
		viewport3D = new InterMAPhics::Viewport3D(renderer);
		viewport3D->setCamera(*camera);
	}
	return viewport3D;
}
