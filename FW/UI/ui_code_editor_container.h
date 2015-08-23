#ifndef C_UIFILEEDITORCONTAINER_H
#define C_UIFILEEDITORCONTAINER_H

#include <QTabWidget>
#include "FW/macro.h"

class C_UiCodeEditorContainer : public QWidget
{

    Q_OBJECT

public:

    explicit C_UiCodeEditorContainer( QWidget* parent = 0 );

    void                          Append( QString file_name );
    void                          Clear( QString file_name );
    void                          Close( int index );
    void                          Close( QString file_name );
    void                          CloseCurrent();
    void                          CloseAll();
    void                          SaveCurrent();
    void                          SaveAll();
    void                          Save( int index );
    bool                          HasFile( QString file_name );
    int                           Size();
    void                          Select( QString file_name );

    M_CONST_POINTER               ( TabWidget, QTabWidget )

public slots:

    void                          OnCloseTabRequested( int index );
};

#endif // C_UIFILEEDITORCONTAINER_H
