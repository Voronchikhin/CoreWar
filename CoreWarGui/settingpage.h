#ifndef SETTINGPAGE_H
#define SETTINGPAGE_H

#include <QWidget>
#include <QLineEdit>

namespace Ui {
  class SettingPage;
}

class SettingPage : public QWidget
{
  Q_OBJECT

public:
  explicit SettingPage(QWidget *parent = 0);
  ~SettingPage();
  std::vector<QLineEdit *> files;
  std::vector<QLineEdit *> tags;
signals:
  void fileChanged(int warriorIndex, QString fileName);
  void tagChanged( int warriorsIndex,QString tag );
  void numberWarriors(int numberWarriors);
  void startButton();
private slots:
  void on_comboBox_currentIndexChanged(int index);

  void on_start_clicked();

  void on_file1_textEdited(const QString &arg1);

  void on_file2_textChanged(const QString &arg1);

  void on_file3_textChanged(const QString &arg1);

  void on_file4_textChanged(const QString &arg1);

  void on_tag1_textChanged(const QString &arg1);

  void on_tag2_textChanged(const QString &arg1);

  void on_tag3_textChanged(const QString &arg1);

  void on_tag4_textChanged(const QString &arg1);

private:
  Ui::SettingPage *ui;

  unsigned warriorsNumber_;
};

#endif // SETTINGPAGE_H
