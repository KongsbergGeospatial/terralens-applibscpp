#pragma once

#include "TerraLens/QTextureViewport.h"

namespace InterMAPhics
{
	class Viewport2D;
	class Camera2D;
}

namespace TerraLens
{
    /**
     * The class constructs a QOpenGLWidget with a TerraLens Viewport 2D
     * object that uses the Texture Renderer pipeline.
     *
     * The Texture Renderer pipeline allows for Qt objects to exist over
     * the Viewport, but has more overhead than the Window Renderer.
     */
    class DECLSPECIFIER QTextureViewport2D : public QTextureViewport
	{
		Q_OBJECT

	public:
        /**
         * Construct the QTextureViewport2D object
         * @param parent Parent object
         * @param msUpdateTime How many milliseconds between viewport updates
         */
        QTextureViewport2D(QWidget* widget = nullptr, int msUpdateTimeout = 16);
        virtual ~QTextureViewport2D();

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
		virtual InterMAPhics::Viewport* buildViewport(InterMAPhics::OpenGLTextureRenderer* render);

	private:
        InterMAPhics::Viewport2D* viewport2D = nullptr;
        std::unique_ptr<InterMAPhics::Camera2D> camera;

	};
}
