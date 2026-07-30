# Port logging

`port_logging` is a small host logging layer shared at the application boundary.
It accepts Aurora log callbacks and C/C++ formatted messages, then serializes
them to the console, a rotating timestamped file, and Android logcat when built
for Android. It contains no Animal Crossing-specific policy and is intended to
be reusable by other Aurora ports.

## Integration

Add the library after Aurora and link its alias:

```cmake
add_subdirectory(extern/aurora EXCLUDE_FROM_ALL)
add_subdirectory(libs/port_logging)

target_link_libraries(game PRIVATE port::logging aurora::core)
```

Initialize logging before Aurora so startup diagnostics use the same sinks,
then install `port_log_callback` in `AuroraConfig`. Shut the logger down after
Aurora has finished so teardown messages reach the file.

```cpp
PortLogConfig log_config{
    .log_directory = "logs",
    .filename_prefix = "game",
    .minimum_level = LOG_INFO,
    .max_retained_files = 10,
    .max_retained_bytes = 100 * 1024 * 1024,
    .write_console = true,
};
port_log_initialize(&log_config);

AuroraConfig config{};
config.logCallback = port_log_callback;
config.logLevel = log_config.minimum_level;

// aurora_initialize(...), application loop, aurora_shutdown()
port_log_shutdown();
```

An empty `log_directory` disables file output. Failure to create or open the
directory leaves console logging active and emits a warning. Retention is
bounded by both file count and total bytes. A zero value selects the library
default of ten files or 100 MiB, respectively.

Use `port_log_printf` from ordinary code and `port_log_vprintf` when adapting a
C `va_list` reporter such as `OSVReport`. Messages are filtered before sink
writes, and each line of a multiline message receives its own level/module
prefix. `LOG_FATAL` is written before the process aborts.

On Android, the target links the platform `log` library automatically and
mirrors accepted messages to logcat.
