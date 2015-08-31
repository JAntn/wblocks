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
class C_Controller;
class C_Context;
class C_Clipboard;
class C_HtmlBuilder;

class C_Document : public C_Variant
{
public:

    C_Document( C_Controller& controller, QString file_name, QString path, C_Variant* parent = 0 );
    ~C_Document();

    int                 SaveFile( QString file_name );
    int                 LoadFile( QString file_name );
    int                 SaveSQL( QString file_name );
    int                 LoadSQL( QString file_name );
    void                UpdateHtml();
    void                Clear();

    M_VALUE             ( Html,        QString )
    M_VALUE             ( FileName,    QString )
    M_VALUE             ( Path,        QString )
    M_POINTER           ( Root,        C_RecordStruct )
    M_POINTER           ( Scene,       C_Scene )
    M_POINTER           ( Context,     C_Context )
    M_POINTER           ( Controller,  C_Controller )

};

#include "context.h"
#include "controller.h"

#endif // C_DOCUMENT_H
