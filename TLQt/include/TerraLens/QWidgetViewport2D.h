#pragma once

#include "TerraLens/QWidgetViewport.h"

namespace InterMAPhics
{
	class Viewport2D;
	class Camera2D;
}

namespace TerraLens
{
    /**
     * The class constructs a QWidget with a TerraLens Viewport 2D
     * object that uses the Window Renderer pipeline.
     *
     * The Texture Renderer pipeline allows for Qt objects to exist over
     * the Viewport, but has more overhead than the Window Renderer.
     */
    class DECLSPECIFIER QWidgetViewport2D : public QWidgetViewport
	{
		Q_OBJECT

	public:
        /**
         * Construct the QWidgetViewport object
         * @param parent Parent object
         * @param msUpdateTime How many milliseconds between viewport updates
         */
        QWidgetViewport2D(QWidget* widget = nullptr, int msUpdateTimeout = 16);
        virtual ~QWidgetViewport2D();

        /**
         * Get the TerraLens viewport object from this widget.
         * @return The viewport object
         */
        InterMAPhics::Viewport2D* getViewport();
        /**
         * Get the TerraLens camera object from this widget.
         * @return The camera object
         */
        InterMAPhics::Camera2D* getCamera();

	protected:
		virtual InterMAPhics::Viewport* buildViewport(InterMAPhics::OpenGLWindowRenderer* render);

	private:
        InterMAPhics::Viewport2D* viewport2D = nullptr;
        std::unique_ptr<InterMAPhics::Camera2D> camera;

	};
}
