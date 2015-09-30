#ifndef UIEDITORCONTAINER_H
#define UIEDITORCONTAINER_H

#include <QTabWidget>
#include "FW/tools.h"

class TypeUiEditor;
class TypeController;

class TypeUiEditorContainer : public QWidget, public TypeVariant
{
    Q_OBJECT

public:

    explicit TypeUiEditorContainer( TypeController& controller, QWidget* parent = 0 );

    void                          Append( TypeUiEditor* editor );
    TypeUiEditor*                 EditorFromId( QString id );
    int                           IndexFromId( QString id );

    void                          Close( int index );
    void                          Close( QString id );
    void                          CloseCurrent();
    void                          CloseAll();

    void                          Save( int index );
    void                          Save( QString id );

    void                          SaveCurrent();
    void                          SaveAsCurrent();
    void                          SaveAll();


    bool                          HasId( QString id );
    int                           Size();

    void                          SetCurrent( int index );
    void                          SetCurrent( QString id );

    void                          SetTabName( QString id, QString tab_name );
    void                          SetTabName( int index, QString tab_name );
    void                          SetTabToolTip( QString id, QString tab_tooltip );
    void                          SetTabToolTip( int index, QString tab_tooltip );

    M_REFERENCE_READONLY          ( TabWidget,  QTabWidget )
    M_REFERENCE                   ( Controller, TypeController )


public slots:

    void                          OnCloseTabRequested( int index );
};

#endif // UIEDITORCONTAINER_H
