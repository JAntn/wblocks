#ifndef UIRECORDTABLEMODEL_H
#define UIRECORDTABLEMODEL_H

#include "FW/macro.h"

#include <QAbstractTableModel>

class TypeRecordStruct;
class TypeDocument;

class TypeUiRecordTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:

    explicit TypeUiRecordTableModel( TypeDocument& document, QObject* parent = 0 );
    ~TypeUiRecordTableModel() override;

    int                           rowCount( const QModelIndex& parent = QModelIndex() ) const override;
    int                           columnCount( const QModelIndex& parent = QModelIndex() ) const override;
    QVariant                      data( const QModelIndex& index, int role ) const override;
    QVariant                      headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const override;

    TypeRecordStruct&               Records() const;

    M_POINTER                     ( Document, TypeDocument )

};


#endif // UIRECORDTABLEMODEL_H

