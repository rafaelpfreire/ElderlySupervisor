#include <syslog.h>
#include <sstream>


#define _MACRO_TO_STR_(macro)  #macro
#define MACRO_TO_STR(macro)    _MACRO_TO_STR_(macro)


#ifndef APP_NAME
    #define SYSLOG_IDENT    nullptr
#else
    #define SYSLOG_IDENT    MACRO_TO_STR(APP_NAME)
#endif



#define _SYSLOG_LOG_(level, msg) \
    openlog(SYSLOG_IDENT, LOG_CONS | LOG_PID, LOG_USER); \
    std::stringstream ss; \
    ss << msg << ": " << __FILE__ << "." << __LINE__; \
    syslog(level, "%s", ss.str().c_str()); \
    closelog();


/* User macros */
#define SYSLOG_INFO(msg)   _SYSLOG_LOG_(LOG_INFO, msg)
#define SYSLOG_WARN(msg)   _SYSLOG_LOG_(LOG_WARNING, msg)
#define SYSLOG_ERR(msg)    _SYSLOG_LOG_(LOG_ERR, msg)
#define SYSLOG_DBG(msg)    _SYSLOG_LOG_(LOG_DEBUG, msg)
