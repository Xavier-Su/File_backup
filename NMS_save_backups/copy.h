#ifndef COPY_H
#define COPY_H
#include <stdio.h>

#include <QFileDialog>
#include <QString>

class copy
{
public:
    copy();
    bool copyDirectory(const QString& srcPath, const QString& dstPath, bool coverFileIfExist);
    bool copyFile(QString srcPath, QString dstPath, bool coverFileIfExist);
    bool isDirExistOrMake(QString fullPath);
};

#endif // COPY_H
