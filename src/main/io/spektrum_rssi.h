// Spektrum RSSI signal strength range, in dBm
#define SPEKTRUM_RSSI_MAX         (-42)
#define SPEKTRUM_RSSI_MIN         (-92)

// Spektrum RSSI reported value limit at or below which signals a fade instead of a real RSSI
#define SPEKTRUM_RSSI_FADE_LIMIT (-100)

#define SPEKTRUM_MAX_FADE_PER_SEC       40
#define SPEKTRUM_FADE_REPORTS_PER_SEC   2

typedef struct dbm_table_s
{
    int8_t  dBm;
    uint8_t reportAs;
} dbm_table_t;


void spektrumHandleRSSI(volatile uint8_t spekFrame[]);
