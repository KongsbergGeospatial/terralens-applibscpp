#pragma once

#include "TerraLens/MouseInput.h"

#include "Viewport2D.h"

namespace TerraLens
{
	/**
	* The DrawEditInput class enables adding a new GeoPoint to a MarkerModel, PolygonModel, 
	* or PolylineModel. A new point will be added on mouse press.
	*/
	template <class T>
	class DrawSimpleInput : public MouseInput
	{
	public:
		/**
		* Create a DrawSimpleInput object. The template can be a MarkerModel, PolygonModel or
		* PolylineModel.
		*/
		DrawSimpleInput(InterMAPhics::Viewport2D* v, T* m)
		{
			viewport = v;
			model = m;
		};

		/**
		* On mouse press add a new point to the model.
		*
		* @param point Current mouse position
		*/
		virtual void onPressed(InterMAPhics::ScreenPoint& point)
		{
			InterMAPhics::GeoPoint p = viewport->getGeoPoint(point);
			model->append(p);
		};

	private:
		InterMAPhics::Viewport2D* viewport;
		T* model;
	};
}
