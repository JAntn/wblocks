#ifndef RECORDFLAGS_H
#define RECORDFLAGS_H

#define FLAG_ROLE_BODY           1
#define FLAG_ROLE_HEAD           (1<<1)
#define FLAG_ROLE_JAVASCRIPT     (1<<2)
#define FLAG_ROLE_CSS            (1<<3)
#define FLAG_ROLE_PHP            (1<<4)
#define FLAG_ROLE_ALL            (FLAG_ROLE_BODY|FLAG_ROLE_HEAD|FLAG_ROLE_JAVASCRIPT|FLAG_ROLE_CSS|FLAG_ROLE_PHP)

#define FLAG_ACTION_ADD          (1<<5)
#define FLAG_ACTION_REMOVE       (1<<6)
#define FLAG_ACTION_ACTIVATE     (1<<7)
#define FLAG_ACTION_ADD_SCENE    (1<<8)
#define FLAG_ACTION_REMOVE_SCENE (1<<9)
#define FLAG_ACTION_COPY         (1<<10)
#define FLAG_ACTION_PASTE        (1<<11)
#define FLAG_ACTION_CUT          (1<<12)
#define FLAG_ACTION_OPEN         (1<<13)
#define FLAG_ACTION_ALL          (FLAG_ACTION_ADD|FLAG_ACTION_REMOVE|FLAG_ACTION_ACTIVATE|FLAG_ACTION_ADD_SCENE|FLAG_ACTION_REMOVE_SCENE|FLAG_ACTION_COPY|FLAG_ACTION_PASTE|FLAG_ACTION_CUT|FLAG_ACTION_OPEN)

#endif // RECORDFLAGS_H

