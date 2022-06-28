import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
import PaintedItem 1.0
Window {
    id:root
    width: 840
    height: 880
    visible: true
    title: qsTr("Hello World")

    property int mode //0:none 1:draw 2:clear
    property point pre_point: Qt.point(0,0)
    Image {
        id: customCusor
        source: "qrc:/pen.png"
        width: 28
        height: 33
        z:3
        visible: false//root.mode===0?false:(root.mode===2?false:true)
    }

    Flickable {
        id:flick
        anchors.fill: parent
        //------------很重要,保证底图边界能正常显示
        contentWidth: Math.max(painter.width * painter.scale, root.width)
        contentHeight: Math.max(painter.height * painter.scale, root.height)
        clip: true
        //-----------------------------------------------------------------------------

        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.NoButton
            propagateComposedEvents: true
            PaintedItem{
                id:painter
                property real zoom: 0.0
                property real zoomStep: 0.1

                width:800
                height: 830
                smooth: true
                antialiasing: true
                anchors.centerIn: parent //重要设置，不然拖动平移会出问题
                transformOrigin: Item.Center //重要设置，不然拖动平移会出问题
                scale: Math.min(root.width / width, root.height / height, 1) + zoom
                MouseArea{
                    id:draw_mousearea
                    anchors.fill: parent
                    //cursorShape: pressed?Qt.BlankCursor:Qt.ArrowCursor
                    propagateComposedEvents: true
                    onPressed: {
                        if(root.mode===0)
                        {
                            console.log("0")
                        }
                        else if(root.mode===1)
                        {   console.log("1")
                            pre_point = Qt.point(mouse.x,mouse.y)
                        }
                        else if(root.mode===2)
                        {
                            console.log("2")
                            painter.eraserArea(mouse.x,mouse.y,30,30)
                        }
                    }
                    onPositionChanged:
                    {
                        if(root.mode===0)
                        {

                        }
                        else if(root.mode===1)
                        {
                            console.log("draw")
                            painter.drawLine(pre_point,Qt.point(mouse.x,mouse.y))
                            pre_point = Qt.point(mouse.x,mouse.y)
                        }
                        else if(root.mode===2)
                        {
                            painter.eraserArea(mouse.x,mouse.y,30,30)
                        }
                    }

                    onReleased:
                    {
                        if(root.mode===0)
                        {

                        }
                        else if(root.mode===1)
                        {
                            painter.drawLine(pre_point,Qt.point(mouse.x,mouse.y))
                            painter.cachePixmap()

                        }
                        else if(root.mode===2)
                        {
                            painter.cachePixmap()
                        }
                    }
                }
            }

            onWheel: {
                if (wheel.angleDelta.y > 0)
                    painter.zoom = Number((painter.zoom + painter.zoomStep).toFixed(1))
                else
                    if (painter.zoom > 0) painter.zoom = Number((painter.zoom - painter.zoomStep).toFixed(1))

                wheel.accepted=true
            }
        }
    }

    Button{
        id:save
        width:60
        height: 40
        x:760
        text: "save"
        onClicked: {
            modetip.text="已保存"
            painter.saveMap()
            root.mode=0
            flick.interactive=true
        }
    }

    Button{
        id:draw
        width:60
        height: 40
        anchors.right: save.left
        text: "draw"
        onClicked: {
            modetip.text="绘图模式"
            root.mode= 1
            flick.interactive=false
        }
    }

    Button{
        id:clear
        width:60
        height: 40
        anchors.right: draw.left
        text: "clear"
        onClicked: {
            modetip.text="擦除模式"
            root.mode=2
            flick.interactive=false
        }
    }
    Button{
        id:undo
        width:60
        height: 40
        anchors.right: clear.left
        text: "undo"
        onClicked: painter.undoDraw()
    }

    Button{
        id:redo
        width:60
        height: 40
        anchors.right: undo.left
        text: "redo"
        onClicked: painter.redoDraw()
    }
    Text {
        id: modetip
        text: "绘制模式"
        width: 80
        height:40
        anchors.right: redo.left
        font.pixelSize: 15
        color:"white"
    }
    //                        customCusor.x = (mouse.x - customCusor.width/2+10)
    //                        customCusor.y = (mouse.y - customCusor.height/2-10)
    //                        customCusor.x = mouse.x*scale
    //                        customCusor.y = mouse.y*scale
    //                        console.log("Cusor xy",customCusor.x,customCusor.y)
    //                        console.log("mouse xy",mouse.x,mouse.y)

    //Component.onCompleted: painter.setLines()
}
