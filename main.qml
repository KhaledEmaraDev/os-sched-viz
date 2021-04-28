import QtCharts 2.3
import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import "JobModel.js" as TM_func

Item {
    id: root
    width: 900
    height: 700

    signal visualize()

    property var timelineModel
    property var jobModel

    GridLayout {
        x: 109
        y: 20
        rows: 1
        columns: 4
        ComboBox {
            id: algorithm_comboBox
            width: 267
            height: 40
            model: algorithms
            transformOrigin: Item.Center
            focusPolicy: Qt.ClickFocus
            flat: false
            editable: false
            Layout.preferredHeight: 40
            Layout.preferredWidth: 267
            currentIndex: 0 // start with FCFS
            Component.onCompleted: TM_func.init()
            onCurrentIndexChanged: TM_func.init()
        }

        Button {
            id: add_process_button
            height: 40
            text: qsTr("Add Process")
            focusPolicy: Qt.ClickFocus
            onClicked: TM_func.addProcess()
        }

        Button {
            id: remove_process_button
            height: 40
            text: qsTr("Remove Last Process")
            focusPolicy: Qt.ClickFocus
            onClicked: TM_func.removeProcess()
        }

        Button {
            id: clear_button
            height: 40
            text: qsTr("Clear")
            onClicked: TM_func.clearTable()
        }
    }

    ListModel{
        id: algorithms

        ListElement{
            name: "FCFS"
        }
        ListElement{
            name: "SJF"
        }
        ListElement{
            name: "Round Robin"
        }
        ListElement{
            name: "Priority"
        }
    }

    CheckBox {
        id: preemtive_checkBox
        x: 747
        y: 23
        width: 145
        height: 35
        text: qsTr("Preemtive")
        font.bold: true
//        onCheckedChanged:{
//            preemtive_checkBox.text = (preemtive_checkBox.checked)? "Preemtive":"Non-preemtive";
//        }
    }

    ColumnLayout {
    }

    GridLayout {
    }

    Label {
        id: label
        x: 620
        y: 170
        width: 162
        height: 21
        color: "#000000"
        text: qsTr("Average Waiting Time :  ")
        horizontalAlignment: Text.AlignHCenter
        Layout.preferredHeight: 22
        Layout.preferredWidth: 108
        styleColor: "#b01414"
        font.bold: true
        font.pointSize: 11
    }
    RowLayout {
        x: 116
        y: 68
        width: 776
        height: 21

        Rectangle {
            id: process_name_rectangle
            color: "#7f8aa4c1"
            radius: 10.5
            border.width: 2
            Layout.preferredHeight: 21
            Layout.preferredWidth: 56

            TextInput {
                id: process_name_textEdit
                x: 77
                y: 121
                anchors.centerIn: parent
                width: parent.width
                height: 18
                color: "#000000"
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
            }

            Label {
                id: process_label
                x: -85
                y: 4
                color: "#000000"
                text: qsTr("Process Name")
                font.bold: true
            }
        }

        Rectangle {
            id: burst_time_rectangle
            x: 130
            color: "#7f8aa4c1"
            radius: 10.5
            border.width: 2
            Layout.preferredHeight: 21
            Layout.preferredWidth: 56
            TextInput {
                id: burst_time_textEdit
                x: 77
                y: 121
                width: parent.width
                height: 18
                color: "#000000"
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                anchors.centerIn: parent
            }

            Label {
                id: burst_time_label
                x: -63
                y: 4
                color: "#000000"
                text: qsTr("Burst Time")
                font.bold: true
            }
        }

        Rectangle {
            id: arrival_time_rectangle
            x: 280
            color: "#7f8aa4c1"
            radius: 10.5
            border.width: 2
            Layout.preferredHeight: 21
            Layout.preferredWidth: 56
            TextInput {
                id: arrival_time_textEdit
                x: 77
                y: 121
                width: parent.width
                height: 18
                color: "#000000"
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                anchors.centerIn: parent
            }

            Label {
                id: arrival_time_label
                x: -73
                y: 4
                color: "#000000"
                text: qsTr("Arrival Time")
                font.bold: true
            }
        }

        Rectangle {
            id: priority_rectangle
            x: 400
            color: "#7f8aa4c1"
            radius: 10.5
            border.width: 2
            Layout.preferredHeight: 21
            Layout.preferredWidth: 56
            TextInput {
                id: priority_textEdit
                x: 77
                y: 121
                width: parent.width
                height: 18
                color: "#000000"
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                anchors.centerIn: parent
            }

            Label {
                id: priority_label
                x: -47
                y: 4
                color: "#000000"
                text: qsTr("Priority")
                font.bold: true
            }
        }

        Rectangle {
            id: time_quantum_rectangle
            x: 555
            color: "#7f8aa4c1"
            radius: 10.5
            border.width: 2
            Layout.preferredHeight: 21
            Layout.preferredWidth: 56
            TextInput {
                id: time_quantum_textEdit
                x: 80
                y: 121
                width: parent.width
                height: 18
                color: "#000000"
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                anchors.centerIn: parent
            }

            Label {
                id: time_quantum_label
                x: -82
                y: 4
                color: "#000000"
                text: qsTr("Time Quantum")
                font.bold: true
            }
        }
    }

    Rectangle {
        id: avr_waiting_rectangle
        x: 637
        y: 197
        width: 128
        height: 33
        color: "#ffffff"
        radius: 6
        border.color: "#000000"
        border.width: 3
        transformOrigin: Item.Center
        Layout.preferredHeight: 32
        Layout.preferredWidth: 135

        Label {
            anchors.centerIn: parent
            id: avr_waiting_label
            x: 51
            y: 10
            text: qsTr("0")
        }
    }

    Rectangle {
        id: table_rectangle
        x: 100
        y: 95
        width: 458
        height: 181
        color: "#ffffff"
        radius: 5
        border.color: "#7f353637"
        border.width: 4

        TableView {
            id: tableview_id
            x: 8
            y: 8
            width: 442
            height: 163
            transformOrigin: Item.Center
            activeFocusOnTab: true
            focus: false
            columnSpacing: 1
            rowSpacing: 1
            clip: true
            ScrollIndicator.horizontal: ScrollIndicator { }
            ScrollIndicator.vertical: ScrollIndicator { }
            model: root.jobModel

            delegate: Rectangle {
                implicitWidth: 100
                implicitHeight: 20
                border.color: "black"
                border.width: 2
                color: heading ? "#dcdcdc": "white"
                Text {
                    text: tabledata
                    font.pointSize: 10
                    anchors.centerIn: parent
                }
            }
        }
    }

    Rectangle {
        id: chart_rectangle
        x: 100
        y: 282
        width: 718
        height: 358
        color: "#ffffff"
        radius: 5
        border.color: "#7f353637"
        border.width: 4

        Flickable {
            id: charFlickabe
            x: 8
            y: 8
            width: 700
            height: root.height / 2

            Layout.row: 1
            Layout.column: 1
            Layout.fillWidth: true
            Layout.margins: 8

            clip: true

            contentWidth: timelineChart.width
            contentHeight: timelineChart.height

            ChartView {
                id: timelineChart

                width: 1080
                height: parent.height

                antialiasing: true
                animationOptions: ChartView.AllAnimations
                theme: ChartView.ChartThemeBrownSand
                legend.alignment: Qt.AlignBottom

                ValueAxis {
                    id: timeAxis
                    tickType: ValueAxis.TicksDynamic
                    tickInterval: 5
                }

                HorizontalStackedBarSeries {
                    id: ganttSeries

                    axisX: timeAxis
                    axisY: BarCategoryAxis { categories: ["Timeline"] }

                    labelsVisible: true
                    labelsPosition: AbstractBarSeries.LabelsCenter

                    HBarModelMapper {
                        model: root.timelineModel
                        firstBarSetRow: 0
                        lastBarSetRow: 11
                        firstColumn: 0
                        columnCount: 1

                        Component.onCompleted: {
                            const labels = root.timelineModel.labels()
                            let colorMap = {}
                            for (let i = 0; i < ganttSeries.count; i++) {
                                if (colorMap[labels[i]] === undefined) {
                                    colorMap[labels[i]] = ganttSeries.at(i).color
                                } else {
                                    ganttSeries.at(i).color = colorMap[labels[i]];
                                }
                            }
                        }
                    }
                }
            }

            ScrollBar.horizontal: ScrollBar {
                hoverEnabled: true
                active: hovered || pressed
                orientation: Qt.Horizontal
            }
        }
    }

    Button {
        id: visualize_button
        x: 620
        y: 112
        width: 162
        height: 40
        text: qsTr("Visualize")
        onClicked: {
            root.visualize()
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.3300000429153442}
}
##^##*/
