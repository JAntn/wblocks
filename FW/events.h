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

    C_Events(C_Document& document,C_UiMainWindow& window, QObject* parent=0);
    ~C_Events() override;

    ATR_POINTER         (Document,   C_Document)
    ATR_POINTER         (MainWindow, C_UiMainWindow)
    ATR_VALUE           (EventData,  QStringList)

    void                InitConnections();

public slots:

    void                OnDirectoryChanged();

    void                OnRecordExplorerChanged();
    void                OnFileExplorerChanged();
    void                OnRecordsChanged();
    void                OnSceneChanged();
    void                OnClientScriptChanged();
    void                OnCodeEditorContainerChanged();

    void                OnActionRunClientScript();
    void                OnActionUpdateClientScript();
    void                OnActionSaveClientScript();

    void                OnActionLoadFile();
    void                OnActionSaveFile();
    void                OnActionLoadSQL();
    void                OnActionSaveSQL();

    void                OnActionExit();
    void                OnActionNewFile();

    void                OnActionAddRecord();
    void                OnActionEditRecord();
    void                OnActionRemoveRecord();
    void                OnActionAddSceneItem();
    void                OnActionCopyRecord();
    void                OnActionPasteRecord();
    void                OnActionCutRecord();

    void                OnActionFindRecord();

    void                OnActionNewEditorFile();
    void                OnActionCloseEditorFile();
    void                OnActionCloseAllEditorFiles();
    void                OnActionSaveEditorFile();
    void                OnActionSaveAllEditorFiles();
    void                OnActionLoadEditorFile();

signals:

    void                DirectoryChanged();
    void                RecordExplorerChanged();
    void                FileExplorerChanged();
    void                RecordsChanged();
    void                SceneChanged();
    void                ClientScriptChanged();
    void                CodeEditorContainerChanged();

};

#endif // C_EVENTS_H
