#include "FW/RC/record_struct.h"
#include "FW/RC/record.h"

#include "FW/document.h"
#include "FW/context.h"

#include "FW/UI/ui_record_table_model.h"

QString HORIZONTAL_HEADER_TEXT[] =
{
    "Name",
    "Value",
    "Class"
};

int C_UiRecordTableModel::columnCount( const QModelIndex& ) const
{
    return 3;
}

C_UiRecordTableModel::C_UiRecordTableModel( C_Document& document, QObject* parent )
    : QAbstractTableModel( parent ), m_Document( &document )
{
    // void
}

C_UiRecordTableModel::~C_UiRecordTableModel()
{
    ///void
}

int C_UiRecordTableModel::rowCount( const QModelIndex& ) const
{
    return Records().Size();
}

QVariant C_UiRecordTableModel::data( const QModelIndex& index, int role ) const
{
    if ( !index.isValid() )
        return QVariant();

    if ( index.row() >=
            Records().Size() )

        return QVariant();

    if ( role == Qt::DisplayRole )
    {
        auto record = Records().FromIndex( index.row() );

        if( index.column() == 2 )
            return record->Class();

        else if( index.column() == 0 )
            return record->Name();

        else if( index.column() == 1 )
        {
            if( record->Struct() != 0 )
                return "{" + record->Value() + "}";

            return record->Value();

        }
    }

    return QVariant();
}

QVariant C_UiRecordTableModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    if ( role != Qt::DisplayRole )
        return QVariant();

    if ( orientation == Qt::Horizontal )
        return HORIZONTAL_HEADER_TEXT[section];
    else
        return section;
}

C_RecordStruct& C_UiRecordTableModel::Records() const
{
    return Document().Context().Records();
}








