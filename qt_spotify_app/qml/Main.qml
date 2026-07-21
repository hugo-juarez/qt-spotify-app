import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import qt_spotify_app

ApplicationWindow {
    id: window
    width: 1280
    height: 720
    //visibility: Window.FullScreen
    minimumWidth: 200
    minimumHeight: 250
    visible: true
    title: qsTr("Hello World")
    property bool lightMode: Application.styleHints.colorScheme === Qt.Light
    property color reallyDark: "#1f1f1f"
    property color dark: "#262626"
    property color reallyLight: "#e7e7e7"
    property color light: "#e0e0e0"
    property color textColor: "#e0e0e0"
    property bool isLoaded: Backend.albumCover.toString().length !== 0

    GridLayout {
        id: grid
        columns: 2
        rowSpacing: 0
        columnSpacing: 0
        anchors.fill: parent

        Rectangle {
            id: rectangle1
            color: window.dark
            Layout.fillHeight: true
            Layout.fillWidth: true

            ColumnLayout {
                anchors.centerIn: parent
                Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                width: 450
                spacing: 12

                // Static when the text fits, scrolls when it overflows.
                component MarqueeLabel: Item {
                    id: marquee
                    property alias text: label.text
                    property alias color: label.color
                    property alias font: label.font
                    implicitHeight: label.implicitHeight
                    clip: true      // this is what hides the overflow so it can scroll

                    Text {
                        id: label
                        height: parent.height
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignVCenter

                        readonly property real overshoot: implicitWidth - marquee.width
                        readonly property bool overflowing: overshoot > 0

                        // reset to the start edge when it no longer needs to scroll
                        onOverflowingChanged: if (!overflowing) x = 0

                        SequentialAnimation on x {
                            running: label.overflowing
                            loops: Animation.Infinite
                            PauseAnimation { duration: 1200 }
                            NumberAnimation { to: -label.overshoot
                                              duration: Math.max(1, label.overshoot) * 18
                                              easing.type: Easing.InOutQuad }
                            PauseAnimation { duration: 1200 }
                            NumberAnimation { to: 0
                                              duration: Math.max(1, label.overshoot) * 18
                                              easing.type: Easing.InOutQuad }
                        }
                    }
                }

                Item {
                    id: coverContainer
                    Layout.fillWidth: true
                    Layout.preferredHeight: width      // keeps it square at the content width
                    Layout.topMargin: 4
                    Layout.bottomMargin: 4

                    Image {
                        id: coverImage
                        anchors.fill: parent
                        source: Backend.albumCover
                        asynchronous: true
                        fillMode: Image.PreserveAspectFit
                        visible: (isLoaded && status === Image.Ready)
                    }
                    BusyIndicator {
                        anchors.centerIn: parent
                        running: (!isLoaded || coverImage.status === Image.Loading)
                        visible: running
                    }
                }

                MarqueeLabel {
                    Layout.fillWidth: true
                    text: qsTr(Backend.songName)
                    color: window.textColor
                    font.pixelSize: 40
                }

                MarqueeLabel {
                    Layout.fillWidth: true
                    text: qsTr(Backend.artists)
                    color: window.textColor
                    opacity: 0.75
                    font.pixelSize: 22
                }

                ProgressBar {
                    id: progressBar
                    Layout.fillWidth: true
                    Layout.topMargin: 4
                }

                RowLayout {
                    id: rowLayout
                    Layout.fillWidth: true
                    spacing: 4
                    readonly property string iconPath: "qrc:/qt/qml/qt_spotify_app/assets/icons/"

                    component MediaButton: RoundButton {
                        Layout.fillWidth: true     // buttons distribute evenly across the width
                        implicitWidth: 48
                        implicitHeight: 44
                        icon.width: 22
                        icon.height: 22
                        icon.color: "white"
                    }

                    MediaButton { icon.source: rowLayout.iconPath + "shuffle.svg" }
                    MediaButton { icon.source: rowLayout.iconPath + "previous.svg" }
                    MediaButton {
                        icon.source: rowLayout.iconPath + "pause.svg"
                        visible: Backend.player.playing
                    }
                    MediaButton {
                        icon.source: rowLayout.iconPath + "play.svg"
                        visible: !Backend.player.playing
                    }
                    MediaButton { icon.source: rowLayout.iconPath + "next.svg" }
                    MediaButton { icon.source: rowLayout.iconPath + "repeat.svg" }
                }
            }
        }

        Rectangle {
            id: rectangle2
            color: window.dark
            Layout.fillHeight: true
            Layout.fillWidth: true

            ColumnLayout {
                anchors.fill: parent
                Layout.alignment: Qt.AlignHCenter | Qt.AlignTop

                Button {
                    id: button1
                    text: window.lightMode ? qsTr("\u263D  Dark mode")
                                           : qsTr("\u263C  Light mode")
                    Layout.bottomMargin: 16
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom

                    contentItem: Text {
                        text: button1.text
                        color: window.lightMode ? window.light : window.dark
                        font: button1.font
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }

                    background: Rectangle {
                        implicitWidth: 120
                        implicitHeight: 36
                        radius: 8
                        color: window.lightMode ? window.dark : window.light
                    }

                    onClicked: window.lightMode = !window.lightMode
                }
            }
        }
    }

}
