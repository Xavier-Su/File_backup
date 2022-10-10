#include "menu.h"
#include "ini.h"
#include "copy.h"
#include <stdio.h>
#include <stdlib.h>
#include "ui_menu.h"
#include <QFileDialog>
#include <QString>
#include <QPushButton>
#include <QSettings>
#include <QDateTime>
menu::menu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::menu)
{
    ui->setupUi(this);

    QSettings setting(ini_path,QSettings::IniFormat);
    QString recovery_path=setting.value("path/recovery_path").toString();
    if (recovery_path.length()>1)
    {
        path=recovery_path;
        ui->lineEdit->setText(recovery_path);
    }
    QString backup_path=setting.value("path/backup_path").toString();
    if (backup_path.length()>1)
    {
        path_after=backup_path;
        ui->lineEdit->setText(backup_path);
    }
    ui->lineEdit->setText(recovery_path);
    ui->lineEdit_2->setText(backup_path);


}

menu::~menu()
{
    delete ui;
}


void menu::on_open_clicked()
{
    this->update();

    QSettings setting(ini_path,QSettings::IniFormat);
    QString recovery_path=setting.value("path/recovery_path").toString();
    if (recovery_path.length()>1)
    {
        path=recovery_path;
        ui->lineEdit->setText(path);
    }

    QString mediafile = QFileDialog::getExistingDirectory(this,notice,path);
    if(mediafile.length()<=0){
        return;
    }
    if(mediafile.count()!=0){
        ui->lineEdit->setText(mediafile);
    }

    setting.setValue("path/recovery_path",mediafile);
    setting.sync();

    QString value_path=setting.value("path/recovery_path").toString();
    ui->lineEdit->setText(value_path);
    this->update();
}


void menu::on_open_after_clicked()
{
    this->update();

    QSettings setting(ini_path,QSettings::IniFormat);
    QString backup_path=setting.value("path/backup_path").toString();
    if (backup_path.length()>1)
    {
        path_after=backup_path;
        ui->lineEdit_2->setText(path_after);
    }



    QString mediafile_after = QFileDialog::getExistingDirectory(this,notice,path_after);
    if(mediafile_after.length()<=0){
        return;
    }
    if(mediafile_after.count()!=0){
        ui->lineEdit_2->setText(mediafile_after);
    }

    setting.setValue("path/backup_path",mediafile_after);
    setting.sync();

    QString value_path=setting.value("path/backup_path").toString();
    ui->lineEdit_2->setText(value_path);
    this->update();

}

void menu::on_backup_clicked()
{
    QDateTime dateTime(QDateTime::currentDateTime());
    QString dir_name = dateTime.toString("yyyy_MM_dd_hh_mm_s");
     qDebug()<<"qStr="<<dir_name<<endl;
    copy copyfile;
    QString dir_now=path_after+"/"+dir_name;
    copyfile.isDirExistOrMake(dir_now);
//    copyfile.copyFile("C:/game/1/2.txt","C:/game/4.txt",true);
    qDebug()<<"path="<<path<<endl;
    qDebug()<<"path="<<path_after<<endl;
    qDebug()<<"path="<<dir_now<<endl;
    copyfile.copyDirectory(path,dir_now,true);


}

void menu::on_recovery_clicked()
{
    QString dir_now=path+"_backup";
    copy copyfile;
    copyfile.isDirExistOrMake(dir_now);
    copyfile.copyDirectory(path,dir_now,true);
        qDebug()<<"path="<<dir_now<<endl;
}
