#include "FW/document.h"
#include "FW/UI/ui_editor_container.h"
#include "FW/UI/ED/ui_editor.h"
#include <QVBoxLayout>

C_UiEditorContainer::C_UiEditorContainer( C_Controller& controller, QWidget* parent ):
    QWidget( parent ),
    m_Controller( &controller )
{
    m_TabWidget = new QTabWidget;
    m_TabWidget->setTabsClosable( true );
    m_TabWidget->setMovable( true );

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget( m_TabWidget );
    setLayout( layout );

    connect(
        m_TabWidget,
        QTabWidget::tabCloseRequested,
        this,
        C_UiEditorContainer::OnCloseTabRequested
    );
}

void C_UiEditorContainer::Append( C_UiEditor* editor )
{
    m_TabWidget->addTab( editor, editor->TabName() );
    emit Controller().TextEditorContainerChanged();
}

void C_UiEditorContainer::SetCurrent( QString id )
{
    for( int index = 0; index < m_TabWidget->count(); ++index )
    {
        C_UiEditor* editor = static_cast<C_UiEditor*>( m_TabWidget->widget( index ) );

        if( editor->Id() == id )
        {
            m_TabWidget->setCurrentIndex( index );
            return;
        }
    }
}

void C_UiEditorContainer::SetCurrent( int index )
{
    m_TabWidget->setCurrentIndex( index );
}

void C_UiEditorContainer::Close( QString id )
{
    for( int index = 0; index < m_TabWidget->count(); ++index )
    {
        C_UiEditor* editor = static_cast<C_UiEditor*>( m_TabWidget->widget( index ) );

        if( editor->Id() == id )
        {
            m_TabWidget->removeTab( index );
            emit Controller().TextEditorContainerChanged();
            return;
        }
    }
}

void C_UiEditorContainer::Close( int index )
{
    m_TabWidget->removeTab( index );
    emit Controller().TextEditorContainerChanged();
    return;
}

void C_UiEditorContainer::CloseCurrent()
{
    int index = m_TabWidget->currentIndex();
    m_TabWidget->removeTab( index );
    emit Controller().TextEditorContainerChanged();
}

void C_UiEditorContainer::CloseAll()
{
    m_TabWidget->clear();
    emit Controller().TextEditorContainerChanged();
}

void C_UiEditorContainer::Save( int index )
{
    C_UiEditor* editor = static_cast<C_UiEditor*>( m_TabWidget->widget( index ) );
    editor->OnActionSave();
}

void C_UiEditorContainer::Save( QString id )
{
    for( int index = 0; index < m_TabWidget->count(); ++index )
    {
        C_UiEditor* editor = static_cast<C_UiEditor*>( m_TabWidget->widget( index ) );

        if( editor->Id() == id )
        {
            editor->OnActionSave();
            return;
        }
    }
}

void C_UiEditorContainer::SaveAll()
{
    for( int index = 0; index < m_TabWidget->count(); ++index )
    {
        C_UiEditor* editor = static_cast<C_UiEditor*>( m_TabWidget->widget( index ) );
        editor->OnActionSave();
    }
}

void C_UiEditorContainer::SaveCurrent()
{
    int index = m_TabWidget->currentIndex();
    C_UiEditor* editor = static_cast<C_UiEditor*>( m_TabWidget->widget( index ) );
    editor->OnActionSave();
}

bool C_UiEditorContainer::HasId( QString id )
{
    for( int index = 0; index < m_TabWidget->count(); ++index )
    {
        C_UiEditor* editor = static_cast<C_UiEditor*>( m_TabWidget->widget( index ) );

        if( editor->Id() == id )
            return true;
    }

    return false;
}

int C_UiEditorContainer::Size()
{
    return m_TabWidget->count();
}

void C_UiEditorContainer::OnCloseTabRequested( int index )
{
    C_UiEditor* editor = static_cast<C_UiEditor*>( m_TabWidget->widget( index ) );

    if( editor->HasChanged() )
        if( C_Controller::AcceptMessage( tr( "Save changes?" ) ) )
            editor->OnActionSave();

    Close( index );
}
