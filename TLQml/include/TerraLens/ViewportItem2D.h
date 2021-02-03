#ifndef VIEWPORTITEM2D_H
#define VIEWPORTITEM2D_H

#include "TerraLens/ViewportItem.h"

namespace InterMAPhics
{
class Viewport2D;
class Camera2D;
}

namespace TerraLens
{
/**
 * The ViewportItem2D class handles displaying a TerraLens Viewport2D
 * inside of a QQuickItem.
 */
class DECLSPECIFIER ViewportItem2D : public ViewportItem
{

    Q_OBJECT

public:

    /**
     * Construct the ViewportItem2D object
     * @param parent Parent object
     */
    explicit ViewportItem2D( QQuickItem* parent = nullptr );

    //! Destructor.
    virtual ~ViewportItem2D();

    /**
     * Get the TerraLens viewport object from this widget.
     * @return The viewport object
     */
    InterMAPhics::Viewport2D* getViewport();
    /**
     * Get the TerraLens camera object from this widget.
     * @return The camera object
     */
    InterMAPhics::Camera2D* getCamera();

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
    InterMAPhics::Viewport2D* m_viewport2D = nullptr;
    std::unique_ptr<InterMAPhics::Camera2D> m_camera;


};
}
#endif // ViewportItem2D_H
