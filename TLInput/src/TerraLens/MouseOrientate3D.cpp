#include "TerraLens/MouseOrientate3D.h"
#include "DegreeAngle.h"
#include "Viewport3D.h"
#include "Camera3D.h"

using InterMAPhics::DegreeAngle;

//Magic number to make sensitivity 1.0 feel reasonable
static const double senScale = 5.0;

TerraLens::MouseOrientate3D::MouseOrientate3D(InterMAPhics::Viewport3D* v)
{
	viewport = v;
}

double TerraLens::MouseOrientate3D::getSensitivity()
{
	return sensitivity;
}

void TerraLens::MouseOrientate3D::setSensitivity(double s)
{
	sensitivity = s;
}

double TerraLens::MouseOrientate3D::getMinPitch()
{
	return minPitch;
}

double TerraLens::MouseOrientate3D::getMaxPitch()
{
	return maxPitch;
}

void TerraLens::MouseOrientate3D::setPitchLimits(double min, double max)
{
	minPitch = min;
	maxPitch = max;
}

void TerraLens::MouseOrientate3D::onPressed(InterMAPhics::ScreenPoint& point)
{
	lastPoint = point;
}

void TerraLens::MouseOrientate3D::onMoved(InterMAPhics::ScreenPoint& point)
{
	InterMAPhics::Camera3D* m_camera = viewport->getCamera();

	InterMAPhics::ScreenPoint delta = point - lastPoint;

	DegreeAngle yaw = m_camera->getOrientation().getYaw() - DegreeAngle(delta.getX().get() * sensitivity / senScale);
	DegreeAngle pitch = m_camera->getOrientation().getPitch() + DegreeAngle(delta.getY().get() * sensitivity / senScale);

	if (pitch.get() < minPitch)
		pitch.set(minPitch);
	if (pitch.get() > maxPitch)
		pitch.set(maxPitch);

	m_camera->setOrientation(InterMAPhics::Orientation3D(yaw, pitch, 0.0));

	lastPoint = point;
}

void TerraLens::MouseOrientate3D::onReleased(InterMAPhics::ScreenPoint& point)
{
	InterMAPhics::Camera3D* m_camera = viewport->getCamera();

	InterMAPhics::ScreenPoint delta = point - lastPoint;

	DegreeAngle yaw = m_camera->getOrientation().getYaw() - DegreeAngle(delta.getX().get() / sensitivity / senScale);
	DegreeAngle pitch = m_camera->getOrientation().getPitch() + DegreeAngle(delta.getY().get() / sensitivity / senScale);

	if (pitch.get() < minPitch)
		pitch.set(minPitch);
	if (pitch.get() > maxPitch)
		pitch.set(maxPitch);

	m_camera->setOrientation(InterMAPhics::Orientation3D(yaw, pitch, 0.0));
}
