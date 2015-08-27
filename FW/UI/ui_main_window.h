#ifndef C_UIMAINWINDOW_H
#define C_UIMAINWINDOW_H

#include "FW/macro.h"
#include <QMainWindow>

class C_Document;
class C_Record;
class C_UiRecordExplorer;
class C_UiRecordTableModel;
class C_UiTextEditorContainer;
class C_UiFileExplorer;
class C_Config;

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
    void                          UpdateHtmlCodeView();
    void                          UpdateWebView();
    void                          UpdateSceneView();
    void                          UpdateMenubar();

    void                          InitConnections();
    void                          closeEvent( QCloseEvent* ) override;
    void                          SetTitle( QString title );
    void                          SetCurrentTab( int index );

    M_POINTER                     ( Config,              C_Config )
    M_POINTER                     ( Document,            C_Document )
    M_POINTER                     ( RecordExplorer,      C_UiRecordExplorer )
    M_POINTER                     ( FileExplorer,        C_UiFileExplorer )
    M_POINTER                     ( TextEditorContainer, C_UiTextEditorContainer )
    M_VALUE                       ( BinPath,             QString )

private:

    Ui::C_UiMainWindow*           ui;
};

#define MAINWINDOW_TAB_SCENE   0
#define MAINWINDOW_TAB_EDITOR  1
#define MAINWINDOW_TAB_CLIENT  2
#define MAINWINDOW_TAB_OUTPUT  3

#endif // C_UIMAINWINDOW_H
