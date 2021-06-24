#ifndef CONFIGCHWIN_H
#define CONFIGCHWIN_H

#include <QDialog>

namespace Ui {
class ConfigChWin;
}

class ConfigChWin : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigChWin(QWidget *parent = nullptr);
    ~ConfigChWin();

private:
    Ui::ConfigChWin *ui;
};

#endif // CONFIGCHWIN_H
