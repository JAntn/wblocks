#ifndef MACRO_H
#define MACRO_H


#define SINGLETON_CLASS(__CLASS_NAME)     __CLASS_NAME(__CLASS_NAME const&) = delete;\
                                            void operator=(__CLASS_NAME const&)  = delete;\
                                            static __CLASS_NAME& Instance() { static __CLASS_NAME singleton; return singleton; }

#define M_REFERENCE(__VAR_NAME,__VAR_TYPE)\
                                           protected:\
                                           __VAR_TYPE* m_##__VAR_NAME;\
                                           public:\
                                           __VAR_TYPE& __VAR_NAME() const {return *m_##__VAR_NAME;}\
                                           void Set##__VAR_NAME(__VAR_TYPE& __ARG) { m_##__VAR_NAME = &__ARG;}

#define M_REFERENCE_READONLY(__VAR_NAME,__VAR_TYPE)\
                                           protected:\
                                           __VAR_TYPE* m_##__VAR_NAME;\
                                           public:\
                                           const __VAR_TYPE& __VAR_NAME() const {return *m_##__VAR_NAME;}

#define M_VALUE(__VAR_NAME,__VAR_TYPE)\
                                           protected:\
                                           __VAR_TYPE m_##__VAR_NAME;\
                                           public:\
                                           const __VAR_TYPE& __VAR_NAME() const {return m_##__VAR_NAME;}\
                                           __VAR_TYPE& __VAR_NAME() {return m_##__VAR_NAME;}\
                                           void Set##__VAR_NAME(const __VAR_TYPE& __ARG) { m_##__VAR_NAME = __ARG;}

#define M_VALUE_READONLY(__VAR_NAME,__VAR_TYPE)\
                                           protected:\
                                           __VAR_TYPE m_##__VAR_NAME;\
                                           public:\
                                           const __VAR_TYPE& __VAR_NAME() const {return m_##__VAR_NAME;}\

#define M_POINTER(__VAR_NAME,__VAR_TYPE)\
                                           protected:\
                                           __VAR_TYPE* m_##__VAR_NAME;\
                                           public:\
                                           __VAR_TYPE* __VAR_NAME() const {return m_##__VAR_NAME;}\
                                           void Set##__VAR_NAME(__VAR_TYPE* __ARG) { m_##__VAR_NAME = __ARG;}

#define M_POINTER_READONLY(__VAR_NAME,__VAR_TYPE)\
                                           protected:\
                                           __VAR_TYPE* m_##__VAR_NAME;\
                                           public:\
                                           __VAR_TYPE* __VAR_NAME() const {return m_##__VAR_NAME;}\

#define FLAG_ACTION_ALL          0xFFFF
#define FLAG_ACTION_ADD          0x0001
#define FLAG_ACTION_REMOVE       0x0002
#define FLAG_ACTION_ACTIVATE     0x0004
#define FLAG_ACTION_ADD_SCENE    0x0008
#define FLAG_ACTION_REMOVE_SCENE 0x0010
#define FLAG_ACTION_COPY         0x0020
#define FLAG_ACTION_PASTE        0x0040
#define FLAG_ACTION_CUT          0x0080
#define FLAG_ACTION_OPEN         0x0100




#endif // MACRO

