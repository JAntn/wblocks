#ifndef C_APPMANAGER_H
#define C_APPMANAGER_H

#include "FW/macro.h"
#include "FW/variant.h"

#include <QFile>
#include <QObject>

class C_Scene;
class C_RecordStruct;
class C_Script;
class C_Database;
class C_Record;
class C_SceneItem;
class C_Signals;
class C_UiMainWindow;
class C_Context;

class C_Document : public C_Variant
{
public:

                        C_Document(C_UiMainWindow& main_window, C_Variant* parent = 0);

    void                FileSave(QFile& file);
    void                FileLoad(QFile& file);

    void                DatabaseSave(QString file_name);
    void                DatabaseLoad(QString file_name);

    void                UpdateScript();
    void                UpdateScene();

    C_Record*           RecordAtId(QString id);
    C_Record*           RecordAtName(QString name);

    void                Clear();

    static bool         AcceptMessage(QString msg);
    static void         Message(QString msg);

    C_POINTER           (MainWindow, C_UiMainWindow)
    C_POINTER           (Database, C_Database)
    C_POINTER           (Script,   C_Script)
    C_POINTER           (Signals,  C_Signals)
    C_POINTER           (Records,  C_RecordStruct)
    C_POINTER           (Scene,    C_Scene)
    C_POINTER           (Context,  C_Context)

    static QString      LoadTextFile(QString file_name);
    static void         SaveTextFile(QString file_name, QString text);
};

#include "context.h"
#include "script.h"
#include "signals.h"

#endif // C_APPMANAGER_H
