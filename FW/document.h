#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "FW/tools.h"

class TypeScene;
class TypeStruct;
class TypeStructRecord;
class TypeScript;
class TypeDatabase;
class TypeRecord;
class TypeSceneItem;
class TypeController;
class TypeContext;
class TypeClipboard;
class TypeHtmlBuilder;
class TypeRootStruct;
class TypeUiHtmlTextView;

class TypeDocument : public TypeVariant
{
public:

    TypeDocument( TypeController& controller, QString file_name, QString path, TypeVariant* Parent = 0 );
    ~TypeDocument();

    int                                     SaveFile( QString file_name );
    int                                     LoadFile( QString file_name );
    int                                     SaveSQL( QString file_name );
    int                                     LoadSQL( QString file_name );
    void                                    UpdateHtml();
    void                                    Clear();

    virtual QWidget*                        EditorWidget();


    M_VALUE                                 ( FileName,        QString )
    M_VALUE                                 ( Path,            QString )
    M_REFERENCE                             ( Root,            TypeRootStruct )
    M_REFERENCE                             ( Scene,           TypeScene )
    M_REFERENCE                             ( HtmlBuilder,     TypeHtmlBuilder )
    M_REFERENCE                             ( Context,         TypeContext )
    M_REFERENCE                             ( Controller,      TypeController )


};

#endif // DOCUMENT_H
