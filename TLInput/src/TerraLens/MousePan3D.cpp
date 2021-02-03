#include "TerraLens/MousePan3D.h"

#include "Viewport3D.h"
#include "Camera3D.h"

#include "Orientation3D.h"
#include "PolarPoint3D.h"
#include "DegreeAngle.h"

//Magic number to make sensitivity 1.0 feel reasonable
static const double senScale = 350.0;

TerraLens::MousePan3D::MousePan3D(InterMAPhics::Viewport3D* v)
{
	viewport = v;
}

double TerraLens::MousePan3D::getSensitivity()
{
	return sensitivity;
}

void TerraLens::MousePan3D::setSensitivity(double s)
{
	sensitivity = s;
}

void TerraLens::MousePan3D::onPressed(InterMAPhics::ScreenPoint& point)
{
	lastPoint = point;
}

void TerraLens::MousePan3D::onMoved(InterMAPhics::ScreenPoint& point)
{
	InterMAPhics::ScreenPoint delta = point - lastPoint;

	InterMAPhics::Camera3D* camera = viewport->getCamera();
	InterMAPhics::GeoPoint3D targetPosition;
	camera->getViewPosition(targetPosition);
	InterMAPhics::Orientation3D orient = camera->getOrientation();
	int deltaY = delta.getY().get();
	InterMAPhics::PolarPoint3D yFactor = InterMAPhics::PolarPoint3D(orient.getYaw() +
		(deltaY < 0 ? InterMAPhics::DegreeAngle(180) : InterMAPhics::DegreeAngle(0)),
		targetPosition.getAltitude() * abs(deltaY) * sensitivity / senScale, 0);

	int deltaX = delta.getX().get();
	InterMAPhics::PolarPoint3D xFactor = InterMAPhics::PolarPoint3D(orient.getYaw() +
		(deltaX > 0 ? InterMAPhics::DegreeAngle(-90) : InterMAPhics::DegreeAngle(90)),
		targetPosition.getAltitude() * abs(deltaX) * sensitivity / senScale, 0);

	targetPosition = targetPosition.move(xFactor + yFactor);

	camera->setViewPosition(targetPosition);

	lastPoint = point;
}

void TerraLens::MousePan3D::onReleased(InterMAPhics::ScreenPoint& point)
{
	InterMAPhics::ScreenPoint delta = point - lastPoint;

	InterMAPhics::Camera3D* camera = viewport->getCamera();
	InterMAPhics::GeoPoint3D targetPosition;
	camera->getViewPosition(targetPosition);
	InterMAPhics::Orientation3D orient = camera->getOrientation();
	int deltaY = delta.getY().get();
	InterMAPhics::PolarPoint3D yFactor = InterMAPhics::PolarPoint3D(orient.getYaw() +
		(deltaY < 0 ? InterMAPhics::DegreeAngle(180) : InterMAPhics::DegreeAngle(0)),
		targetPosition.getAltitude() * abs(deltaY) * sensitivity / senScale, 0);

	int deltaX = delta.getX().get();
	InterMAPhics::PolarPoint3D xFactor = InterMAPhics::PolarPoint3D(orient.getYaw() +
		(deltaX > 0 ? InterMAPhics::DegreeAngle(-90) : InterMAPhics::DegreeAngle(90)),
		targetPosition.getAltitude() * abs(deltaX) * sensitivity / senScale, 0);

	targetPosition = targetPosition.move(xFactor + yFactor);

	camera->setViewPosition(targetPosition);
}
