import QtQuick 2.0







Rectangle {
    id: activityContainer
    width: 100
    height: 62
    color: "#343434"

    ListModel {
        id: activityModel
    }

    Component {
        id: activityListDelegate

        Item {
            id: activityDelegateItem
            width: listView.width
            height: 80
            clip: true

            Column {
                anchors {
                    horizontalCenter: parent.horizontalCenter;
                    bottom: parent.verticalCenter
                }

                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: name
                    font.pixelSize: 15
                    color: "white"
                }

                Row {
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 5
                    Repeater {
                        model: attributes
                        Text { text: description; color: "White" }
                    }
                }

            }

            Item {
                anchors {
                    left: parent.right
                    horizontalCenter: parent.horizontalCenter;
                    top: parent.verticalCenter
                    bottom: parent.bottom
                }

                Row {
                    anchors.centerIn: parent
                    spacing: 10

                    PressAndHoldButton {
                        anchors.verticalCenter: parent.verticalCenter
                        source: "content/pics/plus-sign.png"
                        onClicked: activityModel.setProperty(index, "cost", cost + 0.25)
                    }

                    Text {
                        id: costText
                        anchors.verticalCenter: parent.verticalCenter
                        text: '$' + Number(cost).toFixed(2)
                        font.pixelSize: 15
                        color: "white"
                        font.bold: true
                    }

                    PressAndHoldButton {
                        anchors.verticalCenter: parent.verticalCenter
                        source: "content/pics/minus-sign.png"
                        onClicked: activityModel.setProperty(index, "cost", Math.max(0,cost-0.25))
                    }

                    Image {
                        source: "content/pics/list-delete.png"
                        MouseArea { anchors.fill:parent; onClicked: activityModel.remove(index) }
                    }
                }

            }

            // Animate adding and removing of items:
            ListView.onAdd: SequentialAnimation {
                PropertyAction { target: delegateItem; property: "height"; value: 0 }
                NumberAnimation { target: delegateItem; property: "height"; to: 80; duration: 250; easing.type: Easing.InOutQuad }
            }

            ListView.onRemove: SequentialAnimation {
                PropertyAction { target: delegateItem; property: "ListView.delayRemove"; value: true }
                NumberAnimation { target: delegateItem; property: "height"; to: 0; duration: 250; easing.type: Easing.InOutQuad }

                // Make sure delayRemove is set back to false so that the item can be destroyed
                PropertyAction { target: delegateItem; property: "ListView.delayRemove"; value: false }
            }
        }

    }

    // The view:
    ListView {
        id: listView
        anchors {
            left: parent.left; top: parent.top;
            right: parent.right; bottom: parent.bottom;
            margins: 20
        }
        model: activityModel
        delegate: activityListDelegate
    }

}
