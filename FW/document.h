#ifndef TypeDOCUMENT_H
#define TypeDOCUMENT_H

#include "FW/macro.h"
#include "FW/variant.h"

#include <QFile>
#include <QObject>

class TypeScene;
class TypeRecordStruct;
class TypeScript;
class TypeDatabase;
class TypeRecord;
class TypeSceneItem;
class TypeController;
class TypeContext;
class TypeClipboard;
class TypeHtmlBuilder;

class TypeDocument : public TypeVariant
{
public:

    TypeDocument( TypeController& controller, QString file_name, QString path, TypeVariant* parent = 0 );
    ~TypeDocument();

    int                 SaveFile( QString file_name );
    int                 LoadFile( QString file_name );
    int                 SaveSQL( QString file_name );
    int                 LoadSQL( QString file_name );
    void                UpdateHtml();
    void                Clear();

    M_VALUE             ( Html,        QString )
    M_VALUE             ( FileName,    QString )
    M_VALUE             ( Path,        QString )
    M_POINTER           ( Root,        TypeRecordStruct )
    M_POINTER           ( Scene,       TypeScene )
    M_POINTER           ( Context,     TypeContext )
    M_POINTER           ( Controller,  TypeController )

};

#include "context.h"
#include "controller.h"

#endif // TypeDOCUMENT_H
