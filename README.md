
# Preface

This md file is only used for recording the development process and thinking of YeMing product, more details will be seen on my blog wiki column : [YeMing - Multifunctionaltimer](https://www.charlesyu1997.com/wiki/MultiTimer/index.html)

# Development process records

In order to read and understand the finished code more quickly during the intermittent development, some definitions, enums, variables and functions are written down here.

## Define

```C
#define MAXIMUM_KEY_COUNT 1900  // The max count time of key press.
```

## Enum

```C
typedef enum  /* ---------- main switch status */
{
  POWER_OFF = 0x00U,
  POWER_ON  = 0x01U
} enum_PowerStatusTypeDef;

enum_PowerStatusTypeDef global_power_status;
enum_PowerStatusTypeDef global_timer_status;

typedef enum  /* ---------- display status */
{
  DISPLAY_OFF     = 0x00U,      // Display nothing
  DISPLAY_ON      = 0x01U,      // Display turns on
  DISPLAY_HOUR    = 0x02U,      // The hour will flash
  DISPLAY_MINUTE  = 0x03U,      // The minute will flash
  DISPLAY_SECOND  = 0x04U,      // The second will flash
  DISPLAY_ALL     = 0x05U       // 
} enum_DisplayStatusTypeDef;

enum_DisplayStatusTypeDef global_display_status;

typedef enum  /* ---------- key event */
{
  KEY_EVENT_NULL    = 0x00U,
  KEY_EVENT_CLICK   = 0x01U,
  KEY_EVENT_HOLD    = 0x02U
} enum_KeyEventTypeDef;

enum_KeyEventTypeDef global_key_event;

typedef enum  /* ---------- timer count status */
{
  TIMER_COUNT_OFF = 0x00U,
  TIMER_COUNT_ON  = 0x01U
} enum_TimerCountStatusTypeDef;

enum_TimerCountStatusTypeDef global_timer_count_status;
```

## Variable

```C
int key_count = 0;                          // Time count of button press          
int global_timeout_count = 0;               // Count and flash hour or minute display.
int global_second_dot_count = 0;            // Count and flash second dot display.

/* ---------- Total time count */
uint8_t minute_count = 0;                   // These three variable are about the time count.
uint8_t hour_count = 0;                     // The total time count is 
uint8_t second_count = 0;                   // (minute_count*60 + hour_count*3600 + second_count), in seconds .
```

## Module

This sections records the STM32 hardware modules which are used in the development.

### Timer

The timer3 is in charge of the countdown task and the timer4 will deal with the time display task.
