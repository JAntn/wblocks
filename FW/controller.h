#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "FW/macro.h"
#include "FW/variant.h"
#include <QObject>
#include <QStringList>

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

    static bool         AcceptMessage( QString msg );
    static void         Message( QString msg );
    static QString      LoadTextFile( QString file_name );
    static void         SaveTextFile( QString file_name, QString text );

    M_POINTER           ( Document,    TypeDocument )
    M_POINTER           ( MainWindow,  TypeUiMainWindow )
    M_POINTER           ( Config,      TypeConfig )
    M_POINTER           ( Database,    TypeDatabase )
    M_POINTER           ( HtmlBuilder, TypeHtmlBuilder )
    M_POINTER           ( Clipboard,   TypeClipboard )
    M_VALUE             ( BinPath,     QString )
    M_POINTER           ( SyntaxHighlighterFactory,   TypeUiSyntaxHighlighterFactory )

    void                ConnectSlots();

    QString             NewFileNameId( QString file_name );
    QString             NewHtmlBlocksEditorId(QString file_name);

    void                SetPropertyWidgetRecord( TypeRecord& record );
    void                OpenRecordEditorWidget( TypeRecord& record );
    void                OpenFileUiEditor( QString file_name );


public slots:

    void                OnDirectoryChanged();

    void                OnRecordExplorerChanged();
    void                OnFileExplorerChanged();
    void                OnRecordsChanged();
    void                OnSceneChanged();
    void                OnHtmlBlocksChanged();
    void                OnEditorContainerChanged();

    void                OnActionRunHtmlBlocks();
    void                OnActionUpdateHtmlBlocks();
    void                OnActionSaveHtmlBlocks();

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
    void                HtmlBlocksChanged();
    void                EditorContainerChanged();

};

#endif // CONTROLLER_H
