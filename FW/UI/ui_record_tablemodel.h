#ifndef UIRECORDTABLEMODEL_H
#define UIRECORDTABLEMODEL_H

#include "FW/tools.h"
#include <QAbstractTableModel>

class TypeStruct;
class TypeDocument;

class TypeUiRecordTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:

    explicit TypeUiRecordTableModel( TypeStruct& struct_val, QObject* parent = 0 );
    ~TypeUiRecordTableModel() override;

    int                           rowCount( const QModelIndex& parent = QModelIndex() ) const override;
    int                           columnCount( const QModelIndex& parent = QModelIndex() ) const override;
    QVariant                      data( const QModelIndex& index, int role ) const override;
    QVariant                      headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const override;

    M_REFERENCE                   ( Struct, TypeStruct )

};


#endif // UIRECORDTABLEMODEL_H

