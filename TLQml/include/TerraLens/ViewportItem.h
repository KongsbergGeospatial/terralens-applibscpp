#ifndef VIEWPORTITEM_H
#define VIEWPORTITEM_H

#include <QQuickItem>
#include <QQuickWindow>
#include <QTimer>
#include <QMutex>

#include <TerraLens/InputControl.h>

#include <memory>

class QTimer;
class QSGTexture;
class QQuickCloseEvent;

namespace InterMAPhics
{
    class OpenGLTextureRenderer;
    class Renderer;
    class Viewport;
}

class QtOpenGLAdapter;

#include <QtCore/QtGlobal>

namespace TerraLens
{
/**
 * The ViewportItem class is an abstract class for displaying a TerraLens Viewport
 * inside of a QQuickItem.
 */
class DECLSPECIFIER ViewportItem : public QQuickItem
{

    Q_OBJECT

public:

    /**
    * Constructor.
    * @param parent The parent item.
    */
    explicit ViewportItem( QQuickItem* parent = nullptr );

    //! Destructor.
    virtual ~ViewportItem();

    /**
    *  Returns the update interval. This controls how often the TerraLens viewport
    *  updates and renders
    *  The default update interval is 16 milliseconds.
    *
    *   @return The update interval.
    */
    int updateInterval() const;

    /**
    * Sets the update interval. This controls how often the TerraLens viewport
    * updates and renders
    * The default update interval is 16 milliseconds.
    *
    *   @param The interval in milliseconds.
    */
    void setUpdateInterval( int interval );

    /**
      *Filters the given event destined for the given object,
      * @param object The object.
      * @param event The event.
      * @return True if the event was filtered, false otherwise.
    */
    virtual bool eventFilter( QObject* object, QEvent* event );

    /**
     * Invoked from the Qml template, this passes the mouse events to the InputControl
     * object
     *
     * @param x Mouse X position
     * @param y Mouse Y position
     * @param type Current Mouse Action (ex. Pressed, Moved, Released)
     * @param buttons What mouse buttons are in this event
     */
    Q_INVOKABLE void onVMouse(qreal x, qreal y, int type, Qt::MouseButtons buttons);

    /**
     * Return the input control object for this widget.
     * Add KeyInput, MouseInput, and WheelInput objects to this object
     * to handle input events.
     * @return The input control object
     */
    TerraLens::InputControl & getInputControl();

protected:
    /**
     * An empty function to be overriden. This will get called after the viewport is first
     * constructed.
     */
    virtual void onInitialization() {};

protected:

    //! Returns a new viewport for the given Renderer.
    /*!
        \param[in] renderer The renderer.
        \return The viewport.
    */
    virtual InterMAPhics::Viewport* createViewport( InterMAPhics::Renderer* renderer ) = 0;

    void sceneGraphError(QQuickWindow::SceneGraphError error, const QString & message);

    //! Invoked by the rendering thread as a result of a call to update().
    /*!
        \param[in] oldNode The node returned the last time the function was called.
        \param[in] updatePaintNodeData The transformation node associated with this item.
        \return The root of the scene graph subtree for this item.
    */
    virtual QSGNode* updatePaintNode( QSGNode* oldNode, UpdatePaintNodeData* updatePaintNodeData );

    virtual void onSize(int width, int height);
    virtual void onUpdate() = 0;

Q_SIGNALS:

    //! Signal to emit to cause the viewport to be updated (switches to the correct thread).
    void updateViewport();
    //! Signal to emit to cause the viewport to be destroyed (switches to the correct thread).
    void destroyViewport();


public Q_SLOTS:

    //! Initializes the viewport and moves its context to the correct thread.
    void onViewportInit();
    //! Deletes various viewport objects when no longer needed.
    void onViewportFini();
    //! Updates the viewport.
    void onViewportUpdate();

protected:

    std::unique_ptr<InterMAPhics::Viewport> m_viewport;                 //!< The viewport.
    QMutex m_mutex;


private:

    //! Invoked when the item's window has changed.
    /*!
        \param[in] window The window.
    */
    void onWindowChanged( QQuickWindow* window );

    int m_width;                                        //!< The width.
    int m_height;                                       //!< The height.
    std::unique_ptr<InterMAPhics::OpenGLTextureRenderer> m_renderer;    //!< The renderer.
    std::unique_ptr<QtOpenGLAdapter> m_adapter;                         //! The OpenGL context adapter.
    unsigned int m_textureId;                           //!< The texture identifier.
    QTimer m_updateTimer;                               //!< The update timer.

    TerraLens::InputControl inputControl;
};
}
#endif // VIEWPORTITEM_H
