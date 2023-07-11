/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <trusswidget.hpp>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionTragwerk_speichern;
    QAction *actionTragwerk_laden;
    QAction *actionAltes_Tragwerk_zeigen;
    QAction *actionNeues_Tragwerk_zeigen;
    QAction *actionVerschiebung_zeigen;
    QAction *actionJointMode;
    QAction *actionConnectionMode;
    QAction *actionForceMode;
    QAction *actionEraserMode;
    QAction *actionSimulieren;
    QAction *actionSteuerung;
    QAction *actionneues_Tragwerk;
    QAction *actionAls_Bild_speichern;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_7;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    TrussWidget *myTrussWidget;
    QHBoxLayout *horizontalLayout_7;
    QLabel *Mouse_coordinate1;
    QLabel *Mouse_coordinate2;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_5;
    QFormLayout *formLayout;
    QLineEdit *E_modul_input;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *Emodul_aktiv;
    QRadioButton *radioButton;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *Emodul_speichern;
    QPushButton *Emodul_laden;
    QFrame *line;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QFormLayout *formLayout_2;
    QLabel *label_3;
    QLineEdit *X_input;
    QLabel *label_4;
    QLineEdit *Y_input;
    QLabel *label_9;
    QLineEdit *Joint_locator;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *addJoint_Button;
    QPushButton *deleteJoint_Button;
    QLabel *label_5;
    QComboBox *Lager;
    QFrame *line_3;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_11;
    QLineEdit *Force_x;
    QLabel *label_12;
    QLineEdit *Force_y;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_13;
    QLineEdit *Force_Locator;
    QPushButton *addForce_Button;
    QPushButton *deleteForce_Button;
    QFrame *line_2;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_4;
    QFormLayout *formLayout_3;
    QLabel *label_7;
    QLineEdit *thickness;
    QLabel *label;
    QLineEdit *Edge_Joint1;
    QLabel *label_2;
    QLineEdit *Edge_Joint2;
    QHBoxLayout *horizontalLayout;
    QPushButton *Knoten_verbinden;
    QPushButton *deleteEdge_Button;
    QSpacerItem *verticalSpacer;
    QMenuBar *menubar;
    QMenu *menuDatei;
    QMenu *menuAnsicht;
    QMenu *menuHilfe;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(851, 848);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setTabShape(QTabWidget::Rounded);
        actionTragwerk_speichern = new QAction(MainWindow);
        actionTragwerk_speichern->setObjectName(QString::fromUtf8("actionTragwerk_speichern"));
        actionTragwerk_laden = new QAction(MainWindow);
        actionTragwerk_laden->setObjectName(QString::fromUtf8("actionTragwerk_laden"));
        actionAltes_Tragwerk_zeigen = new QAction(MainWindow);
        actionAltes_Tragwerk_zeigen->setObjectName(QString::fromUtf8("actionAltes_Tragwerk_zeigen"));
        actionAltes_Tragwerk_zeigen->setCheckable(true);
        actionAltes_Tragwerk_zeigen->setChecked(true);
        actionNeues_Tragwerk_zeigen = new QAction(MainWindow);
        actionNeues_Tragwerk_zeigen->setObjectName(QString::fromUtf8("actionNeues_Tragwerk_zeigen"));
        actionNeues_Tragwerk_zeigen->setCheckable(true);
        actionVerschiebung_zeigen = new QAction(MainWindow);
        actionVerschiebung_zeigen->setObjectName(QString::fromUtf8("actionVerschiebung_zeigen"));
        actionVerschiebung_zeigen->setCheckable(true);
        actionJointMode = new QAction(MainWindow);
        actionJointMode->setObjectName(QString::fromUtf8("actionJointMode"));
        actionJointMode->setCheckable(true);
        actionConnectionMode = new QAction(MainWindow);
        actionConnectionMode->setObjectName(QString::fromUtf8("actionConnectionMode"));
        actionConnectionMode->setCheckable(true);
        actionForceMode = new QAction(MainWindow);
        actionForceMode->setObjectName(QString::fromUtf8("actionForceMode"));
        actionForceMode->setCheckable(true);
        actionEraserMode = new QAction(MainWindow);
        actionEraserMode->setObjectName(QString::fromUtf8("actionEraserMode"));
        actionEraserMode->setCheckable(true);
        actionSimulieren = new QAction(MainWindow);
        actionSimulieren->setObjectName(QString::fromUtf8("actionSimulieren"));
        actionSimulieren->setCheckable(true);
        actionSteuerung = new QAction(MainWindow);
        actionSteuerung->setObjectName(QString::fromUtf8("actionSteuerung"));
        actionneues_Tragwerk = new QAction(MainWindow);
        actionneues_Tragwerk->setObjectName(QString::fromUtf8("actionneues_Tragwerk"));
        actionAls_Bild_speichern = new QAction(MainWindow);
        actionAls_Bild_speichern->setObjectName(QString::fromUtf8("actionAls_Bild_speichern"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy1);
        verticalLayout_7 = new QVBoxLayout(centralwidget);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        myTrussWidget = new TrussWidget(layoutWidget);
        myTrussWidget->setObjectName(QString::fromUtf8("myTrussWidget"));
        myTrussWidget->setMinimumSize(QSize(500, 500));

        verticalLayout_2->addWidget(myTrussWidget);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(0);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setSizeConstraint(QLayout::SetMinimumSize);
        Mouse_coordinate1 = new QLabel(layoutWidget);
        Mouse_coordinate1->setObjectName(QString::fromUtf8("Mouse_coordinate1"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(Mouse_coordinate1->sizePolicy().hasHeightForWidth());
        Mouse_coordinate1->setSizePolicy(sizePolicy2);
        Mouse_coordinate1->setMinimumSize(QSize(70, 0));
        Mouse_coordinate1->setMaximumSize(QSize(17, 16777215));

        horizontalLayout_7->addWidget(Mouse_coordinate1);

        Mouse_coordinate2 = new QLabel(layoutWidget);
        Mouse_coordinate2->setObjectName(QString::fromUtf8("Mouse_coordinate2"));
        sizePolicy2.setHeightForWidth(Mouse_coordinate2->sizePolicy().hasHeightForWidth());
        Mouse_coordinate2->setSizePolicy(sizePolicy2);
        Mouse_coordinate2->setMinimumSize(QSize(70, 0));
        Mouse_coordinate2->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_7->addWidget(Mouse_coordinate2);


        verticalLayout_2->addLayout(horizontalLayout_7);

        splitter->addWidget(layoutWidget);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        verticalLayout_6 = new QVBoxLayout(layoutWidget1);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        groupBox_4 = new QGroupBox(layoutWidget1);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        sizePolicy2.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy2);
        groupBox_4->setMinimumSize(QSize(325, 0));
        groupBox_4->setMaximumSize(QSize(325, 16777215));
        verticalLayout_5 = new QVBoxLayout(groupBox_4);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        E_modul_input = new QLineEdit(groupBox_4);
        E_modul_input->setObjectName(QString::fromUtf8("E_modul_input"));

        formLayout->setWidget(0, QFormLayout::LabelRole, E_modul_input);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        Emodul_aktiv = new QPushButton(groupBox_4);
        Emodul_aktiv->setObjectName(QString::fromUtf8("Emodul_aktiv"));

        horizontalLayout_4->addWidget(Emodul_aktiv);

        radioButton = new QRadioButton(groupBox_4);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));

        horizontalLayout_4->addWidget(radioButton);


        formLayout->setLayout(0, QFormLayout::FieldRole, horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        Emodul_speichern = new QPushButton(groupBox_4);
        Emodul_speichern->setObjectName(QString::fromUtf8("Emodul_speichern"));

        horizontalLayout_5->addWidget(Emodul_speichern);

        Emodul_laden = new QPushButton(groupBox_4);
        Emodul_laden->setObjectName(QString::fromUtf8("Emodul_laden"));

        horizontalLayout_5->addWidget(Emodul_laden);


        formLayout->setLayout(1, QFormLayout::SpanningRole, horizontalLayout_5);


        verticalLayout_5->addLayout(formLayout);


        verticalLayout_6->addWidget(groupBox_4);

        line = new QFrame(layoutWidget1);
        line->setObjectName(QString::fromUtf8("line"));
        sizePolicy2.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy2);
        line->setMinimumSize(QSize(325, 0));
        line->setMaximumSize(QSize(325, 16777215));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_6->addWidget(line);

        groupBox_2 = new QGroupBox(layoutWidget1);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        sizePolicy2.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy2);
        groupBox_2->setMinimumSize(QSize(325, 0));
        groupBox_2->setMaximumSize(QSize(325, 16777215));
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_3);

        X_input = new QLineEdit(groupBox_2);
        X_input->setObjectName(QString::fromUtf8("X_input"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, X_input);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_4);

        Y_input = new QLineEdit(groupBox_2);
        Y_input->setObjectName(QString::fromUtf8("Y_input"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, Y_input);

        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_9);

        Joint_locator = new QLineEdit(groupBox_2);
        Joint_locator->setObjectName(QString::fromUtf8("Joint_locator"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, Joint_locator);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        addJoint_Button = new QPushButton(groupBox_2);
        addJoint_Button->setObjectName(QString::fromUtf8("addJoint_Button"));

        horizontalLayout_6->addWidget(addJoint_Button);

        deleteJoint_Button = new QPushButton(groupBox_2);
        deleteJoint_Button->setObjectName(QString::fromUtf8("deleteJoint_Button"));

        horizontalLayout_6->addWidget(deleteJoint_Button);


        formLayout_2->setLayout(3, QFormLayout::FieldRole, horizontalLayout_6);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout_2->setWidget(4, QFormLayout::LabelRole, label_5);

        Lager = new QComboBox(groupBox_2);
        Lager->addItem(QString());
        Lager->addItem(QString());
        Lager->setObjectName(QString::fromUtf8("Lager"));

        formLayout_2->setWidget(4, QFormLayout::FieldRole, Lager);


        verticalLayout_3->addLayout(formLayout_2);


        verticalLayout_6->addWidget(groupBox_2);

        line_3 = new QFrame(layoutWidget1);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        sizePolicy2.setHeightForWidth(line_3->sizePolicy().hasHeightForWidth());
        line_3->setSizePolicy(sizePolicy2);
        line_3->setMinimumSize(QSize(325, 0));
        line_3->setMaximumSize(QSize(325, 16777215));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout_6->addWidget(line_3);

        groupBox = new QGroupBox(layoutWidget1);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        sizePolicy2.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy2);
        groupBox->setMinimumSize(QSize(325, 0));
        groupBox->setMaximumSize(QSize(325, 16777215));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_2->addWidget(label_11);

        Force_x = new QLineEdit(groupBox);
        Force_x->setObjectName(QString::fromUtf8("Force_x"));

        horizontalLayout_2->addWidget(Force_x);

        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_2->addWidget(label_12);

        Force_y = new QLineEdit(groupBox);
        Force_y->setObjectName(QString::fromUtf8("Force_y"));

        horizontalLayout_2->addWidget(Force_y);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_3->addWidget(label_13);

        Force_Locator = new QLineEdit(groupBox);
        Force_Locator->setObjectName(QString::fromUtf8("Force_Locator"));

        horizontalLayout_3->addWidget(Force_Locator);

        addForce_Button = new QPushButton(groupBox);
        addForce_Button->setObjectName(QString::fromUtf8("addForce_Button"));

        horizontalLayout_3->addWidget(addForce_Button);

        deleteForce_Button = new QPushButton(groupBox);
        deleteForce_Button->setObjectName(QString::fromUtf8("deleteForce_Button"));

        horizontalLayout_3->addWidget(deleteForce_Button);


        verticalLayout->addLayout(horizontalLayout_3);


        verticalLayout_6->addWidget(groupBox);

        line_2 = new QFrame(layoutWidget1);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setMaximumSize(QSize(325, 16777215));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_6->addWidget(line_2);

        groupBox_3 = new QGroupBox(layoutWidget1);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        sizePolicy2.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy2);
        groupBox_3->setMinimumSize(QSize(325, 0));
        groupBox_3->setMaximumSize(QSize(325, 16777215));
        verticalLayout_4 = new QVBoxLayout(groupBox_3);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        formLayout_3 = new QFormLayout();
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_7);

        thickness = new QLineEdit(groupBox_3);
        thickness->setObjectName(QString::fromUtf8("thickness"));

        formLayout_3->setWidget(0, QFormLayout::FieldRole, thickness);

        label = new QLabel(groupBox_3);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, label);

        Edge_Joint1 = new QLineEdit(groupBox_3);
        Edge_Joint1->setObjectName(QString::fromUtf8("Edge_Joint1"));

        formLayout_3->setWidget(1, QFormLayout::FieldRole, Edge_Joint1);

        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout_3->setWidget(2, QFormLayout::LabelRole, label_2);

        Edge_Joint2 = new QLineEdit(groupBox_3);
        Edge_Joint2->setObjectName(QString::fromUtf8("Edge_Joint2"));

        formLayout_3->setWidget(2, QFormLayout::FieldRole, Edge_Joint2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        Knoten_verbinden = new QPushButton(groupBox_3);
        Knoten_verbinden->setObjectName(QString::fromUtf8("Knoten_verbinden"));

        horizontalLayout->addWidget(Knoten_verbinden);

        deleteEdge_Button = new QPushButton(groupBox_3);
        deleteEdge_Button->setObjectName(QString::fromUtf8("deleteEdge_Button"));

        horizontalLayout->addWidget(deleteEdge_Button);


        formLayout_3->setLayout(3, QFormLayout::SpanningRole, horizontalLayout);


        verticalLayout_4->addLayout(formLayout_3);


        verticalLayout_6->addWidget(groupBox_3);

        verticalSpacer = new QSpacerItem(325, 24, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer);

        splitter->addWidget(layoutWidget1);

        verticalLayout_7->addWidget(splitter);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 851, 22));
        menuDatei = new QMenu(menubar);
        menuDatei->setObjectName(QString::fromUtf8("menuDatei"));
        menuAnsicht = new QMenu(menubar);
        menuAnsicht->setObjectName(QString::fromUtf8("menuAnsicht"));
        menuHilfe = new QMenu(menubar);
        menuHilfe->setObjectName(QString::fromUtf8("menuHilfe"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuDatei->menuAction());
        menubar->addAction(menuAnsicht->menuAction());
        menubar->addAction(menuHilfe->menuAction());
        menuDatei->addAction(actionTragwerk_speichern);
        menuDatei->addAction(actionTragwerk_laden);
        menuDatei->addAction(actionneues_Tragwerk);
        menuDatei->addAction(actionAls_Bild_speichern);
        menuAnsicht->addAction(actionAltes_Tragwerk_zeigen);
        menuAnsicht->addAction(actionNeues_Tragwerk_zeigen);
        menuAnsicht->addAction(actionVerschiebung_zeigen);
        menuHilfe->addAction(actionSteuerung);
        toolBar->addSeparator();
        toolBar->addAction(actionSimulieren);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Tragwerksimulator", nullptr));
        actionTragwerk_speichern->setText(QApplication::translate("MainWindow", "Tragwerk speichern", nullptr));
        actionTragwerk_laden->setText(QApplication::translate("MainWindow", "Tragwerk laden", nullptr));
        actionAltes_Tragwerk_zeigen->setText(QApplication::translate("MainWindow", "Altes Tragwerk zeigen", nullptr));
        actionNeues_Tragwerk_zeigen->setText(QApplication::translate("MainWindow", "Neues Tragwerk zeigen", nullptr));
        actionVerschiebung_zeigen->setText(QApplication::translate("MainWindow", "Verschiebung zeigen", nullptr));
        actionJointMode->setText(QApplication::translate("MainWindow", "JointMode", nullptr));
        actionConnectionMode->setText(QApplication::translate("MainWindow", "ConnectionMode", nullptr));
        actionForceMode->setText(QApplication::translate("MainWindow", "ForceMode", nullptr));
        actionEraserMode->setText(QApplication::translate("MainWindow", "EraserMode", nullptr));
        actionSimulieren->setText(QApplication::translate("MainWindow", "Simulieren", nullptr));
        actionSteuerung->setText(QApplication::translate("MainWindow", "Steuerung", nullptr));
        actionneues_Tragwerk->setText(QApplication::translate("MainWindow", "neues Tragwerk", nullptr));
        actionAls_Bild_speichern->setText(QApplication::translate("MainWindow", "Als Bild speichern", nullptr));
        Mouse_coordinate1->setText(QApplication::translate("MainWindow", "X:", nullptr));
        Mouse_coordinate2->setText(QApplication::translate("MainWindow", "Y:", nullptr));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Elastizit\303\244tsmodul:", nullptr));
        Emodul_aktiv->setText(QApplication::translate("MainWindow", "aktivieren", nullptr));
        radioButton->setText(QApplication::translate("MainWindow", "linear", nullptr));
        Emodul_speichern->setText(QApplication::translate("MainWindow", "speichern", nullptr));
        Emodul_laden->setText(QApplication::translate("MainWindow", "laden", nullptr));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Knoten:", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "X:", nullptr));
        X_input->setText(QString());
        label_4->setText(QApplication::translate("MainWindow", "Y:", nullptr));
        label_9->setText(QApplication::translate("MainWindow", "Locator:", nullptr));
        addJoint_Button->setText(QApplication::translate("MainWindow", "hinzuf\303\274gen", nullptr));
        deleteJoint_Button->setText(QApplication::translate("MainWindow", "l\303\266schen", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Lager:", nullptr));
        Lager->setItemText(0, QApplication::translate("MainWindow", "mit Lager", nullptr));
        Lager->setItemText(1, QApplication::translate("MainWindow", "ohne Lager", nullptr));

        groupBox->setTitle(QApplication::translate("MainWindow", "Kr\303\244fte:", nullptr));
        label_11->setText(QApplication::translate("MainWindow", "F<sub>x</sub>:", nullptr));
        label_12->setText(QApplication::translate("MainWindow", "F<sub>y</sub>:", nullptr));
        label_13->setText(QApplication::translate("MainWindow", "Locator:", nullptr));
        addForce_Button->setText(QApplication::translate("MainWindow", "hinzuf\303\274gen", nullptr));
        deleteForce_Button->setText(QApplication::translate("MainWindow", "l\303\266schen", nullptr));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "St\303\244be:", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "Dicke:", nullptr));
        thickness->setText(QString());
        label->setText(QApplication::translate("MainWindow", "Locator 1:", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Locator 2:", nullptr));
        Knoten_verbinden->setText(QApplication::translate("MainWindow", "verbinden", nullptr));
        deleteEdge_Button->setText(QApplication::translate("MainWindow", "trennen", nullptr));
        menuDatei->setTitle(QApplication::translate("MainWindow", "Datei", nullptr));
        menuAnsicht->setTitle(QApplication::translate("MainWindow", "Ansicht", nullptr));
        menuHilfe->setTitle(QApplication::translate("MainWindow", "Hilfe", nullptr));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
