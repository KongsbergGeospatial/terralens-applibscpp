#include "TerraLens/MousePan2D.h"
#include "Viewport2D.h"
#include "Camera2D.h"

TerraLens::MousePan2D::MousePan2D(InterMAPhics::Viewport2D* v)
{
	viewport = v;
}

void TerraLens::MousePan2D::onPressed(InterMAPhics::ScreenPoint& point)
{
	lastPoint = point;
}

void TerraLens::MousePan2D::onMoved(InterMAPhics::ScreenPoint& point)
{
	InterMAPhics::ScreenPoint delta = point - lastPoint;
	viewport->getCamera()->panViewCenter(delta.getX(), delta.getY());
	lastPoint = point;
}

void TerraLens::MousePan2D::onReleased(InterMAPhics::ScreenPoint& point)
{
	InterMAPhics::ScreenPoint delta = point - lastPoint;
	viewport->getCamera()->panViewCenter(delta.getX(), delta.getY());
}
