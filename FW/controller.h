#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "FW/tools.h"

class TypeRecord;
class TypeUiMainWindow;
class TypeDocument;
class TypeStateWriter;
class TypeConfig;
class TypeDatabase;
class TypeClipboard;
class TypeHtmlBuilder;
class TypeUiSyntaxHighlighter;
class TypeUiSyntaxHighlighterFactory;

class TypeController : public QObject, public TypeVariant
{
    Q_OBJECT

public:

    TypeController();
    ~TypeController() override;

    static bool                             AcceptMessage( QString msg );
    static void                             Message( QString msg );
    static QString                          LoadTextFile( QString file_name );
    static void                             SaveTextFile( QString file_name, QString text );

    M_REFERENCE                             ( Document,    TypeDocument )
    M_REFERENCE                             ( MainWindow,  TypeUiMainWindow )
    M_REFERENCE                             ( Config,      TypeConfig )
    M_REFERENCE                             ( Database,    TypeDatabase )
    M_REFERENCE                             ( HtmlBuilder, TypeHtmlBuilder )
    M_REFERENCE                             ( Clipboard,   TypeClipboard )
    M_VALUE                                 ( BinPath,     QString )
    M_REFERENCE                             ( SyntaxHighlighterFactory,   TypeUiSyntaxHighlighterFactory )

    void                                    ConnectSlots();

    QString                                 NewFileNameId( QString file_name );
    QString                                 NewHtmlTextViewId( QString file_name );

    void                                    SetPropertyWidgetRecord( TypeRecord& record );
    //void                                    ClearPropertyWidgetRecord();

    void                                    OpenRecordEditorWidget( TypeRecord& record );
    void                                    OpenFileUiEditor( QString file_name );

public slots:

    // change events

    void                                    OnLeftTabCurrentChanged( int index );
    void                                    OnRightTabCurrentChanged( int index );

    void                                    OnDirectoryChanged();
    void                                    OnRecordExplorerChanged();
    void                                    OnFileExplorerChanged();

    void                                    OnRecordsChanged();
    void                                    OnSceneChanged();
    void                                    OnHtmlTextChanged();
    void                                    OnEditorContainerChanged();

    // html

    void                                    OnActionUpdateHtmlWeb();
    void                                    OnActionUpdateHtmlText();
    void                                    OnActionSaveHtmlFile();

    // project

    void                                    OnActionNewProjectFile();
    void                                    OnActionLoadProjectFile();
    void                                    OnActionSaveProjectFile();
    void                                    OnActionLoadProjectSQL();
    void                                    OnActionSaveProjectSQL();

    void                                    OnActionExit();

    // record

    void                                    OnActionAddRecord();
    void                                    OnActionChangePropertyWidget();
    void                                    OnActionRemoveRecord();
    void                                    OnActionAddSceneItem();
    void                                    OnActionCopyRecord();
    void                                    OnActionPasteRecord();
    void                                    OnActionCutRecord();
    void                                    OnActionOpenRecordInEditor();

    // file

    void                                    OnActionNewFile();
    void                                    OnActionCloseFile();
    void                                    OnActionCloseAllFiles();
    void                                    OnActionSaveFile();
    void                                    OnActionSaveAllFiles();
    void                                    OnActionLoadFile();



signals:

    void                                    DirectoryChanged();
    void                                    RecordExplorerChanged();
    void                                    FileExplorerChanged();
    void                                    RecordsChanged();
    void                                    SceneChanged();
    void                                    HtmlTextChanged();
    void                                    EditorContainerChanged();
    void                                    SetActiveRecord(TypeRecord* record);


};

#endif // CONTROLLER_H
