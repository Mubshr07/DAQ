#ifndef GRAPHWIN_H
#define GRAPHWIN_H

#include <QDialog>

namespace Ui {
class graphWin;
}

class graphWin : public QDialog
{
    Q_OBJECT

public:
    explicit graphWin(QWidget *parent = nullptr);
    ~graphWin();

private:
    Ui::graphWin *ui;
};

#endif // GRAPHWIN_H
