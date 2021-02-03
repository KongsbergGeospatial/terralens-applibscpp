#include "TerraLens/MarkerModel.h"

#include "Viewport2D.h"
#include "Camera2D.h"

#include "WorldPoint.h"
#include "WorldDistance.h"

TerraLens::MarkerModel::MarkerModel()
{
}

TerraLens::MarkerModel::~MarkerModel()
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

InterMAPhics::GeoMarker* TerraLens::MarkerModel::getCurrent()
{
	makeCurrent();
	return current;
}

void TerraLens::MarkerModel::clearCurrent()
{
	makeCurrent();
	points.clear();
	current->set(points);
}

void TerraLens::MarkerModel::completeCurrent()
{
	if (current)
	{
		previous.push_back(current);
		current = nullptr;
		points.clear();
	}
}

void TerraLens::MarkerModel::append(InterMAPhics::GeoPoint p)
{
	makeCurrent();
	points.push_back(p);
	current->append(p);
}

int TerraLens::MarkerModel::getIndex(InterMAPhics::Viewport2D* viewport, InterMAPhics::GeoPoint p)
{
	InterMAPhics::Camera2D* cam = viewport->getCamera();
	double range = cam->getRange().get();
	InterMAPhics::ScreenDistance width, height;
	viewport->getSize(width, height);
	int pixels = width > height ? width.get() : height.get();

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

void TerraLens::MarkerModel::setPoint(int index, InterMAPhics::GeoPoint& p)
{
	if (index >= 0 && index < points.size())
	{
		points[index] = p;
		current->set(points);
	}
}

void TerraLens::MarkerModel::setMaxPixelDistance(double d)
{
	maxPixelDistance = d;
}

double TerraLens::MarkerModel::getMaxPixelDistance()
{
	return maxPixelDistance;
}

std::vector<InterMAPhics::GeoMarker*> TerraLens::MarkerModel::getPrevious()
{
	return previous;
}

InterMAPhics::BasicPresentation& TerraLens::MarkerModel::getPresentation()
{
	return presentation;
}

void TerraLens::MarkerModel::detach(InterMAPhics::GeoMarker* marker)
{
	if (marker == current)
	{
		current = nullptr;
	}
	else
	{
		for (int i = 0; i < previous.size(); ++i)
		{
			if (previous[i] == marker)
			{
				previous.erase(previous.begin() + i);
				return;
			}
		}
	}
}

void TerraLens::MarkerModel::makeCurrent()
{
	if (!current)
	{
		current = new InterMAPhics::GeoMarker();
		presentation.add(*current);
	}
}
