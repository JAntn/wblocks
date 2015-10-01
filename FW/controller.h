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
class TypeRecordFactory;

class TypeController : public QObject, public TypeVariant
{
    Q_OBJECT

    static QList<TypeRecordFactory*>        m_FactoryList;
    static TypeUiSyntaxHighlighterFactory   m_SyntaxHighlighterFactory;

public:

    static const QList<TypeRecordFactory*>& FactoryList();
    static TypeRecordFactory*               FactoryFromName( QString class_name );
    static TypeUiSyntaxHighlighterFactory&  SyntaxHighlighterFactory();

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
    M_REFERENCE                             ( Clipboard,   TypeClipboard )
    M_VALUE                                 ( BinPath,     QString )

    void                                    ConnectSlots();

    QString                                 NewFileNameId( QString file_name );
    QString                                 NewHtmlTextViewId( QString file_name );

    void                                    OpenRecordEditorWidget( TypeRecord& record );
    void                                    OpenFileUiEditor( QString file_name );
    void                                    NewFileUiEditor( QString file_name );

public slots:

    // change events

    void                                    OnLeftTabCurrentChanged( int index );
    void                                    OnRightTabCurrentChanged( int index );

    void                                    OnDirectoryChanged();
    void                                    OnRecordExplorerChanged();
    void                                    OnFileExplorerChanged();

    void                                    OnRecordChanged( TypeRecord* record );
    void                                    OnRecordRemoved( TypeRecord* record );

    void                                    OnSceneChanged();
    void                                    OnHtmlTextChanged();
    void                                    OnEditorContainerChanged();

    // html

    void                                    OnActionHtmlUpdateWeb();
    void                                    OnActionHtmlUpdateText();
    void                                    OnActionHtmlSaveAs();
    void                                    OnActionHtmlSave();

    // project

    void                                    OnActionProjectNew();
    void                                    OnActionProjectOpen();
    void                                    OnActionProjectSaveAs();
    void                                    OnActionProjectSave();

    void                                    OnActionExit();

    // record

    void                                    OnActionRecordAdd();
    void                                    OnActionChangePropertyWidget();
    void                                    OnActionRecordRemove();
    void                                    OnActionRecordAddSceneItem();
    void                                    OnActionRecordCopy();
    void                                    OnActionRecordPaste();
    void                                    OnActionRecordCut();
    void                                    OnActionRecordOpenInEditor();

    // file

    void                                    OnActionFileNew();
    void                                    OnActionFileClose();
    void                                    OnActionFileCloseAll();
    void                                    OnActionFileSaveAs();
    void                                    OnActionFileSave();
    void                                    OnActionFileSaveAll();
    void                                    OnActionFileOpen();

    // file explorer

    void                                    OnActionFileNew_FileExplorer();
    void                                    OnActionFileOpen_FileExplorer();
    void                                    OnActionFileRemove_FileExplorer();
    void                                    OnActionFileMkDir_FileExplorer();

signals:

    void                                    DirectoryChanged();
    void                                    RecordExplorerChanged();
    void                                    FileExplorerChanged();

    void                                    RecordChanged( TypeRecord* record = 0 );
    void                                    RecordRemoved( TypeRecord* record = 0 );

    void                                    SceneChanged();
    void                                    HtmlTextChanged();
    void                                    EditorContainerChanged();
    void                                    SetActiveRecord( TypeRecord* record = 0 );
};

#endif // CONTROLLER_H
