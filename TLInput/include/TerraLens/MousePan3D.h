#pragma once
#include "TerraLens/MouseInput.h"
#include "ScreenPoint.h"

namespace InterMAPhics
{
	class Viewport3D;
}

namespace TerraLens
{
	/**
	* This class handles panning the 3D Camera by dragging the
	* mouse. The method needs to be assigned to an actual button.
	* It will not function nicely on the "None" button.
	*/
	class DECLSPECIFIER MousePan3D : public MouseInput
	{
	public:
		/**
		* Default Constructor.
		*
		* @param viewport Valid Viewport3D pointer
		*/
		MousePan3D(InterMAPhics::Viewport3D* viewport);

		/**
		* Get the sensitivity of input handler.
		* 
		* The default value is 1.0. Increasing this value will cause
		* the camera to pan farther from mouse movements.
		* 
		* @return The sensitivity value
		*/
		double getSensitivity();

		/**
		* Set the sensitivity of input handler.
		*
		* The default value is 1.0. Increasing this value will cause
		* the camera to pan farther from mouse movements.
		*
		* @param s The sensitivity value
		*/
		void setSensitivity(double s);

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
	};
}
