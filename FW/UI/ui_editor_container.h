#ifndef TypeUITEXTEDITORCONTAINER_H
#define TypeUITEXTEDITORCONTAINER_H

#include <QTabWidget>
#include "FW/macro.h"

class TypeUiEditor;
class TypeController;

class TypeUiEditorContainer : public QWidget
{
    Q_OBJECT

public:

    explicit TypeUiEditorContainer( TypeController& controller, QWidget* parent = 0 );

    void                          Append( TypeUiEditor* editor );

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
    M_POINTER                     ( Controller, TypeController )

public slots:

    void                          OnCloseTabRequested( int index );
};

#endif // TypeUITEXTEDITORCONTAINER_H
