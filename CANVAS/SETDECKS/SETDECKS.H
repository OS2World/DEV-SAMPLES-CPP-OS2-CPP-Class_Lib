/************************************************************
/ Canvas - ISetCanvas decks example.
/
/ Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
/ All Rights Reserved.
************************************************************/
#define INCL_WINFRAMEMGR     /* For FID_CLIENT, SC_CLOSE. */
#include <os2.h>

/* Resource ids. */
#define ID_DECKS_FRAME        1

/* Menu item ids. */
#define ID_FILE               1000

#define ID_DECKS              1100
#define ID_DECK_DIR           1110
#define ID_DECK_HORZ          1111
#define ID_DECK_VERT          1112
#define ID_DECK_COUNT         1120
#define ID_DECK_COUNT_1       1121
#define ID_DECK_COUNT_2       1122
#define ID_DECK_COUNT_3       1123
#define ID_DECK_COUNT_4       1124
#define ID_DECK_COUNT_5       1125
#define ID_DECK_COUNT_6       1126
#define ID_DECK_COUNT_7       1127
#define ID_DECK_COUNT_8       1128
#define ID_DECK_COUNT_9       1129

#define ID_WHITESPACE         1200
#define ID_MARGIN             1210
#define ID_MARGIN_11          1211
#define ID_MARGIN_88          1212
#define ID_MARGIN_X           1213
#define ID_MARGIN_XX2         1214
#define ID_MARGIN_XD2         1215
#define ID_MARGIN_Y           1216
#define ID_MARGIN_YX2         1217
#define ID_MARGIN_YD2         1218
#define ID_PAD                1220
#define ID_PAD_11             1221
#define ID_PAD_88             1222
#define ID_PAD_X              1223
#define ID_PAD_XX2            1224
#define ID_PAD_XD2            1225
#define ID_PAD_Y              1226
#define ID_PAD_YX2            1227
#define ID_PAD_YD2            1228

#define ID_CHILDREN           1300
#define ID_ADD_FIRST          1311
#define ID_ADD_LAST           1312
#define ID_DELETE_FIRST       1313
#define ID_DELETE_LAST        1314

/* Control ids. */
#define ID_CLIENT             FID_CLIENT
#define ID_DECK_CANVAS        100
#define ID_DUMMY              1
