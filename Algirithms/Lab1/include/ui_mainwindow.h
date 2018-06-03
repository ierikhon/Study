/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_7;
    QAction *action_9;
    QAction *action_10;
    QAction *action_3;
    QAction *action;
    QAction *action_2;
    QAction *action_4;
    QAction *action_11;
    QAction *action_5;
    QAction *action_6;
    QWidget *centralWidget;
    QLabel *label;
    QTextEdit *textEdit;
    QCheckBox *checkBox;
    QTextEdit *textEdit_3;
    QLabel *label_3;
    QPushButton *pushButton;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QTextEdit *textEdit_2;
    QTextEdit *textEdit_4;
    QPushButton *pushButton_5;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_2;
    QPushButton *pushButton_7;
    QPushButton *pushButton_6;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menu1;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(924, 238);
        action_7 = new QAction(MainWindow);
        action_7->setObjectName(QStringLiteral("action_7"));
        action_9 = new QAction(MainWindow);
        action_9->setObjectName(QStringLiteral("action_9"));
        action_10 = new QAction(MainWindow);
        action_10->setObjectName(QStringLiteral("action_10"));
        action_3 = new QAction(MainWindow);
        action_3->setObjectName(QStringLiteral("action_3"));
        action_3->setEnabled(false);
        action = new QAction(MainWindow);
        action->setObjectName(QStringLiteral("action"));
        action_2 = new QAction(MainWindow);
        action_2->setObjectName(QStringLiteral("action_2"));
        action_4 = new QAction(MainWindow);
        action_4->setObjectName(QStringLiteral("action_4"));
        action_4->setEnabled(false);
        action_11 = new QAction(MainWindow);
        action_11->setObjectName(QStringLiteral("action_11"));
        action_5 = new QAction(MainWindow);
        action_5->setObjectName(QStringLiteral("action_5"));
        action_6 = new QAction(MainWindow);
        action_6->setObjectName(QStringLiteral("action_6"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 0, 141, 16));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(10, 20, 311, 71));
        textEdit->setReadOnly(true);
        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(10, 160, 111, 17));
        textEdit_3 = new QTextEdit(centralWidget);
        textEdit_3->setObjectName(QStringLiteral("textEdit_3"));
        textEdit_3->setEnabled(true);
        textEdit_3->setGeometry(QRect(10, 120, 311, 31));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(130, 100, 141, 16));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(330, 20, 281, 28));
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(330, 90, 281, 28));
        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(330, 150, 281, 28));
        textEdit_2 = new QTextEdit(centralWidget);
        textEdit_2->setObjectName(QStringLiteral("textEdit_2"));
        textEdit_2->setGeometry(QRect(330, 120, 281, 31));
        textEdit_4 = new QTextEdit(centralWidget);
        textEdit_4->setObjectName(QStringLiteral("textEdit_4"));
        textEdit_4->setGeometry(QRect(620, 20, 281, 161));
        textEdit_4->setReadOnly(true);
        pushButton_5 = new QPushButton(centralWidget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(180, 160, 81, 20));
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(330, 60, 281, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_2 = new QPushButton(horizontalLayoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        pushButton_7 = new QPushButton(horizontalLayoutWidget);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));

        horizontalLayout->addWidget(pushButton_7);

        pushButton_6 = new QPushButton(horizontalLayoutWidget);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        horizontalLayout->addWidget(pushButton_6);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 924, 26));
        menu1 = new QMenu(menuBar);
        menu1->setObjectName(QStringLiteral("menu1"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menu1->menuAction());
        menu1->addAction(action_5);
        menu1->addSeparator();
        menu1->addSeparator();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Binary trees", nullptr));
        action_7->setText(QApplication::translate("MainWindow", "Exit", nullptr));
        action_9->setText(QApplication::translate("MainWindow", "\320\241\321\207\320\270\321\202\320\260\321\202\321\214 \320\264\320\265\321\200\320\265\320\262\320\276", nullptr));
        action_10->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \320\262\321\202\320\276\321\200\320\276\320\265 \320\264\320\265\321\200\320\265\320\262\320\276", nullptr));
        action_3->setText(QApplication::translate("MainWindow", "\320\237\320\276\321\201\321\202\321\200\320\276\320\270\321\202\321\214 \320\277\320\265\321\200\320\262\320\276\320\265 \320\264\320\265\321\200\320\265\320\262\320\276", nullptr));
        action->setText(QApplication::translate("MainWindow", "Gravity on", nullptr));
        action_2->setText(QApplication::translate("MainWindow", "Gravity off", nullptr));
        action_4->setText(QApplication::translate("MainWindow", "\320\237\320\276\321\201\321\202\321\200\320\276\320\270\321\202\321\214 \320\262\321\202\320\276\321\200\320\276\320\265 \320\264\320\265\321\200\320\265\320\262\320\276", nullptr));
        action_11->setText(QApplication::translate("MainWindow", "Find Hamilton Ways", nullptr));
        action_5->setText(QApplication::translate("MainWindow", "Open", nullptr));
        action_6->setText(QApplication::translate("MainWindow", "Construct the graph", nullptr));
        label->setText(QApplication::translate("MainWindow", "Files's content", nullptr));
        checkBox->setText(QApplication::translate("MainWindow", "Gravity ON/OFF", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Debug", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "Construct the Graph", nullptr));
        pushButton_3->setText(QApplication::translate("MainWindow", "Complete Full Hamilton Search", nullptr));
        pushButton_4->setText(QApplication::translate("MainWindow", "Print Selected Way", nullptr));
        textEdit_2->setPlaceholderText(QApplication::translate("MainWindow", "Enter the Number of the Way You Want to Print", nullptr));
        textEdit_4->setPlaceholderText(QApplication::translate("MainWindow", "List of Hamilton Ways Founded", nullptr));
        pushButton_5->setText(QApplication::translate("MainWindow", "Clear ", nullptr));
        pushButton_2->setText(QApplication::translate("MainWindow", "<", nullptr));
        pushButton_7->setText(QApplication::translate("MainWindow", "Print", nullptr));
        pushButton_6->setText(QApplication::translate("MainWindow", ">", nullptr));
        menu1->setTitle(QApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
