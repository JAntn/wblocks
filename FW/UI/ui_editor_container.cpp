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

    setStyleSheet(
        "QTabBar::tab:selected{border-style: solid; border-width:3px;background:rgb(250, 250, 250);}"
        "QTabBar::tab{ border-style: solid; border-width:3px; background:rgb(220, 220, 220); }"
        "QTabWidget::pane{ border-style:solid; border-width:3px; background:rgb(250, 250, 250); }" );
}

void TypeUiEditorContainer::Append( TypeUiEditor* editor )
{
    m_TabWidget->addTab( editor, editor->TabName() );
    m_TabWidget->setCurrentWidget( editor );
    editor->SetEditorContainer( this );
    editor->OnActionUpdate();
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

void TypeUiEditorContainer::SetTabName( QString id, QString tab_name )
{
    m_TabWidget->setTabText( IndexFromId( id ), tab_name );

}

void TypeUiEditorContainer::SetTabName( int index, QString tab_name )
{
    m_TabWidget->setTabText( index, tab_name );

}

void TypeUiEditorContainer::SetTabToolTip( QString id, QString tab_tooltip )
{
    m_TabWidget->setTabToolTip( IndexFromId( id ), tab_tooltip );
}

void TypeUiEditorContainer::SetTabToolTip( int index, QString tab_tooltip )
{
    m_TabWidget->setTabToolTip( index, tab_tooltip );
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
