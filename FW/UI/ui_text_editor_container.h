#ifndef C_UITEXTEDITORCONTAINER_H
#define C_UITEXTEDITORCONTAINER_H

#include <QTabWidget>
#include "FW/macro.h"

class C_UiTextEditor;

class C_UiTextEditorContainer : public QWidget
{
    Q_OBJECT

public:

    explicit C_UiTextEditorContainer( QWidget* parent = 0 );

    void                          Append( C_UiTextEditor* text_editor );

    void                          Close( int index );
    void                          Close( QString id );
    void                          CloseCurrent();
    void                          CloseAll();

    void                          SaveState( int index );
    void                          SaveState( QString id );
    void                          SaveStateCurrent();
    void                          SaveStateAll();


    bool                          HasId( QString id );
    int                           Size();

    void                          SetCurrent( int index );
    void                          SetCurrent( QString id );

    M_CONST_POINTER               ( TabWidget, QTabWidget )

public slots:

    void                          OnCloseTabRequested( int index );
};

#endif // C_UITEXTEDITORCONTAINER_H
