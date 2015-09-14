#include "FW/tools.h"
#include "FW/document.h"
#include "FW/controller.h"
#include "FW/UI/ui_editor_container.h"
#include "FW/UI/ED/ui_editor.h"
#include <QVBoxLayout>

TypeUiEditorContainer::TypeUiEditorContainer( TypeController& controller, QWidget* parent ):
    QWidget( parent ),
    TypeVariant( 0 ),
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
    m_TabWidget->setCurrentWidget( editor );

    emit Controller().EditorContainerChanged();
}

TypeUiEditor* TypeUiEditorContainer::EditorFromId( QString id )
{
    for( int index = 0; index < m_TabWidget->count(); ++index )
    {
        TypeUiEditor* editor = ( TypeUiEditor* )m_TabWidget->widget( index );

        if( editor->Id() == id )
            return editor;
    }

    return 0;
}

int TypeUiEditorContainer::IndexFromId( QString id )
{
    for( int index = 0; index < m_TabWidget->count(); ++index )
    {
        TypeUiEditor* editor = ( TypeUiEditor* )m_TabWidget->widget( index );

        if( editor->Id() == id )
            return index;
    }

    return -1;
}

void TypeUiEditorContainer::SetCurrent( QString id )
{
    m_TabWidget->setCurrentIndex( IndexFromId( id ) );
}

void TypeUiEditorContainer::SetCurrent( int index )
{
    m_TabWidget->setCurrentIndex( index );
}

void TypeUiEditorContainer::Close( QString id )
{
    m_TabWidget->removeTab( IndexFromId( id ) );
    emit Controller().EditorContainerChanged();
    return;
}

void TypeUiEditorContainer::Close( int index )
{
    m_TabWidget->removeTab( index );
    emit Controller().EditorContainerChanged();
    return;
}

void TypeUiEditorContainer::CloseCurrent()
{
    int index = m_TabWidget->currentIndex();
    m_TabWidget->removeTab( index );
    emit Controller().EditorContainerChanged();
}

void TypeUiEditorContainer::CloseAll()
{
    m_TabWidget->clear();
    emit Controller().EditorContainerChanged();
}

void TypeUiEditorContainer::Save( int index )
{
    TypeUiEditor* editor = ( TypeUiEditor* )m_TabWidget->widget( index );
    editor->OnActionSave();
}

void TypeUiEditorContainer::Save( QString id )
{
    TypeUiEditor* editor = EditorFromId( id );

    if( editor != 0 )
        editor->OnActionSave();
}

void TypeUiEditorContainer::SaveAll()
{
    for( int index = 0; index < m_TabWidget->count(); ++index )
    {
        TypeUiEditor* editor = ( TypeUiEditor* )m_TabWidget->widget( index );
        editor->OnActionSave();
    }
}

void TypeUiEditorContainer::SaveCurrent()
{
    int index = m_TabWidget->currentIndex();
    TypeUiEditor* editor = ( TypeUiEditor* )m_TabWidget->widget( index );
    editor->OnActionSave();
}

void TypeUiEditorContainer::SaveAsCurrent()
{
    int index = m_TabWidget->currentIndex();
    TypeUiEditor* editor = ( TypeUiEditor* )m_TabWidget->widget( index );
    editor->OnActionSaveAs();
}

bool TypeUiEditorContainer::HasId( QString id )
{
    if( EditorFromId( id ) != 0 )
        return true;

    return false;
}

int TypeUiEditorContainer::Size()
{
    return m_TabWidget->count();
}

void TypeUiEditorContainer::OnCloseTabRequested( int index )
{
    TypeUiEditor* editor = ( TypeUiEditor* )m_TabWidget->widget( index );

    if( editor->HasChanged() )
        if( TypeController::AcceptMessage( tr( "Save changes?" ) ) )
            editor->OnActionSave();

    Close( index );
}
