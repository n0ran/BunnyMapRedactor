/********************************************************************************
** Form generated from reading UI file 'mapsizedialog.ui'
**
** Created: Thu 15. Nov 20:33:23 2012
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAPSIZEDIALOG_H
#define UI_MAPSIZEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MapSizeDialog
{
public:
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox;
    QLabel *label_2;
    QLabel *label;
    QSpinBox *vertNum;
    QSpinBox *horNum;

    void setupUi(QWidget *MapSizeDialog)
    {
        if (MapSizeDialog->objectName().isEmpty())
            MapSizeDialog->setObjectName(QString::fromUtf8("MapSizeDialog"));
        MapSizeDialog->resize(179, 127);
        buttonBox = new QDialogButtonBox(MapSizeDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(10, 100, 156, 23));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        groupBox = new QGroupBox(MapSizeDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 160, 80));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 50, 80, 20));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 80, 20));
        vertNum = new QSpinBox(groupBox);
        vertNum->setObjectName(QString::fromUtf8("vertNum"));
        vertNum->setGeometry(QRect(100, 49, 42, 22));
        horNum = new QSpinBox(groupBox);
        horNum->setObjectName(QString::fromUtf8("horNum"));
        horNum->setGeometry(QRect(100, 19, 42, 22));

        retranslateUi(MapSizeDialog);

        QMetaObject::connectSlotsByName(MapSizeDialog);
    } // setupUi

    void retranslateUi(QWidget *MapSizeDialog)
    {
        MapSizeDialog->setWindowTitle(QApplication::translate("MapSizeDialog", "\320\235\320\276\320\262\320\260\321\217 \320\272\320\260\321\200\321\202\320\260", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MapSizeDialog", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \320\272\320\260\321\200\321\202\321\213", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MapSizeDialog", "\320\222\321\213\321\201\320\276\321\202\320\260", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MapSizeDialog", "\320\250\320\270\321\200\320\270\320\275\320\260", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MapSizeDialog: public Ui_MapSizeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPSIZEDIALOG_H
