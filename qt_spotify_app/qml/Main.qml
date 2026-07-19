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

    AnimatedImage {
        id: backgroundImage
        anchors.fill: parent
        source: "qrc:/qt/qml/qt_spotify_app/assets/background.gif" // Path to your GIF
        cache: false                     // Recommended for performance
        fillMode: Image.PreserveAspectCrop
        onCurrentFrameChanged: {
            if (currentFrame === frameCount - 1) {
                // reached the last frame — loop manually
                currentFrame = 0;
            }
        }
        onStatusChanged: {
            if (status === AnimatedImage.Ready)
                console.warn("frameCount =", frameCount);
        }
    }

    GridLayout {
        id: grid
        columns: width < 400 ? 1 : 2
        rowSpacing: 0
        columnSpacing: 0
        anchors.fill: parent

        Rectangle {
            id: rectangle1
            color: "transparent"
            Layout.fillHeight: true
            Layout.fillWidth: true

            ColumnLayout {
                anchors.fill: parent
                Layout.alignment: Qt.AlignHCenter | Qt.AlignTop

                Label {
                    id: text1
                    color: window.lightMode ? window.dark : window.light
                    font.pixelSize: 120
                    fontSizeMode: Text.Fit
                    text: qsTr("Hello World")
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.margins: 16
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                Image {
                    id: remoteImage
                    width: 300
                    height: 300
                    source: Backend.albumCover
                    // Keeps aspect ratio intact while fitting the item boundary
                    fillMode: Image.PreserveAspectFit
                }
            }
        }

        Rectangle {
            id: rectangle2
            color: "transparent"
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
