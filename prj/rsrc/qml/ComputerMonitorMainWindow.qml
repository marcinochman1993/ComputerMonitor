import QtQuick 2.2
import QtQuick.Controls 1.0

 ApplicationWindow{
     id: page
     width: 500; height: 200

     menuBar: MenuBar{
         Menu{
             title: "File"
             MenuItem{
                 text: "Exit"
                 onTriggered: Qt.quit()
             }
         }
         Menu{
             title: "Help"
             MenuItem{
                 text: "About"

             }
         }
     }

     Text {
         id: helloText
         text: "Hello world!"
         anchors.centerIn: parent
         font.pointSize: 24; font.bold: true
     }
 }
