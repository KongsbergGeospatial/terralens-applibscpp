#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLFramebufferObject>
#include <QTimer>

#include "Viewport.h"
#include "OpenGLTextureRenderer.h"

#include "TerraLens/InputControl.h"

#include <memory>

namespace TerraLens
{
    /**
     * The QTextureViewport class is an abstract class for creating a QOpenGLWidget with
     * a TerraLens Viewport that uses the Texture Renderer pipeline.
     *
     * The Texture Renderer pipeline allows for Qt objects to exist over
     * the Viewport, but has more overhead than the Window Renderer.
     */
    class DECLSPECIFIER QTextureViewport : public QOpenGLWidget, protected QOpenGLFunctions
    {
        Q_OBJECT

    public:
        /**
         * Construct the QTextureViewport object
         * @param parent Parent object
         * @param msUpdateTime How many milliseconds between viewport updates
         */
        QTextureViewport(QWidget* parent = nullptr, int msUpdateTime = 16);
        virtual ~QTextureViewport();

        /**
         * Return the input control object for this widget.
         * Add KeyInput, MouseInput, and WheelInput objects to this object
         * to handle input events.
         * @return The input control object
         */
        TerraLens::InputControl& getInputControl();

        QSize minimumSizeHint() const Q_DECL_OVERRIDE { return QSize(640, 480); }
        QSize sizeHint() const Q_DECL_OVERRIDE { return QSize(640, 480); }

    protected:
        /**
         * An empty function to be overriden. This will get called after the viewport is first
         * constructed.
         */
        virtual void onInitialization() {}

    protected:
        /**
         * This function needs to be overrided to construct the appropriate viewport type (2D or 3D).
         * This will get called internally when the viewport is ready to construct.
         * @param render Texture Renderer object for viewport object constructor
         * @return The viewport object
         */
        virtual InterMAPhics::Viewport* buildViewport(InterMAPhics::OpenGLTextureRenderer* render) = 0;

    public slots:
        void cleanup();

    protected:
        void initializeGL() Q_DECL_OVERRIDE;
        void paintGL() Q_DECL_OVERRIDE;
        void resizeGL(int width, int height) Q_DECL_OVERRIDE;
        void keyPressEvent(QKeyEvent* event) Q_DECL_OVERRIDE;
        void keyReleaseEvent(QKeyEvent* event) Q_DECL_OVERRIDE;

        void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
        void mouseMoveEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
        void mouseReleaseEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
        void wheelEvent(QWheelEvent* event) Q_DECL_OVERRIDE;

        TerraLens::InputControl inputControl;

    private:
        std::unique_ptr<QOpenGLFramebufferObject> m_fbo;
        std::unique_ptr<InterMAPhics::OpenGLTextureRenderer> m_renderer;
        std::unique_ptr<InterMAPhics::OpenGLAdapter> m_adapter;
        std::unique_ptr<InterMAPhics::Viewport> m_viewport;
        QTimer m_timer;
    };
}
