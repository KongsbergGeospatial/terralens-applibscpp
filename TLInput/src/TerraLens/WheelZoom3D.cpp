#include "TerraLens/WheelZoom3D.h"

#include "Viewport3D.h"
#include "Camera3D.h"
#include "PolarPoint3D.h"
#include "PolarPoint.h"

using namespace InterMAPhics;

static double baseSensitivity = 1.0 / 10.0;

TerraLens::WheelZoom3D::WheelZoom3D(InterMAPhics::Viewport3D* v)
{
	viewport = v;
}

void TerraLens::WheelZoom3D::onWheel(int delta)
{
	Camera3D* camera = viewport->getCamera();
	GeoPoint3D view = camera->getViewPosition();
	Orientation3D ori = camera->getOrientation();

	double toGroundFactor = sin(ori.getPitch().get());
	double fwdFactor = cos(ori.getPitch().get());

	double moveDistance = view.getAltitude().get() * sensitivity * baseSensitivity;

	if (moveDistance < minDistance.get())
		moveDistance = minDistance.get();

	WorldPoint3D move = WorldPoint3D();
	if (delta > 0)
	{
		move.set(PolarPoint(ori.getYaw(), moveDistance * fwdFactor), moveDistance * toGroundFactor * -1.0);
	}
	else if (delta < 0)
	{
		move.set(PolarPoint(ori.getYaw(), moveDistance * fwdFactor * -1.0), moveDistance * toGroundFactor);
	}

	view = view.move(move);
	camera->setViewPosition(view);
}

double TerraLens::WheelZoom3D::getSensitivity()
{
	return sensitivity;
}

void TerraLens::WheelZoom3D::setSensitivity(double s)
{
	sensitivity = s;
}

InterMAPhics::WorldDistance TerraLens::WheelZoom3D::getMinimumDistance()
{
	return minDistance;
}

void TerraLens::WheelZoom3D::setMinimumDistance(InterMAPhics::WorldDistance distance)
{
	minDistance = distance;
}
