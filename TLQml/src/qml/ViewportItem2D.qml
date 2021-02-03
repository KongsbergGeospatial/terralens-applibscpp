import QtQuick 2.2
import ViewportItem2D 1.0

Item
{
    id: mainItem2D

    ViewportItem2D
    {
        id: viewport
        anchors.fill: parent

        MouseArea
        {
            acceptedButtons: Qt.LeftButton | Qt.MiddleButton | Qt.RightButton

            anchors.fill: parent
            onPressed: viewport.onVMouse(mouseX, mouseY, 1, pressedButtons)
            onPositionChanged: viewport.onVMouse(mouseX, mouseY, 2, pressedButtons)
            onReleased: viewport.onVMouse(mouseX, mouseY, 3, pressedButtons)
        }
    }
}
