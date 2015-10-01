#ifndef UIRECORDTABLEVIEW_H
#define UIRECORDTABLEVIEW_H

#include "FW/tools.h"
#include <QTableView>

namespace Ui
{
class TypeUiRecordExplorer;
}

class TypeUiRecordTableModel;
class TypeStruct;
class TypeController;
class TypeRecord;
class TypeDocument;

class TypeUiRecordExplorer : public QWidget, public TypeVariant
{
    Q_OBJECT

public:
    explicit TypeUiRecordExplorer( TypeController& controller, TypeDocument& document, QWidget* parent = 0 );
    ~TypeUiRecordExplorer() override;

    void                                    Update();

    M_REFERENCE                             ( Controller,       TypeController )
    M_REFERENCE                             ( Document,         TypeDocument )
    M_REFERENCE                             ( RecordTableModel, TypeUiRecordTableModel )
    M_POINTER                               ( ActiveRecord,     TypeRecord )

    QList<TypeRecord*>                      Selection();
    void                                    ClearSelection();
    bool                                    HasSelection();
    void                                    OpenRecord( TypeRecord* record );
    void                                    ActivateRecord( TypeRecord* record );

public slots:

    void                                    OnCustomContextMenuRequested( const QPoint& point );
    void                                    OnDoubleClicked( const QModelIndex& index );
    void                                    OnRootButtonClicked();
    void                                    OnUpButtonClicked();
    void                                    OnSelectionChanged( const QItemSelection&, const QItemSelection& );
    void                                    OnLineEditReturnPressed();

private:

    Ui::TypeUiRecordExplorer*               ui;
};

#endif // UIRECORDTABLEVIEW_H
