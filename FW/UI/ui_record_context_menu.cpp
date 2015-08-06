#include "FW/UI/ui_record_context_menu.h"
#include "FW/RC/record.h"
#include "FW/document.h"
#include "FW/SC/scene.h"

#include "FW/UI/ui_add_record.h"

#include <QMenu>

C_UiRecordContextMenu::C_UiRecordContextMenu(C_Document& document, const QPoint& position, C_Record* record, QObject* parent):
    QObject(parent),
    m_Record(record),
    m_Document(&document)
{
    QMenu menu;

    if(m_Record != 0)
    {
        QAction *action_1 = menu.addAction(tr("Edit"));
        connect(action_1, SIGNAL(triggered()), this, SLOT(OnEdit()));

        QAction *action_2 = menu.addAction(tr("Add"));
        connect(action_2, SIGNAL(triggered()), this, SLOT(OnAdd()));

        QAction *action_3 = menu.addAction(tr("Add to scene"));
        connect(action_3, SIGNAL(triggered()), this, SLOT(OnAddSceneItem()));

        menu.addSeparator();

        QAction *action_4 = menu.addAction(tr("Remove"));
        connect(action_4, SIGNAL(triggered()), this, SLOT(OnRemove()));
    }
    else
    {
        QAction *action_5 = menu.addAction(tr("Add"));
        connect(action_5, SIGNAL(triggered()), this, SLOT(OnAdd()));
    }

    menu.exec(position);
}


void C_UiRecordContextMenu::OnEdit()
{
    Record().ShowEditor(Document());
}

void C_UiRecordContextMenu::OnRemove()
{
    if( C_Document::AcceptMessage(tr("Do you want to remove this record?")))
    {
        delete & Record();

        emit Document()
                .Signals()
                .RecordsChanged();
    }
}

void C_UiRecordContextMenu::OnAdd()
{
    QWidget* dialog;

    if( m_Record != 0)
    {
        // Get record from current context's record table
        dialog = new C_UiAddRecord(
                    Document(),
                    Document()
                    .Context()
                    .Records()
                    .GetIndex(&Record()));
    }
    else {
        dialog = new C_UiAddRecord(Document());
    }

    dialog->show();
}

void C_UiRecordContextMenu::OnAddSceneItem()
{
    Document()
            .Context()
            .Scene()
            .CreateItem(Record());

    emit Document()
            .Signals()
            .SceneChanged();
}


