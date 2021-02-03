#pragma once

#include <QWidget>
#include <QTimer>
#include "TerraLens/InputControl.h"

#include "Viewport.h"
#include "OpenGLWindowRenderer.h"

#include <memory>

namespace TerraLens
{
/**
 * The QWidgetViewport class is an abstract class for creating a QWidget with
 * a TerraLens Viewport that uses the Window Renderer pipeline.
 *
 * The Texture Renderer pipeline allows for Qt objects to exist over
 * the Viewport, but has more overhead than the Window Renderer.
 */
class DECLSPECIFIER QWidgetViewport : public QWidget
{
    Q_OBJECT

public:
    /**
     * Construct the QWidgetViewport object
     * @param parent Parent object
     * @param msUpdateTime How many milliseconds between viewport updates
     */
    QWidgetViewport(QWidget* parent = nullptr, int msUpdateTimeout = 16);
    virtual ~QWidgetViewport();

    QSize minimumSizeHint() const Q_DECL_OVERRIDE { return QSize(640, 480); }
    QSize sizeHint() const Q_DECL_OVERRIDE { return QSize(640, 480); }

public slots:
    void updateView();

protected:
    void resizeEvent(QResizeEvent* event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent* event) Q_DECL_OVERRIDE;
    void keyReleaseEvent(QKeyEvent* event) Q_DECL_OVERRIDE;


    void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent* event) Q_DECL_OVERRIDE;

    TerraLens::InputControl inputControl;
    virtual InterMAPhics::Viewport* buildViewport(InterMAPhics::OpenGLWindowRenderer* render) = 0;
    virtual void onInitialization() {};

private:
    std::unique_ptr<InterMAPhics::OpenGLWindowRenderer> m_renderer;
    std::unique_ptr<InterMAPhics::Viewport> m_viewport;
    QTimer m_timer;
};
}
