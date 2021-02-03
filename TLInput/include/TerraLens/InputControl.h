#pragma once

#include "TerraLens/MouseInput.h"
#include "TerraLens/KeyInput.h"
#include "TerraLens/WheelInput.h"
#include <vector>

namespace TerraLens
{
	/**
	* The InputControl class provides a generic means of passing input events
	* to an application regardless of the GUI system they originate from.
	* 
	* Each of the different inputs handled by this system has a list of added
	* input handlers, but only one for each input type (Keyboard, Left Mouse,
	* Right Mouse, etc.) is active at one time. The relevant input can be selected
	* with the appropriate "select input" method.
	*/
	class DECLSPECIFIER InputControl
	{
	public:
		/**
		* Default constructor for the InputControl object.
		*/
		InputControl();
		/**
		* Destructor. This will delete all inputs that are currently assigned to it.
		*/
		~InputControl();

		/**
		* Add a MouseInput object, which handles mouse button presses and movement.
		* 
		* @param button Which button this is event is mapped to
		* @param input The input handler to add
		* @return The index for this newly added input
		*/
		int addMouseInput(TerraLens::MouseButton button, TerraLens::MouseInput* input);

		/**
		* Removes a MouseInput that's been previously added.
		* 
		* @param button Which button this is event is mapped to
		* @param input The input handler to remove
		*/
		void removeMouseInput(TerraLens::MouseButton button, TerraLens::MouseInput* input);

		/**
		* Selects a MouseInput that's been previously added.
		*
		* @param button Which button this is event is mapped to
		* @param index What index to select. An invalid index will
		*	result in no handling for this mouse button
		*/
		void selectMouseInput(TerraLens::MouseButton button, int index);

		/**
		* Get the count of mouse input handlers for this button.
		* 
		* @param button Which button to count inputs for
		* @return Count of input handlers for this button
		*/
		int getMouseInputCount(TerraLens::MouseButton button);

		/**
		* This method should be called by your windowing system with the appropriate
		* arguements when a mouse event happens.
		* 
		* The method will pass on the event data to the appropriate handler, if any
		* exists.
		* 
		* @param button The mouse button that has been pressed
		* @param p The current cursor location
		*/
		void onMousePress(TerraLens::MouseButton button, InterMAPhics::ScreenPoint & p);

		/**
		* This method should be called by your windowing system with the appropriate
		* arguements when a mouse event happens.
		* 
		* The method will pass on the event data to the any input handlers for any
		* mouse input handlers that are currently pressed, as well as the "No Button"
		* handler.
		*
		* @param button The mouse button that has been pressed
		* @param p The current cursor location
		*/
		void onMouseMove(InterMAPhics::ScreenPoint& p);

		/**
		* This method should be called by your windowing system with the appropriate
		* arguements when a mouse event happens.
		* 
		* The method will pass on the event data to the appropriate handler, if any
		* exists.
		*
		* @param button The mouse button that has been released
		* @param p The current cursor location
		*/
		void onMouseRelease(TerraLens::MouseButton button, InterMAPhics::ScreenPoint& p);

		/**
		* Add a KeyInput object, which handles keyboard key presses.
		*
		* @param input The input handler to add
		* @return The index for this newly added input
		*/
		int addKeyInput(TerraLens::KeyInput* input);

		/**
		* Removes a KeyInput that's been previously added.
		*
		* @param input The input handler to remove
		*/
		void removeKeyInput(TerraLens::KeyInput* input);

		/**
		* Selects a KeyInput that's been previously added.
		*
		* @param index What index to select. An invalid index will
		*	result in no handling for keyboard presses
		*/
		void selectKeyInput(int index);

		/**
		* Get the count of keyboard input handlers
		*
		* @return Count of input handlers for the keyboard
		*/
		int getKeyInputCount();

		/**
		* This method should be called by your windowing system with the appropriate
		* arguements when a key event happens.
		* 
		* The method will pass on the event data to the appropriate handler, if any
		* exists.
		*
		* @param key The keyboard key pressed
		*/
		void onKeyPress(int key);

		/**
		* This method should be called by your windowing system with the appropriate
		* arguements when a key event happens.
		*
		* The method will pass on the event data to the appropriate handler, if any
		* exists.
		*
		* @param key The keyboard key released
		*/
		void onKeyRelease(int key);

		/**
		* Add a WheelInput object, which handles mouse wheel movements.
		*
		* @param input The input handler to add
		* @return The index for this newly added input
		*/
		int addWheelInput(TerraLens::WheelInput* input);

		/**
		* Removes a WheelInput that's been previously added.
		*
		* @param input The input handler to remove
		*/
		void removeWheelInput(TerraLens::WheelInput* input);

		/**
		* Selects a WheelInput that's been previously added.
		*
		* @param button Which button this is event is mapped to
		* @param index What index to select. An invalid index will
		*	result in no handling for the mouse wheel
		*/
		void selectWheelInput(int index);

		/**
		* Get the count of wheel input handlers.
		*
		* @return Count of input handlers for the mouse wheel
		*/
		int getWheelInputCount();

		/**
		* This method should be called by your windowing system with the appropriate
		* arguements when a mouse wheel event happens.
		*
		* The method will pass on the event data to the appropriate handler, if any
		* exists.
		*
		* @param delta The direction of the mouse wheel
		*/
		void onWheel(int delta);

	private:
		bool isMousePressed[MB_MAX] = { 0 };
		int currentMouseInput[MB_MAX] = { 0 };
		std::vector<TerraLens::MouseInput*> mouseInputs[MB_MAX];

		std::vector<TerraLens::KeyInput*> keyInputs;
		int currentKeyInput = 0;
		int keyMods = 0;

		std::vector<TerraLens::WheelInput*> wheelInputs;
		int currentWheelInput = 0;
	};
}
