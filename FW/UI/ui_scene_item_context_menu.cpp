#include "FW/UI/ui_scene_item_context_menu.h"
#include "FW/SC/scene.h"
#include "FW/RC/record.h"
#include "FW/document.h"

#include <QAction>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QMessageBox>

C_UiSceneItemContextMenu::C_UiSceneItemContextMenu(C_SceneItem& item,
        QGraphicsSceneContextMenuEvent *event,
        QObject* parent)
    : QObject(parent),
      m_SceneItem(&item)
{
    QMenu menu;

    QAction *action1 = menu.addAction(tr("Edit"));
    connect(action1, SIGNAL(triggered()), this, SLOT(OnEdit()));

    menu.addSeparator();

    QAction *action1_1 = menu.addAction(tr("Remove from scene"));
    connect(action1_1, SIGNAL(triggered()), this, SLOT(OnRemoveFromScene()));

    QAction *action2 = menu.addAction(tr("Remove from document"));
    connect(action2, SIGNAL(triggered()), this, SLOT(OnRemove()));

    menu.exec(event->screenPos());
}

C_UiSceneItemContextMenu::~C_UiSceneItemContextMenu()
{
    //void
}

void C_UiSceneItemContextMenu::OnEdit()
{
    SceneItem().Record().ShowEditor(SceneItem().Scene().Document());
}

void C_UiSceneItemContextMenu::OnRemove()
{

    if( C_Document::AcceptMessage(
            tr("Do you want to remove this record?")))
    {
        delete & SceneItem().Record();

        emit SceneItem()
                .Scene()
                .Document()
                .Signals()
                .RecordsChanged();
    }
}

void C_UiSceneItemContextMenu::OnRemoveFromScene()
{
    if( C_Document::AcceptMessage(
            tr("Do you want to remove this item from scene?")))
    {
        delete & SceneItem();
    }
}

