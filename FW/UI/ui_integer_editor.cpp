#include "FW/RC/integer_record.h"
#include "FW/document.h"

#include "FW/UI/ui_integer_editor.h"
#include "ui_integereditor.h"
#include <QRegExp>

C_UiIntegerEditor::C_UiIntegerEditor( C_IntegerRecord& record, C_Document& document, QWidget* parent ) :
    QDialog( parent ),
    m_Record( &record ),
    m_Document( &document ),
    ui( new Ui::C_UiIntegerEditor )
{
    ui->setupUi( this );
    ui->NameLineEdit->setText( Record().Name() );
    ui->ValueLineEdit->setText( Record().Value() );

    connect(
        ui->ButtonBox,
        QDialogButtonBox::accepted,
        this,
        C_UiIntegerEditor::OnButtonBoxAccepted
    );

    connect(
        ui->RemoveButton,
        QPushButton::clicked,
        this,
        C_UiIntegerEditor::OnRemoveButtonClicked
    );
}

C_UiIntegerEditor::~C_UiIntegerEditor()
{
    delete ui;
}

void C_UiIntegerEditor::OnButtonBoxAccepted()
{
    if( !ui->NameLineEdit->text().contains( QRegExp( "^\\S+$" ) ) )
    {
        Document().Message( tr( "Name must not contain white spaces" ) );
        return;
    }

    if( !ui->ValueLineEdit->text().contains( QRegExp( "(^\\s*[-+]?\\d+(E[+]?\\d+)?\\s*$)" ) ) )
    {
        Document().Message( tr( "Bad number string" ) );
        return;
    }

    Record().m_Value = ui->ValueLineEdit->text();
    Record().m_Name = ui->NameLineEdit->text();
    emit Document().Events().RecordsChanged();
}

void C_UiIntegerEditor::OnRemoveButtonClicked()
{
    if( C_Document::AcceptMessage(
                tr( "Do you want to remove this record?" ) ) )
    {
        delete & Record();
        emit Document().Events().RecordsChanged();
        close();
    }
}



