#include "FW/RC/record.h"
#include "FW/document.h"
#include "FW/SC/scene.h"

#include "FW/UI/ui_add_record.h"
#include "ui_addrecord.h"

#include <QMessageBox>

C_UiAddRecord::C_UiAddRecord( C_Document& document, int index, QWidget* parent ) :
    QDialog( parent ),
    m_Document( &document ),
    ui( new Ui::C_UiAddRecord )
{
    ui->setupUi( this );

    for( C_RecordFactory* record_factory : C_RecordStruct::FactoryList() )
        ui->ComboBox->addItem( record_factory->RecordClass() );

    int index_max = Document()
                    .Context()
                    .Records()
                    .Size();

    if( index < 0 )
        index = index_max;

    ui->ComboBox->setCurrentIndex( 0 );
    ui->SpinBox->setMaximum( index_max );
    ui->SpinBox->setMinimum( 0 );
    ui->SpinBox->setValue( index  );
    ui->LineEdit->setText( "" );
}

C_UiAddRecord::~C_UiAddRecord()
{
    delete ui;
}

bool C_UiAddRecord::CheckFormData() const
{
    int index = ui->SpinBox->value();
    int index_max = Document()
                    .Context()
                    .Records()
                    .Size();

    if ( ( index > index_max ) || ( index < 0 ) )
    {
        Document().Message( tr( "Position out of bounds" ) );
        return false;
    }

    QString class_name = ui->ComboBox->currentText();

    if( class_name.isEmpty() )
    {
        Document().Message( tr( "Class name is empty" ) );
        return false;
    }

    bool bad_class_name = true;

    for( C_RecordFactory* factory : C_RecordStruct::FactoryList() )
    {
        if( factory->RecordClass() == class_name )
        {
            bad_class_name = false;
            break;
        }
    }

    if( bad_class_name )
    {
        Document().Message( tr( "Bad class name" ) );
        return false;
    }

    QString name = ui->LineEdit->text();

    if( name.isEmpty() )
    {
        Document().Message( tr( "Name is empty" ) );
        return false;
    }

    if( !name.contains( QRegExp( "^\\S+$" ) ) )
    {
        Document().Message( tr( "Name must not contain white spaces" ) );
        return false;
    }

    return true;
}

void C_UiAddRecord::on_ButtonBox_accepted()
{
    if( CheckFormData() )
    {
        QString class_name = ui->ComboBox->currentText();
        QString name = ui->LineEdit->text();
        int index = ui->SpinBox->value();

        C_Record* record = Document()
                           .Context()
                           .Records()
                           .CreateRecord( name, "", class_name, index );

        emit Document()
        .Signals()
        .RecordsChanged();

        if( ui->CheckBox->isChecked() )
        {
            Document()
            .Context()
            .Scene()
            .CreateItem( *record );

            emit Document()
            .Signals()
            .SceneChanged();
        }

        close();
    }
}

void C_UiAddRecord::on_EditButton_clicked()
{

    // Create again but then go to editor dialog

    if( CheckFormData() )
    {
        QString class_name = ui->ComboBox->currentText();
        QString name = ui->LineEdit->text();
        int index = ui->SpinBox->value();

        C_Record* record = Document()
                           .Context()
                           .Records()
                           .CreateRecord( name, "", class_name, index );

        emit Document()
        .Signals()
        .RecordsChanged();

        if( ui->CheckBox->isChecked() )
        {

            Document()
            .Context()
            .Scene()
            .CreateItem( *record );

            emit Document()
            .Signals()
            .SceneChanged();
        }

        record->ShowEditor( Document() );
        close();
    }
}

void C_UiAddRecord::on_ButtonBox_rejected()
{
    close();
}
