#ifndef C_DOCUMENT_H
#define C_DOCUMENT_H

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
class C_Events;
class C_UiMainWindow;
class C_Context;
class C_Clipboard;

class C_Document : public C_Variant
{
public:

    C_Document(QString file_name, QString path, C_UiMainWindow& main_window, C_Variant* parent = 0 );
    ~C_Document();

    void                SaveFile( QFile& file );
    void                LoadFile( QFile& file );

    void                SaveSQL( QString file_name );
    void                LoadSQL( QString file_name );

    void                UpdateScript();
    void                UpdateScene();

    void                Clear();

    ATR_VALUE           ( FileName,   QString )
    ATR_VALUE           ( Path,       QString )

    ATR_POINTER         ( MainWindow, C_UiMainWindow )
    ATR_POINTER         ( Database,   C_Database )
    ATR_POINTER         ( Script,     C_Script )
    ATR_POINTER         ( Events,     C_Events )
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
#include "events.h"

#endif // C_DOCUMENT_H
