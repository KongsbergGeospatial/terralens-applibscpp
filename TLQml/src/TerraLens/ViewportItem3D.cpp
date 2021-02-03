#include "TerraLens/ViewportItem3D.h"

#include <QQuickItem>

#include "Viewport3D.h"
#include "Camera3D.h"


using namespace InterMAPhics;

/*
 * This ViewportItem3D will be instantiated by the QML engine
 * when the QML file it is registered to is created.
*/
TerraLens::ViewportItem3D::ViewportItem3D( QQuickItem* parent )
    : ViewportItem( parent )
{
    setAcceptedMouseButtons( Qt::AllButtons ); // so Qt sends events to our event(QEvent) function.
}

TerraLens::ViewportItem3D::~ViewportItem3D()
{
}

InterMAPhics::Viewport3D* TerraLens::ViewportItem3D::getViewport()
{
    return m_viewport3D;
}
InterMAPhics::Camera3D* TerraLens::ViewportItem3D::getCamera()
{
    return m_camera.get();
}
InterMAPhics::Viewport* TerraLens::ViewportItem3D::createViewport( InterMAPhics::Renderer* renderer )
{
    m_viewport3D = new InterMAPhics::Viewport3D(renderer);
    m_camera = std::make_unique<InterMAPhics::Camera3D>();
    m_viewport3D->setCamera(*m_camera);

    return m_viewport3D;
}

void TerraLens::ViewportItem3D::onSize(int width, int height)
{
    if( m_viewport3D )
    {
        m_viewport3D->onSize( width, height );
    }
}
void TerraLens::ViewportItem3D::onUpdate()
{
    if( m_viewport3D)
    {
        m_mutex.lock();
        m_viewport3D->updateRender();
        m_mutex.unlock();
    }
}
