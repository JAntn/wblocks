#ifndef UIRECORDTABLEVIEW_H
#define UIRECORDTABLEVIEW_H

#include "FW/macro.h"
#include <QTableView>
#include <QWidget>

namespace Ui
{
class C_UiRecordStructView;
}

class C_UiRecordTableModel;
class C_RecordStruct;
class C_Document;
class C_Record;

class C_UiRecordStructView : public QWidget
{
    Q_OBJECT

public:
    explicit C_UiRecordStructView( C_Document& document, QWidget* parent = 0 );
    ~C_UiRecordStructView() override;

    void                          Update();

    ATR_POINTER                   ( Document,         C_Document )
    ATR_POINTER                   ( RecordTableModel, C_UiRecordTableModel )

    C_RecordStruct&               Records();
    list<C_Record*>               Selection();
    void                          ClearSelection();
    bool                          HasSelection();

public slots:

    void                          OnCustomContextMenuRequested( const QPoint& point );
    void                          OnDoubleClicked( const QModelIndex& index );
    void                          OnRootButtonClicked();
    void                          OnUpButtonClicked();
    void                          OnSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);

private:

    Ui::C_UiRecordStructView*  ui;
};

#endif // UIRECORDTABLEVIEW_H
