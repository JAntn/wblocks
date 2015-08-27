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
class C_HtmlBuilder;

class C_Document : public C_Variant
{
public:

    C_Document(QString file_name, QString path, C_UiMainWindow& main_window, C_Variant* parent = 0 );
    ~C_Document();

    void                SaveFile( QFile& file );
    void                LoadFile( QFile& file );
    void                SaveSQL( QString file_name );
    void                LoadSQL( QString file_name );
    void                UpdateHtml();
    void                Clear();

    static bool         AcceptMessage( QString msg );
    static void         Message( QString msg );
    static QString      LoadTextFile( QString file_name );
    static void         SaveTextFile( QString file_name, QString text );

    M_VALUE             ( Html,        QString)
    M_VALUE             ( FileName,    QString )
    M_VALUE             ( Path,        QString )
    M_POINTER           ( MainWindow,  C_UiMainWindow )
    M_POINTER           ( Database,    C_Database )
    M_POINTER           ( HtmlBuilder, C_HtmlBuilder )
    M_POINTER           ( Events,      C_Events )
    M_POINTER           ( Root,        C_RecordStruct )
    M_POINTER           ( Scene,       C_Scene )
    M_POINTER           ( Context,     C_Context )
    M_POINTER           ( Clipboard,   C_Clipboard )
};

#include "context.h"
#include "events.h"

#endif // C_DOCUMENT_H
