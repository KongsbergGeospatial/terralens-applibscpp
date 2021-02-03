#pragma once

#include "TerraLens/QTextureViewport.h"

namespace InterMAPhics
{
	class Viewport3D;
	class Camera3D;
}

namespace TerraLens
{
    /**
     * The class constructs a QOpenGLWidget with a TerraLens Viewport 3D
     * object that uses the Texture Renderer pipeline.
     *
     * The Texture Renderer pipeline allows for Qt objects to exist over
     * the Viewport, but has more overhead than the Window Renderer.
     */
    class DECLSPECIFIER QTextureViewport3D : public QTextureViewport
	{
		Q_OBJECT

	public:
        /**
         * Construct the QTextureViewport object
         * @param parent Parent object
         * @param msUpdateTime How many milliseconds between viewport updates
         */
        QTextureViewport3D(QWidget* widget = nullptr, int msUpdateTimeout = 16);
        virtual ~QTextureViewport3D();

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
		virtual InterMAPhics::Viewport* buildViewport(InterMAPhics::OpenGLTextureRenderer* render);

	private:
        InterMAPhics::Viewport3D* viewport3D = nullptr;
        std::unique_ptr<InterMAPhics::Camera3D> camera;

	};
}
