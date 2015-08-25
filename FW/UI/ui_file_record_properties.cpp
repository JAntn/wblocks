#include "FW/document.h"
#include "FW/UI/ui_file_record_properties.h"
#include "ui_filerecordproperties.h"
#include <QFileDialog>
#include "FW/RC/file_record.h"
#include "FW/UI/ui_main_window.h"

C_UiFileRecordProperties::C_UiFileRecordProperties( C_FileRecord& record, C_Document& document, QWidget* parent ):
    QDialog( parent ),
    m_Record( &record ),
    m_Document( &document ),
    ui( new Ui::C_UiFileRecordProperties )
{
    ui->setupUi( this );
    ui->NameLineEdit->setText( Record().Name() );
    ui->ValueLineEdit->setText( Record().Value() );

    connect(
        ui->ButtonBox,
        QDialogButtonBox::accepted,
        this,
        C_UiFileRecordProperties::OnButtonBoxAccepted
    );

    connect(
        ui->RemoveButton,
        QPushButton::clicked,
        this,
        C_UiFileRecordProperties::OnRemoveButtonClicked
    );

    connect(
        ui->SelectButton,
        QPushButton::clicked,
        this,
        C_UiFileRecordProperties::OnSelectButtonClicked
    );
}

C_UiFileRecordProperties::~C_UiFileRecordProperties()
{
    delete ui;
}

void C_UiFileRecordProperties::OnButtonBoxAccepted()
{
    if( !ui->NameLineEdit->text().contains( QRegExp( "^\\S+$" ) ) )
    {
        Document().Message( tr( "Name must not contain white spaces" ) );
        return;
    }

    Record().SetValue( ui->ValueLineEdit->text() );
    Record().SetName( ui->NameLineEdit->text() );
    emit Document().Events().RecordsChanged();
}

void C_UiFileRecordProperties::OnRemoveButtonClicked()
{
    if( Document().AcceptMessage( tr( "Do you want to remove this record?" ) ) )
    {
        delete & Record();
        emit Document().Events().RecordsChanged();
        close();
    }
}

void C_UiFileRecordProperties::OnSelectButtonClicked()
{
    QString file_name =
        QFileDialog::getOpenFileName(
            &Document().MainWindow(),
            QFileDialog::tr( "Select file" ),
            Record().Value()
        );


    if( file_name.isEmpty() )
    {
        qDebug() << "File Selection failed";
        return;
    }

    Record().SetValue( file_name);
    ui->ValueLineEdit->setText( Record().Value() );
}

