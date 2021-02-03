#include "TerraLens/QWidgetViewport.h"
#include "qevent.h"

TerraLens::QWidgetViewport::QWidgetViewport(QWidget* parent, int msUpdateTime)
    : QWidget(parent)
{
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(updateView()));
    m_timer.setInterval(msUpdateTime);
    m_timer.start();

    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute( Qt::WA_DeleteOnClose );
}

TerraLens::QWidgetViewport::~QWidgetViewport()
{
}

void TerraLens::QWidgetViewport::updateView()
{
    if (m_viewport)
    {
        m_viewport->updateRender();
    }
}


void TerraLens::QWidgetViewport::resizeEvent(QResizeEvent* event)
{
    if (!m_viewport) {
        m_renderer = std::make_unique<InterMAPhics::OpenGLWindowRenderer>();
        //m_renderer->setTexture( m_fbo->textur() );
        m_renderer->setWindow((void*)this->winId());
        m_renderer->setAntiAliasing(InterMAPhics::OpenGLRenderer::MSAA_2X);
        m_renderer->setFiltering(InterMAPhics::OpenGLRenderer::Anisotropic2X);

        // You need to pass a Texture Renderer to the viewport so it knows where to draw to.
        m_viewport.reset(buildViewport( m_renderer.get() ));
        onInitialization();
    }

    if (m_viewport) {
        QSize size = event->size();
        m_viewport->onSize(size.width(), size.height());
    }
}

void TerraLens::QWidgetViewport::mousePressEvent(QMouseEvent* event)
{
    InterMAPhics::ScreenPoint point = InterMAPhics::ScreenPoint(event->x(), event->y());
    if (event->button() == (Qt::MouseButton::LeftButton))
    {
        inputControl.onMousePress(TerraLens::MB_Left, point);
    }
    if (event->button() == (Qt::MouseButton::MiddleButton))
    {
        inputControl.onMousePress(TerraLens::MB_Middle, point);
    }
    if (event->button() == (Qt::MouseButton::RightButton))
    {
        inputControl.onMousePress(TerraLens::MB_Right, point);
    }
}

void TerraLens::QWidgetViewport::mouseMoveEvent(QMouseEvent* event)
{
    InterMAPhics::ScreenPoint point = InterMAPhics::ScreenPoint(event->x(), event->y());
    inputControl.onMouseMove(point);
}

void TerraLens::QWidgetViewport::mouseReleaseEvent(QMouseEvent* event)
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

void TerraLens::QWidgetViewport::keyPressEvent(QKeyEvent* event)
{
    inputControl.onKeyPress(event->nativeVirtualKey());
}
void TerraLens::QWidgetViewport::keyReleaseEvent(QKeyEvent* event)
{
    inputControl.onKeyRelease(event->nativeVirtualKey());
}
void TerraLens::QWidgetViewport::wheelEvent(QWheelEvent* event)
{
    inputControl.onWheel(event->delta());
}
