#ifndef MODI_INTERFACE_PROPERTIES_H_
#define MODI_INTERFACE_PROPERTIES_H_

#define PROP_ENV_ILLUMINANCE                2
#define PROP_ENV_RED                        3
#define PROP_ENV_GREEN                      4
#define PROP_ENV_BLUE                       5
#define PROP_ENV_TEMPERATURE                6
#define PROP_ENV_HUMIDITY                   7

#define PROP_GYRO_ROLL                      2
#define PROP_GYRO_PITCH                     3
#define PROP_GYRO_YAW                       4
#define PROP_GYRO_GYRO_X                    5
#define PROP_GYRO_GYRO_Y                    6
#define PROP_GYRO_GYRO_Z                    7
#define PROP_GYRO_ACCEL_X                   8
#define PROP_GYRO_ACCEL_Y                   9
#define PROP_GYRO_ACCEL_Z                   10
#define PROP_GYRO_VIBRATION                 11

#define PROP_MIC_VOLUME                     2
#define PROP_MIC_FREQUENCY                  3
#define PROP_MIC_50HZ                       4
#define PROP_MIC_100HZ                      5
#define PROP_MIC_150HZ                      6
#define PROP_MIC_200HZ                      7
#define PROP_MIC_250HZ                      8
#define PROP_MIC_300HZ                      9
#define PROP_MIC_350HZ                      10
#define PROP_MIC_400HZ                      11

#define PROP_BUTTON_CLICK                   2
#define PROP_BUTTON_DOUBLE_CLICK            3
#define PROP_BUTTON_PUSH_STATE              4
#define PROP_BUTTON_TOGGLE                  5

#define PROP_DIAL_TURN                      2
#define PROP_DIAL_TURN_SPEED                3


#define PROP_ULTRASONIC_DISTANCE            2

#define PROP_IR_DISTANCE                    2
#define PROP_IR_INTENSITY                   3
#define PROP_IR_REMOTE                      4

#define PROP_LED_RED                        2
#define PROP_LED_GREEN                      3
#define PROP_LED_BLUE                       4
#define PROP_LED_RGB                        16

#define PROP_MOTOR_UTORQUE                  2
#define PROP_MOTOR_USPEED                   3
#define PROP_MOTOR_UANGLE                   4
#define PROP_MOTOR_USPEED_S                 5
#define PROP_MOTOR_UANGLE_S                 6
#define PROP_MOTOR_BTORQUE                  10
#define PROP_MOTOR_BSPEED                   11
#define PROP_MOTOR_BANGLE                   12
#define PROP_MOTOR_BSPEED_S                 13
#define PROP_MOTOR_BANGLE_S                 14
#define PROP_MOTOR_TORQUE                   16
#define PROP_MOTOR_SPEED                    17
#define PROP_MOTOR_ANGLE                    18

#define PROP_SPEAKER_VOLUME                 2
#define PROP_SPEAKER_FREQUENCY              3
#define PROP_SPEAKER_TUNE                   16
#define PROP_SPEAKER_RESET                  17
#define PROP_SPEAKER_EFFECT                 18
#define PROP_SPEAKER_MELODY                 19

#define PROP_DISPLAY_POSITION               16
#define PROP_DISPLAY_TEXT                   17
#define PROP_DISPLAY_DRAW_DATA              18
#define PROP_DISPLAY_DRAW_VARIABLE          19
#define PROP_DISPLAY_DATA                   20
#define PROP_DISPLAY_RESET                  21
#define PROP_DISPLAY_VARIABLE1              22
#define PROP_DISPLAY_VARIABLE2              23
#define PROP_DISPLAY_VARIABLE3              24
#define PROP_DISPLAY_HORIZONTAL             25
#define PROP_DISPLAY_VERTICAL               26

#define PROP_DISPLAY_ADD_PICTURE            27

#define PROP_DISPLAY_VARIABLE(x)            PROP_DISPLAY_VARIABLE1 + x

#define PROP_NETWORK_DATA                   2
#define PROP_NETWORK_EVENT                  3

#define MODULE_PNP_OFF                      0
#define MODULE_PNP_ON                       1


#define F_DO_1                              32
#define F_RE_1                              36
#define F_MI_1                              41
#define F_PA_1                              43
#define F_SOL_1                             48
#define F_RA_1                              55
#define F_SI_1                              61
#define F_DO_S_1                            34
#define F_RE_S_1                            39
#define F_PA_S_1                            46
#define F_SOL_S_1                           52
#define F_RA_S_1                            58
#define F_DO_2                              65
#define F_RE_2                              73
#define F_MI_2                              82
#define F_PA_2                              87
#define F_SOL_2                             97
#define F_RA_2                              110
#define F_SI_2                              123
#define F_DO_S_2                            69
#define F_RE_S_2                            77
#define F_PA_S_2                            92
#define F_SOL_S_2                           103
#define F_RA_S_2                            116
#define F_DO_3                              130
#define F_RE_3                              146
#define F_MI_3                              165
#define F_PA_3                              174
#define F_SOL_3                             196
#define F_RA_3                              220
#define F_SI_3                              247
#define F_DO_S_3                            138
#define F_RE_S_3                            155
#define F_PA_S_3                            185
#define F_SOL_S_3                           207
#define F_RA_S_3                            233
#define F_DO_4                              261
#define F_RE_4                              293
#define F_MI_4                              329
#define F_PA_4                              349
#define F_SOL_4                             392
#define F_RA_4                              440
#define F_SI_4                              493
#define F_DO_S_4                            277
#define F_RE_S_4                            311
#define F_PA_S_4                            369
#define F_SOL_S_4                           415
#define F_RA_S_4                            466
#define F_DO_5                              523
#define F_RE_5                              587
#define F_MI_5                              659
#define F_PA_5                              698
#define F_SOL_5                             783
#define F_RA_5                              880
#define F_SI_5                              988
#define F_DO_S_5                            554
#define F_RE_S_5                            622
#define F_PA_S_5                            739
#define F_SOL_S_5                           830
#define F_RA_S_5                            932
#define F_DO_6                              1046
#define F_RE_6                              1174
#define F_MI_6                              1318
#define F_PA_6                              1397
#define F_SOL_6                             1567
#define F_RA_6                              1760
#define F_SI_6                              1975
#define F_DO_S_6                            1108
#define F_RE_S_6                            1244
#define F_PA_S_6                            1479
#define F_SOL_S_6                           1661
#define F_RA_S_6                            1864
#define F_DO_7                              2093
#define F_RE_7                              2349
#define F_MI_7                              2637
#define F_PA_7                              2793
#define F_SOL_7                             3135
#define F_RA_7                              3520
#define F_SI_7                              3951
#define F_DO_S_7                            2217
#define F_RE_S_7                            2489
#define F_PA_S_7                            2959
#define F_SOL_S_7                           3322
#define F_RA_S_7                            3729

#endif // MODI_INTERFACE_PROPERTIES_H_

/* End of File */
