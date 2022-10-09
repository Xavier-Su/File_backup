//ini.h
#ifndef INI_H
#define INI_H

#include <stdio.h>
#include <string.h>

int GetIniKeyString( char const*title, char const*key, char const*filename, char *buf);

int PutIniKeyString(const char *title,const char *key,const char *val,const char *filename);

#endif //INI_H
