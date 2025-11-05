#ifndef CL_TYPES_H
#define CL_TYPES_H

#include <QString>

using namespace std;

typedef struct tagColumn
{
    tagColumn()
    {
        m_nID = 0;
        m_qsName.clear();
        m_bVisible = true;
    };

    tagColumn( quint8 nID, QString qsName, bool bVisible = true )
    {
        m_nID = nID;
        m_qsName = qsName;
        m_bVisible = bVisible;
    };

    quint8  m_nID;
    QString m_qsName;
    bool    m_bVisible;
}Column;

#endif // CL_TYPES_H
