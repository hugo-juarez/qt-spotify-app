import QtQuick

Item {
    id: root
    width: 400
    height: 60

    // Helper to format ms as m:ss
    function formatTime(ms) {
        if (ms < 0) ms = 0
        var totalSeconds = Math.floor(ms / 1000)
        var minutes = Math.floor(totalSeconds / 60)
        var seconds = totalSeconds % 60
        return minutes + ":" + (seconds < 10 ? "0" : "") + seconds
    }

    Column {
        anchors.fill: parent
        spacing: 6

        // The progress bar track
        Rectangle {
            id: track
            width: parent.width
            height: 6
            radius: 3
            color: "#404040"

            Rectangle {
                id: fill
                width: track.width * Backend.player.progress
                height: parent.height
                radius: 3
                color: "#1db954" // Spotify green

                // Smooth the movement between updates
                Behavior on width {
                    NumberAnimation { duration: 100; easing.type: Easing.Linear }
                }
            }
        }

        // Time labels
        Item {
            width: parent.width
            height: 16

            Text {
                anchors.left: parent.left
                text: root.formatTime(Backend.player.position)
                color: "#b3b3b3"
                font.pixelSize: 12
            }

            Text {
                anchors.right: parent.right
                text: root.formatTime(Backend.player.duration)
                color: "#b3b3b3"
                font.pixelSize: 12
            }
        }
    }
}