#ifndef UIMAINWINDOW_H
#define UIMAINWINDOW_H

#include "FW/variant.h"
#include "FW/tools.h"
#include <QMainWindow>

class TypeController;
class TypeUiRecordExplorer;
class TypeUiRecordTableModel;
class TypeUiEditorContainer;
class TypeUiFileExplorer;
class TypeConfig;
class TypeDocument;
class TypeUiEditor;
class TypeUiHtmlTextView;
class TypeRecord;

namespace Ui
{
class TypeUiMainWindow;
}

class TypeUiMainWindow : public QMainWindow, public TypeVariant
{
    Q_OBJECT

public:

    explicit TypeUiMainWindow( TypeController& controller, QWidget* parent = 0 );
    ~TypeUiMainWindow() override;

    void                          UpdateRecordExplorer();
    void                          UpdateFileExplorer();
    void                          UpdateHtmlTextView();
    void                          UpdateHtmlWebView();
    void                          UpdateSceneView();
    void                          UpdateActions();

    void                          InitConnections();
    void                          closeEvent( QCloseEvent* ) override;
    void                          SetTitle( QString title );
    void                          SetCurrentTab( int index );

    M_REFERENCE                   ( Controller,          TypeController )
    M_REFERENCE                   ( RecordExplorer,      TypeUiRecordExplorer )
    M_REFERENCE                   ( FileExplorer,        TypeUiFileExplorer )
    M_REFERENCE                   ( EditorContainer,     TypeUiEditorContainer )
    M_REFERENCE                   ( HtmlTextView,        TypeUiHtmlTextView )

    void                          SetPropertyWidgetRecord( TypeRecord* record );
    void                          SetPropertyWidget( QWidget* widget );
    void                          OpenEditorWidget( TypeUiEditor* widget );

private:

    QWidget*                      m_PropertiesWidget;
    Ui::TypeUiMainWindow*         ui;

};

#define MAINWINDOW_TAB_SCENE   0
#define MAINWINDOW_TAB_EDITOR  1
#define MAINWINDOW_TAB_HTML  2
#define MAINWINDOW_TAB_OUTPUT  3



#endif // UIMAINWINDOW_H
