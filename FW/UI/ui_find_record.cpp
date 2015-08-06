#include "FW/document.h"
#include "FW/RC/record.h"

#include "FW/UI/ui_find_record.h"
#include "ui_findrecord.h"

#include <QMessageBox>

C_UiFindRecord::C_UiFindRecord(C_Document& document,QWidget *parent) :
    QDialog(parent),
    m_Document(&document),
    m_Record(0),
    ui(new Ui::C_UiFindRecord)
{
    ui->setupUi(this);

    int max = Document()
            .Context()
            .Records()
            .Size();

    ui->SpinBox->setMaximum(max-1);
    ui->SpinBox->setMinimum(0);
    ui->LineEdit->setText("");
    ui->RemoveButton->setEnabled(false);
    ui->EditButton->setEnabled(false);
}

C_UiFindRecord::~C_UiFindRecord()
{
    delete ui;
}

void C_UiFindRecord::on_LineEdit_returnPressed()
{
    QString name = ui->LineEdit->text();

    m_Record = Document()
            .Context()
            .Records()
            .FromName(name);

    if(m_Record != 0) {

        // Find in current context

        int index = Document()
                .Context()
                .Records()
                .GetIndex(&Record());

        ui->PlainTextEdit->clear();
        ui->PlainTextEdit->appendPlainText(tr("Record: %1 \nFound at: %2").arg(name).arg(index));
        ui->PlainTextEdit->appendPlainText(Record().Class());
        ui->PlainTextEdit->appendPlainText(Record().Value());
        ui->SpinBox->setValue(index);
        ui->RemoveButton->setEnabled(true);
        ui->EditButton->setEnabled(true);

    }
    else {
        ui->PlainTextEdit->clear();
        ui->PlainTextEdit->appendPlainText(tr("Record: %1 \nNot Found").arg(name));
        ui->SpinBox->setValue(0);
        ui->RemoveButton->setEnabled(false);
        ui->EditButton->setEnabled(false);
    }
}

void C_UiFindRecord::on_SpinBox_valueChanged(int index)
{
    int index_max = Document()
            .Context()
            .Records()
            .Size();

    if(!((index > index_max) || (index < 0)))
    {

        // Find in current context

        m_Record = Document()
                .Context()
                .Records()
                .FromIndex(index);

        ui->LineEdit->setText(Record().Name());
        ui->PlainTextEdit->clear();
        ui->PlainTextEdit->appendPlainText(
                    QString(tr("Record %1 \nFound at: %2"))
                    .arg(Record().Name())
                    .arg(index));

        ui->PlainTextEdit->appendPlainText(Record().Class());
        ui->PlainTextEdit->appendPlainText(Record().Value());
        ui->RemoveButton->setEnabled(true);
        ui->EditButton->setEnabled(true);
    }
    else {
            m_Record = 0;
            ui->LineEdit->setText("");
            ui->PlainTextEdit->clear();
            ui->PlainTextEdit->appendPlainText(tr("Out of Bounds"));
            ui->EditButton->setEnabled(false);
            ui->RemoveButton->setEnabled(false);
            ui->SpinBox->setValue(0);
    }
}

void C_UiFindRecord::on_CloseButton_clicked()
{
    close();
}

void C_UiFindRecord::on_EditButton_clicked()
{
    if( m_Record != 0 ) {
        Record().ShowEditor(Document());

        int max = Document()
                .Context()
                .Records()
                .Size();

        ui->SpinBox->setMaximum(max-1);
    }
}

void C_UiFindRecord::on_RemoveButton_clicked()
{
    if( C_Document::AcceptMessage(
            tr("Do you want to remove this record?")))
    {
        delete & Record();

        emit Document()
                .Signals()
                .RecordsChanged();

        m_Record = 0;
        ui->LineEdit->setText("");
        ui->PlainTextEdit->clear();
        ui->PlainTextEdit->appendPlainText(tr("Out of Bounds"));
        ui->EditButton->setEnabled(false);
        ui->RemoveButton->setEnabled(false);

        int max = Document()
                .Context()
                .Records()
                .Size();

        ui->SpinBox->setMaximum(max-1);
    }
}


