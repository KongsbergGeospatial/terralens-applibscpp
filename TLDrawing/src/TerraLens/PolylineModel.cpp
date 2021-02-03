#include "TerraLens/PolylineModel.h"

#include "Viewport2D.h"
#include "Camera2D.h"

#include "WorldPoint.h"
#include "WorldDistance.h"

TerraLens::PolylineModel::PolylineModel()
{
}

TerraLens::PolylineModel::~PolylineModel()
{
	if (current)
	{
		delete current;
	}
	for (int i = 0; i < previous.size(); ++i)
	{
		delete previous[i];
	}
}

InterMAPhics::GeoPolyline* TerraLens::PolylineModel::getCurrent()
{
	makeCurrent();
	return current;
}

void TerraLens::PolylineModel::clearCurrent()
{
	makeCurrent();
	points.clear();
	current->set(points);
}

void TerraLens::PolylineModel::completeCurrent()
{
	if (current)
	{
		previous.push_back(current);
		current = nullptr;
		points.clear();
	}
}

void TerraLens::PolylineModel::append(InterMAPhics::GeoPoint p)
{
	makeCurrent();
	points.push_back(p);
	current->append(p);
}

int TerraLens::PolylineModel::getIndex(InterMAPhics::Viewport2D* viewport, InterMAPhics::GeoPoint p)
{
	InterMAPhics::Camera2D* cam = viewport->getCamera();
	double range = cam->getRange().get();
	InterMAPhics::ScreenDistance width, height;
	viewport->getSize(width, height);
	int pixels = width > height ? width.get() : height.get();

	double maxPixelDistance = 3.0;
	double mpdSq = maxPixelDistance * maxPixelDistance;

	for (int i = 0; i < points.size(); ++i)
	{
		InterMAPhics::WorldPoint delta = p.getRangeAndBearing(points[i]);
		double c2 = delta.getX().get() * delta.getX().get() + delta.getY().get() * delta.getY().get();
		double pixelDisSq = c2 * pixels * pixels / (range * range);
		if (pixelDisSq < mpdSq)
		{
			return i;
		}
	}

	return -1;
}

void TerraLens::PolylineModel::setPoint(int index, InterMAPhics::GeoPoint& p)
{
	if (index >= 0 && index < points.size())
	{
		points[index] = p;
		current->set(points);
	}
}

void TerraLens::PolylineModel::setMaxPixelDistance(double d)
{
	maxPixelDistance = d;
}

double TerraLens::PolylineModel::getMaxPixelDistance()
{
	return maxPixelDistance;
}

std::vector<InterMAPhics::GeoPolyline*> TerraLens::PolylineModel::getPrevious()
{
	return previous;
}

InterMAPhics::BasicPresentation& TerraLens::PolylineModel::getPresentation()
{
	return presentation;
}

void TerraLens::PolylineModel::detach(InterMAPhics::GeoPolyline* Polyline)
{
	if (Polyline == current)
	{
		current = nullptr;
	}
	else
	{
		for (int i = 0; i < previous.size(); ++i)
		{
			if (previous[i] == Polyline)
			{
				previous.erase(previous.begin() + i);
				return;
			}
		}
	}
}

void TerraLens::PolylineModel::makeCurrent()
{
	if (!current)
	{
		current = new InterMAPhics::GeoPolyline();
		presentation.add(*current);
	}
}
