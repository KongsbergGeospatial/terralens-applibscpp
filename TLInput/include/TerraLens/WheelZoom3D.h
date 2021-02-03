#pragma once

#include "TerraLens/WheelInput.h"
#include "Meter.h"
namespace InterMAPhics
{
	class Viewport3D;
}

namespace TerraLens
{
	/**
	* This class handles zooming the 3D Camera by scrolling the mouse wheel
	*/
	class DECLSPECIFIER WheelZoom3D : public WheelInput
	{
	public:
		/**
		* Default constructor.
		*
		* @param viewport A valid Viewport3D pointer
		*/
		WheelZoom3D(InterMAPhics::Viewport3D* viewport);

		/**
		* Handle zooming the camera by scrolling the mouse wheel. The zoom is dependent on
		* the current direction of the camera.
		*
		* @param delta The direction of mouse wheel movement
		*/
		virtual void onWheel(int delta);

		/**
		* Get the sensitivity of input handler.
		*
		* The default value is 1.0. Increasing this value will cause
		* the camera to move farther based on the current camera altitude.
		*
		* @return The sensitivity value
		*/
		double getSensitivity();

		/**
		* Set the sensitivity of input handler.
		*
		* The default value is 1.0. Increasing this value will cause
		* the camera to move farther based on the current camera altitude.
		*
		* @param s The sensitivity value
		*/
		void setSensitivity(double s);

		/**
		* Set the minimum distance to move. This is to prevent a lack of movement close to the surface.
		*
		* @param distance The minimum move distance
		*/
		InterMAPhics::WorldDistance getMinimumDistance();

		/**
		* Set the minimum distance to move. This is to prevent a lack of movement close to the surface.
		* 
		* @return The minimum move distance
		*/
		void setMinimumDistance(InterMAPhics::WorldDistance distance);
	protected:
		InterMAPhics::Viewport3D* viewport = nullptr;
		double sensitivity = 1.0;
		InterMAPhics::WorldDistance minDistance = InterMAPhics::Meter(50);
	};
}
