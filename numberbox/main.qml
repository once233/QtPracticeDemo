import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    id:numberboxRect
    width: 100
    height: 30
    visible: true
    title: qsTr("Hello World")

    property int number: 0
    Rectangle
    {

        id:numberbox
        anchors.fill: parent
        border.color: "#DEE4FF"
        border.width: 1
        radius: 5
        Rectangle{
            id:subbuttom
            x:0
            y:0
            width: parent.width/4
            height:parent.height
            color: "#FFFFFF"
            border.color: "#DEE4FF"
            border.width: 1
            radius: 5
            Image {
                id: subimage
                source: "qrc:/sy_list_jian.png"
                anchors.centerIn:  parent
            }
            MouseArea
            {
                id:subbuttomArea
                anchors.fill: parent
                onClicked:
                {
                    if(number>0)
                    numberboxRect.number--
                }

            }
        }

        Rectangle
        {
            id:numbershow
            //anchors.left: subbuttom.right
            width: parent.width/2+6
            height:parent.height
            x:subbuttom.width-3

            z:1
            border.width: 1
            border.color: "#DEE4FF"

            Text {
                id: numbertext
                text: number
                anchors.centerIn:  parent
                color:"#8383A1"
                font.pixelSize: 20
                font.family: "Source Han Sans CN-Normal"
                font.styleName: "Normal"
            }

        }

        Rectangle{
            id:addbuttom

            width: parent.width/4
            height:parent.height
            color:"#FFFFFF"
            border.color: "#DEE4FF"
            border.width: 1
            x:numberbox.width/2+subbuttom.width
            radius: 5
            Image {
                id: addimage
                source: "qrc:/sy_list_jia.png"
                anchors.centerIn: parent
            }
            MouseArea
            {
                id:addbuttomArea
                anchors.fill: parent
                onClicked:
                {
                numberboxRect.number++
                }

            }

        }
    }
}
