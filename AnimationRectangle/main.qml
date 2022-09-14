import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    width: 1000
    height: 515
    visible: true
    title: qsTr("Hello World")

    property real lastX:100
    property real lastY:10

    property real curX:100
    property real curY:10
    property int timer_speed: 10
    property int timer_count: 0
    property int line_width: 3
    property int radius: 1
    Canvas{
        id:root
        anchors.fill: parent
        onPaint: {
            var ctx = getContext('2d')
            ctx.lineWidth = line_width
            ctx.strokeStyle = "red"
            ctx.beginPath()
            //ctx.arc(line_width - radius, 100 - radius, radius, 0, Math.PI / 2);
            ctx.moveTo(lastX, lastY)
            lastX = curX
            lastY = curY
            ctx.lineTo(lastX, lastY)
            ctx.stroke()
        }



    }
    Timer{
        id:timer1
        interval: timer_speed
        triggeredOnStart: false
        repeat: true
        onTriggered:
        {
            curX+=1
           timer_count++
            root.requestPaint()
            if(timer_count>=100)
            {
                timer_count=0


                 timer1.stop()
                timer2.start()
            }

        }
    }

    Timer{
        id:timer2
        interval: timer_speed
        triggeredOnStart: false
        repeat: true
        onTriggered:
        {
            curY+=1
           timer_count++
            root.requestPaint()
            if(timer_count>=100)
            {
                timer_count=0
                 timer2.stop()
                timer3.start()
            }

        }
    }
    Timer{
        id:timer3
        interval: timer_speed
        triggeredOnStart: false
        repeat: true
        onTriggered:
        {
            curX-=1
           timer_count++
            root.requestPaint()
            if(timer_count>=100)
            {
                timer_count=0
                 timer3.stop()
                timer4.start()
            }

        }
    }
    Timer{
        id:timer4
        interval: timer_speed
        triggeredOnStart: false
        repeat: true
        onTriggered:
        {
            curY-=1
           timer_count++
            root.requestPaint()
            if(timer_count>=100)
            {
                timer_count=0
                 timer4.stop()
            }

        }
    }

    AnimatedImage{
        id:animage
        anchors.fill: parent
        source:"qrc:/record_map1.gif"

        onFrameChanged:
        {
            console.log(animage.currentFrame,frameCount)
            if(currentFrame===frameCount-1)
                paused = true
        }

    }

    Component.onCompleted: {

        timer1.start()
    }
}
