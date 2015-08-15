#ifndef C_UIMAINWINDOW_H
#define C_UIMAINWINDOW_H

#include "FW/macro.h"
#include <QMainWindow>

class C_Document;
class C_Record;
class C_UiRecordStructView;
class C_UiRecordTableModel;

namespace Ui
{
class C_UiMainWindow;
}

class C_UiMainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit C_UiMainWindow( QWidget* parent = 0 );
    ~C_UiMainWindow() override;

    void                          UpdateTableView();
    void                          UpdateScriptView();
    void                          UpdateSceneView();
    void                          UpdateMenubar();
    void                          UpdateWebView();
    void                          ConnectEvents();

    ATR_POINTER                   ( Document,         C_Document )
    ATR_POINTER                   ( RecordStructView, C_UiRecordStructView )


private:

    Ui::C_UiMainWindow*           ui;
};

#endif // C_UIMAINWINDOW_H
