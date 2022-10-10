/*ini.c*/
#include "ini.h"
#include <stdio.h>
#include <string.h>
#include <QFile>
#include<QTextCodec>
/*
    * 函数名：         GetIniKeyString
    * 入口参数：        title
    *                      配置文件中一组数据的标识
    *                  key
    *                      这组数据中要读出的值的标识
    *                  filename
    *                      要读取的文件路径
    * 返回值：         找到需要查的值则返回正确结果 0
    *                  否则返回-1
    */
int GetIniKeyString( QString Qtitle, QString Qkey, QString Qfilename, char *buf)
{
    char const*title=QStringTochar(Qtitle);
    char const*key=QStringTochar(Qkey);
    char const*filename=QStringTochar(Qfilename);
    printf("file=%s\n",filename);

    FILE *fp;
    int  flag = 0;
    char sTitle[64], *wTmp;
    char sLine[1024];
    sprintf(sTitle, "[%s]", title);

    if(nullptr == (fp = fopen(filename, "r"))) {
        perror("fopen");
        return -1;
    }
    while (nullptr != fgets(sLine, 1024, fp)) {
        // 这是注释行
        if (0 == strncmp("//", sLine, 2)) continue;
        if ('#' == sLine[0])              continue;
        wTmp = strchr(sLine, '=');
        if ((nullptr != wTmp) && (1 == flag)) {
            if (0 == strncmp(key, sLine, strlen(key))) { // 长度依文件读取的为准
                sLine[strlen(sLine) - 1] = '\0';
                fclose(fp);
                while(*(wTmp + 1) == ' '){
                    wTmp++;
                }
                strcpy(buf,wTmp + 1);
                return 0;
            }
        } else {
            if (0 == strncmp(sTitle, sLine, strlen(sTitle))) { // 长度依文件读取的为准
                flag = 1; // 找到标题位置
            }
        }
    }
    fclose(fp);
    return -1;
}

/*
    * 函数名：         PutIniKeyString
    * 入口参数：        title
    *                      配置文件中一组数据的标识
    *                  key
    *                      这组数据中要读出的值的标识
    *                  val
    *                      更改后的值
    *                  filename
    *                      要读取的文件路径
    * 返回值：         成功返回  0
    *                  否则返回 -1
    */
int PutIniKeyString(QString Qtitle,QString Qkey,QString Qval,QString Qfilename)
{
    char const*title=QStringTochar(Qtitle);
    char const*key=QStringTochar(Qkey);
    char const*val=QStringTochar(Qval);
    char const*filename=QStringTochar(Qfilename);

    FILE *fpr, *fpw;
    int  flag = 0;
    char sLine[1024], sTitle[32], *wTmp;
    sprintf(sTitle, "[%s]", title);
    if (nullptr == (fpr = fopen(filename, "r")))
        return -1;// 读取原文件
    sprintf(sLine, "%s.tmp", filename);
    if (nullptr == (fpw = fopen(sLine,    "w")))
        return -1;// 写入临时文件
    while (nullptr != fgets(sLine, 1024, fpr)) {
        if (2 != flag) { // 如果找到要修改的那一行，则不会执行内部的操作
            wTmp = strchr(sLine, '=');
            if ((nullptr != wTmp) && (1 == flag)) {
                if (0 == strncmp(key, sLine, strlen(key))) { // 长度依文件读取的为准
                    flag = 2;// 更改值，方便写入文件
                    sprintf(wTmp + 1, " %s\n", val);
                }
            } else {
                if (0 == strncmp(sTitle, sLine, strlen(sTitle))) { // 长度依文件读取的为准
                    flag = 1; // 找到标题位置
                }
            }
        }
        fputs(sLine, fpw); // 写入临时文件
    }
    fclose(fpr);
    fclose(fpw);
    sprintf(sLine, "%s.tmp", filename);

    bool remove=QFile::remove(filename);
    if (!remove){printf("remove error!");return -1;}
    bool rename=QFile::rename(sLine, filename);
    if (!rename){printf("rename error!");return -2;}
//    return rename(sLine, filename);// 将临时文件更新到原文件
    return 0;
}

char* QStringTochar(QString qstring)
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
    QByteArray path = qstring.toLocal8Bit(); // must
    return path.data();

}

