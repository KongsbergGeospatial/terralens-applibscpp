#include "TerraLens/WheelZoom2D.h"
#include "Viewport2D.h"
#include "Camera2D.h"

TerraLens::WheelZoom2D::WheelZoom2D(InterMAPhics::Viewport2D* v)
{
	viewport = v;
}

void TerraLens::WheelZoom2D::onWheel(int delta)
{
	viewport->getCamera()->setZoom(delta > 0 ? 1.1 : 0.9);
}
