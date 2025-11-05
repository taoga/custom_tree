#ifndef CSTRRES_H
#define CSTRRES_H
#include <QString>
/////////////////////////////////////////////////////////////////////////////////////////
// Ресурсы строк, используемые в проекте
class CStrRes
{
public:
    CStrRes();
    static const QString IDS_COL_TWSENSORS_MAC_SRC;
    static const QString IDS_COL_TWSENSORS_MAC_DST;
    static const QString IDS_COL_TWSENSORS_TIME;
    static const QString IDS_COL_TWSENSORS_CHANNEL;
    static const QString IDS_COL_TWSENSORS_SIGNAL;
    static const QString IDS_COL_TWSENSORS_NOISE;
    static const QString IDS_COL_TWSENSORS_TYPE;
    static const QString IDS_COL_TWSENSORS_SCRYPT;
    static const QString IDS_COL_TWSENSORS_PACKETS;
    static const QString IDS_COL_TWSENSORS_ESSID;
    static const QString IDS_COL_TWZONES_MAC_SRC;
    static const QString IDS_MTWG_OPTIONS;
    static const QString IDS_MTWG_OPTIONS_MSG;
};

#endif // CSTRRES_H
