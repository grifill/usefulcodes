//------------------------------------------------------------------------------
#ifndef DEBUG_TRACE_H
#define DEBUG_TRACE_H
//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------
#include <stdio.h>
#include <uartstdio.h>

extern void UARTprintf(const char *pcString, ...);
//------------------------------------------------------------------------------
//         Global Definitions
//------------------------------------------------------------------------------

#define TRACE_LEVEL_DEBUG      5
#define TRACE_LEVEL_INFO       4
#define TRACE_LEVEL_WARNING    3
#define TRACE_LEVEL_ERROR      2
#define TRACE_LEVEL_FATAL      1
#define TRACE_LEVEL_NO_TRACE   0

#define TRACE_LEVEL TRACE_LEVEL_DEBUG

//#define PRINT_ESCAPE "\n"
////	Default printf
#define printf(...) 	UARTprintf(__VA_ARGS__)
#define fprintf(...) 	UARTprintf(__VA_ARGS__)
// By default, all traces are output except the debug one.
#if !defined(TRACE_LEVEL)
#define TRACE_LEVEL TRACE_LEVEL_INFO
#endif

// By default, trace level is static (not dynamic)
#if !defined(DYN_TRACES)
#define DYN_TRACES 0
#endif

#if defined(NOTRACE)
#error "Error: NOTRACE has to be not defined !"
#endif

#undef NOTRACE
#if (TRACE_LEVEL == TRACE_LEVEL_NO_TRACE)
#define NOTRACE
#endif

//------------------------------------------------------------------------------
/// Outputs a formatted string using <printf> if the log level is high
/// enough. Can be disabled by defining TRACE_LEVEL=0 during compilation.
/// \param format  Formatted string to output.
/// \param ...  Additional parameters depending on formatted string.
//------------------------------------------------------------------------------
#if defined(NOTRACE)

// Empty macro
#define TRACE_DEBUG(...)      {for(int i = 0; i < 10000;i++); }
#define TRACE_INFO(...)       {for(int i = 0; i < 10000;i++); }
#define TRACE_WARNING(...)    {for(int i = 0; i < 10000;i++); }
#define TRACE_ERROR(...)      {for(int i = 0; i < 10000;i++); }
#define TRACE_FATAL(...)      { while(1); }

#define TRACE_HEXDUMP(...)		{for(int i = 0; i < 10000;i++); }

#define TRACE_DEBUG_WP(...)   {for(int i = 0; i < 10000;i++); }
#define TRACE_INFO_WP(...)    {for(int i = 0; i < 10000;i++); }
#define TRACE_WARNING_WP(...) {for(int i = 0; i < 10000;i++); }
#define TRACE_ERROR_WP(...)   {for(int i = 0; i < 10000;i++); }
#define TRACE_FATAL_WP(...)   { while(1); }

#elif (DYN_TRACES == 1)

// Trace output depends on traceLevel value
#define TRACE_DEBUG(...)      { if (traceLevel >= TRACE_LEVEL_DEBUG)   { dprintf("-D- " __VA_ARGS__); } }
#define TRACE_INFO(...)       { if (traceLevel >= TRACE_LEVEL_INFO)    { dprintf("-I- " __VA_ARGS__); } }
#define TRACE_WARNING(...)    { if (traceLevel >= TRACE_LEVEL_WARNING) { dprintf("-W- " __VA_ARGS__); } }
#define TRACE_ERROR(...)      { if (traceLevel >= TRACE_LEVEL_ERROR)   { dprintf("-E- " __VA_ARGS__); } }
#define TRACE_FATAL(...)      { if (traceLevel >= TRACE_LEVEL_FATAL)   { dprintf("-F- " __VA_ARGS__); while(1); } }

#define TRACE_DEBUG_WP(...)   { if (traceLevel >= TRACE_LEVEL_DEBUG)   { dprintf(__VA_ARGS__); } }
#define TRACE_INFO_WP(...)    { if (traceLevel >= TRACE_LEVEL_INFO)    { dprintf(__VA_ARGS__); } }
#define TRACE_WARNING_WP(...) { if (traceLevel >= TRACE_LEVEL_WARNING) { dprintf(__VA_ARGS__); } }
#define TRACE_ERROR_WP(...)   { if (traceLevel >= TRACE_LEVEL_ERROR)   { dprintf(__VA_ARGS__); } }
#define TRACE_FATAL_WP(...)   { if (traceLevel >= TRACE_LEVEL_FATAL)   { dprintf(__VA_ARGS__); while(1); } }

#else

// Trace compilation depends on TRACE_LEVEL value
#if (TRACE_LEVEL >= TRACE_LEVEL_DEBUG)
#define TRACE_DEBUG(...)			printf(__VA_ARGS__)
#define TRACE_DEBUG_WP(...)			printf(__VA_ARGS__)
#define TRACE_DEBUG_FILE(...)		{}
#define TRACE_DEBUG_STRING(...)		{}
#define TRACE_HEXDUMP(...)			hexdump_std(__VA_ARGS__)
//#define hexdump_std(...)			hexdump(__VA_ARGS__)

#define DEBUG_GetChar()				UARTgetc()
#define DEBUG_IsRxReady()			UARTCharsAvail(UART1_BASE)

#else
#define TRACE_DEBUG(...)			{ }
#define TRACE_DEBUG_WP(...)			{ }
#define TRACE_DEBUG_FILE(...)		{ }
#define TRACE_DEBUG_STRING(...)		{ }

#define DEBUG_Getc()				{ }
#define TRACE_HEXDUMP(...)			{ }
#endif

#if (TRACE_LEVEL >= TRACE_LEVEL_INFO)
#define TRACE_INFO(...)       { printf("-I- " __VA_ARGS__); }
#define TRACE_INFO_WP(...)    { printf(__VA_ARGS__); }
#else
#define TRACE_INFO(...)       { }
#define TRACE_INFO_WP(...)    { }
#endif

#if (TRACE_LEVEL >= TRACE_LEVEL_WARNING)
#define TRACE_WARNING(...)    { printf("-W- " __VA_ARGS__); }
#define TRACE_WARNING_WP(...) { printf(__VA_ARGS__); }
#else
#define TRACE_WARNING(...)    { }
#define TRACE_WARNING_WP(...) { }
#endif

#if (TRACE_LEVEL >= TRACE_LEVEL_ERROR)
#define TRACE_ERROR(...)      { printf("-E- " __VA_ARGS__); }
#define TRACE_ERROR_WP(...)   { printf(__VA_ARGS__); }
#else
#define TRACE_ERROR(...)      { }
#define TRACE_ERROR_WP(...)   { }
#endif

#if (TRACE_LEVEL >= TRACE_LEVEL_FATAL)
#define TRACE_FATAL(...)      { printf("-F- " __VA_ARGS__); while(1); }
#define TRACE_FATAL_WP(...)   { printf(__VA_ARGS__); while(1); }
#else
#define TRACE_FATAL(...)      { while(1); }
#define TRACE_FATAL_WP(...)   { while(1); }
#endif

#endif

//------------------------------------------------------------------------------
//         Exported variables
//------------------------------------------------------------------------------
// Depending on DYN_TRACES, traceLevel is a modifable runtime variable
// or a define
#if !defined(NOTRACE) && (DYN_TRACES == 1)
    extern unsigned int traceLevel;
#endif

#endif //#ifndef DEBUG_TRACE_H

