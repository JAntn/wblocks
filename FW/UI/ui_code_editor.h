#ifndef UI_FILE_EDITOR_H
#define UI_FILE_EDITOR_H

#include <QWidget>
#include "FW/macro.h"

namespace Ui
{
class C_UiCodeEditor;
}

class C_UiCodeEditor : public QWidget
{
    Q_OBJECT

public:

    explicit C_UiCodeEditor( QString file_name, QWidget* parent = 0 );
    ~C_UiCodeEditor();

    void                         Save();

    ATR_VALUE                    ( FileName,    QString )
    ATR_VALUE                    ( HasChanged,  bool )

public slots:

    void                         OnTextChanged();

signals:

    void                         TextChangedEvent();
    void                         SavedEvent();

private:

    Ui::C_UiCodeEditor* ui;
};

#endif // UI_FILE_EDITOR_H
