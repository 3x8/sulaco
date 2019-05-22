void pidAudioUpdate(void);
void pidAudioInit(void);

typedef enum {
    PID_AUDIO_OFF = 0,
    PID_AUDIO_PIDSUM_X,
    PID_AUDIO_PIDSUM_Y,
    PID_AUDIO_PIDSUM_XY,
} pidAudioModes_e;
pidAudioModes_e pidAudioGetMode(void);
void pidAudioSetMode(pidAudioModes_e mode);
