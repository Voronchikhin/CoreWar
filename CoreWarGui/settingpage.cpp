#include "settingpage.h"
#include "ui_settingpage.h"
#include <iostream>

SettingPage::SettingPage(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::SettingPage)
{
  ui->setupUi(this);
  files.push_back(ui->file1); tags.push_back(ui->tag1);
  files.push_back(ui->file2); tags.push_back(ui->tag2);
  files.push_back(ui->file3); tags.push_back(ui->tag3);
  files.push_back(ui->file4); tags.push_back(ui->tag4);
  for( int i = 2; i < 4; ++i ){
    files[i]->hide();
    tags[i]->hide();
  }

}

SettingPage::~SettingPage()
{
  delete ui;
}

void SettingPage::on_comboBox_currentIndexChanged(int index)
{
    warriorsNumber_ = index + 2;
    std::cout<<index<<std::endl;
    for( int i = index+1 ; i < 4; ++i){
        files[i]->clear();
        tags[i]->clear();
        files[i]->hide();
        tags[i]->hide();
      }
    for( int i = 0; i <= index+1; ++i ){
        files[i]->show();
        tags[i]->show();
    }
    emit numberWarriors(warriorsNumber_);
}


void SettingPage::on_file1_textEdited(const QString &arg1)
{
    emit fileChanged(1, arg1);
}

void SettingPage::on_file2_textChanged(const QString &arg1)
{
    emit fileChanged(2, arg1);
}

void SettingPage::on_file3_textChanged(const QString &arg1)
{
    emit fileChanged(3, arg1);
}

void SettingPage::on_file4_textChanged(const QString &arg1)
{
    emit fileChanged(4, arg1);
}

void SettingPage::on_tag1_textChanged(const QString &arg1)
{
    emit tagChanged(1,arg1);
}

void SettingPage::on_tag2_textChanged(const QString &arg1)
{
    emit tagChanged(2,arg1);
}

void SettingPage::on_tag3_textChanged(const QString &arg1)
{
    emit tagChanged(3, arg1);
}

void SettingPage::on_tag4_textChanged(const QString &arg1)
{
    emit tagChanged(4, arg1);
}

void SettingPage::on_start_clicked()
{
    emit startButton();
}
