#pragma once
#include "Object.h"

namespace TerraLens {
	/**
	* This class handles panning the 2D Camera by dragging the
	* mouse. The method needs to be assigned to an actual button.
	* It will not function nicely on the "None" button.
	*/
	class DECLSPECIFIER WheelInput
	{
	public:
		/**
		* Default constructor.
		*/
		WheelInput() {};

		/**
		* This method handles mouse wheel events
		* 
		* @param delta Which direction the mouse wheel moved
		*/
		virtual void onWheel(int delta) {};
	};
}
