#ifndef C_CONTROLLER_H
#define C_CONTROLLER_H

#include "FW/macro.h"
#include "FW/variant.h"

#include <QObject>
#include <QStringList>

class C_Record;
class C_UiMainWindow;
class C_Document;
class C_StateWriter;
class C_Config;
class C_Database;
class C_Clipboard;
class C_HtmlBuilder;

class C_Controller : public QObject, public C_Variant
{
    Q_OBJECT

public:

    C_Controller();
    ~C_Controller() override;

    static bool         AcceptMessage( QString msg );
    static void         Message( QString msg );
    static QString      LoadTextFile( QString file_name );
    static void         SaveTextFile( QString file_name, QString text );

    M_POINTER           ( Document,    C_Document )
    M_POINTER           ( MainWindow,  C_UiMainWindow )
    M_POINTER           ( Config,      C_Config )
    M_POINTER           ( Database,    C_Database )
    M_POINTER           ( HtmlBuilder, C_HtmlBuilder )
    M_POINTER           ( Clipboard,   C_Clipboard )

    void                ConnectSlots();

    void                SetPropertyWidgetRecord( C_Record& record );
    void                OpenRecordEditorWidget( C_Record& record );
    void                OpenFileEditorWidget( QString file_name );

public slots:

    void                OnDirectoryChanged();

    void                OnRecordExplorerChanged();
    void                OnFileExplorerChanged();
    void                OnRecordsChanged();
    void                OnSceneChanged();
    void                OnHtmlCodeChanged();
    void                OnEditorContainerChanged();

    void                OnActionRunHtmlCode();
    void                OnActionUpdateHtmlCode();
    void                OnActionSaveHtmlCode();

    void                OnActionNewProjectFile();
    void                OnActionLoadProjectFile();
    void                OnActionSaveProjectFile();
    void                OnActionLoadProjectSQL();
    void                OnActionSaveProjectSQL();

    void                OnActionExit();

    void                OnActionAddRecord();
    void                OnActionChangePropertyWidget();
    void                OnActionRemoveRecord();
    void                OnActionAddSceneItem();
    void                OnActionCopyRecord();
    void                OnActionPasteRecord();
    void                OnActionCutRecord();
    void                OnActionOpenRecordInEditor();

    void                OnActionNewFile();
    void                OnActionCloseFile();
    void                OnActionCloseAllFiles();
    void                OnActionSaveFile();
    void                OnActionSaveAllFiles();
    void                OnActionLoadFile();

signals:

    void                DirectoryChanged();
    void                RecordExplorerChanged();
    void                FileExplorerChanged();
    void                RecordsChanged();
    void                SceneChanged();
    void                HtmlCodeChanged();
    void                TextEditorContainerChanged();

};

#endif // C_CONTROLLER_H
