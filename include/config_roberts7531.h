#ifdef MACHINE_ROBERTS7531
# ifndef CONF_ATARI_HARDWARE
#  define CONF_ATARI_HARDWARE 0
# endif
# ifndef CONF_WITH_ADVANCED_CPU
#  define CONF_WITH_ADVANCED_CPU 0
# endif
# ifndef CONF_WITH_APOLLO_68080
#  define CONF_WITH_APOLLO_68080 0
# endif
# ifndef CONF_WITH_BUS_ERROR
#  define CONF_WITH_BUS_ERROR 1
# endif
# ifndef CONF_WITH_CACHE_CONTROL
#  define CONF_WITH_CACHE_CONTROL 0
# endif
# ifndef ALWAYS_SHOW_INITINFO
#  define ALWAYS_SHOW_INITINFO 1
# endif

# ifndef CONF_STRAM_SIZE
#  define CONF_STRAM_SIZE 1*1024*1024
# endif
# ifndef CONF_WITH_ALT_RAM
#  define CONF_WITH_ALT_RAM 0
# endif
# ifndef CONF_WITH_DUART
#  define CONF_WITH_DUART 1
# endif
# ifndef DUART_BASE
#  define DUART_BASE 0x00800000UL
# endif
# ifndef CONF_WITH_DUART_CHANNEL_B
#  define CONF_WITH_DUART_CHANNEL_B 1
# endif
# ifndef CONF_DUART_TIMER_C
#  define CONF_DUART_TIMER_C 1
# endif
# ifndef CONF_DUART_AUTOVECTOR
#  define CONF_DUART_AUTOVECTOR 7
# endif
# ifndef DUART_DEBUG_PRINT
#  define DUART_DEBUG_PRINT 1
# endif
# ifndef RS232_DEBUG_PRINT
#  define RS232_DEBUG_PRINT 0
# endif

# ifndef CONF_WITH_IDE
#  define CONF_WITH_IDE 1
# endif
# ifndef CONF_ATARI_IDE
#  define CONF_ATARI_IDE 1
# endif
# ifndef CONF_IDE_NO_RESET
#  define CONF_IDE_NO_RESET 1
# endif

# ifndef CONF_WITH_RESET
#  define CONF_WITH_RESET 0
# endif

# ifndef CONF_SERIAL_CONSOLE
#  define CONF_SERIAL_CONSOLE 1
# endif
# ifndef CONF_SERIAL_CONSOLE_ANSI
#  if CONF_SERIAL_CONSOLE
#   define CONF_SERIAL_CONSOLE_ANSI 1
#  else
#   define CONF_SERIAL_CONSOLE_ANSI 0
#  endif
# endif
# ifndef CONF_SERIAL_CONSOLE_POLLING_MODE
#  define CONF_SERIAL_CONSOLE_POLLING_MODE 1
# endif

# ifndef USE_STOP_INSN_TO_FREE_HOST_CPU
#  define USE_STOP_INSN_TO_FREE_HOST_CPU 0
# endif
# ifndef DETECT_NATIVE_FEATURES
#  define DETECT_NATIVE_FEATURES 0
# endif

# ifndef DEFAULT_BAUDRATE
#  define DEFAULT_BAUDRATE B19200
# endif

#endif
