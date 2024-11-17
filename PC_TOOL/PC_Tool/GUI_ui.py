# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'GUI.ui'
##
## Created by: Qt User Interface Compiler version 6.8.0
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide6.QtCore import (QCoreApplication, QDate, QDateTime, QLocale,
    QMetaObject, QObject, QPoint, QRect,
    QSize, QTime, QUrl, Qt)
from PySide6.QtGui import (QBrush, QColor, QConicalGradient, QCursor,
    QFont, QFontDatabase, QGradient, QIcon,
    QImage, QKeySequence, QLinearGradient, QPainter,
    QPalette, QPixmap, QRadialGradient, QTransform)
from PySide6.QtWidgets import (QApplication, QComboBox, QFrame, QGridLayout,
    QGroupBox, QHBoxLayout, QLabel, QLineEdit,
    QMainWindow, QPushButton, QSizePolicy, QSpacerItem,
    QStackedWidget, QVBoxLayout, QWidget)
import resources_rc

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        if not MainWindow.objectName():
            MainWindow.setObjectName(u"MainWindow")
        MainWindow.resize(1024, 807)
        MainWindow.setStyleSheet(u"")
        self.centralwidget = QWidget(MainWindow)
        self.centralwidget.setObjectName(u"centralwidget")
        self.centralwidget.setAutoFillBackground(False)
        self.centralwidget.setStyleSheet(u"* {\n"
"\n"
"}\n"
"\n"
"/* Side menu */\n"
"#slide_menu_container{\n"
"	background-color: rgb(177, 177, 177)\n"
"}\n"
"\n"
"#menu QPushButton, #exit QPushButton {\n"
"	color: #000000;\n"
"	text-align: left;\n"
"	border-radius: 5px; \n"
"	font-size: 14px;\n"
"	font-weight: bold;\n"
"	background-color:  rgb(250, 250, 250);\n"
"	padding: 5px;\n"
"	border: 2px solid #000000;\n"
"}\n"
"\n"
"#menu QPushButton:hover, #exit QPushButton:hover {\n"
"	color: rgb(255, 255, 255);\n"
"	background-color: rgb(193, 193, 193);\n"
"	border: 2px solid #ffffff;\n"
"	box-shadow: 0 0 10px #00aaff;\n"
"}\n"
"\n"
"/* Main board */\n"
"\n"
"#main_body {\n"
"	background-color: #F9F9F9; /*#ECF0F1;*/\n"
"}\n"
"\n"
"#header_title {\n"
"	font-size: 20px;\n"
"	font-weight: bold;\n"
"	border: none;\n"
"}\n"
"\n"
"#header_frame QPushButton {\n"
"	border: none;\n"
"	padding: 5px;\n"
"	background: none;\n"
"}\n"
"\n"
"#header_frame QPushButton:hover{\n"
"	border: none;\n"
"	background: qradialgradient(cx:0.5, cy:0.5, radius:0.6, fx:0.5, fy:0.5, "
                        "stop:0 rgba(255, 255, 255, 150), stop:1 rgba(255, 255, 255, 0));\n"
"}\n"
"\n"
"#dashboard, #setting_frame {\n"
"	background-color: #f6f8fc;\n"
"	border-radius: 10px;\n"
"}\n"
"\n"
"#speed_frame, #temperature_frame, #speed_node, #temperature_node {\n"
"	background-color: #ffffff;\n"
"	border-radius: 5px;\n"
"	border: 1.5px solid #000000;\n"
"}\n"
"\n"
"#speed_node, #temperature_node {\n"
"	background-color: white;\n"
"	border-radius: 5px\n"
"}\n"
"\n"
"#speed_text_result, #temperature_text_result, #com_result_text {\n"
"	background-color: #61BD4F; \n"
"	color: white;\n"
"	border-radius: 5px;\n"
"}\n"
"\n"
"#control_btn QPushButton {\n"
"	border-radius: 5px;\n"
"	font-size: 14px;\n"
"	font-weight: bold;\n"
"	background-color:  white;\n"
"	border: 1px solid #000000\n"
"}\n"
"\n"
"#start_btn:hover {\n"
"	color: #1abc9c;\n"
"	border: 2px solid #1abc9c;\n"
"}\n"
"\n"
"#stop_btn:hover {\n"
"	color: rgb(226, 0, 5);\n"
"	border: 2px solid #EB5A46;\n"
"}\n"
"/* Setting */\n"
"\n"
"#connect_btn, #uart_save_btn, #uart_ch"
                        "ange_btn, #uart_cancel_btn, #browse_btn {\n"
"	color: #6d718d;\n"
"	border-radius: 5px;\n"
"	background-color: #ffffff;\n"
"	text-align: center;\n"
"}\n"
"\n"
"#connect_btn:hover {\n"
"	color: #1abc9c;\n"
"	border: 1px solid #1abc9c;\n"
"}\n"
"\n"
"#uart_save_btn:hover, #uart_change_btn:hover, #browse_btn:hover {\n"
"	color: #315ae7;\n"
"	border: 1px solid #315ae7;\n"
"}\n"
"\n"
"#uart_cancel_btn:hover  {\n"
"	color: #EB5A46;\n"
"	border: 1px solid #EB5A46;\n"
"}\n"
"\n"
"#portList, #baudList, #parity, #stopBit, #byteSize {\n"
"	background-color: white;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"	border: 1px solid #315ae7;\n"
"}\n"
"")
        self.horizontalLayout = QHBoxLayout(self.centralwidget)
        self.horizontalLayout.setSpacing(0)
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.horizontalLayout.setContentsMargins(0, 0, 0, 0)
        self.slide_menu_container = QFrame(self.centralwidget)
        self.slide_menu_container.setObjectName(u"slide_menu_container")
        self.slide_menu_container.setMinimumSize(QSize(0, 0))
        self.slide_menu_container.setMaximumSize(QSize(200, 16777215))
        self.slide_menu_container.setStyleSheet(u"")
        self.slide_menu_container.setFrameShape(QFrame.StyledPanel)
        self.slide_menu_container.setFrameShadow(QFrame.Raised)
        self.verticalLayout = QVBoxLayout(self.slide_menu_container)
        self.verticalLayout.setSpacing(0)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)
        self.slide_menu = QFrame(self.slide_menu_container)
        self.slide_menu.setObjectName(u"slide_menu")
        self.slide_menu.setMinimumSize(QSize(196, 0))
        self.slide_menu.setFrameShape(QFrame.StyledPanel)
        self.slide_menu.setFrameShadow(QFrame.Raised)
        self.gridLayout = QGridLayout(self.slide_menu)
        self.gridLayout.setSpacing(0)
        self.gridLayout.setObjectName(u"gridLayout")
        self.gridLayout.setContentsMargins(0, 0, 0, 0)
        self.menu = QFrame(self.slide_menu)
        self.menu.setObjectName(u"menu")
        sizePolicy = QSizePolicy(QSizePolicy.Policy.Preferred, QSizePolicy.Policy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.menu.sizePolicy().hasHeightForWidth())
        self.menu.setSizePolicy(sizePolicy)
        self.menu.setFrameShape(QFrame.StyledPanel)
        self.menu.setFrameShadow(QFrame.Raised)
        self.verticalLayout_4 = QVBoxLayout(self.menu)
        self.verticalLayout_4.setSpacing(0)
        self.verticalLayout_4.setObjectName(u"verticalLayout_4")
        self.verticalLayout_4.setContentsMargins(0, 0, 0, 0)
        self.home_button = QPushButton(self.menu)
        self.home_button.setObjectName(u"home_button")
        sizePolicy1 = QSizePolicy(QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Fixed)
        sizePolicy1.setHorizontalStretch(0)
        sizePolicy1.setVerticalStretch(0)
        sizePolicy1.setHeightForWidth(self.home_button.sizePolicy().hasHeightForWidth())
        self.home_button.setSizePolicy(sizePolicy1)
        font = QFont()
        font.setBold(True)
        self.home_button.setFont(font)
        self.home_button.setAutoFillBackground(False)
        self.home_button.setStyleSheet(u"text-align: left\n"
"")
        icon = QIcon()
        icon.addFile(u":/icons/icon/home.png", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        self.home_button.setIcon(icon)
        self.home_button.setIconSize(QSize(32, 32))
        self.home_button.setFlat(False)

        self.verticalLayout_4.addWidget(self.home_button)

        self.settings_button = QPushButton(self.menu)
        self.settings_button.setObjectName(u"settings_button")
        sizePolicy1.setHeightForWidth(self.settings_button.sizePolicy().hasHeightForWidth())
        self.settings_button.setSizePolicy(sizePolicy1)
        self.settings_button.setFont(font)
        self.settings_button.setStyleSheet(u"text-align: left")
        icon1 = QIcon()
        icon1.addFile(u":/icons/icon/settings.png", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        self.settings_button.setIcon(icon1)
        self.settings_button.setIconSize(QSize(32, 32))

        self.verticalLayout_4.addWidget(self.settings_button)


        self.gridLayout.addWidget(self.menu, 0, 0, 1, 1)

        self.exit = QFrame(self.slide_menu)
        self.exit.setObjectName(u"exit")
        self.exit.setFrameShape(QFrame.StyledPanel)
        self.exit.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_7 = QHBoxLayout(self.exit)
        self.horizontalLayout_7.setSpacing(0)
        self.horizontalLayout_7.setObjectName(u"horizontalLayout_7")
        self.horizontalLayout_7.setContentsMargins(0, 0, 0, 0)
        self.exit_btn = QPushButton(self.exit)
        self.exit_btn.setObjectName(u"exit_btn")
        sizePolicy2 = QSizePolicy(QSizePolicy.Policy.Minimum, QSizePolicy.Policy.MinimumExpanding)
        sizePolicy2.setHorizontalStretch(0)
        sizePolicy2.setVerticalStretch(0)
        sizePolicy2.setHeightForWidth(self.exit_btn.sizePolicy().hasHeightForWidth())
        self.exit_btn.setSizePolicy(sizePolicy2)
        self.exit_btn.setStyleSheet(u"text-align: left\n"
"")
        icon2 = QIcon()
        icon2.addFile(u":/icons/icon/external-link.png", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        self.exit_btn.setIcon(icon2)
        self.exit_btn.setIconSize(QSize(32, 32))

        self.horizontalLayout_7.addWidget(self.exit_btn, 0, Qt.AlignBottom)


        self.gridLayout.addWidget(self.exit, 2, 0, 1, 1)

        self.verticalSpacer = QSpacerItem(20, 40, QSizePolicy.Policy.Minimum, QSizePolicy.Policy.Expanding)

        self.gridLayout.addItem(self.verticalSpacer, 1, 0, 1, 1)


        self.verticalLayout.addWidget(self.slide_menu)


        self.horizontalLayout.addWidget(self.slide_menu_container)

        self.main_body = QFrame(self.centralwidget)
        self.main_body.setObjectName(u"main_body")
        sizePolicy3 = QSizePolicy(QSizePolicy.Policy.Preferred, QSizePolicy.Policy.Preferred)
        sizePolicy3.setHorizontalStretch(0)
        sizePolicy3.setVerticalStretch(0)
        sizePolicy3.setHeightForWidth(self.main_body.sizePolicy().hasHeightForWidth())
        self.main_body.setSizePolicy(sizePolicy3)
        self.main_body.setFont(font)
        self.main_body.setStyleSheet(u"")
        self.main_body.setFrameShape(QFrame.StyledPanel)
        self.main_body.setFrameShadow(QFrame.Raised)
        self.verticalLayout_2 = QVBoxLayout(self.main_body)
        self.verticalLayout_2.setSpacing(0)
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.verticalLayout_2.setContentsMargins(0, 0, 0, 0)
        self.header_frame = QFrame(self.main_body)
        self.header_frame.setObjectName(u"header_frame")
        sizePolicy.setHeightForWidth(self.header_frame.sizePolicy().hasHeightForWidth())
        self.header_frame.setSizePolicy(sizePolicy)
        self.header_frame.setStyleSheet(u"background-color: rgb(213, 213, 213)")
        self.header_frame.setFrameShape(QFrame.StyledPanel)
        self.header_frame.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_2 = QHBoxLayout(self.header_frame)
        self.horizontalLayout_2.setSpacing(0)
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.horizontalLayout_2.setContentsMargins(0, 0, 0, 0)
        self.menu_btn = QPushButton(self.header_frame)
        self.menu_btn.setObjectName(u"menu_btn")
        icon3 = QIcon()
        icon3.addFile(u":/icons/icon/icon_gray/align-left.png", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        self.menu_btn.setIcon(icon3)
        self.menu_btn.setIconSize(QSize(32, 32))

        self.horizontalLayout_2.addWidget(self.menu_btn)

        self.horizontalSpacer = QSpacerItem(40, 20, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Minimum)

        self.horizontalLayout_2.addItem(self.horizontalSpacer)

        self.header_title = QLabel(self.header_frame)
        self.header_title.setObjectName(u"header_title")
        sizePolicy3.setHeightForWidth(self.header_title.sizePolicy().hasHeightForWidth())
        self.header_title.setSizePolicy(sizePolicy3)
        self.header_title.setMinimumSize(QSize(0, 0))
        self.header_title.setFont(font)

        self.horizontalLayout_2.addWidget(self.header_title)

        self.horizontalLayout_2.setStretch(1, 1)
        self.horizontalLayout_2.setStretch(2, 4)

        self.verticalLayout_2.addWidget(self.header_frame)

        self.panel = QFrame(self.main_body)
        self.panel.setObjectName(u"panel")
        self.panel.setFrameShape(QFrame.StyledPanel)
        self.panel.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_5 = QHBoxLayout(self.panel)
        self.horizontalLayout_5.setSpacing(0)
        self.horizontalLayout_5.setObjectName(u"horizontalLayout_5")
        self.horizontalLayout_5.setContentsMargins(0, 0, 0, 0)
        self.stackedWidget = QStackedWidget(self.panel)
        self.stackedWidget.setObjectName(u"stackedWidget")
        self.stackedWidget.setFrameShape(QFrame.Box)
        self.stackedWidget.setLineWidth(2)
        self.home_page = QWidget()
        self.home_page.setObjectName(u"home_page")
        self.verticalLayout_5 = QVBoxLayout(self.home_page)
        self.verticalLayout_5.setSpacing(0)
        self.verticalLayout_5.setObjectName(u"verticalLayout_5")
        self.verticalLayout_5.setContentsMargins(0, 0, 0, 0)
        self.dashboard = QFrame(self.home_page)
        self.dashboard.setObjectName(u"dashboard")
        self.dashboard.setFrameShape(QFrame.StyledPanel)
        self.dashboard.setFrameShadow(QFrame.Raised)
        self.verticalLayout_6 = QVBoxLayout(self.dashboard)
        self.verticalLayout_6.setSpacing(0)
        self.verticalLayout_6.setObjectName(u"verticalLayout_6")
        self.verticalLayout_6.setContentsMargins(0, 0, 0, 0)
        self.main_dashboard = QFrame(self.dashboard)
        self.main_dashboard.setObjectName(u"main_dashboard")
        sizePolicy4 = QSizePolicy(QSizePolicy.Policy.Preferred, QSizePolicy.Policy.Expanding)
        sizePolicy4.setHorizontalStretch(0)
        sizePolicy4.setVerticalStretch(0)
        sizePolicy4.setHeightForWidth(self.main_dashboard.sizePolicy().hasHeightForWidth())
        self.main_dashboard.setSizePolicy(sizePolicy4)
        self.main_dashboard.setStyleSheet(u"")
        self.main_dashboard.setFrameShape(QFrame.StyledPanel)
        self.main_dashboard.setFrameShadow(QFrame.Raised)
        self.verticalLayout_3 = QVBoxLayout(self.main_dashboard)
        self.verticalLayout_3.setSpacing(0)
        self.verticalLayout_3.setObjectName(u"verticalLayout_3")
        self.verticalLayout_3.setContentsMargins(0, 0, 0, 0)
        self.indicator_light = QFrame(self.main_dashboard)
        self.indicator_light.setObjectName(u"indicator_light")
        self.indicator_light.setMaximumSize(QSize(16777215, 100))
        self.indicator_light.setStyleSheet(u"")
        self.indicator_light.setFrameShape(QFrame.StyledPanel)
        self.indicator_light.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_9 = QHBoxLayout(self.indicator_light)
#ifndef Q_OS_MAC
        self.horizontalLayout_9.setSpacing(-1)
#endif
        self.horizontalLayout_9.setObjectName(u"horizontalLayout_9")
        self.horizontalLayout_9.setContentsMargins(12, 12, 12, 12)
        self.speed_warning_light = QLabel(self.indicator_light)
        self.speed_warning_light.setObjectName(u"speed_warning_light")
        self.speed_warning_light.setMinimumSize(QSize(20, 20))
        self.speed_warning_light.setMaximumSize(QSize(20, 20))
        self.speed_warning_light.setPixmap(QPixmap(u":/icons/led_icons/led-off.png"))
        self.speed_warning_light.setScaledContents(True)

        self.horizontalLayout_9.addWidget(self.speed_warning_light)

        self.horizontalSpacer_2 = QSpacerItem(70, 20, QSizePolicy.Policy.Fixed, QSizePolicy.Policy.Minimum)

        self.horizontalLayout_9.addItem(self.horizontalSpacer_2)

        self.temperature_warning_light = QLabel(self.indicator_light)
        self.temperature_warning_light.setObjectName(u"temperature_warning_light")
        self.temperature_warning_light.setMinimumSize(QSize(20, 20))
        self.temperature_warning_light.setMaximumSize(QSize(20, 20))
        self.temperature_warning_light.setPixmap(QPixmap(u":/icons/led_icons/led-off.png"))
        self.temperature_warning_light.setScaledContents(True)

        self.horizontalLayout_9.addWidget(self.temperature_warning_light)

        self.horizontalLayout_9.setStretch(0, 1)

        self.verticalLayout_3.addWidget(self.indicator_light)

        self.nodes_data = QFrame(self.main_dashboard)
        self.nodes_data.setObjectName(u"nodes_data")
        sizePolicy5 = QSizePolicy(QSizePolicy.Policy.Preferred, QSizePolicy.Policy.MinimumExpanding)
        sizePolicy5.setHorizontalStretch(0)
        sizePolicy5.setVerticalStretch(0)
        sizePolicy5.setHeightForWidth(self.nodes_data.sizePolicy().hasHeightForWidth())
        self.nodes_data.setSizePolicy(sizePolicy5)
        self.nodes_data.setStyleSheet(u"")
        self.nodes_data.setFrameShape(QFrame.StyledPanel)
        self.nodes_data.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_3 = QHBoxLayout(self.nodes_data)
        self.horizontalLayout_3.setSpacing(0)
        self.horizontalLayout_3.setObjectName(u"horizontalLayout_3")
        self.horizontalLayout_3.setContentsMargins(0, 0, 0, 0)
        self.speed_node = QFrame(self.nodes_data)
        self.speed_node.setObjectName(u"speed_node")
        self.speed_node.setMaximumSize(QSize(16777215, 16777215))
        self.speed_node.setFrameShape(QFrame.Panel)
        self.speed_node.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_4 = QHBoxLayout(self.speed_node)
        self.horizontalLayout_4.setSpacing(0)
        self.horizontalLayout_4.setObjectName(u"horizontalLayout_4")
        self.horizontalLayout_4.setContentsMargins(0, 0, 0, 0)
        self.frame_speed = QFrame(self.speed_node)
        self.frame_speed.setObjectName(u"frame_speed")
        self.frame_speed.setMinimumSize(QSize(0, 0))
        self.frame_speed.setFrameShape(QFrame.StyledPanel)
        self.frame_speed.setFrameShadow(QFrame.Raised)
        self.verticalLayout_17 = QVBoxLayout(self.frame_speed)
        self.verticalLayout_17.setSpacing(0)
        self.verticalLayout_17.setObjectName(u"verticalLayout_17")
        self.verticalLayout_17.setContentsMargins(0, 0, 0, 0)
        self.speed_main_frame = QFrame(self.frame_speed)
        self.speed_main_frame.setObjectName(u"speed_main_frame")
        self.speed_main_frame.setFrameShape(QFrame.StyledPanel)
        self.speed_main_frame.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_16 = QHBoxLayout(self.speed_main_frame)
        self.horizontalLayout_16.setSpacing(2)
        self.horizontalLayout_16.setObjectName(u"horizontalLayout_16")
        self.horizontalLayout_16.setContentsMargins(0, 0, 0, 0)
        self.speed_data_frame = QFrame(self.speed_main_frame)
        self.speed_data_frame.setObjectName(u"speed_data_frame")
        self.speed_data_frame.setFrameShape(QFrame.StyledPanel)
        self.speed_data_frame.setFrameShadow(QFrame.Raised)
        self.verticalLayout_20 = QVBoxLayout(self.speed_data_frame)
        self.verticalLayout_20.setSpacing(0)
        self.verticalLayout_20.setObjectName(u"verticalLayout_20")
        self.verticalLayout_20.setContentsMargins(0, 0, 0, 0)
        self.value_lbl = QLabel(self.speed_data_frame)
        self.value_lbl.setObjectName(u"value_lbl")
        self.value_lbl.setMinimumSize(QSize(0, 30))
        self.value_lbl.setMaximumSize(QSize(16777215, 30))
        font1 = QFont()
        font1.setPointSize(14)
        font1.setBold(True)
        self.value_lbl.setFont(font1)
        self.value_lbl.setStyleSheet(u"")
        self.value_lbl.setAlignment(Qt.AlignCenter)

        self.verticalLayout_20.addWidget(self.value_lbl)

        self.frame_20 = QFrame(self.speed_data_frame)
        self.frame_20.setObjectName(u"frame_20")
        self.frame_20.setStyleSheet(u"border: none")
        self.frame_20.setFrameShape(QFrame.StyledPanel)
        self.frame_20.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_44 = QHBoxLayout(self.frame_20)
        self.horizontalLayout_44.setSpacing(2)
        self.horizontalLayout_44.setObjectName(u"horizontalLayout_44")
        self.horizontalLayout_44.setContentsMargins(0, 0, 0, 0)
        self.speed_value = QLabel(self.frame_20)
        self.speed_value.setObjectName(u"speed_value")
        self.speed_value.setMinimumSize(QSize(100, 0))
        font2 = QFont()
        font2.setPointSize(38)
        self.speed_value.setFont(font2)
        self.speed_value.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.horizontalLayout_44.addWidget(self.speed_value)

        self.speed_unit = QLabel(self.frame_20)
        self.speed_unit.setObjectName(u"speed_unit")
        self.speed_unit.setMinimumSize(QSize(35, 0))
        font3 = QFont()
        font3.setPointSize(30)
        self.speed_unit.setFont(font3)
        self.speed_unit.setMargin(5)

        self.horizontalLayout_44.addWidget(self.speed_unit)

        self.horizontalLayout_44.setStretch(1, 4)

        self.verticalLayout_20.addWidget(self.frame_20)


        self.horizontalLayout_16.addWidget(self.speed_data_frame)

        self.speed_status_frame = QFrame(self.speed_main_frame)
        self.speed_status_frame.setObjectName(u"speed_status_frame")
        self.speed_status_frame.setFrameShape(QFrame.StyledPanel)
        self.speed_status_frame.setFrameShadow(QFrame.Raised)
        self.verticalLayout_19 = QVBoxLayout(self.speed_status_frame)
        self.verticalLayout_19.setSpacing(0)
        self.verticalLayout_19.setObjectName(u"verticalLayout_19")
        self.verticalLayout_19.setContentsMargins(0, 0, 0, 0)
        self.speed_warning_lbl = QLabel(self.speed_status_frame)
        self.speed_warning_lbl.setObjectName(u"speed_warning_lbl")
        self.speed_warning_lbl.setMinimumSize(QSize(0, 30))
        self.speed_warning_lbl.setMaximumSize(QSize(16777215, 30))
        self.speed_warning_lbl.setFont(font1)
        self.speed_warning_lbl.setAlignment(Qt.AlignCenter)

        self.verticalLayout_19.addWidget(self.speed_warning_lbl)

        self.speed_warning_text = QLabel(self.speed_status_frame)
        self.speed_warning_text.setObjectName(u"speed_warning_text")
        self.speed_warning_text.setMinimumSize(QSize(150, 0))
        font4 = QFont()
        font4.setPointSize(26)
        self.speed_warning_text.setFont(font4)
        self.speed_warning_text.setStyleSheet(u"")
        self.speed_warning_text.setAlignment(Qt.AlignCenter)

        self.verticalLayout_19.addWidget(self.speed_warning_text)


        self.horizontalLayout_16.addWidget(self.speed_status_frame)


        self.verticalLayout_17.addWidget(self.speed_main_frame)

        self.frame_9 = QFrame(self.frame_speed)
        self.frame_9.setObjectName(u"frame_9")
        self.frame_9.setMinimumSize(QSize(0, 40))
        self.frame_9.setMaximumSize(QSize(16777215, 40))
        self.frame_9.setFrameShape(QFrame.StyledPanel)
        self.frame_9.setFrameShadow(QFrame.Raised)
        self.verticalLayout_24 = QVBoxLayout(self.frame_9)
        self.verticalLayout_24.setSpacing(0)
        self.verticalLayout_24.setObjectName(u"verticalLayout_24")
        self.verticalLayout_24.setContentsMargins(0, 0, 0, 0)
        self.speed_text_result = QLabel(self.frame_9)
        self.speed_text_result.setObjectName(u"speed_text_result")
        self.speed_text_result.setMinimumSize(QSize(0, 40))
        self.speed_text_result.setMaximumSize(QSize(16777215, 40))
        font5 = QFont()
        font5.setPointSize(10)
        font5.setBold(True)
        self.speed_text_result.setFont(font5)
        self.speed_text_result.setIndent(10)

        self.verticalLayout_24.addWidget(self.speed_text_result)


        self.verticalLayout_17.addWidget(self.frame_9)


        self.horizontalLayout_4.addWidget(self.frame_speed)

        self.horizontalLayout_4.setStretch(0, 5)

        self.horizontalLayout_3.addWidget(self.speed_node)

        self.temperature_node = QFrame(self.nodes_data)
        self.temperature_node.setObjectName(u"temperature_node")
        self.temperature_node.setMaximumSize(QSize(16777215, 16777215))
        self.temperature_node.setFrameShape(QFrame.Panel)
        self.temperature_node.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_34 = QHBoxLayout(self.temperature_node)
        self.horizontalLayout_34.setSpacing(0)
        self.horizontalLayout_34.setObjectName(u"horizontalLayout_34")
        self.horizontalLayout_34.setContentsMargins(0, 0, 0, 0)
        self.frame_temperature = QFrame(self.temperature_node)
        self.frame_temperature.setObjectName(u"frame_temperature")
        self.frame_temperature.setMinimumSize(QSize(0, 0))
        self.frame_temperature.setFrameShape(QFrame.StyledPanel)
        self.frame_temperature.setFrameShadow(QFrame.Raised)
        self.verticalLayout_18 = QVBoxLayout(self.frame_temperature)
        self.verticalLayout_18.setSpacing(0)
        self.verticalLayout_18.setObjectName(u"verticalLayout_18")
        self.verticalLayout_18.setContentsMargins(0, 0, 0, 0)
        self.temperature_main_frame = QFrame(self.frame_temperature)
        self.temperature_main_frame.setObjectName(u"temperature_main_frame")
        self.temperature_main_frame.setFrameShape(QFrame.StyledPanel)
        self.temperature_main_frame.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_30 = QHBoxLayout(self.temperature_main_frame)
        self.horizontalLayout_30.setSpacing(2)
        self.horizontalLayout_30.setObjectName(u"horizontalLayout_30")
        self.horizontalLayout_30.setContentsMargins(0, 0, 0, 0)
        self.temperature_data_frame = QFrame(self.temperature_main_frame)
        self.temperature_data_frame.setObjectName(u"temperature_data_frame")
        self.temperature_data_frame.setFrameShape(QFrame.StyledPanel)
        self.temperature_data_frame.setFrameShadow(QFrame.Raised)
        self.verticalLayout_21 = QVBoxLayout(self.temperature_data_frame)
        self.verticalLayout_21.setSpacing(0)
        self.verticalLayout_21.setObjectName(u"verticalLayout_21")
        self.verticalLayout_21.setContentsMargins(0, 0, 0, 0)
        self.label_20 = QLabel(self.temperature_data_frame)
        self.label_20.setObjectName(u"label_20")
        self.label_20.setMinimumSize(QSize(0, 30))
        self.label_20.setMaximumSize(QSize(16777215, 30))
        self.label_20.setFont(font1)
        self.label_20.setAlignment(Qt.AlignCenter)

        self.verticalLayout_21.addWidget(self.label_20)

        self.frame_22 = QFrame(self.temperature_data_frame)
        self.frame_22.setObjectName(u"frame_22")
        self.frame_22.setStyleSheet(u"border: none")
        self.frame_22.setFrameShape(QFrame.StyledPanel)
        self.frame_22.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_45 = QHBoxLayout(self.frame_22)
        self.horizontalLayout_45.setSpacing(2)
        self.horizontalLayout_45.setObjectName(u"horizontalLayout_45")
        self.horizontalLayout_45.setContentsMargins(0, 0, 0, 0)
        self.temperature_value = QLabel(self.frame_22)
        self.temperature_value.setObjectName(u"temperature_value")
        self.temperature_value.setMinimumSize(QSize(100, 0))
        self.temperature_value.setFont(font2)
        self.temperature_value.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)
        self.temperature_value.setIndent(-1)

        self.horizontalLayout_45.addWidget(self.temperature_value)

        self.temperature_unit = QLabel(self.frame_22)
        self.temperature_unit.setObjectName(u"temperature_unit")
        self.temperature_unit.setMinimumSize(QSize(35, 0))
        self.temperature_unit.setFont(font3)

        self.horizontalLayout_45.addWidget(self.temperature_unit)

        self.horizontalLayout_45.setStretch(0, 6)
        self.horizontalLayout_45.setStretch(1, 4)

        self.verticalLayout_21.addWidget(self.frame_22)


        self.horizontalLayout_30.addWidget(self.temperature_data_frame)

        self.temperature_status_frame = QFrame(self.temperature_main_frame)
        self.temperature_status_frame.setObjectName(u"temperature_status_frame")
        self.temperature_status_frame.setFrameShape(QFrame.StyledPanel)
        self.temperature_status_frame.setFrameShadow(QFrame.Raised)
        self.verticalLayout_22 = QVBoxLayout(self.temperature_status_frame)
        self.verticalLayout_22.setSpacing(0)
        self.verticalLayout_22.setObjectName(u"verticalLayout_22")
        self.verticalLayout_22.setContentsMargins(0, 0, 0, 0)
        self.temperature_warning_lbl = QLabel(self.temperature_status_frame)
        self.temperature_warning_lbl.setObjectName(u"temperature_warning_lbl")
        self.temperature_warning_lbl.setMinimumSize(QSize(0, 30))
        self.temperature_warning_lbl.setMaximumSize(QSize(16777215, 30))
        self.temperature_warning_lbl.setFont(font1)
        self.temperature_warning_lbl.setAlignment(Qt.AlignCenter)

        self.verticalLayout_22.addWidget(self.temperature_warning_lbl)

        self.temperature_warning_text = QLabel(self.temperature_status_frame)
        self.temperature_warning_text.setObjectName(u"temperature_warning_text")
        self.temperature_warning_text.setMinimumSize(QSize(150, 0))
        self.temperature_warning_text.setFont(font4)
        self.temperature_warning_text.setAlignment(Qt.AlignCenter)

        self.verticalLayout_22.addWidget(self.temperature_warning_text)


        self.horizontalLayout_30.addWidget(self.temperature_status_frame)


        self.verticalLayout_18.addWidget(self.temperature_main_frame)

        self.frame_23 = QFrame(self.frame_temperature)
        self.frame_23.setObjectName(u"frame_23")
        self.frame_23.setMinimumSize(QSize(0, 40))
        self.frame_23.setMaximumSize(QSize(16777215, 40))
        self.frame_23.setFrameShape(QFrame.StyledPanel)
        self.frame_23.setFrameShadow(QFrame.Raised)
        self.verticalLayout_25 = QVBoxLayout(self.frame_23)
        self.verticalLayout_25.setSpacing(0)
        self.verticalLayout_25.setObjectName(u"verticalLayout_25")
        self.verticalLayout_25.setContentsMargins(0, 0, 0, 0)
        self.temperature_text_result = QLabel(self.frame_23)
        self.temperature_text_result.setObjectName(u"temperature_text_result")
        self.temperature_text_result.setMinimumSize(QSize(0, 40))
        self.temperature_text_result.setMaximumSize(QSize(16777215, 40))
        self.temperature_text_result.setFont(font5)
        self.temperature_text_result.setIndent(10)

        self.verticalLayout_25.addWidget(self.temperature_text_result)


        self.verticalLayout_18.addWidget(self.frame_23)


        self.horizontalLayout_34.addWidget(self.frame_temperature)

        self.horizontalLayout_34.setStretch(0, 5)

        self.horizontalLayout_3.addWidget(self.temperature_node)


        self.verticalLayout_3.addWidget(self.nodes_data)

        self.nodes_status = QFrame(self.main_dashboard)
        self.nodes_status.setObjectName(u"nodes_status")
        sizePolicy3.setHeightForWidth(self.nodes_status.sizePolicy().hasHeightForWidth())
        self.nodes_status.setSizePolicy(sizePolicy3)
        self.nodes_status.setFrameShape(QFrame.StyledPanel)
        self.nodes_status.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_8 = QHBoxLayout(self.nodes_status)
        self.horizontalLayout_8.setSpacing(0)
        self.horizontalLayout_8.setObjectName(u"horizontalLayout_8")
        self.horizontalLayout_8.setContentsMargins(0, 0, 0, 0)
        self.speed_frame = QFrame(self.nodes_status)
        self.speed_frame.setObjectName(u"speed_frame")
        sizePolicy6 = QSizePolicy(QSizePolicy.Policy.Preferred, QSizePolicy.Policy.Maximum)
        sizePolicy6.setHorizontalStretch(0)
        sizePolicy6.setVerticalStretch(0)
        sizePolicy6.setHeightForWidth(self.speed_frame.sizePolicy().hasHeightForWidth())
        self.speed_frame.setSizePolicy(sizePolicy6)
        self.speed_frame.setMaximumSize(QSize(16777215, 250))
        self.speed_frame.setFrameShape(QFrame.StyledPanel)
        self.speed_frame.setFrameShadow(QFrame.Raised)
        self.verticalLayout_13 = QVBoxLayout(self.speed_frame)
        self.verticalLayout_13.setSpacing(0)
        self.verticalLayout_13.setObjectName(u"verticalLayout_13")
        self.verticalLayout_13.setContentsMargins(0, 0, 0, 0)
        self.speed_header = QFrame(self.speed_frame)
        self.speed_header.setObjectName(u"speed_header")
        self.speed_header.setFrameShape(QFrame.StyledPanel)
        self.speed_header.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_17 = QHBoxLayout(self.speed_header)
        self.horizontalLayout_17.setObjectName(u"horizontalLayout_17")
        self.horizontalLayout_17.setContentsMargins(0, 9, 0, 9)
        self.speed_lbl = QLabel(self.speed_header)
        self.speed_lbl.setObjectName(u"speed_lbl")
        sizePolicy7 = QSizePolicy(QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Preferred)
        sizePolicy7.setHorizontalStretch(0)
        sizePolicy7.setVerticalStretch(0)
        sizePolicy7.setHeightForWidth(self.speed_lbl.sizePolicy().hasHeightForWidth())
        self.speed_lbl.setSizePolicy(sizePolicy7)
        self.speed_lbl.setMinimumSize(QSize(130, 30))
        self.speed_lbl.setMaximumSize(QSize(130, 16777215))
        self.speed_lbl.setFont(font1)
        self.speed_lbl.setIndent(10)

        self.horizontalLayout_17.addWidget(self.speed_lbl, 0, Qt.AlignLeft)


        self.verticalLayout_13.addWidget(self.speed_header)

        self.speed_info = QFrame(self.speed_frame)
        self.speed_info.setObjectName(u"speed_info")
        self.speed_info.setFrameShape(QFrame.StyledPanel)
        self.speed_info.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_19 = QHBoxLayout(self.speed_info)
        self.horizontalLayout_19.setSpacing(0)
        self.horizontalLayout_19.setObjectName(u"horizontalLayout_19")
        self.horizontalLayout_19.setContentsMargins(0, 0, 0, 0)
        self.frame_19 = QFrame(self.speed_info)
        self.frame_19.setObjectName(u"frame_19")
        self.frame_19.setMinimumSize(QSize(80, 0))
        self.frame_19.setMaximumSize(QSize(16777215, 16777215))
        self.frame_19.setFrameShape(QFrame.StyledPanel)
        self.frame_19.setFrameShadow(QFrame.Raised)
        self.verticalLayout_15 = QVBoxLayout(self.frame_19)
        self.verticalLayout_15.setSpacing(0)
        self.verticalLayout_15.setObjectName(u"verticalLayout_15")
        self.verticalLayout_15.setContentsMargins(0, 0, 0, 0)
        self.speed_id = QLabel(self.frame_19)
        self.speed_id.setObjectName(u"speed_id")
        font6 = QFont()
        font6.setPointSize(10)
        self.speed_id.setFont(font6)
        self.speed_id.setIndent(10)

        self.verticalLayout_15.addWidget(self.speed_id)

        self.speed_status = QLabel(self.frame_19)
        self.speed_status.setObjectName(u"speed_status")
        self.speed_status.setFont(font6)
        self.speed_status.setIndent(10)

        self.verticalLayout_15.addWidget(self.speed_status)

        self.speed_threshold = QLabel(self.frame_19)
        self.speed_threshold.setObjectName(u"speed_threshold")
        self.speed_threshold.setFont(font6)
        self.speed_threshold.setIndent(10)

        self.verticalLayout_15.addWidget(self.speed_threshold)


        self.horizontalLayout_19.addWidget(self.frame_19)

        self.frame_24 = QFrame(self.speed_info)
        self.frame_24.setObjectName(u"frame_24")
        self.frame_24.setFrameShape(QFrame.StyledPanel)
        self.frame_24.setFrameShadow(QFrame.Raised)
        self.verticalLayout_16 = QVBoxLayout(self.frame_24)
#ifndef Q_OS_MAC
        self.verticalLayout_16.setSpacing(-1)
#endif
        self.verticalLayout_16.setObjectName(u"verticalLayout_16")
        self.verticalLayout_16.setContentsMargins(0, 0, 0, 0)
        self.frame_25 = QFrame(self.frame_24)
        self.frame_25.setObjectName(u"frame_25")
        self.frame_25.setFrameShape(QFrame.StyledPanel)
        self.frame_25.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_28 = QHBoxLayout(self.frame_25)
        self.horizontalLayout_28.setObjectName(u"horizontalLayout_28")
        self.horizontalLayout_28.setContentsMargins(0, 0, 0, 0)
        self.speed_nodeID_output = QLabel(self.frame_25)
        self.speed_nodeID_output.setObjectName(u"speed_nodeID_output")
        self.speed_nodeID_output.setFont(font6)
        self.speed_nodeID_output.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.horizontalLayout_28.addWidget(self.speed_nodeID_output, 0, Qt.AlignRight)

        self.speed_nodeID_input = QLineEdit(self.frame_25)
        self.speed_nodeID_input.setObjectName(u"speed_nodeID_input")
        self.speed_nodeID_input.setMinimumSize(QSize(70, 0))
        self.speed_nodeID_input.setMaximumSize(QSize(70, 16777215))
        self.speed_nodeID_input.setFont(font6)

        self.horizontalLayout_28.addWidget(self.speed_nodeID_input, 0, Qt.AlignRight)


        self.verticalLayout_16.addWidget(self.frame_25)

        self.frame_26 = QFrame(self.frame_24)
        self.frame_26.setObjectName(u"frame_26")
        self.frame_26.setFrameShape(QFrame.StyledPanel)
        self.frame_26.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_32 = QHBoxLayout(self.frame_26)
        self.horizontalLayout_32.setObjectName(u"horizontalLayout_32")
        self.horizontalLayout_32.setContentsMargins(0, 0, 0, 0)
        self.speed_status_checkconnect = QLabel(self.frame_26)
        self.speed_status_checkconnect.setObjectName(u"speed_status_checkconnect")
        self.speed_status_checkconnect.setFont(font5)
        self.speed_status_checkconnect.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.horizontalLayout_32.addWidget(self.speed_status_checkconnect)


        self.verticalLayout_16.addWidget(self.frame_26)

        self.frame_27 = QFrame(self.frame_24)
        self.frame_27.setObjectName(u"frame_27")
        self.frame_27.setFrameShape(QFrame.StyledPanel)
        self.frame_27.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_35 = QHBoxLayout(self.frame_27)
        self.horizontalLayout_35.setObjectName(u"horizontalLayout_35")
        self.horizontalLayout_35.setContentsMargins(0, 0, 0, 0)
        self.speed_threshold_output = QLabel(self.frame_27)
        self.speed_threshold_output.setObjectName(u"speed_threshold_output")
        self.speed_threshold_output.setFont(font6)
        self.speed_threshold_output.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.horizontalLayout_35.addWidget(self.speed_threshold_output, 0, Qt.AlignRight)

        self.speed_threshold_input = QLineEdit(self.frame_27)
        self.speed_threshold_input.setObjectName(u"speed_threshold_input")
        self.speed_threshold_input.setMinimumSize(QSize(70, 0))
        self.speed_threshold_input.setMaximumSize(QSize(70, 16777215))
        self.speed_threshold_input.setFont(font6)

        self.horizontalLayout_35.addWidget(self.speed_threshold_input, 0, Qt.AlignRight)


        self.verticalLayout_16.addWidget(self.frame_27)


        self.horizontalLayout_19.addWidget(self.frame_24)

        self.horizontalLayout_19.setStretch(0, 4)
        self.horizontalLayout_19.setStretch(1, 6)

        self.verticalLayout_13.addWidget(self.speed_info)

        self.verticalLayout_13.setStretch(0, 2)
        self.verticalLayout_13.setStretch(1, 8)

        self.horizontalLayout_8.addWidget(self.speed_frame)

        self.temperature_frame = QFrame(self.nodes_status)
        self.temperature_frame.setObjectName(u"temperature_frame")
        sizePolicy.setHeightForWidth(self.temperature_frame.sizePolicy().hasHeightForWidth())
        self.temperature_frame.setSizePolicy(sizePolicy)
        self.temperature_frame.setMaximumSize(QSize(16777215, 250))
        self.temperature_frame.setFrameShape(QFrame.StyledPanel)
        self.temperature_frame.setFrameShadow(QFrame.Raised)
        self.verticalLayout_12 = QVBoxLayout(self.temperature_frame)
        self.verticalLayout_12.setSpacing(0)
        self.verticalLayout_12.setObjectName(u"verticalLayout_12")
        self.verticalLayout_12.setContentsMargins(0, 0, 0, 0)
        self.temperature_header = QFrame(self.temperature_frame)
        self.temperature_header.setObjectName(u"temperature_header")
        self.temperature_header.setFrameShape(QFrame.StyledPanel)
        self.temperature_header.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_15 = QHBoxLayout(self.temperature_header)
        self.horizontalLayout_15.setObjectName(u"horizontalLayout_15")
        self.horizontalLayout_15.setContentsMargins(0, 9, 0, 9)
        self.angle_lbl = QLabel(self.temperature_header)
        self.angle_lbl.setObjectName(u"angle_lbl")
        sizePolicy7.setHeightForWidth(self.angle_lbl.sizePolicy().hasHeightForWidth())
        self.angle_lbl.setSizePolicy(sizePolicy7)
        self.angle_lbl.setMinimumSize(QSize(130, 30))
        self.angle_lbl.setMaximumSize(QSize(130, 16777215))
        self.angle_lbl.setFont(font1)
        self.angle_lbl.setIndent(10)

        self.horizontalLayout_15.addWidget(self.angle_lbl, 0, Qt.AlignLeft)


        self.verticalLayout_12.addWidget(self.temperature_header)

        self.temperature_info = QFrame(self.temperature_frame)
        self.temperature_info.setObjectName(u"temperature_info")
        self.temperature_info.setFrameShape(QFrame.StyledPanel)
        self.temperature_info.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_18 = QHBoxLayout(self.temperature_info)
        self.horizontalLayout_18.setSpacing(0)
        self.horizontalLayout_18.setObjectName(u"horizontalLayout_18")
        self.horizontalLayout_18.setContentsMargins(0, 0, 0, 0)
        self.frame_15 = QFrame(self.temperature_info)
        self.frame_15.setObjectName(u"frame_15")
        self.frame_15.setMinimumSize(QSize(80, 0))
        self.frame_15.setMaximumSize(QSize(16777215, 16777215))
        self.frame_15.setFrameShape(QFrame.StyledPanel)
        self.frame_15.setFrameShadow(QFrame.Raised)
        self.verticalLayout_11 = QVBoxLayout(self.frame_15)
        self.verticalLayout_11.setObjectName(u"verticalLayout_11")
        self.verticalLayout_11.setContentsMargins(0, 0, 0, 0)
        self.label_6 = QLabel(self.frame_15)
        self.label_6.setObjectName(u"label_6")
        self.label_6.setFont(font6)
        self.label_6.setIndent(10)

        self.verticalLayout_11.addWidget(self.label_6)

        self.label_7 = QLabel(self.frame_15)
        self.label_7.setObjectName(u"label_7")
        self.label_7.setFont(font6)
        self.label_7.setIndent(10)

        self.verticalLayout_11.addWidget(self.label_7)

        self.label_9 = QLabel(self.frame_15)
        self.label_9.setObjectName(u"label_9")
        self.label_9.setFont(font6)
        self.label_9.setIndent(10)

        self.verticalLayout_11.addWidget(self.label_9)


        self.horizontalLayout_18.addWidget(self.frame_15)

        self.frame_16 = QFrame(self.temperature_info)
        self.frame_16.setObjectName(u"frame_16")
        self.frame_16.setFrameShape(QFrame.StyledPanel)
        self.frame_16.setFrameShadow(QFrame.Raised)
        self.verticalLayout_14 = QVBoxLayout(self.frame_16)
#ifndef Q_OS_MAC
        self.verticalLayout_14.setSpacing(-1)
#endif
        self.verticalLayout_14.setObjectName(u"verticalLayout_14")
        self.verticalLayout_14.setContentsMargins(0, 0, 0, 0)
        self.frame_17 = QFrame(self.frame_16)
        self.frame_17.setObjectName(u"frame_17")
        self.frame_17.setFrameShape(QFrame.StyledPanel)
        self.frame_17.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_27 = QHBoxLayout(self.frame_17)
        self.horizontalLayout_27.setObjectName(u"horizontalLayout_27")
        self.horizontalLayout_27.setContentsMargins(0, 0, 0, 0)
        self.temperature_nodeID_output = QLabel(self.frame_17)
        self.temperature_nodeID_output.setObjectName(u"temperature_nodeID_output")
        self.temperature_nodeID_output.setFont(font6)
        self.temperature_nodeID_output.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.horizontalLayout_27.addWidget(self.temperature_nodeID_output, 0, Qt.AlignRight)

        self.temperature_nodeID_input = QLineEdit(self.frame_17)
        self.temperature_nodeID_input.setObjectName(u"temperature_nodeID_input")
        self.temperature_nodeID_input.setMinimumSize(QSize(70, 0))
        self.temperature_nodeID_input.setMaximumSize(QSize(70, 16777215))
        self.temperature_nodeID_input.setFont(font6)

        self.horizontalLayout_27.addWidget(self.temperature_nodeID_input, 0, Qt.AlignRight)


        self.verticalLayout_14.addWidget(self.frame_17)

        self.frame_18 = QFrame(self.frame_16)
        self.frame_18.setObjectName(u"frame_18")
        self.frame_18.setFrameShape(QFrame.StyledPanel)
        self.frame_18.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_31 = QHBoxLayout(self.frame_18)
        self.horizontalLayout_31.setObjectName(u"horizontalLayout_31")
        self.horizontalLayout_31.setContentsMargins(0, 0, 0, 0)
        self.temperature_status_checkconnect = QLabel(self.frame_18)
        self.temperature_status_checkconnect.setObjectName(u"temperature_status_checkconnect")
        self.temperature_status_checkconnect.setFont(font5)
        self.temperature_status_checkconnect.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.horizontalLayout_31.addWidget(self.temperature_status_checkconnect)


        self.verticalLayout_14.addWidget(self.frame_18)

        self.frame_21 = QFrame(self.frame_16)
        self.frame_21.setObjectName(u"frame_21")
        self.frame_21.setFrameShape(QFrame.StyledPanel)
        self.frame_21.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_33 = QHBoxLayout(self.frame_21)
        self.horizontalLayout_33.setObjectName(u"horizontalLayout_33")
        self.horizontalLayout_33.setContentsMargins(0, 0, 0, 0)
        self.temperature_threshold_output = QLabel(self.frame_21)
        self.temperature_threshold_output.setObjectName(u"temperature_threshold_output")
        self.temperature_threshold_output.setFont(font6)
        self.temperature_threshold_output.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.horizontalLayout_33.addWidget(self.temperature_threshold_output, 0, Qt.AlignRight)

        self.temperature_threshold_input = QLineEdit(self.frame_21)
        self.temperature_threshold_input.setObjectName(u"temperature_threshold_input")
        self.temperature_threshold_input.setMinimumSize(QSize(70, 0))
        self.temperature_threshold_input.setMaximumSize(QSize(70, 16777215))
        self.temperature_threshold_input.setFont(font6)

        self.horizontalLayout_33.addWidget(self.temperature_threshold_input, 0, Qt.AlignRight)


        self.verticalLayout_14.addWidget(self.frame_21)


        self.horizontalLayout_18.addWidget(self.frame_16)

        self.horizontalLayout_18.setStretch(0, 4)
        self.horizontalLayout_18.setStretch(1, 6)

        self.verticalLayout_12.addWidget(self.temperature_info)

        self.verticalLayout_12.setStretch(0, 2)
        self.verticalLayout_12.setStretch(1, 8)

        self.horizontalLayout_8.addWidget(self.temperature_frame)


        self.verticalLayout_3.addWidget(self.nodes_status)


        self.verticalLayout_6.addWidget(self.main_dashboard)

        self.control_btn = QFrame(self.dashboard)
        self.control_btn.setObjectName(u"control_btn")
        self.control_btn.setFrameShape(QFrame.StyledPanel)
        self.control_btn.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_13 = QHBoxLayout(self.control_btn)
        self.horizontalLayout_13.setObjectName(u"horizontalLayout_13")
        self.start_btn = QPushButton(self.control_btn)
        self.start_btn.setObjectName(u"start_btn")
        self.start_btn.setMinimumSize(QSize(0, 40))
        self.start_btn.setMaximumSize(QSize(150, 16777215))
        self.start_btn.setFont(font)
        self.start_btn.setCursor(QCursor(Qt.CursorShape.PointingHandCursor))
        icon4 = QIcon()
        icon4.addFile(u":/icons/icon/play-circle.png", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        self.start_btn.setIcon(icon4)
        self.start_btn.setIconSize(QSize(24, 24))
        self.start_btn.setCheckable(False)
        self.start_btn.setChecked(False)

        self.horizontalLayout_13.addWidget(self.start_btn)

        self.stop_btn = QPushButton(self.control_btn)
        self.stop_btn.setObjectName(u"stop_btn")
        self.stop_btn.setMinimumSize(QSize(0, 40))
        self.stop_btn.setMaximumSize(QSize(150, 16777215))
        self.stop_btn.setCursor(QCursor(Qt.CursorShape.PointingHandCursor))
        icon5 = QIcon()
        icon5.addFile(u":/icons/icon/stop-circle.png", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        self.stop_btn.setIcon(icon5)
        self.stop_btn.setIconSize(QSize(24, 24))
        self.stop_btn.setCheckable(False)

        self.horizontalLayout_13.addWidget(self.stop_btn)


        self.verticalLayout_6.addWidget(self.control_btn)


        self.verticalLayout_5.addWidget(self.dashboard)

        self.stackedWidget.addWidget(self.home_page)
        self.settings_page = QWidget()
        self.settings_page.setObjectName(u"settings_page")
        self.verticalLayout_7 = QVBoxLayout(self.settings_page)
        self.verticalLayout_7.setSpacing(0)
        self.verticalLayout_7.setObjectName(u"verticalLayout_7")
        self.verticalLayout_7.setContentsMargins(0, 0, 0, 0)
        self.setting_frame = QFrame(self.settings_page)
        self.setting_frame.setObjectName(u"setting_frame")
        self.setting_frame.setFrameShape(QFrame.StyledPanel)
        self.setting_frame.setFrameShadow(QFrame.Raised)
        self.verticalLayout_23 = QVBoxLayout(self.setting_frame)
        self.verticalLayout_23.setSpacing(0)
        self.verticalLayout_23.setObjectName(u"verticalLayout_23")
        self.verticalLayout_23.setContentsMargins(0, 0, 0, -1)
        self.setting_header = QFrame(self.setting_frame)
        self.setting_header.setObjectName(u"setting_header")
        self.setting_header.setMinimumSize(QSize(0, 40))
        self.setting_header.setMaximumSize(QSize(16777215, 40))
        font7 = QFont()
        font7.setPointSize(8)
        font7.setBold(False)
        self.setting_header.setFont(font7)
        self.setting_header.setFrameShape(QFrame.StyledPanel)
        self.setting_header.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_6 = QHBoxLayout(self.setting_header)
        self.horizontalLayout_6.setObjectName(u"horizontalLayout_6")
        self.horizontalLayout_6.setContentsMargins(0, 0, 0, 0)
        self.setting_lbl = QLabel(self.setting_header)
        self.setting_lbl.setObjectName(u"setting_lbl")
        font8 = QFont()
        font8.setPointSize(20)
        font8.setBold(True)
        self.setting_lbl.setFont(font8)
        self.setting_lbl.setIndent(20)

        self.horizontalLayout_6.addWidget(self.setting_lbl)


        self.verticalLayout_23.addWidget(self.setting_header)

        self.setting_content = QFrame(self.setting_frame)
        self.setting_content.setObjectName(u"setting_content")
        font9 = QFont()
        font9.setPointSize(8)
        self.setting_content.setFont(font9)
        self.setting_content.setFrameShape(QFrame.StyledPanel)
        self.setting_content.setFrameShadow(QFrame.Raised)
        self.verticalLayout_26 = QVBoxLayout(self.setting_content)
        self.verticalLayout_26.setSpacing(10)
        self.verticalLayout_26.setObjectName(u"verticalLayout_26")
        self.verticalLayout_26.setContentsMargins(10, 10, 10, 10)
        self.uart_settings = QGroupBox(self.setting_content)
        self.uart_settings.setObjectName(u"uart_settings")
        font10 = QFont()
        font10.setPointSize(16)
        font10.setBold(True)
        self.uart_settings.setFont(font10)
        self.verticalLayout_27 = QVBoxLayout(self.uart_settings)
#ifndef Q_OS_MAC
        self.verticalLayout_27.setSpacing(-1)
#endif
        self.verticalLayout_27.setObjectName(u"verticalLayout_27")
        self.verticalLayout_27.setContentsMargins(5, 5, 5, 5)
        self.row1 = QFrame(self.uart_settings)
        self.row1.setObjectName(u"row1")
        self.row1.setFrameShape(QFrame.StyledPanel)
        self.row1.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_10 = QHBoxLayout(self.row1)
        self.horizontalLayout_10.setObjectName(u"horizontalLayout_10")
        self.horizontalLayout_10.setContentsMargins(0, 0, 0, 0)
        self.channel_frame = QFrame(self.row1)
        self.channel_frame.setObjectName(u"channel_frame")
        self.channel_frame.setFrameShape(QFrame.StyledPanel)
        self.channel_frame.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_11 = QHBoxLayout(self.channel_frame)
        self.horizontalLayout_11.setObjectName(u"horizontalLayout_11")
        self.channel_lbl = QLabel(self.channel_frame)
        self.channel_lbl.setObjectName(u"channel_lbl")
        font11 = QFont()
        font11.setPointSize(12)
        self.channel_lbl.setFont(font11)

        self.horizontalLayout_11.addWidget(self.channel_lbl)

        self.portList = QComboBox(self.channel_frame)
        self.portList.setObjectName(u"portList")
        self.portList.setEnabled(True)
        self.portList.setMinimumSize(QSize(40, 30))
        self.portList.setMaximumSize(QSize(100, 16777215))
        self.portList.setFont(font6)
        self.portList.setCursor(QCursor(Qt.CursorShape.PointingHandCursor))
        self.portList.setDuplicatesEnabled(True)

        self.horizontalLayout_11.addWidget(self.portList)


        self.horizontalLayout_10.addWidget(self.channel_frame)

        self.baudrate_frame = QFrame(self.row1)
        self.baudrate_frame.setObjectName(u"baudrate_frame")
        self.baudrate_frame.setFrameShape(QFrame.StyledPanel)
        self.baudrate_frame.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_12 = QHBoxLayout(self.baudrate_frame)
        self.horizontalLayout_12.setObjectName(u"horizontalLayout_12")
        self.baudrate_lbl = QLabel(self.baudrate_frame)
        self.baudrate_lbl.setObjectName(u"baudrate_lbl")
        self.baudrate_lbl.setFont(font11)

        self.horizontalLayout_12.addWidget(self.baudrate_lbl)

        self.baudList = QComboBox(self.baudrate_frame)
        self.baudList.setObjectName(u"baudList")
        self.baudList.setMinimumSize(QSize(40, 30))
        self.baudList.setMaximumSize(QSize(100, 16777215))
        self.baudList.setFont(font6)
        self.baudList.setCursor(QCursor(Qt.CursorShape.PointingHandCursor))
        self.baudList.setDuplicatesEnabled(True)

        self.horizontalLayout_12.addWidget(self.baudList)


        self.horizontalLayout_10.addWidget(self.baudrate_frame)


        self.verticalLayout_27.addWidget(self.row1)

        self.row2 = QFrame(self.uart_settings)
        self.row2.setObjectName(u"row2")
        self.row2.setFrameShape(QFrame.StyledPanel)
        self.row2.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_14 = QHBoxLayout(self.row2)
        self.horizontalLayout_14.setObjectName(u"horizontalLayout_14")
        self.horizontalLayout_14.setContentsMargins(0, 0, 0, 0)
        self.parity_frame = QFrame(self.row2)
        self.parity_frame.setObjectName(u"parity_frame")
        self.parity_frame.setFrameShape(QFrame.StyledPanel)
        self.parity_frame.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_23 = QHBoxLayout(self.parity_frame)
        self.horizontalLayout_23.setObjectName(u"horizontalLayout_23")
        self.parity_lbl = QLabel(self.parity_frame)
        self.parity_lbl.setObjectName(u"parity_lbl")
        self.parity_lbl.setFont(font11)

        self.horizontalLayout_23.addWidget(self.parity_lbl)

        self.parity = QComboBox(self.parity_frame)
        self.parity.setObjectName(u"parity")
        self.parity.setMinimumSize(QSize(40, 30))
        self.parity.setMaximumSize(QSize(100, 16777215))

        self.horizontalLayout_23.addWidget(self.parity)


        self.horizontalLayout_14.addWidget(self.parity_frame)

        self.stopbits_frame = QFrame(self.row2)
        self.stopbits_frame.setObjectName(u"stopbits_frame")
        self.stopbits_frame.setFrameShape(QFrame.StyledPanel)
        self.stopbits_frame.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_24 = QHBoxLayout(self.stopbits_frame)
        self.horizontalLayout_24.setObjectName(u"horizontalLayout_24")
        self.stopbits_lbl = QLabel(self.stopbits_frame)
        self.stopbits_lbl.setObjectName(u"stopbits_lbl")
        self.stopbits_lbl.setFont(font11)

        self.horizontalLayout_24.addWidget(self.stopbits_lbl)

        self.stopBit = QComboBox(self.stopbits_frame)
        self.stopBit.setObjectName(u"stopBit")
        self.stopBit.setMinimumSize(QSize(40, 30))
        self.stopBit.setMaximumSize(QSize(100, 16777215))

        self.horizontalLayout_24.addWidget(self.stopBit)


        self.horizontalLayout_14.addWidget(self.stopbits_frame)


        self.verticalLayout_27.addWidget(self.row2)

        self.row3 = QFrame(self.uart_settings)
        self.row3.setObjectName(u"row3")
        self.row3.setFrameShape(QFrame.StyledPanel)
        self.row3.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_22 = QHBoxLayout(self.row3)
        self.horizontalLayout_22.setObjectName(u"horizontalLayout_22")
        self.horizontalLayout_22.setContentsMargins(0, 0, 0, 0)
        self.bytesize_frame = QFrame(self.row3)
        self.bytesize_frame.setObjectName(u"bytesize_frame")
        self.bytesize_frame.setFrameShape(QFrame.StyledPanel)
        self.bytesize_frame.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_25 = QHBoxLayout(self.bytesize_frame)
        self.horizontalLayout_25.setObjectName(u"horizontalLayout_25")
        self.bytesize_lbl = QLabel(self.bytesize_frame)
        self.bytesize_lbl.setObjectName(u"bytesize_lbl")
        self.bytesize_lbl.setFont(font11)

        self.horizontalLayout_25.addWidget(self.bytesize_lbl)

        self.byteSize = QComboBox(self.bytesize_frame)
        self.byteSize.setObjectName(u"byteSize")
        self.byteSize.setMinimumSize(QSize(40, 30))
        self.byteSize.setMaximumSize(QSize(100, 16777215))

        self.horizontalLayout_25.addWidget(self.byteSize)


        self.horizontalLayout_22.addWidget(self.bytesize_frame)

        self.uart_grp_btn = QFrame(self.row3)
        self.uart_grp_btn.setObjectName(u"uart_grp_btn")
        self.uart_grp_btn.setFrameShape(QFrame.StyledPanel)
        self.uart_grp_btn.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_29 = QHBoxLayout(self.uart_grp_btn)
        self.horizontalLayout_29.setObjectName(u"horizontalLayout_29")
        self.horizontalLayout_29.setContentsMargins(0, 0, 0, 0)
        self.connect_btn = QPushButton(self.uart_grp_btn)
        self.connect_btn.setObjectName(u"connect_btn")
        self.connect_btn.setMinimumSize(QSize(40, 40))
        self.connect_btn.setMaximumSize(QSize(120, 16777215))
        self.connect_btn.setFont(font5)
        self.connect_btn.setCursor(QCursor(Qt.CursorShape.PointingHandCursor))
        icon6 = QIcon()
        icon6.addFile(u":/icon_green/resource/icon/icon_green/zap.svg", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        icon6.addFile(u":/icon_red/resource/icon/icon_red/zap-off.svg", QSize(), QIcon.Mode.Normal, QIcon.State.On)
        self.connect_btn.setIcon(icon6)
        self.connect_btn.setIconSize(QSize(18, 18))
        self.connect_btn.setCheckable(True)

        self.horizontalLayout_29.addWidget(self.connect_btn)

        self.uart_change_btn = QPushButton(self.uart_grp_btn)
        self.uart_change_btn.setObjectName(u"uart_change_btn")
        self.uart_change_btn.setMinimumSize(QSize(40, 40))
        self.uart_change_btn.setMaximumSize(QSize(120, 16777215))
        self.uart_change_btn.setFont(font5)
        self.uart_change_btn.setCursor(QCursor(Qt.CursorShape.PointingHandCursor))
        icon7 = QIcon()
        icon7.addFile(u":/icon_blue/resource/icon/icon_blue/edit.svg", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        self.uart_change_btn.setIcon(icon7)
        self.uart_change_btn.setIconSize(QSize(18, 18))

        self.horizontalLayout_29.addWidget(self.uart_change_btn)

        self.Uart_Dialog = QFrame(self.uart_grp_btn)
        self.Uart_Dialog.setObjectName(u"Uart_Dialog")
        self.Uart_Dialog.setFrameShape(QFrame.StyledPanel)
        self.Uart_Dialog.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_37 = QHBoxLayout(self.Uart_Dialog)
        self.horizontalLayout_37.setObjectName(u"horizontalLayout_37")
        self.horizontalLayout_37.setContentsMargins(0, 0, 0, 0)
        self.uart_save_btn = QPushButton(self.Uart_Dialog)
        self.uart_save_btn.setObjectName(u"uart_save_btn")
        self.uart_save_btn.setMinimumSize(QSize(40, 40))
        self.uart_save_btn.setMaximumSize(QSize(120, 16777215))
        self.uart_save_btn.setFont(font5)
        self.uart_save_btn.setCursor(QCursor(Qt.CursorShape.PointingHandCursor))
        icon8 = QIcon()
        icon8.addFile(u":/icon_blue/resource/icon/icon_blue/save.svg", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        self.uart_save_btn.setIcon(icon8)
        self.uart_save_btn.setIconSize(QSize(18, 18))

        self.horizontalLayout_37.addWidget(self.uart_save_btn)

        self.uart_cancel_btn = QPushButton(self.Uart_Dialog)
        self.uart_cancel_btn.setObjectName(u"uart_cancel_btn")
        self.uart_cancel_btn.setEnabled(True)
        self.uart_cancel_btn.setMinimumSize(QSize(40, 40))
        self.uart_cancel_btn.setMaximumSize(QSize(120, 16777215))
        self.uart_cancel_btn.setFont(font5)
        self.uart_cancel_btn.setCursor(QCursor(Qt.CursorShape.PointingHandCursor))
        icon9 = QIcon()
        icon9.addFile(u":/icon_red/resource/icon/icon_red/x.svg", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        self.uart_cancel_btn.setIcon(icon9)
        self.uart_cancel_btn.setIconSize(QSize(19, 19))

        self.horizontalLayout_37.addWidget(self.uart_cancel_btn)


        self.horizontalLayout_29.addWidget(self.Uart_Dialog)


        self.horizontalLayout_22.addWidget(self.uart_grp_btn)

        self.horizontalLayout_22.setStretch(0, 5)
        self.horizontalLayout_22.setStretch(1, 5)

        self.verticalLayout_27.addWidget(self.row3)

        self.row4 = QFrame(self.uart_settings)
        self.row4.setObjectName(u"row4")
        self.row4.setMinimumSize(QSize(0, 50))
        self.row4.setFrameShape(QFrame.StyledPanel)
        self.row4.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_26 = QHBoxLayout(self.row4)
        self.horizontalLayout_26.setSpacing(0)
        self.horizontalLayout_26.setObjectName(u"horizontalLayout_26")
        self.horizontalLayout_26.setContentsMargins(0, 0, 0, 0)
        self.uart_noti_frame = QFrame(self.row4)
        self.uart_noti_frame.setObjectName(u"uart_noti_frame")
        self.uart_noti_frame.setFrameShape(QFrame.StyledPanel)
        self.uart_noti_frame.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_21 = QHBoxLayout(self.uart_noti_frame)
        self.horizontalLayout_21.setSpacing(0)
        self.horizontalLayout_21.setObjectName(u"horizontalLayout_21")
        self.horizontalLayout_21.setContentsMargins(0, 0, 0, 0)
        self.com_result_text = QLabel(self.uart_noti_frame)
        self.com_result_text.setObjectName(u"com_result_text")
        self.com_result_text.setMinimumSize(QSize(0, 40))
        self.com_result_text.setMaximumSize(QSize(16777215, 100))
        self.com_result_text.setFont(font10)
        self.com_result_text.setIndent(10)

        self.horizontalLayout_21.addWidget(self.com_result_text)


        self.horizontalLayout_26.addWidget(self.uart_noti_frame)


        self.verticalLayout_27.addWidget(self.row4)


        self.verticalLayout_26.addWidget(self.uart_settings)

        self.setting_save = QGroupBox(self.setting_content)
        self.setting_save.setObjectName(u"setting_save")
        self.setting_save.setMinimumSize(QSize(0, 90))
        self.setting_save.setMaximumSize(QSize(16777215, 80))
        font12 = QFont()
        font12.setPointSize(14)
        self.setting_save.setFont(font12)
        self.setting_save.setStyleSheet(u"")
        self.horizontalLayout_20 = QHBoxLayout(self.setting_save)
        self.horizontalLayout_20.setObjectName(u"horizontalLayout_20")
        self.horizontalLayout_20.setContentsMargins(-1, 0, -1, 9)
        self.frame = QFrame(self.setting_save)
        self.frame.setObjectName(u"frame")
        self.frame.setFrameShape(QFrame.StyledPanel)
        self.frame.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_36 = QHBoxLayout(self.frame)
#ifndef Q_OS_MAC
        self.horizontalLayout_36.setSpacing(-1)
#endif
        self.horizontalLayout_36.setObjectName(u"horizontalLayout_36")
        self.horizontalLayout_36.setContentsMargins(0, 0, 5, 0)
        self.folder_line = QLineEdit(self.frame)
        self.folder_line.setObjectName(u"folder_line")
        self.folder_line.setMinimumSize(QSize(0, 30))
        self.folder_line.setMaximumSize(QSize(16777215, 16777215))
        self.folder_line.setFont(font6)
        self.folder_line.setReadOnly(True)

        self.horizontalLayout_36.addWidget(self.folder_line)

        self.browse_btn = QPushButton(self.frame)
        self.browse_btn.setObjectName(u"browse_btn")
        sizePolicy3.setHeightForWidth(self.browse_btn.sizePolicy().hasHeightForWidth())
        self.browse_btn.setSizePolicy(sizePolicy3)
        self.browse_btn.setMinimumSize(QSize(100, 40))
        self.browse_btn.setMaximumSize(QSize(100, 40))
        self.browse_btn.setFont(font5)
        self.browse_btn.setCursor(QCursor(Qt.CursorShape.PointingHandCursor))
        icon10 = QIcon()
        icon10.addFile(u":/icon_blue/resource/icon/icon_blue/folder.svg", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        self.browse_btn.setIcon(icon10)
        self.browse_btn.setIconSize(QSize(18, 18))

        self.horizontalLayout_36.addWidget(self.browse_btn)


        self.horizontalLayout_20.addWidget(self.frame)


        self.verticalLayout_26.addWidget(self.setting_save)

        self.verticalSpacer_2 = QSpacerItem(20, 40, QSizePolicy.Policy.Minimum, QSizePolicy.Policy.Fixed)

        self.verticalLayout_26.addItem(self.verticalSpacer_2)


        self.verticalLayout_23.addWidget(self.setting_content)


        self.verticalLayout_7.addWidget(self.setting_frame)

        self.stackedWidget.addWidget(self.settings_page)

        self.horizontalLayout_5.addWidget(self.stackedWidget)


        self.verticalLayout_2.addWidget(self.panel)


        self.horizontalLayout.addWidget(self.main_body)

        MainWindow.setCentralWidget(self.centralwidget)

        self.retranslateUi(MainWindow)

        self.stackedWidget.setCurrentIndex(0)
        self.portList.setCurrentIndex(-1)
        self.baudList.setCurrentIndex(-1)


        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate("MainWindow", u"MainWindow", None))
        self.home_button.setText(QCoreApplication.translate("MainWindow", u"Home", None))
        self.settings_button.setText(QCoreApplication.translate("MainWindow", u"Settings", None))
        self.exit_btn.setText(QCoreApplication.translate("MainWindow", u"Exit", None))
        self.menu_btn.setText("")
        self.header_title.setText(QCoreApplication.translate("MainWindow", u"SPEED AND TEMPERATURE MONITORING SYSTEM", None))
        self.speed_warning_light.setText("")
        self.temperature_warning_light.setText("")
        self.value_lbl.setText(QCoreApplication.translate("MainWindow", u"VALUE", None))
        self.speed_value.setText(QCoreApplication.translate("MainWindow", u"0", None))
        self.speed_unit.setText(QCoreApplication.translate("MainWindow", u"km/h", None))
        self.speed_warning_lbl.setText(QCoreApplication.translate("MainWindow", u"WARNING", None))
        self.speed_warning_text.setText(QCoreApplication.translate("MainWindow", u"_", None))
        self.speed_text_result.setText(QCoreApplication.translate("MainWindow", u"Successfully", None))
        self.label_20.setText(QCoreApplication.translate("MainWindow", u"VALUE", None))
        self.temperature_value.setText(QCoreApplication.translate("MainWindow", u"0", None))
        self.temperature_unit.setText(QCoreApplication.translate("MainWindow", u"\u00b0C", None))
        self.temperature_warning_lbl.setText(QCoreApplication.translate("MainWindow", u"WARNING", None))
        self.temperature_warning_text.setText(QCoreApplication.translate("MainWindow", u"_", None))
        self.temperature_text_result.setText(QCoreApplication.translate("MainWindow", u"Successfully", None))
        self.speed_lbl.setText(QCoreApplication.translate("MainWindow", u"Speed", None))
        self.speed_id.setText(QCoreApplication.translate("MainWindow", u"Node ID", None))
        self.speed_status.setText(QCoreApplication.translate("MainWindow", u"Status", None))
        self.speed_threshold.setText(QCoreApplication.translate("MainWindow", u"Threshold", None))
        self.speed_nodeID_output.setText(QCoreApplication.translate("MainWindow", u"0", None))
        self.speed_status_checkconnect.setText("")
        self.speed_threshold_output.setText(QCoreApplication.translate("MainWindow", u"0", None))
        self.angle_lbl.setText(QCoreApplication.translate("MainWindow", u"Temperature", None))
        self.label_6.setText(QCoreApplication.translate("MainWindow", u"Node ID", None))
        self.label_7.setText(QCoreApplication.translate("MainWindow", u"Status", None))
        self.label_9.setText(QCoreApplication.translate("MainWindow", u"Threshold", None))
        self.temperature_nodeID_output.setText(QCoreApplication.translate("MainWindow", u"0", None))
        self.temperature_status_checkconnect.setText("")
        self.temperature_threshold_output.setText(QCoreApplication.translate("MainWindow", u"0", None))
        self.start_btn.setText(QCoreApplication.translate("MainWindow", u" Start", None))
        self.stop_btn.setText(QCoreApplication.translate("MainWindow", u"Stop", None))
        self.setting_lbl.setText(QCoreApplication.translate("MainWindow", u"Settings", None))
        self.uart_settings.setTitle(QCoreApplication.translate("MainWindow", u"UART", None))
        self.channel_lbl.setText(QCoreApplication.translate("MainWindow", u"Channel", None))
        self.baudrate_lbl.setText(QCoreApplication.translate("MainWindow", u"BAUD Rate", None))
        self.parity_lbl.setText(QCoreApplication.translate("MainWindow", u"Parity", None))
        self.stopbits_lbl.setText(QCoreApplication.translate("MainWindow", u"Stop bits", None))
        self.bytesize_lbl.setText(QCoreApplication.translate("MainWindow", u"Byte size", None))
#if QT_CONFIG(tooltip)
        self.connect_btn.setToolTip(QCoreApplication.translate("MainWindow", u"<html><head/><body><p>Connect</p></body></html>", None))
#endif // QT_CONFIG(tooltip)
        self.connect_btn.setText(QCoreApplication.translate("MainWindow", u"Connect", None))
        self.uart_change_btn.setText(QCoreApplication.translate("MainWindow", u"Change", None))
        self.uart_save_btn.setText(QCoreApplication.translate("MainWindow", u" Save", None))
        self.uart_cancel_btn.setText(QCoreApplication.translate("MainWindow", u"Cancel", None))
        self.com_result_text.setText(QCoreApplication.translate("MainWindow", u"Connect Successfully", None))
        self.setting_save.setTitle(QCoreApplication.translate("MainWindow", u"Save As", None))
        self.folder_line.setPlaceholderText(QCoreApplication.translate("MainWindow", u"E.g C:\\User\\", None))
        self.browse_btn.setText(QCoreApplication.translate("MainWindow", u" Browse", None))
    # retranslateUi

