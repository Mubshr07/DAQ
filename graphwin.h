#ifndef GRAPHWIN_H
#define GRAPHWIN_H

#include <QDialog>

#include "classes/globalvars.h"

namespace Ui {
class graphWin;
}

class graphWin : public QDialog
{
    Q_OBJECT

public:
    explicit graphWin(QWidget *parent = nullptr);
    ~graphWin();

signals:
    void tx_GraphWindowIsOpen(bool windOpen);

    void tx_AddNewChannelToGraph(int idx, int chnlID);
    void tx_RemoveChannelToGraph(int idx, int chnlID);

    void tx_giveMeEnablesChannels();

public slots:
    void rx_EnableChannelsAre(int chnlID);
    void rx_GraphChannelValue(int indx, int chnl, float val);

    void on_timer_singleShot_Elapsed();

private slots:
    void on_pb_Add_toGraph_clicked();
    void on_pb_RemoveGraph_0_clicked();
    void on_pb_RemoveGraph_1_clicked();
    void on_pb_RemoveGraph_2_clicked();
    void on_pb_RemoveGraph_3_clicked();





    void on_pb_CloseWindow_clicked();

private:
    Ui::graphWin *ui;
    QTimer *timer_singleShot;

    QVector<int> qv_EnablChannels;
    QVector<int> qv_availableList;
    int graphedChannels[4] = {123, 123, 123, 123};

    bool initial_bool = false;
    bool chnl4thIsEnable = false;
    bool chnl4thIsAppliable = false;
    bool availIndex[4] = {false, false, false, false};

    QColor plot0_Color = QColor(40, 110, 255);
    QColor plot1_Color = QColor(12, 222, 12);
    QColor plot2_Color = QColor(40, 222, 255);
    QColor plot3_Color = QColor(222, 110, 255);

    QString style_removBtn_0 = "font: 500 16pt 'Times New Roman'; padding: 5px; color:white; background-color:"+ plot0_Color.name()+"; border: 1px solid black; border-radius:5px;";
    QString style_removBtn_1 = "font: 500 16pt 'Times New Roman'; padding: 5px; color:white; background-color:"+ plot1_Color.name()+"; border: 1px solid black; border-radius:5px;";
    QString style_removBtn_2 = "font: 500 16pt 'Times New Roman'; padding: 5px; color:white; background-color:"+ plot2_Color.name()+"; border: 1px solid black; border-radius:5px;";
    QString style_removBtn_3 = QString("font: 500 16pt 'Times New Roman'; padding: 5px; color:white; background-color:"+ plot3_Color.name()+"; border: 1px solid black; border-radius:5px;");

    QString style_removBtn_Disabled = "font: 500 16pt 'Times New Roman'; padding: 5px; color:black; background-color:transparent; border: 1px solid transparent; border-radius:5px;";


    void update_cmbBoxItems();




};

#endif // GRAPHWIN_H
