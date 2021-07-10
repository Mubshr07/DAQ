#include "globalvars.h"

QString globalVars::logFile="";
uint32_t *globalVars::global_FPGA_ADDR = nullptr;

globalVars::globalVars(QObject *parent) : QObject(parent)
{

}
