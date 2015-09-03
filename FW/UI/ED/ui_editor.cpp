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
}

TypeUiEditor::~TypeUiEditor()
{
    // void
}

void TypeUiEditor::OnActionSave()
{
    m_SaveCallback( *this );
}

