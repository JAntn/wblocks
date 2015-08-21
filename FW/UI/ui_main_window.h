#ifndef C_UIMAINWINDOW_H
#define C_UIMAINWINDOW_H

#include "FW/macro.h"
#include <QMainWindow>

class C_Document;
class C_Record;
class C_UiRecordExplorer;
class C_UiRecordTableModel;
class C_UiCodeEditorContainer;
class C_UiFileExplorer;

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

    void                          UpdateRecordExplorer();
    void                          UpdateFileExplorer();
    void                          UpdateClientScriptView();
    void                          UpdateSceneView();
    void                          UpdateMenubar();
    void                          UpdateWebView();
    void                          ConnectEvents();

    ATR_POINTER                   ( Document,            C_Document )
    ATR_POINTER                   ( RecordExplorer,      C_UiRecordExplorer )
    ATR_POINTER                   ( CodeEditorContainer, C_UiCodeEditorContainer )
    ATR_POINTER                   ( FileExplorer,        C_UiFileExplorer )

private:

    Ui::C_UiMainWindow*           ui;
};

#endif // C_UIMAINWINDOW_H
