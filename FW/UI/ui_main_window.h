#ifndef UIMAINWINDOW_H
#define UIMAINWINDOW_H

#include "FW/variant.h"
#include "FW/macro.h"
#include <QMainWindow>

class TypeController;
class TypeUiRecordExplorer;
class TypeUiRecordTableModel;
class TypeUiEditorContainer;
class TypeUiFileExplorer;
class TypeConfig;
class TypeDocument;
class TypeUiEditor;
class TypeUiHtmlBlocksEditor;

namespace Ui
{
class TypeUiMainWindow;
}

class TypeUiMainWindow : public QMainWindow, public TypeVariant
{
    Q_OBJECT

public:

    explicit TypeUiMainWindow( TypeController& controller,QWidget* parent = 0 );
    ~TypeUiMainWindow() override;

    void                          UpdateRecordExplorer();
    void                          UpdateFileExplorer();
    void                          UpdateHtmlTextView();
    void                          UpdateWebView();
    void                          UpdateSceneView();
    void                          UpdateMenubar();

    void                          InitConnections();
    void                          closeEvent( QCloseEvent* ) override;
    void                          SetTitle( QString title );
    void                          SetCurrentTab( int index );

    M_POINTER                     ( Controller,          TypeController )
    M_POINTER                     ( Document,            TypeDocument )
    M_POINTER                     ( RecordExplorer,      TypeUiRecordExplorer )
    M_POINTER                     ( FileExplorer,        TypeUiFileExplorer )
    M_POINTER                     ( TextEditorContainer, TypeUiEditorContainer )
    M_POINTER                     ( HtmlBlocksEditor,    TypeUiHtmlBlocksEditor )

    void                          SetPropertyWidget( QWidget* widget );
    void                          OpenEditorWidget( TypeUiEditor* widget );

private:

    QWidget*                      m_PropertiesWidget;
    Ui::TypeUiMainWindow*         ui;
};

#define MAINWINDOW_TAB_SCENE   0
#define MAINWINDOW_TAB_EDITOR  1
#define MAINWINDOW_TAB_CLIENT  2
#define MAINWINDOW_TAB_OUTPUT  3

#endif // UIMAINWINDOW_H
