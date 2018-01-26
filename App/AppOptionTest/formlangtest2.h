#ifndef FORMLANGTEST2_H
#define FORMLANGTEST2_H

#include <QWidget>
#include <QTranslator>

namespace Ui {
class FormLangTest2;
}

class FormLangTest2 : public QWidget
{
  Q_OBJECT

public:
  explicit FormLangTest2(QWidget *parent = 0);
  ~FormLangTest2();

private:
  Ui::FormLangTest2 *ui;
  QTranslator trans;
};

#endif // FORMLANGTEST2_H
