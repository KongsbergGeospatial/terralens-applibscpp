#pragma once

#include "ScreenPoint.h"

namespace TerraLens {
	enum MouseButton
	{
		MB_None,
		MB_Left,
		MB_Middle,
		MB_Right,
		MB_MAX
	};
	/**
	* The MouseInput class exists to handle mouse events
	*/
	class DECLSPECIFIER MouseInput
	{
	public:
		/**
		* Default constructor
		*/
		MouseInput() {};

		/**
		* The method handles mouse press events
		* 
		* @param point The current mouse position
		*/
		virtual void onPressed(InterMAPhics::ScreenPoint& point) {}

		/**
		* The method handles mouse movements events. This will only get hit if
		* the this input handler is assigned to a mouse button that is currently
		* being held, or if it's assigned to the "None" button.
		*
		* @param point The current mouse position
		*/
		virtual void onMoved(InterMAPhics::ScreenPoint& point) {}

		/**
		* The method handles mouse release events
		*
		* @param point The current mouse position
		*/
		virtual void onReleased(InterMAPhics::ScreenPoint& point) {}
	};
}
