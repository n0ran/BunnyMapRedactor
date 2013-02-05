/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue 5. Feb 20:52:38 2013
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *backgroundLabel;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *openFileButton;
    QPushButton *saveFileButton;
    QPushButton *createFileButton;
    QLineEdit *Number;
    QSpinBox *Timer;
    QSpinBox *Steps;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(899, 633);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        backgroundLabel = new QLabel(centralWidget);
        backgroundLabel->setObjectName(QString::fromUtf8("backgroundLabel"));
        backgroundLabel->setGeometry(QRect(0, 0, 900, 600));
        backgroundLabel->setPixmap(QPixmap(QString::fromUtf8(":/back")));
        backgroundLabel->setScaledContents(true);
        backgroundLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 0, 880, 600));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        openFileButton = new QPushButton(centralWidget);
        openFileButton->setObjectName(QString::fromUtf8("openFileButton"));
        openFileButton->setGeometry(QRect(60, -20, 50, 50));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/openfile"), QSize(), QIcon::Normal, QIcon::Off);
        openFileButton->setIcon(icon);
        openFileButton->setIconSize(QSize(40, 40));
        openFileButton->setFlat(true);
        saveFileButton = new QPushButton(centralWidget);
        saveFileButton->setObjectName(QString::fromUtf8("saveFileButton"));
        saveFileButton->setGeometry(QRect(110, -20, 50, 50));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/savefile"), QSize(), QIcon::Normal, QIcon::Off);
        saveFileButton->setIcon(icon1);
        saveFileButton->setIconSize(QSize(40, 40));
        saveFileButton->setFlat(true);
        createFileButton = new QPushButton(centralWidget);
        createFileButton->setObjectName(QString::fromUtf8("createFileButton"));
        createFileButton->setGeometry(QRect(10, -20, 50, 50));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(createFileButton->sizePolicy().hasHeightForWidth());
        createFileButton->setSizePolicy(sizePolicy);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/newfile"), QSize(), QIcon::Normal, QIcon::Off);
        createFileButton->setIcon(icon2);
        createFileButton->setIconSize(QSize(40, 40));
        createFileButton->setFlat(true);
        Number = new QLineEdit(centralWidget);
        Number->setObjectName(QString::fromUtf8("Number"));
        Number->setGeometry(QRect(220, -20, 45, 50));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(Number->sizePolicy().hasHeightForWidth());
        Number->setSizePolicy(sizePolicy1);
        QFont font;
        font.setFamily(QString::fromUtf8("Arial Black"));
        font.setPointSize(12);
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        Number->setFont(font);
        Number->setReadOnly(true);
        Timer = new QSpinBox(centralWidget);
        Timer->setObjectName(QString::fromUtf8("Timer"));
        Timer->setEnabled(false);
        Timer->setGeometry(QRect(270, -20, 45, 50));
        sizePolicy1.setHeightForWidth(Timer->sizePolicy().hasHeightForWidth());
        Timer->setSizePolicy(sizePolicy1);
        Timer->setFont(font);
        Timer->setMinimum(-1);
        Timer->setValue(-1);
        Steps = new QSpinBox(centralWidget);
        Steps->setObjectName(QString::fromUtf8("Steps"));
        Steps->setEnabled(true);
        Steps->setGeometry(QRect(170, -20, 45, 50));
        sizePolicy1.setHeightForWidth(Steps->sizePolicy().hasHeightForWidth());
        Steps->setSizePolicy(sizePolicy1);
        Steps->setFont(font);
        Steps->setMinimum(1);
        Steps->setValue(10);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 899, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setIconSize(QSize(35, 35));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\320\240\320\265\320\264\320\260\320\272\321\202\320\276\321\200 \320\272\320\260\321\200\321\202", 0, QApplication::UnicodeUTF8));
        backgroundLabel->setText(QString());
#ifndef QT_NO_TOOLTIP
        openFileButton->setToolTip(QApplication::translate("MainWindow", "Open file...", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        saveFileButton->setToolTip(QApplication::translate("MainWindow", "Save file as...", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        createFileButton->setToolTip(QApplication::translate("MainWindow", "Create file...", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
