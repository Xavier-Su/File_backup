#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QDir>
#include <QStandardPaths>
#include <QCoreApplication>
#include <QDebug>
#include <QListWidgetItem>
QT_BEGIN_NAMESPACE
namespace Ui { class menu; }
QT_END_NAMESPACE

class menu : public QWidget
{
    Q_OBJECT

public:
    menu(QWidget *parent = nullptr);
    ~menu();


private slots:
    void on_open_clicked();

    void on_open_after_clicked();

    void on_backup_clicked();

    void on_recovery_clicked();
    QStringList findFolder(QString folder);

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::menu *ui;
    QString notice="选择存档位置";
    QString path=QDir::homePath()+"/AppData/Roaming/HelloGames/NMS";
    QString path_after="C:/";
    QString ini_path=QCoreApplication::applicationDirPath()+"/setting.ini";


};
#endif // MENU_H
