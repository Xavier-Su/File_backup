#include "menu.h"
#include "ini.h"
#include "copy.h"
#include <stdio.h>
#include "ui_menu.h"
#include <QFileDialog>
#include <QString>
#include <QPushButton>

menu::menu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::menu)
{
    ui->setupUi(this);

    char buff[100];
    int ret;

//    QString ini_path=QCoreApplication::applicationDirPath();
//    char *ini_path=QStringTochar(QCoreApplication::applicationDirPath()+"/test.ini");
//    printf("ini_path=%s",ini_path);



    ret = GetIniKeyString("path","recovery_path ",ini_path,buff);
    ui->lineEdit->setText(buff);
}

menu::~menu()
{
    delete ui;
}


void menu::on_open_clicked()
{
    this->update();
    QString mediafile = QFileDialog::getExistingDirectory(this,notice,path);
    if(mediafile.length()<=0){
        return;
    }
    if(mediafile.count()!=0){
        ui->lineEdit->setText(mediafile);
    }

//    char*  recovery_path=QStringTochar(mediafile);
    PutIniKeyString("path","recovery_path ",mediafile,ini_path);

    this->update();
}


void menu::on_open_after_clicked()
{
    this->update();
    QString mediafile_after = QFileDialog::getExistingDirectory(this,notice,path_after);
    if(mediafile_after.length()<=0){
        return;
    }
    if(mediafile_after.count()!=0){
//        ui->listWidget->addItems(mediafile);
        ui->lineEdit_2->setText(mediafile_after);
    }
    char*  path_now;
    QByteArray path = mediafile_after.toLatin1(); // must
    path_now=path.data();

    QString curPath = QDir::currentPath();
    ui->lineEdit->setText(curPath);
    PutIniKeyString("path","backup_path",path_now,"D:/Github/QT/NMS_save_backups/NMS_save_backups/test.ini");
    PutIniKeyString("study","university ","88888","D:/Github/QT/NMS_save_backups/NMS_save_backups/test.ini");

    this->update();

}

void menu::on_backup_clicked()
{
    char buff[100];
    int ret;

    ret = GetIniKeyString("path","backup_path","D:/Github/QT/NMS_save_backups/NMS_save_backups/test.ini",buff);
    ui->lineEdit->setText(buff);
//    printf("ret:%d,%s\n",ret,buff);


//    ret = GetIniKeyString("study","highschool","test.ini",buff);
//    ui->lineEdit_2->setText(buff);
////    printf("ret:%d,%s\n",ret,buff);

    ret = PutIniKeyString("study","highschool","6666","D:/Github/QT/NMS_save_backups/NMS_save_backups/test.ini");
    printf("put ret:%d\n",ret);
//    ret = GetIniKeyString("study","highschool","test.ini",buff);
//    printf("ret:%d,%s\n",ret,buff);

    copy copyfile;
    copyfile.isDirExistOrMake("C:/game/back/20221009");
    copyfile.copyFile("C:/game/1/2.txt","C:/game/4.txt",true);
    copyfile.copyDirectory("C:/game/1","C:/game/back",true);


}
