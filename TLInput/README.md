# TerraLens Input #

This is basic library for integrating mouse and keyboard input in a GUI and OS agnostic manner.

MouseInput, WheelInput and KeyInput objects are added to a InputControl object. When inputs are fed into InputControl they will be passed to the added input handlers.

Only one input handler can be used for each type of input at a time, but the current input handler can be switched at any time. When adding an input handler, that input handler's index is returned. This value is used to switch the current input handler.

The keyboard inputs should be mapped with "TerraLens/KeyCodes.h". These values will match the native virtual key values. 
