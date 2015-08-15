#ifndef C_SIGNALS_H
#define C_SIGNALS_H

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

    void                ConnectEvents();

public slots:

    void                OnRecordsChanged();
    void                OnScriptChanged();
    void                OnSceneChanged();

    void                OnActionFileLoad();
    void                OnActionFileSave();
    void                OnActionSQLLoad();
    void                OnActionSQLSave();
    void                OnActionScriptSave();

    void                OnActionAdd();
    void                OnActionEdit();
    void                OnActionRemove();
    void                OnActionAddSceneItem();
    void                OnActionCopy();
    void                OnActionPaste();
    void                OnActionCut();
    void                OnActionRunScript();
    void                OnActionExit();
    void                OnActionNewDocument();
    void                OnActionFind();

signals:

    void                RecordsChanged();
    void                ScriptChanged();
    void                SceneChanged();


};

#endif // C_SIGNALS_H
