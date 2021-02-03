#pragma once

#include "TerraLens/WheelInput.h"
namespace InterMAPhics
{
	class Viewport2D;
}

namespace TerraLens
{
	/**
	* This class handles zooming the 2D Camera by scrolling the mouse wheel
	*/
	class DECLSPECIFIER WheelZoom2D : public WheelInput
	{
	public:
		/**
		* Default constructor.
		* 
		* @param viewport A valid Viewport2D pointer
		*/
		WheelZoom2D(InterMAPhics::Viewport2D* viewport);

		/**
		* Handle zooming the camera by scrolling the mouse wheel.
		* 
		* @param delta The direction of mouse wheel movement
		*/
		virtual void onWheel(int delta);
	protected:
		InterMAPhics::Viewport2D* viewport = nullptr;
	};
}
