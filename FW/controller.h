#ifndef TypeCONTROLLER_H
#define TypeCONTROLLER_H

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

    void                ConnectSlots();

    void                SetPropertyWidgetRecord( TypeRecord& record );
    void                OpenRecordEditorWidget( TypeRecord& record );
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

#endif // TypeCONTROLLER_H
