#include "FW/RC/html_record.h"
#include "FW/RC/record_struct.h"
#include "FW/RC/struct_record.h"
#include "FW/document.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include "FW/UI/ui_main_window.h"
#include "FW/RC/string_record.h"
#include "FW/RC/struct_record.h"

#define CLASS_NAME "Html"

C_HtmlRecord::C_HtmlRecord( QString id, QString name, QString value,  C_Variant* parent, C_RecordStruct* root ):
    C_Record( id, name, value, parent, root )
{
    m_Records = new C_RecordStruct( m_Name, this );
    Records().SetFlags( FLAG_ACTION_ALL );

    m_HtmlTag = static_cast<C_StringRecord*> ( Records().CreateRecord( "HtmlTag", "", "String", -1, root ) );
    HtmlTag().SetFlags( ~( FLAG_ACTION_REMOVE & FLAG_ACTION_CUT )  );

    m_HtmlAtributes = static_cast<C_StructRecord*> ( Records().CreateRecord( "HtmlAtributes", "", "Struct", -1, root ) );
    HtmlAtributes().SetFlags( ~( FLAG_ACTION_REMOVE & FLAG_ACTION_CUT ) );


    m_HtmlContent = static_cast<C_StringRecord*> ( Records().CreateRecord( "HtmlContent", "", "String", -1, root ) );
    HtmlContent().SetFlags( ~( FLAG_ACTION_REMOVE & FLAG_ACTION_CUT )  );

    m_Code = "";
}

C_HtmlRecord::C_HtmlRecord( C_StateWriter& state, C_Variant* parent, C_RecordStruct* root ):
    C_Record( "", "", "", parent, root )
{
    m_Records = new C_RecordStruct( "", this );
    Records().SetFlags( FLAG_ACTION_ALL );

    m_HtmlTag = static_cast<C_StringRecord*> ( Records().CreateRecord( "HtmlTag", "", "String", -1, root ) );
    HtmlTag().SetFlags( ~( FLAG_ACTION_REMOVE & FLAG_ACTION_CUT ) );

    m_HtmlAtributes = static_cast<C_StructRecord*> ( Records().CreateRecord( "HtmlAtributes", "", "Struct", -1, root ) );
    HtmlAtributes().SetFlags( ~( FLAG_ACTION_REMOVE & FLAG_ACTION_CUT ) );

    m_HtmlContent = static_cast<C_StringRecord*> ( Records().CreateRecord( "HtmlContent", "", "String", -1, root ) );
    HtmlContent().SetFlags( ~( FLAG_ACTION_REMOVE & FLAG_ACTION_CUT ) );

    SetState( state, root );
}

QString C_HtmlRecord::Html()
{
    QStringList html;

    html << "\n<" << HtmlTag().Value();

    for( C_Variant* variant : HtmlAtributes().Records() )
    {
        auto* record = static_cast<C_StringRecord*>( variant );
        html << "\n" << record->Name() << " = \"" << record->Value() << "\"";
    }

    html << "\n>";
    html << HtmlContent().Value();

    int count = 0;

    for( C_Variant* variant : Records() )
    {
        // SKIP DEFAULT MEMBERS
        if( count < 3 )
            ++count;

        auto* record = static_cast<C_Record*>( variant );
        html << record->Html();
    }

    html << "\n</" << HtmlTag().Value() << ">";
    return html.join("");
}

C_HtmlRecord::~C_HtmlRecord()
{
    // void
}

C_RecordStruct* C_HtmlRecord::Struct()
{
    return m_Records;
}

QString C_HtmlRecord::Value()
{
    return QString::number( Records().Size() );
}

void C_HtmlRecord::SetValue( QString )
{
    // void
}

QString C_HtmlRecord::Class() const
{
    return CLASS_NAME;
}



void C_HtmlRecord::GetState( C_StateReader& state )
{
    QStringList row;
    row.append( Id() );
    row.append( Name() );
    row.append( Value() );
    row.append( Class() );
    state.Read( row );

    for( C_Variant* variant : Records() )
    {
        C_Record* record = static_cast<C_Record*>( variant );
        record->GetState( state );
    }
}

void C_HtmlRecord::SetState( C_StateWriter& state, C_RecordStruct* root )
{
    Records().Clear();

    QStringList row;
    state.Write( row );

    if( state.Flags() & FLAG_STATE_NEWID )
        m_Id    = C_RecordFactory::GenerateId();
    else
        m_Id    = row[0];

    m_Name  = row[1];
    m_Value = row[2];
    int size = m_Value.toInt();

    for( int count = 0; count < size; ++count )
        Records().CreateRecord( state, -1, root );

    m_HtmlTag = static_cast<C_StringRecord*>( Records().FromName( "HtmlTag" ) );
    HtmlTag().SetFlags( ~( FLAG_ACTION_REMOVE & FLAG_ACTION_CUT ) );

    m_HtmlAtributes = static_cast<C_StructRecord*>( Records().FromName( "HtmlAtributes" ) );
    HtmlAtributes().SetFlags( ~( FLAG_ACTION_REMOVE & FLAG_ACTION_CUT ) );

    m_HtmlContent = static_cast<C_StringRecord*>( Records().FromName( "HtmlContent" ) );
    HtmlContent().SetFlags( ~( FLAG_ACTION_REMOVE & FLAG_ACTION_CUT ) );

    m_Code = "";
}

/*
void C_HtmlRecord::OpenInEditor(C_Document& document)
{

}

void C_HtmlRecord::EditProperties(C_Document& document)
{
    //QWidget* dialog = new C_UiHtmlEditor( *this, document, &document.MainWindow() );
    //dialog->show();
}
*/

C_Record* C_HtmlRecordFactory::CreateInstance( QString name, QString value, C_Variant* parent, C_RecordStruct* root )
{
    C_HtmlRecord* record = new C_HtmlRecord( C_RecordFactory::GenerateId(), name, value, parent, root );
    return record;
}

C_Record* C_HtmlRecordFactory::CreateInstance( C_StateWriter& state, C_Variant* parent, C_RecordStruct* root )
{
    C_HtmlRecord* record = new C_HtmlRecord( state, parent, root );
    return record;
}

QString C_HtmlRecordFactory::RecordClass() const
{
    return CLASS_NAME;
}

