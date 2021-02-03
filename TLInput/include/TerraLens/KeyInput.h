#pragma once

#include "TerraLens/KeyCodes.h"

namespace TerraLens
{
	enum KeyModifier
	{
		TL_KMOD_LSHIFT = 0x0001,
		TL_KMOD_RSHIFT = 0x0002,
		TL_KMOD_SHIFT  = 0x0003,

		TL_KMOD_LCTRL = 0x0004,
		TL_KMOD_RCTRL = 0x0008,
		TL_KMOD_CTRL  = 0x000C,

		TL_KMOD_LALT = 0x0010,
		TL_KMOD_RALT = 0x0020,
		TL_KMOD_ALT  = 0x0030,

	};
	/**
	* The KeyInput class exists to handle keyboard events
	*/
	class DECLSPECIFIER KeyInput
	{
	public:
		/**
		* Default Constructor
		*/
		KeyInput() {};

		/**
		* Handles a key press event.
		* 
		* @param key The key that has been pressed
		* @param mod What special modifier key (shift, alt, ctrl) is currently
		*	being held. See the KeyModifier enum for values.
		*/
		virtual void onPressed(int key, int mod = 0) {};

		/**
		* Handles a key release event.
		*
		* @param key The key that has been released
		* @param mod What special modifier key (shift, alt, ctrl) is currently
		*	being held. See the KeyModifier enum for values.
		*/
		virtual void onReleased(int key, int mod = 0) {};
	};
}
