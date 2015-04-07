import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Dialogs 1.1


 ApplicationWindow
 {
     id: mainWindow
     width: 600; height: 400
     title: 'Computer Monitor'

     menuBar: MenuBar
     {
         Menu
         {
             title: "File"
             MenuItem
             {
                 text: "Exit"
                 onTriggered: mainWindow.close()
             }
         }

         Menu
         {
             title: "Help"
             MenuItem
             {
                 text: "About"
             }
         }
     }

     TabView
     {
         anchors.margins: 5
         anchors.fill: parent
         Tab
         {
             title:'Processor'
             anchors.margins: 5
             GroupBox
             {
                 title: 'General'
                 TableView
                 {
                     id: processorGeneralInfo
                     anchors.fill: parent
                 }
             }
         }

         Tab
         {
             title: 'Ram'
         }

         Tab
         {
             title: 'Network'
         }

         Tab
         {
             title: 'Tasks'
         }
     }
 }
