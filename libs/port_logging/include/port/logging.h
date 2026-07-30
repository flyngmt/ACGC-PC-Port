#ifndef PORT_LOGGING_H
#define PORT_LOGGING_H

#include <aurora/aurora.h>

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct PortLogConfig {
    /* UTF-8 directory for timestamped log files. NULL or empty disables files. */
    const char* log_directory;
    /* File prefix, for example "animal-crossing". Unsafe characters become '-'. */
    const char* filename_prefix;
    AuroraLogLevel minimum_level;
    uint32_t max_retained_files;
    uint64_t max_retained_bytes;
    bool write_console;
} PortLogConfig;

/* Initializes or reinitializes the process logger. Console logging remains
 * available if the file directory cannot be created. */
bool port_log_initialize(const PortLogConfig* config);
void port_log_shutdown(void);

/* Returned pointers remain valid until reinitialization or shutdown. */
const char* port_log_file_path(void);
int port_log_file_descriptor(void);

/* Direct AuroraConfig::logCallback implementation. */
void port_log_callback(AuroraLogLevel level, const char* module,
                       const char* message, unsigned int length);

void port_log_message(AuroraLogLevel level, const char* module,
                      const char* message, unsigned int length);
void port_log_vprintf(AuroraLogLevel level, const char* module,
                      const char* format, va_list arguments);
void port_log_printf(AuroraLogLevel level, const char* module,
                     const char* format, ...);

#ifdef __cplusplus
}
#endif

#endif
