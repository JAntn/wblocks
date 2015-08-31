#ifndef C_UITEXTEDITORCONTAINER_H
#define C_UITEXTEDITORCONTAINER_H

#include <QTabWidget>
#include "FW/macro.h"

class C_UiEditor;
class C_Controller;

class C_UiEditorContainer : public QWidget
{
    Q_OBJECT

public:

    explicit C_UiEditorContainer( C_Controller& controller, QWidget* parent = 0 );

    void                          Append( C_UiEditor* editor );

    void                          Close( int index );
    void                          Close( QString id );
    void                          CloseCurrent();
    void                          CloseAll();

    void                          Save( int index );
    void                          Save( QString id );
    void                          SaveCurrent();
    void                          SaveAll();


    bool                          HasId( QString id );
    int                           Size();

    void                          SetCurrent( int index );
    void                          SetCurrent( QString id );

    M_CONST_POINTER               ( TabWidget,  QTabWidget )
    M_POINTER                     ( Controller, C_Controller )

public slots:

    void                          OnCloseTabRequested( int index );
};

#endif // C_UITEXTEDITORCONTAINER_H
