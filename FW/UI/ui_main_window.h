#ifndef C_UIMAINWINDOW_H
#define C_UIMAINWINDOW_H

#include "FW/macro.h"
#include <QMainWindow>

class C_Controller;
class C_UiRecordExplorer;
class C_UiRecordTableModel;
class C_UiEditorContainer;
class C_UiFileExplorer;
class C_Config;
class C_Document;
class C_UiEditor;

namespace Ui
{
class C_UiMainWindow;
}

class C_UiMainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit C_UiMainWindow( C_Controller& controller,QWidget* parent = 0 );
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

    M_POINTER                     ( Controller,          C_Controller )
    M_POINTER                     ( Document,            C_Document )
    M_POINTER                     ( RecordExplorer,      C_UiRecordExplorer )
    M_POINTER                     ( FileExplorer,        C_UiFileExplorer )
    M_POINTER                     ( TextEditorContainer, C_UiEditorContainer )
    M_VALUE                       ( BinPath,             QString )

    void                          SetPropertyWidget( QWidget* widget );
    void                          OpenEditorWidget( C_UiEditor* widget );

private:

    QWidget*                      m_PropertiesWidget;
    Ui::C_UiMainWindow*           ui;
};

#define MAINWINDOW_TAB_SCENE   0
#define MAINWINDOW_TAB_EDITOR  1
#define MAINWINDOW_TAB_CLIENT  2
#define MAINWINDOW_TAB_OUTPUT  3

#endif // C_UIMAINWINDOW_H
