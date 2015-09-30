#include "FW/RC/record.h"
#include "FW/UI/ui_main_window.h"
#include "FW/UI/ui_add_record.h"
#include "FW/SC/scene.h"
#include "FW/UI/SH/ui_syntax_highlighter.h"
#include "FW/UI/ui_record_explorer.h"
#include "FW/UI/ui_editor_container.h"
#include "FW/UI/ui_file_explorer.h"
#include "FW/UI/ED/ui_html_text_view.h"
#include "FW/document.h"
#include "FW/context.h"
#include "FW/controller.h"
#include "FW/config.h"
#include "FW/clipboard.h"
#include "FW/BK/html_builder.h"
#include "ui_record_contextmenu.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QtWebKitWidgets>
#include "FW/tools.h"


TypeUiMainWindow::TypeUiMainWindow( TypeController& controller, QWidget* parent ):
    QMainWindow( parent ),
    TypeVariant( 0 ),
    m_Controller( &controller ),
    ui( new Ui::TypeUiMainWindow )
{
    qDebug() << "Creating Main Window..";

    controller.SetMainWindow( *this );

    m_RecordExplorer = 0;
    m_FileExplorer = 0;
    m_PropertiesWidget = 0;
    m_HtmlTextView = 0;

    ui->setupUi( this );

    qDebug() << "Creating Window Contents..";

    m_RecordExplorer = new TypeUiRecordExplorer( controller.Document().Context(), Controller(), this );
    m_FileExplorer = new TypeUiFileExplorer( controller, this );
    m_EditorContainer = new TypeUiEditorContainer( controller, this );

    ui->RecordExplorerLayout->addWidget( m_RecordExplorer );
    ui->EditorLayout->addWidget( m_EditorContainer );
    ui->FileExplorerLayout->addWidget( m_FileExplorer );
    ui->GraphicsView->setScene( &Controller().Document().Scene().Graphics() ); //Scene should be more abstract-----

    qDebug() << "Creating Html Text Viewer..";

    m_HtmlTextView = static_cast<TypeUiHtmlTextView*>( Controller().Document().EditorWidget() );
    ui->HtmlTextLayout->addWidget( m_HtmlTextView );

    qDebug() << "Creating Html Text Viewer..";

    QRect screen_size = QApplication::desktop()->availableGeometry( this );
    resize( QSize( screen_size.width() * 0.8, screen_size.height() * 0.8 ) );
    SetTitle( controller.Config().ProjectFileName() );

    qDebug() << "Beggining Connections..";

    InitConnections();
    emit Controller().RecordsChanged();
    UpdateActions();
    SetCurrentTab( MAINWINDOW_TAB_SCENE );

    qDebug() << "Main Window created";
}

TypeUiMainWindow::~TypeUiMainWindow()
{
    delete ui;
}

void TypeUiMainWindow::InitConnections()
{
    Controller().ConnectSlots();

    connect(
        &Controller(),
        TypeController::SetActiveRecord,
        this,
        TypeUiMainWindow::SetPropertyWidgetRecord );

    connect(
        ui->ActionExit,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionExit );

    connect(
        ui->ActionProjectOpen,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionProjectOpen );

    connect(
        ui->ActionProjectSaveAs,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionProjectSaveAs );

    connect(
        ui->ActionProjectSave,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionProjectSave );

    connect(
        ui->ActionHtmlSaveAs,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionHtmlSaveAs );

    connect(
        ui->ActionHtmlSave,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionHtmlSave );

    connect(
        ui->ActionHtmlUpdate,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionHtmlUpdateText );

    connect(
        ui->ActionHtmlRun,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionHtmlUpdateWeb );

    connect(
        ui->LeftTabWidget,
        QTabWidget::currentChanged,
        &Controller(),
        TypeController::OnLeftTabCurrentChanged );

    connect(
        ui->ActionRecordAdd,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionRecordAdd );

    connect(
        ui->ActionRecordAdd_to_scene,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionRecordAddSceneItem );

    connect(
        ui->ActionRecordProperties,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionChangePropertyWidget );

    connect(
        ui->ActionRecordOpen_In_Editor,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionRecordOpenInEditor );

    connect(
        ui->ActionRecordRemove,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionRecordRemove );

    connect(
        ui->ActionRecordCopy,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionRecordCopy );

    connect(
        ui->ActionRecordCut,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionRecordCut );

    connect(
        ui->ActionRecordPaste,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionRecordPaste );

    connect(
        ui->ActionProjectNew,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionProjectNew );

    connect(
        ui->ActionFileNew,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionFileNew );

    connect(
        ui->ActionFileClose,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionFileClose );

    connect(
        ui->ActionFileCloseAll,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionFileCloseAll );

    connect(
        ui->ActionFileSaveAs,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionFileSaveAs );

    connect(
        ui->ActionFileSave,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionFileSave );

    connect(
        ui->ActionFileSaveAll,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionFileSaveAll );

    connect(
        ui->ActionFileOpen,
        QAction::triggered,
        &Controller(),
        TypeController::OnActionFileOpen );
}

void TypeUiMainWindow::closeEvent( QCloseEvent* )
{
    Controller().OnActionExit();
}

void TypeUiMainWindow::OpenEditorWidget( TypeUiEditor* widget )
{
    EditorContainer().Append( widget );
    SetCurrentTab( MAINWINDOW_TAB_EDITOR );
}

void TypeUiMainWindow::SetTitle( QString title )
{
    if( !title.isEmpty() )
        title.prepend( " - " );

    setWindowTitle( "wblocks" + title );
}

