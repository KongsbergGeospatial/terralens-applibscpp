#pragma once

#include "TerraLens/QWidgetViewport.h"

namespace InterMAPhics
{
	class Viewport3D;
	class Camera3D;
}

namespace TerraLens
{
    /**
     * The class constructs a QWidget with a TerraLens Viewport 3D
     * object that uses the Window Renderer pipeline.
     *
     * The Texture Renderer pipeline allows for Qt objects to exist over
     * the Viewport, but has more overhead than the Window Renderer.
     */
    class DECLSPECIFIER QWidgetViewport3D : public QWidgetViewport
	{
		Q_OBJECT

	public:
        /**
         * Construct the QWidgetViewport object
         * @param parent Parent object
         * @param msUpdateTime How many milliseconds between viewport updates
         */
        QWidgetViewport3D(QWidget* widget = nullptr, int msUpdateTimeout = 16);
        virtual ~QWidgetViewport3D();

        /**
         * Get the TerraLens viewport object from this widget.
         * @return The viewport object
         */
        InterMAPhics::Viewport3D* getViewport();
        /**
         * Get the TerraLens camera object from this widget.
         * @return The camera object
         */
        InterMAPhics::Camera3D* getCamera();

	protected:
		virtual InterMAPhics::Viewport* buildViewport(InterMAPhics::OpenGLWindowRenderer* render);

	private:
        InterMAPhics::Viewport3D* viewport3D = nullptr;
        std::unique_ptr<InterMAPhics::Camera3D> camera;

	};
}
