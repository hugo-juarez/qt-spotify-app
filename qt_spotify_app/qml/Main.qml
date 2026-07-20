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
        columns: width < 400 ? 1 : 2
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

                Label {
                    id: title
                    color: window.textColor
                    font.pixelSize: 52
                    fontSizeMode: Text.Fit
                    text: qsTr(Backend.songName)
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.margins: 16
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                }

                Item {
                    width: 300
                    height: 300
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Image {
                        id: coverImage
                        anchors.fill: parent
                        source: Backend.albumCover
                        asynchronous: true

                        // Keeps aspect ratio intact while fitting the item boundary
                        fillMode: Image.PreserveAspectFit

                        visible: (isLoaded && status === Image.Ready)
                    }

                    BusyIndicator {
                        id: busyIndicator
                        anchors.centerIn: parent
                        running: (!isLoaded || coverImage.status === Image.Loading)
                        visible: (!isLoaded || coverImage.status === Image.Loading)
                    }
                }

                Label {
                    id: author
                    color: window.textColor
                    opacity: 0.75
                    font.pixelSize: 24
                    fontSizeMode: Text.Fit
                    text: qsTr(Backend.artists)
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.margins: 16
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                }

                ProgressBar {
                    id: progressBar
                }

                RowLayout {
                    id: rowLayout
                    x: 0
                    y: 480
                    Layout.topMargin: 20
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

                    RoundButton {
                        text: "\u23ee"
                        implicitWidth: 80
                        implicitHeight: 40
                        font.pixelSize: 20
                    }

                    RoundButton {
                        text: "\u23f8"
                        implicitWidth: 80
                        implicitHeight: 40
                        font.pixelSize: 20
                    }

                    RoundButton {
                        text: "\u23ed"
                        implicitWidth: 80
                        implicitHeight: 40
                        font.pixelSize: 20
                    }
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
