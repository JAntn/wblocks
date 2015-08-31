#include "FW/document.h"
#include "FW/UI/ui_editor_container.h"
#include "FW/UI/ED/ui_editor.h"
#include <QVBoxLayout>

TypeUiEditorContainer::TypeUiEditorContainer( TypeController& controller, QWidget* parent ):
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
        TypeUiEditorContainer::OnCloseTabRequested
    );
}

void TypeUiEditorContainer::Append( TypeUiEditor* editor )
{
    m_TabWidget->addTab( editor, editor->TabName() );
    emit Controller().TextEditorContainerChanged();
}

void TypeUiEditorContainer::SetCurrent( QString id )
{
    for( int index = 0; index < m_TabWidget->count(); ++index )
    {
        TypeUiEditor* editor = static_cast<TypeUiEditor*>( m_TabWidget->widget( index ) );

        if( editor->Id() == id )
        {
            m_TabWidget->setCurrentIndex( index );
            return;
        }
    }
}

void TypeUiEditorContainer::SetCurrent( int index )
{
    m_TabWidget->setCurrentIndex( index );
}

void TypeUiEditorContainer::Close( QString id )
{
    for( int index = 0; index < m_TabWidget->count(); ++index )
    {
        TypeUiEditor* editor = static_cast<TypeUiEditor*>( m_TabWidget->widget( index ) );

        if( editor->Id() == id )
        {
            m_TabWidget->removeTab( index );
            emit Controller().TextEditorContainerChanged();
            return;
        }
    }
}

void TypeUiEditorContainer::Close( int index )
{
    m_TabWidget->removeTab( index );
    emit Controller().TextEditorContainerChanged();
    return;
}

void TypeUiEditorContainer::CloseCurrent()
{
    int index = m_TabWidget->currentIndex();
    m_TabWidget->removeTab( index );
    emit Controller().TextEditorContainerChanged();
}

void TypeUiEditorContainer::CloseAll()
{
    m_TabWidget->clear();
    emit Controller().TextEditorContainerChanged();
}

void TypeUiEditorContainer::Save( int index )
{
    TypeUiEditor* editor = static_cast<TypeUiEditor*>( m_TabWidget->widget( index ) );
    editor->OnActionSave();
}

void TypeUiEditorContainer::Save( QString id )
{
    for( int index = 0; index < m_TabWidget->count(); ++index )
    {
        TypeUiEditor* editor = static_cast<TypeUiEditor*>( m_TabWidget->widget( index ) );

        if( editor->Id() == id )
        {
            editor->OnActionSave();
            return;
        }
    }
}

void TypeUiEditorContainer::SaveAll()
{
    for( int index = 0; index < m_TabWidget->count(); ++index )
    {
        TypeUiEditor* editor = static_cast<TypeUiEditor*>( m_TabWidget->widget( index ) );
        editor->OnActionSave();
    }
}

void TypeUiEditorContainer::SaveCurrent()
{
    int index = m_TabWidget->currentIndex();
    TypeUiEditor* editor = static_cast<TypeUiEditor*>( m_TabWidget->widget( index ) );
    editor->OnActionSave();
}

bool TypeUiEditorContainer::HasId( QString id )
{
    for( int index = 0; index < m_TabWidget->count(); ++index )
    {
        TypeUiEditor* editor = static_cast<TypeUiEditor*>( m_TabWidget->widget( index ) );

        if( editor->Id() == id )
            return true;
    }

    return false;
}

int TypeUiEditorContainer::Size()
{
    return m_TabWidget->count();
}

void TypeUiEditorContainer::OnCloseTabRequested( int index )
{
    TypeUiEditor* editor = static_cast<TypeUiEditor*>( m_TabWidget->widget( index ) );

    if( editor->HasChanged() )
        if( TypeController::AcceptMessage( tr( "Save changes?" ) ) )
            editor->OnActionSave();

    Close( index );
}
