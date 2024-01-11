from PySide6.QtWidgets import QMainWindow, QHBoxLayout, QVBoxLayout, QWidget, QGroupBox, QLabel, QPushButton, QLineEdit, QTextEdit
from PySide6.QtGui import QIcon, QFont
from PySide6.QtCore import Qt, QTimer
import pyqtgraph as pg
import numpy as np
import serial
import re
from datetime import datetime

SERIAL_COM = "COM3"
BAUD_RATE = 115200


class MainWindow(QMainWindow):
    promotie: str = "2023-2024"
    team: list[str] = [
        "Grigore Maria Emilia",
        "Ionel Ana-Maria",
    ]

    def __init__(self):
        super().__init__()
        self.setWindowTitle(f"Proiect Microprocesoare {self.promotie}")
        self.setWindowIcon(QIcon("./icon.png"))

        self.serial_communication()
        self.setup_UI()
       


    def setup_UI(self):
        primary_layout = QVBoxLayout()
        secondary_layout = QHBoxLayout()
        tertiary_layout = QVBoxLayout()

        team_box = QGroupBox("Team")
        bold_font = QFont()
        bold_font.setBold(True)
        team_box.setFont(bold_font)

        first_member = QLabel(f"Member 1: {self.team[0]}")
        second_member = QLabel(f"Member 2: {self.team[1]}")
        team_box_layout = QVBoxLayout()
        team_box_layout.addWidget(first_member, 1)
        team_box_layout.addWidget(second_member, 1)
        team_box.setLayout(team_box_layout)

        control_panel_box = QGroupBox("Control Panel")
        control_panel_box.setFont(bold_font)

        button1 = QPushButton("Reverse led sequence", self)
        button1.clicked.connect(lambda: self.send_signal(b'M'))
        button2 = QPushButton("Normal led sequence", self)
        button2.clicked.connect(lambda: self.send_signal(b'N'))

        button3 = QPushButton("Stop on white led ")
        button3.clicked.connect(lambda: self.send_signal(b'W'))

        button4 = QPushButton("Stop on green led ")
        button4.clicked.connect(lambda: self.send_signal(b'G'))

        button5 = QPushButton("Stop on turquoise led ")
        button5.clicked.connect(lambda: self.send_signal(b'T'))

        button6 = QPushButton("Stop on yellow led ")
        button6.clicked.connect(lambda: self.send_signal(b'Y'))


        button7 = QPushButton("Stop white led")
        button7.clicked.connect(lambda: self.send_signal(b'w'))

        button8 = QPushButton("Stop green led")
        button8.clicked.connect(lambda: self.send_signal(b'g'))

        button9 = QPushButton("Stop turquoise led")
        button9.clicked.connect(lambda: self.send_signal(b't'))

        button10 = QPushButton("Stop yellow led")
        button10.clicked.connect(lambda: self.send_signal(b'y'))

        button11 = QPushButton("LED Sequence Duration - 10ms")
        button11.clicked.connect(lambda: self.send_signal(b'1'))

        button12 = QPushButton("LED Sequence Duration - 1s")
        button12.clicked.connect(lambda: self.send_signal(b'2'))

        button13 = QPushButton("LED Sequence Duration - 3s")
        button13.clicked.connect(lambda: self.send_signal(b'3'))

        button14 = QPushButton("Reset Duration to 461ms")
        button14.clicked.connect(lambda: self.send_signal(b'4'))

        control_panel_box_layout = QVBoxLayout()

        control_panel_box_layout.setSpacing(5)
        control_panel_box_layout.addWidget(button1, 1)
        control_panel_box_layout.addWidget(button2, 1)
        control_panel_box_layout.addWidget(button3, 1)
        control_panel_box_layout.addWidget(button4, 1)
        control_panel_box_layout.addWidget(button5, 1)
        control_panel_box_layout.addWidget(button6, 1)
        control_panel_box_layout.addWidget(button7, 1)
        control_panel_box_layout.addWidget(button8, 1)
        control_panel_box_layout.addWidget(button9, 1)
        control_panel_box_layout.addWidget(button10, 1)
        control_panel_box_layout.addWidget(button11, 1)
        control_panel_box_layout.addWidget(button12, 1)
        control_panel_box_layout.addWidget(button13, 1)
        control_panel_box_layout.addWidget(button14, 1)


        control_panel_box.setLayout(control_panel_box_layout)

        tertiary_layout.addWidget(team_box, 1)
        tertiary_layout.addWidget(control_panel_box, 5)

        plot_widget = pg.PlotWidget()
        self.plot_curve = plot_widget.plot(pen={'color': 'k', 'width': 2})  # 'k' for black color, 'width': 2 for a thicker line

        zone1_start, zone1_stop, zone1_color = 0, 1, (0, 204, 102)
        zone2_start, zone2_stop, zone2_color = 1, 1.8, (255, 255, 102)
        zone3_start, zone3_stop, zone3_color = 1.8, 3.3, (255, 0, 0)

        plot_widget.addItem(pg.LinearRegionItem([zone1_start, zone1_stop], orientation='horizontal', brush=pg.mkBrush(zone1_color), movable=False))
        plot_widget.addItem(pg.LinearRegionItem([zone2_start, zone2_stop], orientation='horizontal', brush=pg.mkBrush(zone2_color), movable=False))
        plot_widget.addItem(pg.LinearRegionItem([zone3_start, zone3_stop], orientation='horizontal', brush=pg.mkBrush(zone3_color), movable=False))

        secondary_layout.addWidget(plot_widget, 3)
        secondary_layout.addLayout(tertiary_layout, 1)

        primary_layout.addLayout(secondary_layout, 4)
        self.text_edit = QTextEdit()
        self.text_edit.setReadOnly(True)

        debug_box = QGroupBox("Debug")
        debug_box_layout = QVBoxLayout()
        debug_box_layout.addWidget(self.text_edit, 1)
        debug_box.setLayout(debug_box_layout)

        primary_layout.addWidget(debug_box, 1)

        widget = QWidget()
        widget.setLayout(primary_layout)

        self.setCentralWidget(widget)

    def serial_communication(self):
        self.serial_port = serial.Serial(SERIAL_COM, BAUD_RATE, timeout=1)  # Replace "COMx" with your actual COM port

        self.sensor_timer = QTimer(self)
        self.sensor_timer.timeout.connect(self.update_plot)
        self.sensor_timer.start(0.10) 
        self.start_time = datetime.now()
        self.previous_duration = 0
        self.previous_sensor_value = 0


    def send_signal(self, character):
        self.serial_port.write(character)

    def update_plot(self):
        try:
            data = self.serial_port.readline().decode('ascii', errors='ignore').strip()

            print("Raw data:", data)  

            match = re.search(r'[-+]?\d*\.\d+|\d+', data)
            if match:
                sensor_value = float(match.group())
                duration = (datetime.now() - self.start_time).total_seconds()
                self.text_edit.insertPlainText(f"Sensor Value: {sensor_value}, Duration: {duration} seconds\n")
                sensor_value = max(0, min(sensor_value, 3.3))
                x_values = np.linspace(0, duration, 1000)
                y_values = np.full_like(x_values, sensor_value)
                self.plot_curve.setData(x_values, y_values)
                self.plot_curve.setZValue(10)

            else:
                print("Invalid data format: ", data)

        except Exception as e:
            print(f"Error: {e}")

