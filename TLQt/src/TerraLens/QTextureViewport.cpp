#include "TerraLens/QTextureViewport.h"
#include "OpenGLAdapter.h"

#include <qevent.h>

class QtOpenGLAdapter : public InterMAPhics::OpenGLAdapter
{
public:
    QtOpenGLAdapter(QOpenGLContext* shareContext) :
        m_surface(nullptr),
        m_context(nullptr),
        m_lastContext(nullptr)
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
        if (m_lastContext)
        {
            m_lastContext->makeCurrent(m_surface);
        }
        else
        {
            m_context->doneCurrent();
        }
        m_lastContext = nullptr;
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

TerraLens::QTextureViewport::QTextureViewport(QWidget* parent, int msUpdateTime)
    : QOpenGLWidget(parent)
{
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer.setInterval(msUpdateTime);
    m_timer.start();
}

TerraLens::InputControl& TerraLens::QTextureViewport::getInputControl()
{
    return inputControl;
}

TerraLens::QTextureViewport::~QTextureViewport()
{
    cleanup();
}

void TerraLens::QTextureViewport::cleanup()
{
    m_viewport.reset();
    m_renderer.reset();

    makeCurrent();
    {
        // Release OpenGL resources
        m_fbo.reset();
    }
    doneCurrent();
    m_adapter.reset();
}

void TerraLens::QTextureViewport::initializeGL()
{
    initializeOpenGLFunctions();
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &TerraLens::QTextureViewport::cleanup);
}

void TerraLens::QTextureViewport::paintGL()
{
    if (m_viewport) {
        m_viewport->updateRender();
    }

    // Restore Qt context
    makeCurrent();

    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, m_fbo->texture());

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glColor4f(1.f, 1.f, 1.f, 1.f);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1); glVertex2f(-1, -1);
    glTexCoord2f(1, 1); glVertex2f(1, -1);
    glTexCoord2f(1, 0); glVertex2f(1, 1);
    glTexCoord2f(0, 0); glVertex2f(-1, 1);
    glEnd();

}

void TerraLens::QTextureViewport::resizeGL(int w, int h)
{
    if (!m_fbo) {
        m_fbo = std::make_unique<QOpenGLFramebufferObject>(w, h);
        if (m_fbo->isValid()) {
            m_fbo->bind();
            glClearColor(.5f, .5f, .5f, 1.f);
            glClear(GL_COLOR_BUFFER_BIT);
            m_fbo->release();
        }
    }

    if (!m_viewport) {
        m_adapter = std::make_unique<QtOpenGLAdapter>(context());

        m_renderer = std::make_unique<InterMAPhics::OpenGLTextureRenderer>(m_adapter.get());
        m_renderer->setTexture(m_fbo->texture());

        // You need to pass a Texture Renderer to the viewport so it knows where to draw to.
        m_viewport.reset(buildViewport( m_renderer.get() ));
        onInitialization();
    }

    if (m_viewport) {
        m_viewport->onSize(w, h);
    }
}

void TerraLens::QTextureViewport::mousePressEvent(QMouseEvent* event)
{
    InterMAPhics::ScreenPoint point = InterMAPhics::ScreenPoint(event->x(), event->y());
    Qt::MouseButtons buttons = event->buttons();
    if (buttons.testFlag(Qt::MouseButton::LeftButton))
    {
        inputControl.onMousePress(TerraLens::MB_Left, point);
    }
    if (buttons.testFlag(Qt::MouseButton::MiddleButton))
    {
        inputControl.onMousePress(TerraLens::MB_Middle, point);
    }
    if (buttons.testFlag(Qt::MouseButton::RightButton))
    {
        inputControl.onMousePress(TerraLens::MB_Right, point);
    }
}

void TerraLens::QTextureViewport::mouseMoveEvent(QMouseEvent* event)
{
    InterMAPhics::ScreenPoint point = InterMAPhics::ScreenPoint(event->x(), event->y());
    inputControl.onMouseMove(point);
}

void TerraLens::QTextureViewport::mouseReleaseEvent(QMouseEvent* event)
{
    InterMAPhics::ScreenPoint point = InterMAPhics::ScreenPoint(event->x(), event->y());
    if (event->button() == (Qt::MouseButton::LeftButton))
    {
        inputControl.onMouseRelease(TerraLens::MB_Left, point);
    }
    if (event->button() == (Qt::MouseButton::MiddleButton))
    {
        inputControl.onMouseRelease(TerraLens::MB_Middle, point);
    }
    if (event->button() == (Qt::MouseButton::RightButton))
    {
        inputControl.onMouseRelease(TerraLens::MB_Right, point);
    }
}

void TerraLens::QTextureViewport::keyPressEvent(QKeyEvent* event)
{
    inputControl.onKeyPress(event->nativeVirtualKey());
}
void TerraLens::QTextureViewport::keyReleaseEvent(QKeyEvent* event)
{
    inputControl.onKeyRelease(event->nativeVirtualKey());
}
void TerraLens::QTextureViewport::wheelEvent(QWheelEvent* event)
{
    inputControl.onWheel(event->delta());
}
