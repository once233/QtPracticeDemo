import QtQuick 2.15
import QtQuick.Window 2.15

Item  {
    width: 640
    height: 480
    visible: true
    property int color_r: 100

    Rectangle{
        id:rect
        width: 400
        height: 400
        color:"black"



        PinchArea {
            anchors.fill: parent
            pinch.target: rect
            pinch.minimumRotation: 0
            pinch.maximumRotation: 0


            pinch.minimumScale: 0.1
            pinch.maximumScale: 10
            pinch.dragAxis: Pinch.XAndYAxis


            onSmartZoom: {
                if (pinch.scale > 0) {


                   rect.color = Qt.rgba(color_r,100,100)
                    color_r+=20


                } else {
                    rect.color = Qt.rgba(color_r,100,100)
                     color_r-=20
                }
            }

            MouseArea
            {
                anchors.fill:parent
                drag.target: rect


                onDoubleClicked:
                {
                    rect.color = "green"
                }

                onPressAndHold:
                {
                    rect.color = "white"
                }
            }
        }

    }
}