void TypeUiMainWindow::SetCurrentTab( int index )
{
    ui->TabWidget->setCurrentIndex( index );
}

void TypeUiMainWindow::SetPropertyWidgetRecord( TypeRecord* record )
{
    if( record != 0 )
    {
        SetPropertyWidget( record->PropertyWidget( Controller() ) );
        return;
    }

    SetPropertyWidget( 0 );
}

void TypeUiMainWindow::SetPropertyWidget( QWidget* widget )
{
    if( m_PropertiesWidget != 0 )
        delete m_PropertiesWidget;

    m_PropertiesWidget = widget;

    if( m_PropertiesWidget != 0 )
    {
        m_PropertiesWidget->setParent( this );
        ui->PropertiesLayout->addWidget( widget );
    }
}

void TypeUiMainWindow::UpdateHtmlWebView()
{
    Controller().Document().UpdateHtml();

    ui->WebView->setHtml( Controller().Document().HtmlBuilder().Text() );
    ui->WebView->show();
}

void TypeUiMainWindow::UpdateRecordExplorer()
{
    if( m_RecordExplorer != 0 )
        m_RecordExplorer->Update();
}

void TypeUiMainWindow::UpdateFileExplorer()
{
    if( m_FileExplorer != 0 )
        m_FileExplorer->Update();
}

void TypeUiMainWindow::UpdateHtmlTextView()
{
    HtmlTextView().SetFormattedText( Controller().Document().HtmlBuilder().FormattedText() );
    HtmlTextView().OnActionUpdate();
}

void TypeUiMainWindow::UpdateSceneView()
{
    Controller().Document().Scene().UpdateView();
}

void TypeUiMainWindow::UpdateActions()
{

    QList<QAction*> record_action_list =
    {
        ui->ActionRecordCut,
        ui->ActionRecordCopy,
        ui->ActionRecordPaste,
        ui->ActionRecordAdd,
        ui->ActionRecordAdd_to_scene,
        ui->ActionRecordProperties,
        ui->ActionRecordRemove,
        ui->ActionRecordOpen_In_Editor
    };

    QList<long> record_action_flags =
    {
        FLAG_ACTION_CUT,
        FLAG_ACTION_COPY,
        FLAG_ACTION_PASTE,
        FLAG_ACTION_ADD,
        FLAG_ACTION_ADD_SCENE,
        FLAG_ACTION_ACTIVATE,
        FLAG_ACTION_REMOVE,
        FLAG_ACTION_OPEN
    };

    QList<QPushButton*> record_button_list =
    {
        ui->ButtonRecordCut,
        ui->ButtonRecordCopy,
        ui->ButtonRecordPaste,
        ui->ButtonRecordAdd,
        ui->ButtonRecordAddScene,
        ui->ButtonRecordRemove,
    };

    QList<long> record_button_action_flags =
    {
        FLAG_ACTION_CUT,
        FLAG_ACTION_COPY,
        FLAG_ACTION_PASTE,
        FLAG_ACTION_ADD,
        FLAG_ACTION_ADD_SCENE,
        FLAG_ACTION_REMOVE,
    };

    //
    // Disable record actions if explorer or html text is not visible

    if( !ui->RecordExplorerTab->isVisible() && !ui->HtmlTextTab->isVisible() )
    {
        for( QAction* action : record_action_list )
            action->setEnabled( false );
    }
    else
    {
        //
        // Enable record actions conditionated to record flags:

        {
            auto iter = record_action_flags.begin();

            for( QAction* action : record_action_list )
            {
                if( Controller().Document().Context().Struct().Flags() & ( *iter ) )
                    action->setEnabled( true );
                else
                    action->setEnabled( false );

                ++iter;
            }
        }

        //
        // Enable record button conditionated to record flags:

        {
            auto iter = record_button_action_flags.begin();

            for( auto button : record_button_list )
            {
                if( Controller().Document().Context().Struct().Flags() & ( *iter ) )
                    button->setEnabled( true );
                else
                    button->setEnabled( false );

                ++iter;
            }
        }
    }

    //
    // Disable records actions conditionated to record explorer selection:

    {
        QList<QPushButton*> record_button_list =
        {
            ui->ButtonRecordCut,
            ui->ButtonRecordCopy,
            ui->ButtonRecordAddScene,
            ui->ButtonRecordRemove,
        };

        QList<QAction*> record_action_list =
        {
            ui->ActionRecordCut,
            ui->ActionRecordCopy,
            ui->ActionRecordAdd_to_scene,
            ui->ActionRecordProperties,
            ui->ActionRecordRemove,
            ui->ActionRecordOpen_In_Editor
        };

        if( !RecordExplorer().HasSelection() )
        {
            for( QAction* action : record_action_list )
                action->setEnabled( false );

            for( QPushButton* button : record_button_list )
                button->setEnabled( false );
        }
    }

    if( Controller().Clipboard().Empty() )
    {
        ui->ActionRecordPaste->setEnabled( false );
        ui->ButtonRecordPaste->setEnabled( false );
    }

    //
    // Enable file actions conditionated to container is not empty:

    {
        QList<QAction*> file_action_list =
        {
            ui->ActionFileSaveAll,
            ui->ActionFileSave,
            ui->ActionFileSaveAs,
            ui->ActionFileCloseAll,
            ui->ActionFileClose
        };

        if( EditorContainer().Size() == 0 )
        {
            for( QAction* action : file_action_list )
                action->setEnabled( false );

            ui->ButtonFileSave->setEnabled( false );

        }
        else
        {
            for( QAction* action : file_action_list )
                action->setEnabled( true );

            ui->ButtonFileSave->setEnabled( true );
        }
    }

}



