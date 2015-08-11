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
class C_Clipboard;

class C_Document : public C_Variant
{
public:

    C_Document( C_UiMainWindow& main_window, C_Variant* parent = 0 );
    ~C_Document();

    void                FileSave( QFile& file );
    void                FileLoad( QFile& file );

    void                DatabaseSave( QString file_name );
    void                DatabaseLoad( QString file_name );

    void                UpdateScript();
    void                UpdateScene();

    void                Clear();

    ATR_POINTER         ( MainWindow, C_UiMainWindow )
    ATR_POINTER         ( Database,   C_Database )
    ATR_POINTER         ( Script,     C_Script )
    ATR_POINTER         ( Signals,    C_Signals )
    ATR_POINTER         ( Records,    C_RecordStruct )
    ATR_POINTER         ( Scene,      C_Scene )
    ATR_POINTER         ( Context,    C_Context )
    ATR_POINTER         ( Clipboard,  C_Clipboard )

    static bool         AcceptMessage( QString msg );
    static void         Message( QString msg );
    static QString      LoadTextFile( QString file_name );
    static void         SaveTextFile( QString file_name, QString text );
};

#include "context.h"
#include "script.h"
#include "signals.h"

#endif // C_APPMANAGER_H
