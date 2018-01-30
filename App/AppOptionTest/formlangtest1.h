#ifndef FORMLANGTEST1_H
#define FORMLANGTEST1_H

#include <QWidget>
#include <QTranslator>

namespace Ui {
class FormLangTest1;
}

class FormLangTest1 : public QWidget
{
  Q_OBJECT

public:
  explicit FormLangTest1(QWidget *parent = 0);
  ~FormLangTest1();

private:
  Ui::FormLangTest1 *ui;
  QTranslator trans;
};

#endif // FORMLANGTEST1_H
