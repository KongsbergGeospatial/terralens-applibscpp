#pragma once

#include "Object.h"
#include "GeoPolygon.h"
#include "BasicPresentation.h"

namespace InterMAPhics
{
	class Viewport2D;
}

namespace TerraLens
{
	/**
	* The PolygonModel class assists the drawing of Latitude/Longitude polygons on a viewport.
	*/
	class DECLSPECIFIER PolygonModel
	{
	public:
		/**
		* Construct a PolygonModel class.
		*/
		PolygonModel();

		/**
		* Destructor. Any primitives that belong to this model will be deleted.
		*/
		~PolygonModel();

		/**
		* Get the GeoPolygon object that is currently being edited.
		*
		* @return The current GeoPolygon
		*/
		InterMAPhics::GeoPolygon* getCurrent();

		/**
		* Clear all of the points from the current primitive.
		*/
		void clearCurrent();
		/**
		* Move the current primitive to the list of completed primitives,
		* so that it no longer editable.
		*/
		void completeCurrent();

		/**
		* Add a GeoPoint to the current primitive.
		*/
		void append(InterMAPhics::GeoPoint p);
		/**
		* Get the index to the list of points of the current primitive. If the provided point is not
		* near to an existing point in the list, then it will return -1.
		*
		* The GeoPoint does not need to be exact. It can be a number pixels from the input value. See
		* setMaxPixelDistance and getMaxPixelDistance.
		*
		* @param viewport Viewport containing the primitive
		* @param p GeoPoint used for comparision
		* @return -1 if the point is not in the list or a valid index
		*/
		int getIndex(InterMAPhics::Viewport2D* viewport, InterMAPhics::GeoPoint p);
		/**
		* Change an existing point in the point list to a new position
		*
		* @param index The index to change
		* @param p The new GeoPoint value
		*/
		void setPoint(int index, InterMAPhics::GeoPoint& p);

		/**
		* Set the amount of pixels away from a GeoPoint that will recognized as the same point
		* by the getIndex function.
		*
		* The default is 5 pixels.
		*
		* @param d Max distance from a point in pixels
		*/
		void setMaxPixelDistance(double d);
		/**
		* Get the amount of pixels away from a GeoPoint that will recognized as the same point
		* by the getIndex function.
		*
		* The default is 5 pixels.
		*
		* @return Max distance from a point in pixels
		*/
		double getMaxPixelDistance();

		/**
		* Get the previously completed primitives
		*
		* @return List of previously completed primitives
		*/
		std::vector<InterMAPhics::GeoPolygon*> getPrevious();
		/**
		* Get the basic presentation which all primitives in this model
		* are assignd to by default.
		*
		* They can be reassigned to other presentations freely.
		*
		* @return List of previously completed primitives
		*/
		InterMAPhics::BasicPresentation& getPresentation();

		/**
		* Detach a GeoPolygon from this Model. This will prevent the poylgon from
		* being deleted when this model is destroyed.
		*
		* @param polyon GeoPolygon to remove from this model.
		*/
		void detach(InterMAPhics::GeoPolygon* polygon);

	private:
		void makeCurrent();

		std::vector<InterMAPhics::GeoPolygon*> previous;
		InterMAPhics::GeoPolygon* current = nullptr;
		std::vector<InterMAPhics::GeoPoint> points;

		InterMAPhics::BasicPresentation presentation;

		double maxPixelDistance = 5.0;
	};
}
