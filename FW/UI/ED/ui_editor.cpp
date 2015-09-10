#include "FW/UI/ED/ui_editor.h"
#include <QWidget>

TypeUiEditor::TypeUiEditor( QString id, QString name, QString tab_name, QWidget* parent , TypeSaveCallback save_callback ) :
    QWidget( parent ),
    TypeVariant( 0 ),
    m_Id( id ),
    m_Name( name ),
    m_TabName( tab_name ),
    m_HasChanged( false ),
    m_SaveCallback( save_callback )
{

    if( m_TabName.isEmpty() )
        m_TabName = m_Name;

    if( m_TabName.size() < 10 )
        m_TabName.append( QString( 10 - m_TabName.size(), ' ' ) );
}

TypeUiEditor::~TypeUiEditor()
{
    // void
}

bool TypeUiEditor::empty_save_callback( TypeUiEditor& )
{
    return true;
}

void TypeUiEditor::OnActionSave()
{
    if( m_SaveCallback( *this ) )
        emit HasSaved();
}

