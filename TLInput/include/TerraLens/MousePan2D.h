#pragma once

#include "TerraLens/MouseInput.h"
#include "ScreenPoint.h"

namespace InterMAPhics
{
	class Viewport2D;
}

namespace TerraLens
{
	/**
	* This class handles panning the 2D Camera by dragging the
	* mouse. The method needs to be assigned to an actual button. 
	* It will not function nicely on the "None" button.
	*/
	class DECLSPECIFIER MousePan2D : public MouseInput
	{
	public:
		/**
		* Default Constructor.
		* 
		* @param viewport Valid Viewport2D pointer
		*/
		MousePan2D(InterMAPhics::Viewport2D* viewport);

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
		InterMAPhics::Viewport2D* viewport = nullptr;
		InterMAPhics::ScreenPoint lastPoint;
	};
}
