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


#endif // MACRO

