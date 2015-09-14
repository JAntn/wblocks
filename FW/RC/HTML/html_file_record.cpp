#include "FW/tools.h"
#include "FW/RC/HTML/html_file_record.h"
#include <QCoreApplication>

TypeHtmlFileRecord::TypeHtmlFileRecord( QString id, QString name, QString value,  TypeVariant* parent, TypeStruct* root ):
    TypeTextFileRecord( id, name, value, parent, root )
{
    m_Class = "HtmlFile";
}

TypeHtmlFileRecord::TypeHtmlFileRecord( TypeStateWriter& state, TypeVariant* parent, TypeStruct* root ):
    TypeTextFileRecord( "", "", "", parent, root )
{
    m_Class = "HtmlFile";
    SetState( state, root );
}

TypeHtmlFileRecord::~TypeHtmlFileRecord()
{
    // void
}

QString TypeHtmlFileRecord::FileFormatTitle()
{
    //
    // Used in QFileDialog:

    return QCoreApplication::translate( "TypeHtmlFileRecord", "Html" );
}

QString TypeHtmlFileRecord::FileFormat()
{
    //
    // Used in QFileDialog:

    return "HTML";
}

QString TypeHtmlFileRecord::FileExtension()
{
    //
    // Used in QFileDialog:

    return "(*.html)";
}

TypeHtmlFileRecordFactory::TypeHtmlFileRecordFactory()
{
    m_RecordClass = "HtmlFile";
}

TypeRecord* TypeHtmlFileRecordFactory::NewInstance( QString name, QString value, TypeVariant* parent, TypeStruct* root )
{
    return new TypeHtmlFileRecord( TypeRecordFactory::GenerateId(), name, value, parent, root );
}

TypeRecord* TypeHtmlFileRecordFactory::NewInstance( TypeStateWriter& state, TypeVariant* parent, TypeStruct* root )
{
    return new TypeHtmlFileRecord( state, parent, root );
}
