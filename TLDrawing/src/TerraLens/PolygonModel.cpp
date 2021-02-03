#include "TerraLens/PolygonModel.h"

#include "Viewport2D.h"
#include "Camera2D.h"

#include "WorldPoint.h"
#include "WorldDistance.h"

TerraLens::PolygonModel::PolygonModel()
{
	current = 0;
	maxPixelDistance = 5.0;
}

TerraLens::PolygonModel::~PolygonModel()
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

InterMAPhics::GeoPolygon* TerraLens::PolygonModel::getCurrent()
{
	makeCurrent();
	return current;
}

void TerraLens::PolygonModel::clearCurrent()
{
	makeCurrent();
	points.clear();
	current->set(points);
}

void TerraLens::PolygonModel::completeCurrent()
{
	if (current)
	{
		previous.push_back(current);
		current = nullptr;
		points.clear();
	}
}

void TerraLens::PolygonModel::append(InterMAPhics::GeoPoint p)
{
	makeCurrent();
	points.push_back(p);
	current->append(p);
}

int TerraLens::PolygonModel::getIndex(InterMAPhics::Viewport2D* viewport, InterMAPhics::GeoPoint p)
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

void TerraLens::PolygonModel::setPoint(int index, InterMAPhics::GeoPoint& p)
{
	if (index >= 0 && index < points.size())
	{
		points[index] = p;
		current->set(points);
	}
}

void TerraLens::PolygonModel::setMaxPixelDistance(double d)
{
	maxPixelDistance = d;
}

double TerraLens::PolygonModel::getMaxPixelDistance()
{
	return maxPixelDistance;
}

std::vector<InterMAPhics::GeoPolygon*> TerraLens::PolygonModel::getPrevious()
{
	return previous;
}

InterMAPhics::BasicPresentation& TerraLens::PolygonModel::getPresentation()
{
	return presentation;
}

void TerraLens::PolygonModel::detach(InterMAPhics::GeoPolygon* Polygon)
{
	if (Polygon == current)
	{
		current = nullptr;
	}
	else
	{
		for (int i = 0; i < previous.size(); ++i)
		{
			if (previous[i] == Polygon)
			{
				previous.erase(previous.begin() + i);
				return;
			}
		}
	}
}

void TerraLens::PolygonModel::makeCurrent()
{
	if (!current)
	{
		current = new InterMAPhics::GeoPolygon();
		presentation.add(*current);
	}
}
