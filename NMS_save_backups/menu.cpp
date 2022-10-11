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
#include <QMessageBox>
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

//    QString FileFolder = QFileDialog::getExistingDirectory( this, "choose Directory",  "/");

    QString FileFolder = backup_path;
    if(!FileFolder.isEmpty())
    {
        QStringList folders = findFolder(FileFolder);
        for(int i=0; i<folders.size(); i++)
        {

//        if (folders.at(i).contains("_",Qt::CaseSensitive))
        if (folders.at(i).contains(QRegularExpression("[0-9]+[_]*")))
        {
            ui->listWidget->addItem(folders.at(i));
//            ui->textEdit->append(QString("子目录:%1").arg(folders.at(i)));
        }
        }
    }

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
    bool back_ok=copyfile.copyDirectory(path,dir_now,true);


    if(back_ok){
        ui->listWidget->addItem(dir_name);
        QMessageBox::information(this,tr("备份提示"),tr("备份成功！"),
                   QMessageBox::Ok,
                   QMessageBox::Ok);

    }
    if(!back_ok){
        QMessageBox::information(this,tr("备份提示"),tr("备份失败！"),
                   QMessageBox::Cancel,
                   QMessageBox::Cancel);
    }



}

void menu::on_recovery_clicked()
{
    QString dir_now=path+"_backup";
    copy copyfile;
    copyfile.isDirExistOrMake(dir_now);
    copyfile.copyDirectory(path,dir_now,true);
        qDebug()<<"path="<<dir_now<<endl;
    QMessageBox::information(this,tr("还原提示"),tr("还原成功"),
               QMessageBox::Ok | QMessageBox::Cancel,
               QMessageBox::Ok);

}

QStringList menu::findFolder(QString folder)
{
    // 获取所有文件夹名
    QDir dir(folder);
    folder = dir.fromNativeSeparators(folder);//  "\\"转为"/"
    QStringList allFolder = QStringList("");
    dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    dir.setSorting(QDir::Name);
    allFolder = dir.entryList();
    return  allFolder;
}

void menu::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
QString dir=item->text();
ui->textEdit->append(QString("子目录:%1").arg(dir));
}
