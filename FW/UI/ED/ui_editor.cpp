#include "FW/UI/ED/ui_editor.h"
#include <QWidget>


TypeUiEditor::TypeUiEditor(QString id, QString name, QString tab_name, save_callback_t save_callback, QWidget* parent ) :
    QWidget( parent ),
    m_Id( id ),
    m_Name( name ),
    m_TabName( tab_name ),
    m_HasChanged( false ),
    m_SaveCallBack( save_callback )
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
    m_SaveCallBack( *this );
}

