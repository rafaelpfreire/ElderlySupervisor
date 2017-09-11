#include <syslog.h>
#include <sstream>


#ifndef APP_NAME
    #define SYSLOG_IDENT nullptr
#else
    #define SYSLOG_IDENT "#APP_NAME"
#endif



#define _SYSLOG_LOG_(level, msg) \
    openlog(SYSLOG_IDENT, LOG_CONS | LOG_PID, LOG_USER); \
    std::stringstream ss; \
    ss << msg; \
    syslog(level, ss.str().c_str()); \
    closelog();


/* User macros */
#define SYSLOG_INFO(msg)   _SYSLOG_LOG_(LOG_INFO, msg)
#define SYSLOG_WARN(msg)   _SYSLOG_LOG_(LOG_WARNING, msg)
#define SYSLOG_ERR(msg)    _SYSLOG_LOG_(LOG_ERR, msg)
#define SYSLOG_DBG(msg)    _SYSLOG_LOG_(LOG_DEBUG, msg)


//<< __FILE__ << __FUNCTION__ << __LINE__; 
