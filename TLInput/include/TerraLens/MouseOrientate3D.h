#pragma once

#include "TerraLens/MouseInput.h"

namespace InterMAPhics
{
	class Viewport3D;
}

namespace TerraLens
{
	/**
	* This class handles changing the 3D Camera's yaw and pitch by dragging the 
	* mouse. The method needs to be assigned to an actual button. It will not 
	* function nicely on the "None" button.
	*/
	class DECLSPECIFIER MouseOrientate3D : public MouseInput
	{
	public:
		/**
		* Constructor.
		* @param v A valid Viewport3D pointer
		*/
		MouseOrientate3D(InterMAPhics::Viewport3D* v);

		/**
		* Get the sensitivity value.
		* 
		* The default is 1.0, and higher values will cause the camera to rotate more
		* quickly.
		* 
		* @return the sensitivity value
		*/
		double getSensitivity();
		/**
		* Set the sensitivity value.
		* 
		* The default is 1.0, and higher values will cause the camera to rotate more
		* quickly.
		* 
		* @param s The sensitivity value
		*/
		void setSensitivity(double s);

		/**
		* Get the minimum pitch value. The default is 2.0 degrees.
		* 
		* The pitch values are limited to prevent accidently pointing the camera in an
		* odd direction, or even flipping it upside down.
		* 
		* @return The minimum pitch
		*/
		double getMinPitch();
		/**
		* Get the maximum pitch value. The default is 90.0 degrees.
		*
		* The pitch values are limited to prevent accidently pointing the camera in an
		* odd direction, or even flipping it upside down.
		*
		* @return The maximum pitch
		*/
		double getMaxPitch();
		/**
		* Set the pitch value limits. The default is 2.0 to 90.0 degrees.
		*
		* The pitch values are limited to prevent accidently pointing the camera in an
		* odd direction, or even flipping it upside down.
		*
		* @param min The minimum pitch
		* @param max The maximum pitch
		*/
		void setPitchLimits(double min, double max);

		/**
		* The method handles mouse press events
		*
		* @param point The current mouse position
		*/
		virtual void onPressed(InterMAPhics::ScreenPoint& point);
		/**
		* The method handles mouse move events
		*
		* @param point The current mouse position
		*/
		virtual void onMoved(InterMAPhics::ScreenPoint& point);
		/**
		* The method handles mouse release events
		*
		* @param point The current mouse position
		*/
		virtual void onReleased(InterMAPhics::ScreenPoint& point);

	protected:
		InterMAPhics::Viewport3D* viewport = nullptr;
		InterMAPhics::ScreenPoint lastPoint;
		double sensitivity = 1.0;
		double minPitch = 2.0, maxPitch = 90.0;
	};
}
