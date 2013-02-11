#ifndef BUILD_H
#define BUILD_H

#include <QDate>
#include <QString>

const QDate BUILDDATE = QDate( 2013, 2, 11 );
const long  BUILDINFO = 10010;

QString GetBuildInfo()
{
    QString info = "build - " + QString::number(BUILDINFO) + " - " + BUILDDATE.toString("dd.MM.yy");
    return info;
}

#endif // BUILD_H
