#ifndef C_EVENTS_H
#define C_EVENTS_H

#include "FW/macro.h"

#include <QObject>
#include <QStringList>

class C_Record;
class C_UiMainWindow;
class C_Document;

class C_Events : public QObject
{
    Q_OBJECT

public:

    C_Events(C_Document& document,C_UiMainWindow& window);
    ~C_Events() override;

    M_POINTER           (Document,   C_Document)
    M_POINTER           (MainWindow, C_UiMainWindow)
    M_VALUE             (EventData,  QStringList)

    void                InitConnections();

public slots:

    void                OnDirectoryChanged();

    void                OnRecordExplorerChanged();
    void                OnFileExplorerChanged();
    void                OnRecordsChanged();
    void                OnSceneChanged();
    void                OnClientScriptChanged();
    void                OnTextEditorContainerChanged();

    void                OnActionRunClientScript();
    void                OnActionUpdateClientScript();
    void                OnActionSaveClientScript();

    void                OnActionNewProjectFile();
    void                OnActionLoadProjectFile();
    void                OnActionSaveProjectFile();
    void                OnActionLoadProjectSQL();
    void                OnActionSaveProjectSQL();

    void                OnActionExit();

    void                OnActionAddRecord();
    void                OnActionEditRecordProperties();
    void                OnActionRemoveRecord();
    void                OnActionAddSceneItem();
    void                OnActionCopyRecord();
    void                OnActionPasteRecord();
    void                OnActionCutRecord();
    void                OnActionOpenRecordInEditor();

    void                OnActionFindRecord();

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
    void                ClientScriptChanged();
    void                TextEditorContainerChanged();

};

#endif // C_EVENTS_H
