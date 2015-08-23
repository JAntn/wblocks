#include "FW/document.h"
#include "FW/UI/ui_code_editor_container.h"
#include "FW/UI/ui_code_editor.h"
#include <QVBoxLayout>

C_UiCodeEditorContainer::C_UiCodeEditorContainer( QWidget* parent ):
    QWidget( parent )
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
        C_UiCodeEditorContainer::OnCloseTabRequested
    );
}

void C_UiCodeEditorContainer::Select( QString file_name )
{
    for( int index = 0; index < m_TabWidget->count(); ++index )
    {
        auto* editor = static_cast<C_UiCodeEditor*>( m_TabWidget->widget( index ) );

        if( editor->FileName() == file_name )
        {
            m_TabWidget->setCurrentIndex( index );
            return;
        }
    }

}

void C_UiCodeEditorContainer::Append( QString file_name )
{
    m_TabWidget->addTab( new C_UiCodeEditor( file_name ), file_name.split( "/" ).back() );
}

void C_UiCodeEditorContainer::Clear( QString file_name )
{
    for( int index = 0; index < m_TabWidget->count(); ++index )
    {
        auto* editor = static_cast<C_UiCodeEditor*>( m_TabWidget->widget( index ) );

        if( editor->FileName() == file_name )
        {
            m_TabWidget->removeTab( index );
            return;
        }
    }
}

void C_UiCodeEditorContainer::Close( QString file_name )
{
    for( int index = 0; index < m_TabWidget->count(); ++index )
    {
        auto* editor = static_cast<C_UiCodeEditor*>( m_TabWidget->widget( index ) );

        if( editor->FileName() == file_name )
        {
            m_TabWidget->removeTab( index );
            return;
        }
    }
}

void C_UiCodeEditorContainer::Close( int index )
{
    m_TabWidget->removeTab( index );
    return;
}

void C_UiCodeEditorContainer::CloseCurrent()
{
    int index = m_TabWidget->currentIndex();
    m_TabWidget->removeTab( index );
}

void C_UiCodeEditorContainer::SaveAll()
{
    for( int index = 0; index < m_TabWidget->count(); ++index )
    {
        auto* editor = static_cast<C_UiCodeEditor*>( m_TabWidget->widget( index ) );
        editor->Save();
    }
}

void C_UiCodeEditorContainer::SaveCurrent()
{
    int index = m_TabWidget->currentIndex();
    auto* editor = static_cast<C_UiCodeEditor*>( m_TabWidget->widget( index ) );
    editor->Save();
}

void C_UiCodeEditorContainer::Save( int index )
{
    auto* editor = static_cast<C_UiCodeEditor*>( m_TabWidget->widget( index ) );
    editor->Save();
}

bool C_UiCodeEditorContainer::HasFile( QString file_name )
{
    for( int index = 0; index < m_TabWidget->count(); ++index )
    {
        auto* editor = static_cast<C_UiCodeEditor*>( m_TabWidget->widget( index ) );

        if( editor->FileName() == file_name )
            return true;
    }

    return false;
}

int C_UiCodeEditorContainer::Size()
{
    return m_TabWidget->count();
}

void C_UiCodeEditorContainer::CloseAll()
{
    m_TabWidget->clear();
}

void C_UiCodeEditorContainer::OnCloseTabRequested( int index )
{
    auto* editor = static_cast<C_UiCodeEditor*>( m_TabWidget->widget( index ) );

    if( editor->HasChanged() )
        if( C_Document::AcceptMessage( tr( "Save changes?" ) ) )
            editor->Save();

    Close( index );
}
