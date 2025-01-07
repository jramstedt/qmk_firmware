// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

/* PCB connector layout and switch matrix.
1                                                                                   33
┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┐
│ROW0│ROW2│ROW4│ROW6│COL0│COL2│COL4│COL6│COL8│CO10│CO12│CO14│    │ L4 │ L3 │ L1 │ L82│
├────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┼────┤
│ROW1│ROW3│ROW5│ROW7│COL1│COL3│COL5│COL7│COL9│CO11│CO13│CO15│ 3V │ L6 │ L5 │ L2 │    │
└────┴────┴────┴────┴────┴────┴────┴────┴────┴────┴────┴────┴────┴────┴────┴────┴────┘
2                                                                                   34
*/

/* Switch matrix and connector to blackpill wiring. Some matrix locations have alternative switch places for other layouts.
PIN     │ B9        B8      B7      B6      B5          B4      B3      A15     B0      B1      A8      B10     B15     B14     B13     B12 
    CONN│ COL0		COL1	COL2	COL3	COL4		COL5	COL6	COL7	COL8	COL9	CO10	CO11	CO12	CO13	CO14	CO15
────────┼────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
A0  ROW0│ S99		S98		S97		S96		S114		S113	S112	S111	S110	S109	S108	S107	S106	S104	S103	S105
A1  ROW1│ S61		S60		S59		S58		S76			S75		S74		S73		S72		S71		S70		S69		S68		S66		S65		S67
A2  ROW2│ S80		S79		S78		S77		S95			S94		S93		S92		S91		S90		S89		S88		S87		S85		S84		S86
A3  ROW3│ S38		S37		S36		S35		S34			S33		S32		S31		S30		S29		S28		S27		S26		S24		S23		S25
A4  ROW4│ S17/S18	S19		S43		S62		S127/S128	S129	S130	S119	S100	S81		S120	S101	S82		S20	    S44		S63
A5  ROW5│ S16		S15		S14		S13		S12			S11		S10		S9		S8		S7		S6		S5		S4		S2		S1		S3
A6  ROW6│ S42		S41		S40		S39		S57			S56		S55		S54		S53		S52		S51		S50		S49		S47		S46		S48
A7  ROW7│ S118		S117	S116	S115	S126		S125	S124	S123	S102	S122	S83		S121	S64		S22		S21		S45
*/

/* Connected LEDs
PIN| LED
───┼───────────────────
C13│ L1
C14│ L2
C15│ L82 (Caps lock led)
*/

/* ISO Switch and LED layout. 120, 121, 122, 124, 125, 126 are not populated.
                                                L1    L2    L3    L4    L5    L6        
    ┌───┬───┐ ┌────┬────┬────┬────┬────┬────┬────┬────┐ ┌───┬───┐  ┌───┬───┬───┬───┬───┐
    │ 1 │ 2 │ │ 3  │ 4  │ 5  │ 6  │ 7  │ 8  │ 9  │ 10 │ │ 11│ 12│  │ 13│ 14│ 15│ 16│ 17│
    └───┴───┘ └────┴────┴────┴────┴────┴────┴────┴────┘ └───┴───┘  ├───┼───┼───┼───┼───┤
    ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐  │ 35│ 36│ 37│ 38│ 19│
    │ 20│ 21│ 22│ 23│ 24│ 25│ 26│ 27│ 28│ 29│ 30│ 31│ 32│ 33│ 34│  ├───┼───┼───┼───┼───┤
    └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘  │ 39│ 40│ 41│ 42│ 43│
    ┌────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬──────┐  ├───┼───┼───┼───┼───┤
    │ 44 │ 45│ 46│ 47│ 48│ 49│ 50│ 51│ 52│ 53│ 54│ 55│ 56│  57  │  │ 58│ 59│ 60│ 61│ 62│
    ├────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬────┤  ├───┼───┼───┼───┼───┤
    │  63  │ 64│ 65│ 66│ 67│ 68│ 69│ 70│ 71│ 72│ 73│ 74│ 75│ 76 │  │ 77│ 78│ 79│ 80│ 81│
    ├───┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬───┤  ├───┼───┼───┼───┼───┤
 L82│ 82│ 83│ 84│ 85│ 86│ 87│ 88│ 89│ 90│ 91│ 92│ 93│ 94│ 95│   │  │ 96│ 97│ 98│ 99│100│
    ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤114│  ├───┼───┼───┼───┼───┤
    │ 101 │102│103│104│105│106│107│108│109│110│111│112│ 113 │   │  │   │116│117│118│   │
    ├───┬─┴─┬─┴─┬─┴───┴───┴───┴─┬─┴─┬─┴───┴───┴───┴─┬─┴─┬───┼───┤  │115├───┴───┼───┤119│
    │120│121│122│               │123│    NOKIA      │124│125│126│  │   │  128  │130│   │
    └───┴───┴───┘               └───┘    9925794    └───┴───┴───┘  └───┴───────┴───┴───┘

    Notes for other possible layouts:
    S18 replaces S17 and S19 with one 1w2h vertical button.
    S127 and S129 replaces S128
*/

/* Switch matrix used for scanning. Pin scanning is reordered to make keymap better match physical layout.
PIN│ B13	B14		B12		B15		B10		A8		B1		B0		A15		B3		B4		B5			B6		B7		B8		B9
───┼────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
A5 │ S1		S2		S3		S4		S5		S6		S7		S8		S9		S10		S11		S12			S13		S14		S15		S16
A3 │ S23	S24		S25		S26		S27		S28		S29		S30		S31		S32		S33		S34			S35		S36		S37		S38
A6 │ S46	S47		S48	    S49		S50		S51		S52		S53		S54		S55		S56		S57			S39		S40		S41		S42
A1 │ S65	S66		S67		S68		S69		S70		S71		S72		S73		S74		S75		S76			S58		S59		S60		S61
A2 │ S84	S85		S86		S87		S88		S89		S90		S91		S92		S93		S94		S95			S77		S78		S79		S80
A0 │ S103	S104	S105	S106	S107	S108	S109	S110	S111	S112	S113	S114		S96		S97		S98		S99
A7 │ S21	S22		S45		S64		S121	S83		S122	S102	S123	S124	S125	S126		S115	S116	S117	S118
A4 │ S44	S20	    S63		S82		S101	S120	S81		S100	S119	S130	S129	S127/S128	S62		S43		S19		S17/S18
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_iso(
//      S1		S2		S3		S4		S5		S6		S7		S8		S9		S10		S11		S12		S13		S14		S15		S16
        KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,

//      S23		S24		S25		S26		S27		S28		S29		S30		S31		S32		S33		S34		S35		S36		S37		S38
        KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,

//      S46		S47		S48		S49		S50		S51		S52		S53		S54		S55		S56		S57		S39		S40		S41		S42
        KC_NO,  KC_NO,  KC_NO,  KC_Q,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,

//      S65		S66		S67		S68		S69		S70		S71		S72		S73		S74		S75		S76		S58		S59		S60		S61
        KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,

//      S84		S85		S86		S87		S88		S89		S90		S91		S92		S93		S94		S95		S77		S78		S79		S80
        KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,

//      S103	S104	S105	S106	S107	S108	S109	S110	S111	S112	S113	S114	S96		S97		S98		S99
        KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,

//      S21		S22		S45		S64		S121	S83		S122	S102	S123	S124	S125	S126	S115	S116	S117	S118
        KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
        
//      S44		S20		S63		S82		S101	S120	S81		S100	S119	S130	S129	S128	S62		S43		S19		S17
        KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO
    )
};
