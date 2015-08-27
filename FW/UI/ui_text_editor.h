#ifndef C_UITEXTEDITOR_H
#define C_UITEXTEDITOR_H

#include <QWidget>
#include "FW/macro.h"

namespace Ui
{
class C_UiTextEditor;
}

// THIS EDITOR CHANGES ARE STORED IN A RECORD

class C_UiTextEditor : public QWidget
{
    Q_OBJECT

public:

    explicit C_UiTextEditor( QString id, QString name, QString tab_name = "", QWidget* parent = 0 );
    ~C_UiTextEditor();

    virtual QString              Text();
    virtual void                 SetText( QString text, bool signal_block = false );
    virtual void                 SaveState() = 0;

    M_CONST_VALUE                ( Id,          QString )
    M_VALUE                      ( Name,        QString )
    M_VALUE                      ( TabName,     QString )
    M_VALUE                      ( HasChanged,  bool )

public slots:

    void                         OnTextChanged();

private:

    Ui::C_UiTextEditor* ui;
};

#endif // C_UITEXTEDITOR_H
