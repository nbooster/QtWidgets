#pragma once

#include <QIcon>

static constexpr short numberOfColumns = 6; // as many as the attributes of Record

/*! A struct for holding the data of each row of the table. */
struct Record
{
    bool checked = false;
    QIcon icon;
    QString extension;
    QString iconFileName;
    QString appName;
    QString fullExePath;

    Record(bool checked, QString extension, QString iconFileName, QString appName,
           QString fullExePath)
        : checked(checked),
          extension(extension),
          iconFileName(iconFileName),
          appName(appName),
          fullExePath(fullExePath)
    {
        icon = QIcon::fromTheme(iconFileName, QIcon(":/" + iconFileName));
    }
};
