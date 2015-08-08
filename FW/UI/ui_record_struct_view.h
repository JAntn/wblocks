#ifndef UIRECORDTABLEVIEW_H
#define UIRECORDTABLEVIEW_H

#include "FW/macro.h"

#include <QWidget>

namespace Ui {
class C_UiRecordStructView;
}

class C_UiRecordTableModel;
class C_RecordStruct;
class C_Document;

class C_UiRecordStructView : public QWidget
{
    Q_OBJECT

public:
    explicit C_UiRecordStructView(C_Document& document, QWidget *parent = 0);
    ~C_UiRecordStructView() override;

    void                          Update();

    C_POINTER                     (Document,         C_Document)
    C_POINTER                     (RecordTableModel, C_UiRecordTableModel)

    C_RecordStruct&            Records();

private slots:
    
    void                          OnCustomContextMenuRequested(const QPoint& point);
    void                          OnDoubleClicked(const QModelIndex& index);
    void                          on_RootButton_clicked();
    void                          on_UpButton_clicked();

private:

    Ui::C_UiRecordStructView*  ui;
};

#endif // UIRECORDTABLEVIEW_H
