#include "TerraLens/ViewportItem2D.h"

#include <QQuickItem>

#include "Viewport2D.h"
#include "Camera2D.h"
#include "Color.h"

using namespace InterMAPhics;

/*
 * This ViewportItem2D will be instantiated by the QML engine
 * when the QML file it is registered to is created.
*/
TerraLens::ViewportItem2D::ViewportItem2D( QQuickItem* parent )
    : ViewportItem( parent )
{
    setAcceptedMouseButtons( Qt::AllButtons ); // so Qt sends events to our event(QEvent) function.
}

TerraLens::ViewportItem2D::~ViewportItem2D()
{
}

InterMAPhics::Viewport2D* TerraLens::ViewportItem2D::getViewport()
{
    return m_viewport2D;
}
InterMAPhics::Camera2D* TerraLens::ViewportItem2D::getCamera()
{
    return m_camera.get();
}
InterMAPhics::Viewport* TerraLens::ViewportItem2D::createViewport( InterMAPhics::Renderer* renderer )
{
    m_viewport2D = new InterMAPhics::Viewport2D(renderer);
    m_camera = std::make_unique<InterMAPhics::Camera2D>();
    m_viewport2D->setCamera(*m_camera);

    return m_viewport2D;
}

void TerraLens::ViewportItem2D::onSize(int width, int height)
{
    if( m_viewport2D )
    {
        m_viewport2D->onSize( width, height );
    }
}
void TerraLens::ViewportItem2D::onUpdate()
{
    if( m_viewport2D)
    {
        m_mutex.lock();
        m_viewport2D->updateRender();
        m_mutex.unlock();
    }
}
