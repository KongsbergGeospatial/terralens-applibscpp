
#include "TerraLens/ViewportItem.h"

#include <qpa/qplatformnativeinterface.h>
#include <QGuiApplication>
#include <QSurface>
#include <QOpenGLContext>
#include <QSGSimpleTextureNode>
#include <QThread>
//#include <QOpenGLFunctions>
// InterMAPhics
#include <OpenGLTextureRenderer.h>
#include <Viewport.h>
#include <Trace.h>

using namespace InterMAPhics;

namespace
{
    //! Returns the native OpenGL context for the given QOpenGLContext.
    /*!
        \param[in] context The QOpenGLContext.
        \return The native OpenGL context.
    */
    void* nativeContextForContext( QOpenGLContext* context )
    {
        QPlatformNativeInterface* platformNativeInterface = QGuiApplication::platformNativeInterface();

        #ifdef Q_OS_WIN32
            return platformNativeInterface->nativeResourceForContext( "renderingContext", context );
        #endif
        #ifdef Q_OS_WIN64
            return platformNativeInterface->nativeResourceForContext( "renderingContext", context );
        #endif
        #ifdef Q_OS_LINUX
            return platformNativeInterface->nativeResourceForContext( "glxContext", context );
        #endif

        return 0;
    }
}

// Adapter class
class QtOpenGLAdapter : public InterMAPhics::OpenGLAdapter
{
public:
    QtOpenGLAdapter(QOpenGLContext* shareContext):
        m_context(0),
        m_lastContext(0)
    {
        m_surface = shareContext->surface();
        m_context = new QOpenGLContext();
        m_context->setFormat(shareContext->format());
        m_context->setShareContext(shareContext);
        m_context->create();
    }

    virtual ~QtOpenGLAdapter()
    {
        delete m_context;
    }

    bool makeCurrent()
    {
        // Enable the context prior to making any OpenGL calls
        m_lastContext = m_context->currentContext();
        return m_context->makeCurrent(m_surface);
    }

    void doneCurrent()
    {
        if(m_lastContext)
        {
            m_lastContext->makeCurrent(m_surface);
        }
        else
        {
            m_context->doneCurrent();
        }
        m_lastContext = 0;
    }

    QOpenGLContext* context()
    {
        return m_context;
    }

private:
    QSurface* m_surface;
    QOpenGLContext* m_context;
    QOpenGLContext* m_lastContext;
};

TerraLens::ViewportItem::ViewportItem( QQuickItem* parent ) :
    QQuickItem( parent ),
    m_width( 0 ),
    m_height( 0 ),
    m_textureId( 0 )
{
    setFlag( ItemHasContents );

    connect( this, &QQuickItem::windowChanged, this, &TerraLens::ViewportItem::onWindowChanged );
    connect( &m_updateTimer, &QTimer::timeout, this, &TerraLens::ViewportItem::update );
    setUpdateInterval( 16 );
}

TerraLens::ViewportItem::~ViewportItem()
{
}

int TerraLens::ViewportItem::updateInterval() const
{
    return m_updateTimer.interval();
}

void TerraLens::ViewportItem::setUpdateInterval( int interval )
{
    m_updateTimer.setInterval( interval );
    if( !m_updateTimer.isActive() )
    {
        m_updateTimer.start();
    }
}

void TerraLens::ViewportItem::onVMouse(qreal x, qreal y, int type, Qt::MouseButtons buttons)
{
    std::vector<TerraLens::MouseButton> tlbuttons;
    ScreenPoint point = ScreenPoint(x,y);
    if ((buttons&Qt::MouseButton::LeftButton))
    {
        tlbuttons.push_back(TerraLens::MB_Left);
    }
    if ((buttons&Qt::MouseButton::MiddleButton))
    {
        tlbuttons.push_back(TerraLens::MB_Middle);
    }
    if ((buttons&Qt::MouseButton::RightButton))
    {
        tlbuttons.push_back(TerraLens::MB_Right);
    }
    if (buttons == Qt::MouseButton::NoButton)
    {
        tlbuttons.push_back(TerraLens::MB_None);
    }
    for (int b = 0; b < (int)tlbuttons.size(); ++b)
    {
        switch(type)
        {
        case 1: inputControl.onMousePress(tlbuttons[b], point); break;
        case 3: inputControl.onMouseRelease(tlbuttons[b], point); break;
        default:break;
        }
    }
    if (type == 2)
    {
        inputControl.onMouseMove(point);
    }
}

