#pragma once

#include "TerraLens/MouseInput.h"

#include "Viewport2D.h"

namespace TerraLens
{
	/**
	* The DrawEditInput class enables adding a new or modifying an existing GeoPoint to a
	* MarkerModel, PolygonModel, or PolylineModel. By clicking on a existing point, the
	* point can be dragged to a new position. Otherwise, a new point will be added instead.
	*/
	template <class T>
	class DrawEditInput : public MouseInput
	{
	public:
		/**
		* Create a DrawEditInput object. The template can be a MarkerModel, PolygonModel or
		* PolylineModel.
		*/
		DrawEditInput(InterMAPhics::Viewport2D* v, T* m)
		{
			viewport = v;
			model = m;
		};

		/**
		* On mouse press select an existing point to drag or add a new point to the model.
		* 
		* @param point Current mouse position
		*/
		virtual void onPressed(InterMAPhics::ScreenPoint& point)
		{
			InterMAPhics::GeoPoint p = viewport->getGeoPoint(point);
			currIndex = model->getIndex(viewport, p);
			if (currIndex == -1)
			{
				model->append(p);
			}
			else
			{
				model->setPoint(currIndex, p);
			}
		};

		/**
		* On mouse movement, drag the selected point to a new position
		*
		* @param point Current mouse position
		*/
		virtual void onMoved(InterMAPhics::ScreenPoint& point)
		{
			if (currIndex != -1)
			{
				InterMAPhics::GeoPoint p = viewport->getGeoPoint(point);
				model->setPoint(currIndex, p);
			}
		}

		/**
		* On mouse release, set the selected point to a new position
		*
		* @param point Current mouse position
		*/
		virtual void onReleased(InterMAPhics::ScreenPoint& point)
		{
			if (currIndex != -1)
			{
				InterMAPhics::GeoPoint p = viewport->getGeoPoint(point);
				model->setPoint(currIndex, p);
			}
		}

	private:
		InterMAPhics::Viewport2D* viewport;
		T* model;
		int currIndex = -1;
	};
}
