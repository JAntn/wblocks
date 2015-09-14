#ifndef UIEDITOR_H
#define UIEDITOR_H

#include "FW/tools.h"

class TypeUiEditor : public QWidget, public TypeVariant
{
    Q_OBJECT

public:

    typedef std::function<bool( TypeUiEditor& )> TypeSaveCallback;

    explicit TypeUiEditor( QString id, QString name, QString tab_name,
                           QWidget* parent = 0,
                           TypeSaveCallback save_callback = &TypeUiEditor::empty_save_callback,
                           TypeSaveCallback save_as_callback = &TypeUiEditor::empty_save_callback);
    ~TypeUiEditor();

    M_VALUE                                 ( Id,                QString )
    M_VALUE                                 ( Name,              QString )
    M_VALUE                                 ( TabName,           QString )
    M_VALUE                                 ( HasChanged,        bool )
    M_VALUE                                 ( SaveCallback,      TypeSaveCallback )
    M_VALUE                                 ( SaveAsCallback,      TypeSaveCallback )

    static bool                             empty_save_callback( TypeUiEditor& );

public slots:

    void                                    OnActionSave();
    void                                    OnActionSaveAs();

signals:

    void                                    HasSaved();
};

#endif // UIEDITOR_H
