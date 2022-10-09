//ini.h
#ifndef INI_H
#define INI_H

#include <stdio.h>
#include <string.h>
#include <QString>

//int GetIniKeyString( char const*title, char const*key, char const*filename, char *buf);
int GetIniKeyString( QString Qtitle, QString Qkey, QString Qfilename, char *buf);
//int PutIniKeyString(const char *title,const char *key,const char *val,const char *filename);
int PutIniKeyString(QString Qtitle,QString Qkey,QString Qval,QString Qfilename);
char* QStringTochar(QString qstring);

#endif //INI_H
