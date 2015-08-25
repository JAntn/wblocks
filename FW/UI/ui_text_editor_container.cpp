#include "FW/document.h"
#include "FW/UI/ui_text_editor_container.h"
#include "FW/UI/ui_file_text_editor.h"
#include <QVBoxLayout>

C_UiTextEditorContainer::C_UiTextEditorContainer( QWidget* parent ):
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
        C_UiTextEditorContainer::OnCloseTabRequested
    );
}


void C_UiTextEditorContainer::Append(C_UiTextEditor* text_editor )
{
    m_TabWidget->addTab( text_editor, text_editor->TabName() );
}

void C_UiTextEditorContainer::SetCurrent( QString id )
{
    for( int index = 0; index < m_TabWidget->count(); ++index )
    {
        auto* editor = static_cast<C_UiTextEditor*>( m_TabWidget->widget( index ) );

        if( editor->Id() == id )
        {
            m_TabWidget->setCurrentIndex( index );
            return;
        }
    }
}
void C_UiTextEditorContainer::SetCurrent(int index)
{
    m_TabWidget->setCurrentIndex( index );
}

void C_UiTextEditorContainer::Close( QString id )
{
    for( int index = 0; index < m_TabWidget->count(); ++index )
    {
        auto* editor = static_cast<C_UiTextEditor*>( m_TabWidget->widget( index ) );

        if( editor->Id() == id )
        {
            m_TabWidget->removeTab( index );
            return;
        }
    }
}

void C_UiTextEditorContainer::Close( int index )
{
    m_TabWidget->removeTab( index );
    return;
}

void C_UiTextEditorContainer::CloseCurrent()
{
    int index = m_TabWidget->currentIndex();
    m_TabWidget->removeTab( index );
}

void C_UiTextEditorContainer::CloseAll()
{
    m_TabWidget->clear();
}

void C_UiTextEditorContainer::SaveState( int index )
{
    auto* editor = static_cast<C_UiTextEditor*>( m_TabWidget->widget( index ) );
    editor->SaveState();
}

void C_UiTextEditorContainer::SaveState(QString id)
{
    for( int index = 0; index < m_TabWidget->count(); ++index )
    {
        auto* editor = static_cast<C_UiTextEditor*>( m_TabWidget->widget( index ) );

        if( editor->Id() == id )
        {
            editor->SaveState();
            return;
        }
    }
}


void C_UiTextEditorContainer::SaveStateAll()
{
    for( int index = 0; index < m_TabWidget->count(); ++index )
    {
        auto* editor = static_cast<C_UiTextEditor*>( m_TabWidget->widget( index ) );
        editor->SaveState();
    }
}

void C_UiTextEditorContainer::SaveStateCurrent()
{
    int index = m_TabWidget->currentIndex();
    auto* editor = static_cast<C_UiTextEditor*>( m_TabWidget->widget( index ) );
    editor->SaveState();
}

bool C_UiTextEditorContainer::HasId( QString id )
{
    for( int index = 0; index < m_TabWidget->count(); ++index )
    {
        auto* editor = static_cast<C_UiTextEditor*>( m_TabWidget->widget( index ) );

        if( editor->Id() == id )
            return true;
    }

    return false;
}

int C_UiTextEditorContainer::Size()
{
    return m_TabWidget->count();
}

void C_UiTextEditorContainer::OnCloseTabRequested( int index )
{
    auto* editor = static_cast<C_UiTextEditor*>( m_TabWidget->widget( index ) );

    if( editor->HasChanged() )
        if( C_Document::AcceptMessage( tr( "Save changes?" ) ) )
            editor->SaveState();

    Close( index );
}
