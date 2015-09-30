#include "FW/UI/ED/ui_editor.h"
#include <QWidget>

TypeUiEditor::TypeUiEditor(
    QString id,
    QString name,
    QString tab_name,
    QWidget* parent ,
    TypeSaveCallback save_callback ,
    TypeSaveCallback save_as_callback,
    TypeUpdateCallback update_callback ) :

    QWidget( parent ),
    TypeVariant( 0 ),
    m_Id( id ),
    m_Name( name ),
    m_TabName( tab_name ),
    m_HasChanged( false ),
    m_SaveCallback( save_callback ),
    m_SaveAsCallback( save_as_callback ),
    m_UpdateCallback( update_callback ),
    m_EditorContainer( 0 )
{

    if( m_TabName.isEmpty() )
        m_TabName = m_Name;

    if( m_TabName.size() < 16 )
        m_TabName.append( QString( 16 - m_TabName.size(), ' ' ) );

}

TypeUiEditor::~TypeUiEditor()
{
    // void
}

bool TypeUiEditor::empty_save_callback( TypeUiEditor& )
{
    return true;
}

bool TypeUiEditor::empty_update_callback( TypeUiEditor& )
{
    return true;
}

void TypeUiEditor::OnActionUpdate()
{
    if( m_UpdateCallback( *this ) )
        emit HasUpdated();

}

void TypeUiEditor::OnActionSave()
{
    if( m_SaveCallback( *this ) )
        emit HasSaved();
}

void TypeUiEditor::OnActionSaveAs()
{
    if( m_SaveAsCallback( *this ) )
        emit HasSaved();
}
