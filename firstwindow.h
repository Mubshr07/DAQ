#ifndef FIRSTWINDOW_H
#define FIRSTWINDOW_H

#include <QDialog>
#include "classes/globalvars.h"

namespace Ui {
class FirstWindow;
}

class FirstWindow : public QDialog
{
    Q_OBJECT

public:
    explicit FirstWindow(QWidget *parent = nullptr);
    ~FirstWindow();

signals:
    void tx_generate_ThisGUI(GUI_WIN guiEnum);
    void tx_ClosingWindow_FirstWin(bool shutDown);

private slots:
    void on_pb_Config_Logging_clicked();
    void on_pb_Config_Factors_clicked();
    void on_pb_ShutDown_clicked();

    void on_timer_clock_elapsed();


    void on_pb_DebugWindow_clicked();

private:
    Ui::FirstWindow *ui;

    QTimer *timer_clock;
};

#endif // FIRSTWINDOW_H