bool TerraLens::ViewportItem::eventFilter( QObject* object, QEvent* event )
{
    if( object == window() && event->type() == QEvent::Close )
    {
        destroyViewport();
    }
    if ( isVisible() )
    {
        if ( event->type() == QEvent::KeyPress )
        {
            QKeyEvent* keyEvent = dynamic_cast< QKeyEvent* >( event);
            if ( keyEvent )
            {
                inputControl.onKeyPress(keyEvent->nativeVirtualKey());
            }
        }
        else if ( event->type() == QEvent::KeyRelease )
        {
            QKeyEvent* keyEvent = dynamic_cast< QKeyEvent* >( event);
            if ( keyEvent )
            {
                inputControl.onKeyRelease(keyEvent->nativeVirtualKey());
            }
        }
        else if (event->type() == QEvent::Wheel)
        {
            QWheelEvent* wheelEvent = dynamic_cast< QWheelEvent* >(event);
            if (wheelEvent)
            {
                inputControl.onWheel(wheelEvent->delta());
            }
        }
    }
    return QQuickItem::eventFilter( object, event );
}

void TerraLens::ViewportItem::onWindowChanged( QQuickWindow* window )
{
    if( window )
    {
        window->installEventFilter( this );

        // "The sceneGraphInitialized() signal is emitted on the rendering thread before the QML scene is rendered to
        //  the screen for the first time. If the rendering scene graph has been released, the signal will be
        //  emitted again before the next frame is rendered."
        // "The QQuickWindow::sceneGraphInitialized() signal is emitted when a new OpenGL context is created for this window.
        //  Make a Qt::DirectConnection to these signals to be notified."
        // "This signal will be emitted from the scene graph rendering thread."

        connect( window, SIGNAL(sceneGraphInitialized()), this, SLOT(onViewportInit()), Qt::DirectConnection );
        // Set up callbacks needed in order to execute on the correct thread.
        connect( window, SIGNAL(sceneGraphInvalidated()), this, SLOT(onViewportFini()), Qt::QueuedConnection );
        connect( this,   SIGNAL(destroyViewport()),       this, SLOT(onViewportFini()), Qt::QueuedConnection );
        connect( this,   SIGNAL(updateViewport()),        this, SLOT(onViewportUpdate()), Qt::QueuedConnection );

        connect( window, &QQuickWindow::sceneGraphError, this, &TerraLens::ViewportItem::sceneGraphError );
    }
}

void TerraLens::ViewportItem::sceneGraphError(QQuickWindow::SceneGraphError , const QString & message)
{
    qDebug() << message;
}

QSGNode* TerraLens::ViewportItem::updatePaintNode( QSGNode* oldNode, UpdatePaintNodeData* updatePaintNodeData )
{
    Q_UNUSED( updatePaintNodeData );

    QSGSimpleTextureNode* node = 0;

    if( width() > 0 && height() > 0 )
    {
        if( !oldNode )
        {
            node = new QSGSimpleTextureNode;
        }
        else
        {
            node = static_cast< QSGSimpleTextureNode* >( oldNode );
        }

        // Trigger the viewport update
        updateViewport();

        // Always mark dirty, since Qt can't detect the texture change itself
        node->markDirty(QSGNode::DirtyMaterial);

        if( !node->texture() )
        {
            node->setTexture( window()->createTextureFromId( m_textureId, QSize() ) );
        }
        node->setRect( boundingRect() );
    }

    return node;
}


void TerraLens::ViewportItem::onViewportInit()
{
    if(!m_adapter)
    {
        // Create a context for InterMAPhics shared with Qt's context
        QOpenGLContext* shareContext =  window()->openglContext();
        m_adapter = std::make_unique<QtOpenGLAdapter>(shareContext);

        // Create a shared texture
        m_adapter->makeCurrent();
        glGenTextures( 1, &m_textureId );
        m_adapter->doneCurrent();

        // Move to UI thread for updates
        m_adapter->context()->moveToThread(QGuiApplication::instance()->thread());
    }
}

void TerraLens::ViewportItem::onViewportFini()
{
    m_viewport.reset();
    m_renderer.reset();
    m_adapter.reset();

    m_width = 0;
    m_height = 0;

    m_updateTimer.stop();
}

void TerraLens::ViewportItem::onViewportUpdate()
{
    InterMAPhics::TraceEvent("OnViewportUpdate");
    if(!m_viewport && this->isVisible())
    {
        if(!m_renderer) {
            m_renderer = std::make_unique<InterMAPhics::OpenGLTextureRenderer>(m_adapter.get());
        }
        m_renderer->setTexture(m_textureId);
        m_viewport.reset(createViewport( m_renderer.get() ));
        onInitialization();
    }
    if(m_viewport)
    {
        m_viewport->lock();
        if(m_width != width() || m_height != height())
        {
            m_width = width();
            m_height = height();
            onSize( m_width, m_height );
        }
        onUpdate();
        m_viewport->unlock();
    }
}

void TerraLens::ViewportItem::onSize( int width, int height )
{
    if( m_viewport )
    {
        m_viewport->onSize( width, height );
    }
}

TerraLens::InputControl & TerraLens::ViewportItem::getInputControl()
{
    return inputControl;
}
