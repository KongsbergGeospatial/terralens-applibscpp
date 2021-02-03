#ifndef VIEWPORTITEM3D_H
#define VIEWPORTITEM3D_H

#include "TerraLens/ViewportItem.h"

namespace InterMAPhics
{
class Viewport3D;
class Camera3D;
}

namespace TerraLens
{
/**
 * The ViewportItem3D class handles displaying a TerraLens Viewport3D
 * inside of a QQuickItem.
 */
class DECLSPECIFIER ViewportItem3D : public TerraLens::ViewportItem
{

    Q_OBJECT

public:

    /**
     * Construct the ViewportItem2D object
     * @param parent Parent object
     */
    explicit ViewportItem3D( QQuickItem* parent = 0 );

    //! Destructor.
    virtual ~ViewportItem3D();
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

    /**
     * Returns a new viewport for the given OpenGL context and texture.
     * This function is called each time this item's window changes so
     * care must be taken to recreate the viewport in its entirety when
     * this function is called (including preserving state, if any).
     * @param renderer The renderer used in viewport construction
     * @return The viewport constructed
     */
    virtual InterMAPhics::Viewport* createViewport( InterMAPhics::Renderer* renderer );

    virtual void onSize(int width, int height);
    virtual void onUpdate();
private:


    //! The viewport.
    //! Note: the object is not owned by this class.
    InterMAPhics::Viewport3D* m_viewport3D = nullptr;
    std::unique_ptr<InterMAPhics::Camera3D> m_camera;


};
}
#endif // ViewportItem3D_H
