#include "TerraLens/QWidgetViewport2D.h"
#include "Viewport2D.h"
#include "Camera2D.h"

TerraLens::QWidgetViewport2D::QWidgetViewport2D(QWidget* widget, int msUpdateTimeout)
    : QWidgetViewport(widget, msUpdateTimeout)
{
    camera = std::make_unique<InterMAPhics::Camera2D>();
}

TerraLens::QWidgetViewport2D::~QWidgetViewport2D()
{
}

InterMAPhics::Viewport2D* TerraLens::QWidgetViewport2D::getViewport()
{
	return viewport2D;
}

InterMAPhics::Camera2D* TerraLens::QWidgetViewport2D::getCamera()
{
    return camera.get();
}

InterMAPhics::Viewport* TerraLens::QWidgetViewport2D::buildViewport(InterMAPhics::OpenGLWindowRenderer* renderer)
{
	if (!viewport2D)
	{
		viewport2D = new InterMAPhics::Viewport2D(renderer);
		viewport2D->setCamera(*camera);
	}
	return viewport2D;
}
