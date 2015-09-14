#include "FW/UI/ui_file_contextmenu.h"
#include "FW/RC/record.h"
#include "FW/document.h"
#include "FW/context.h"
#include "FW/SC/scene.h"
#include "FW/clipboard.h"
#include "FW/UI/ui_add_record.h"
#include "FW/UI/ui_main_window.h"
#include "FW/UI/ui_record_explorer.h"
#include <QMenu>
#include <QModelIndexList>
#include <QTableView>

TypeUiFileContextMenu::TypeUiFileContextMenu( TypeController& controller, bool has_selection, const QPoint& global_point, QObject* parent ):
    QObject( parent ), TypeVariant( 0 ), m_Controller( &controller )
{
    QMenu menu;

    QAction* action1 = menu.addAction( tr( "New" ) );
    connect( action1, QAction::triggered, &Controller(), TypeController::OnActionFileNew_FileExplorer );

    QAction* action11 = menu.addAction( tr( "New Dir" ) );
    connect( action11, QAction::triggered, &Controller(), TypeController::OnActionFileMkDir_FileExplorer );



    if( has_selection )
    {
        QAction* action2 = menu.addAction( tr( "Open" ) );
        connect( action2, QAction::triggered, &Controller(), TypeController::OnActionFileOpen_FileExplorer );

        menu.addSeparator();

        QAction* action3 = menu.addAction( tr( "Remove" ) );
        connect( action3, QAction::triggered, &Controller(), TypeController::OnActionFileRemove_FileExplorer  );
    }

    menu.exec( global_point );
}

TypeUiFileContextMenu::~TypeUiFileContextMenu()
{
    // void
}

