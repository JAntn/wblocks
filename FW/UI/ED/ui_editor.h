#ifndef UIEDITOR_H
#define UIEDITOR_H

#include "FW/tools.h"

class TypeUiEditorContainer;

class TypeUiEditor : public QWidget, public TypeVariant
{
    Q_OBJECT

public:

    typedef std::function<bool( TypeUiEditor& )> TypeSaveCallback;
    typedef std::function<bool( TypeUiEditor& )> TypeUpdateCallback;

    explicit TypeUiEditor(
        QString id,
        QString name,
        QString tab_name,
        QWidget* parent = 0,
        TypeSaveCallback save_callback = &TypeUiEditor::empty_save_callback,
        TypeSaveCallback save_as_callback = &TypeUiEditor::empty_save_callback,
        TypeUpdateCallback update_callback = &TypeUiEditor::empty_update_callback );

    ~TypeUiEditor();

    M_VALUE                                 ( Id,                QString )
    M_VALUE                                 ( Name,              QString )
    M_VALUE                                 ( TabName,           QString )
    M_VALUE                                 ( HasChanged,        bool )
    M_VALUE                                 ( SaveCallback,      TypeSaveCallback )
    M_VALUE                                 ( SaveAsCallback,    TypeSaveCallback )
    M_VALUE                                 ( UpdateCallback,    TypeUpdateCallback )
    M_POINTER                               ( EditorContainer,   TypeUiEditorContainer )

    static bool                             empty_save_callback( TypeUiEditor& );
    static bool                             empty_update_callback( TypeUiEditor& );

public slots:

    void                                    OnActionUpdate();
    void                                    OnActionSave();
    void                                    OnActionSaveAs();

signals:

    void                                    HasSaved();
    void                                    HasUpdated();
};

#endif // UIEDITOR_H
