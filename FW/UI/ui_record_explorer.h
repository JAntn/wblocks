#ifndef UIRECORDTABLEVIEW_H
#define UIRECORDTABLEVIEW_H

#include "FW/macro.h"
#include <QTableView>
#include <QWidget>

namespace Ui
{
class TypeUiRecordExplorer;
}

class TypeUiRecordTableModel;
class TypeRecordStruct;
class TypeController;
class TypeRecord;
class TypeContext;

class TypeUiRecordExplorer : public QWidget
{
    Q_OBJECT

public:
    explicit TypeUiRecordExplorer( TypeContext& context, TypeController& controller, QWidget* parent = 0 );
    ~TypeUiRecordExplorer() override;

    void                          Update();

    M_POINTER                     ( Context,          TypeContext )
    M_POINTER                     ( Controller,       TypeController )
    M_POINTER                     ( RecordTableModel, TypeUiRecordTableModel )

    QList<TypeRecord*>              Selection();
    void                          ClearSelection();
    bool                          HasSelection();
    void                          Activate( TypeRecord* record );
public slots:

    void                          OnCustomContextMenuRequested( const QPoint& point );
    void                          OnDoubleClicked( const QModelIndex& index );
    void                          OnRootButtonClicked();
    void                          OnUpButtonClicked();
    void                          OnSelectionChanged( const QItemSelection&, const QItemSelection& );
    void                          OnLineEditReturnPressed();
private:

    Ui::TypeUiRecordExplorer*  ui;
};

#endif // UIRECORDTABLEVIEW_H
