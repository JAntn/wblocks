#ifndef UIRECORDTABLEVIEW_H
#define UIRECORDTABLEVIEW_H

#include "FW/macro.h"
#include <QTableView>
#include <QWidget>

namespace Ui
{
class C_UiRecordExplorer;
}

class C_UiRecordTableModel;
class C_RecordStruct;
class C_Controller;
class C_Record;
class C_Context;

class C_UiRecordExplorer : public QWidget
{
    Q_OBJECT

public:
    explicit C_UiRecordExplorer( C_Context& context, C_Controller& controller, QWidget* parent = 0 );
    ~C_UiRecordExplorer() override;

    void                          Update();

    M_POINTER                     ( Context,          C_Context )
    M_POINTER                     ( Controller,       C_Controller )
    M_POINTER                     ( RecordTableModel, C_UiRecordTableModel )

    QList<C_Record*>              Selection();
    void                          ClearSelection();
    bool                          HasSelection();
    void                          Activate( C_Record* record );
public slots:

    void                          OnCustomContextMenuRequested( const QPoint& point );
    void                          OnDoubleClicked( const QModelIndex& index );
    void                          OnRootButtonClicked();
    void                          OnUpButtonClicked();
    void                          OnSelectionChanged( const QItemSelection&, const QItemSelection& );
    void                          OnLineEditReturnPressed();
private:

    Ui::C_UiRecordExplorer*  ui;
};

#endif // UIRECORDTABLEVIEW_H
