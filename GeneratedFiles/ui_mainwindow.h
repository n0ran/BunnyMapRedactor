/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu 15. Nov 19:37:20 2012
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
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpinBox>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *backgroundLabel;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *Number;
    QRadioButton *IsOriginal;
    QRadioButton *IsActive;
    QRadioButton *IsBlock;
    QRadioButton *IsBomb;
    QSpinBox *Timer;
    QRadioButton *IsBunny;
    QRadioButton *IsFire;
    QRadioButton *IsMonster;
    QRadioButton *IsStrong;
    QRadioButton *IsTeleport;
    QCheckBox *Visible;
    QPushButton *openFileButton;
    QPushButton *saveFileButton;
    QPushButton *createFileButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1009, 633);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        backgroundLabel = new QLabel(centralWidget);
        backgroundLabel->setObjectName(QString::fromUtf8("backgroundLabel"));
        backgroundLabel->setGeometry(QRect(0, 0, 880, 600));
        backgroundLabel->setPixmap(QPixmap(QString::fromUtf8(":/back")));
        backgroundLabel->setScaledContents(true);
        backgroundLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 0, 870, 600));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(890, 0, 110, 297));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        Number = new QLineEdit(verticalLayoutWidget);
        Number->setObjectName(QString::fromUtf8("Number"));
        Number->setReadOnly(true);

        verticalLayout->addWidget(Number);

        IsOriginal = new QRadioButton(verticalLayoutWidget);
        IsOriginal->setObjectName(QString::fromUtf8("IsOriginal"));

        verticalLayout->addWidget(IsOriginal);

        IsActive = new QRadioButton(verticalLayoutWidget);
        IsActive->setObjectName(QString::fromUtf8("IsActive"));
        IsActive->setChecked(true);

        verticalLayout->addWidget(IsActive);

        IsBlock = new QRadioButton(verticalLayoutWidget);
        IsBlock->setObjectName(QString::fromUtf8("IsBlock"));

        verticalLayout->addWidget(IsBlock);

        IsBomb = new QRadioButton(verticalLayoutWidget);
        IsBomb->setObjectName(QString::fromUtf8("IsBomb"));

        verticalLayout->addWidget(IsBomb);

        Timer = new QSpinBox(verticalLayoutWidget);
        Timer->setObjectName(QString::fromUtf8("Timer"));
        Timer->setEnabled(false);
        Timer->setMinimum(-1);
        Timer->setValue(-1);

        verticalLayout->addWidget(Timer);

        IsBunny = new QRadioButton(verticalLayoutWidget);
        IsBunny->setObjectName(QString::fromUtf8("IsBunny"));

        verticalLayout->addWidget(IsBunny);

        IsFire = new QRadioButton(verticalLayoutWidget);
        IsFire->setObjectName(QString::fromUtf8("IsFire"));

        verticalLayout->addWidget(IsFire);

        IsMonster = new QRadioButton(verticalLayoutWidget);
        IsMonster->setObjectName(QString::fromUtf8("IsMonster"));

        verticalLayout->addWidget(IsMonster);

        IsStrong = new QRadioButton(verticalLayoutWidget);
        IsStrong->setObjectName(QString::fromUtf8("IsStrong"));

        verticalLayout->addWidget(IsStrong);

        IsTeleport = new QRadioButton(verticalLayoutWidget);
        IsTeleport->setObjectName(QString::fromUtf8("IsTeleport"));

        verticalLayout->addWidget(IsTeleport);

        Visible = new QCheckBox(verticalLayoutWidget);
        Visible->setObjectName(QString::fromUtf8("Visible"));
        Visible->setChecked(true);

        verticalLayout->addWidget(Visible);

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
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1009, 21));
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        backgroundLabel->setText(QString());
        label->setText(QApplication::translate("MainWindow", "Hex index", 0, QApplication::UnicodeUTF8));
        IsOriginal->setText(QApplication::translate("MainWindow", "Original", 0, QApplication::UnicodeUTF8));
        IsActive->setText(QApplication::translate("MainWindow", "StartPoint", 0, QApplication::UnicodeUTF8));
        IsBlock->setText(QApplication::translate("MainWindow", "Stone", 0, QApplication::UnicodeUTF8));
        IsBomb->setText(QApplication::translate("MainWindow", "Bomb", 0, QApplication::UnicodeUTF8));
        IsBunny->setText(QApplication::translate("MainWindow", "Bunny", 0, QApplication::UnicodeUTF8));
        IsFire->setText(QApplication::translate("MainWindow", "Fire", 0, QApplication::UnicodeUTF8));
        IsMonster->setText(QApplication::translate("MainWindow", "Monster", 0, QApplication::UnicodeUTF8));
        IsStrong->setText(QApplication::translate("MainWindow", "Strong", 0, QApplication::UnicodeUTF8));
        IsTeleport->setText(QApplication::translate("MainWindow", "Teleport", 0, QApplication::UnicodeUTF8));
        Visible->setText(QApplication::translate("MainWindow", "Visible", 0, QApplication::UnicodeUTF8));
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
