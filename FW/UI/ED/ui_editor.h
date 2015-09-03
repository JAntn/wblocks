#ifndef UIEDITOR_H
#define UIEDITOR_H

#include "FW/tools.h"

class TypeUiEditor : public QWidget, public TypeVariant
{
    Q_OBJECT

public:

    typedef std::function<void( TypeUiEditor& )> TypeSaveCallback;

    explicit TypeUiEditor( QString id, QString name, QString tab_name,
                           QWidget* parent = 0,
                           TypeSaveCallback save_callback = &TypeUiEditor::empty_save_callback );
    ~TypeUiEditor();

    M_CONST_VALUE                ( Id,                QString )
    M_VALUE                      ( Name,              QString )
    M_VALUE                      ( TabName,           QString )
    M_VALUE                      ( HasChanged,        bool )
    M_VALUE                      ( SaveCallback,      TypeSaveCallback )

    static void empty_save_callback( TypeUiEditor&){}

public slots:

    void                         OnActionSave();

};

#endif // UIEDITOR_H
