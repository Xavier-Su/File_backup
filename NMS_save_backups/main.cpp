#include "menu.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    setbuf(stdout, nullptr);//日志已经被输出到stdout的缓冲区之中，把缓冲区的大小设置成0，日志就可以直接输出了
    menu w;
    w.show();
    return a.exec();
}
