#ifndef C_UIRECORDTABLEMODEL_H
#define C_UIRECORDTABLEMODEL_H

#include "FW/macro.h"

#include <QAbstractTableModel>

class C_RecordStruct;
class C_Document;

class C_UiRecordTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:

    explicit C_UiRecordTableModel(C_Document& document, QObject *parent = 0);
     ~C_UiRecordTableModel() override;

    int                           rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int                           columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant                      data(const QModelIndex &index, int role) const override;
    QVariant                      headerData(int section, Qt::Orientation orientation,int role = Qt::DisplayRole) const override;

    C_RecordStruct&               Records() const;

    ATR_POINTER                   (Document,C_Document)

};


#endif // C_UIRECORDTABLEMODEL_H

