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

    void tx_AddNewChannelToGraph(int chnlID);
    void tx_RemoveChannelToGraph(int chnlID);

    void tx_giveMeEnablesChannels();

public slots:
    void rx_EnableChannelsAre(int chnlID);
    void rx_GraphChannelValue(int indx, int chnl, float val);

    void on_timer_singleShot_Elapsed();

private:
    Ui::graphWin *ui;
    QTimer *timer_singleShot;

    QVector<int> qv_EnablChannels;
    QVector<int> qv_availableList;
    QVector<int> qv_graphList;

    bool initial_bool = false;


};

#endif // GRAPHWIN_H
