#include <stdint.h>
#include <WaveTable.h>
// Sample's base frequency: 523.629906 Hz
// Sample's sample rate: 32000 Hz
const int8_t WaveTable[WAVETABLE_LEN] ={
// Attack Samples:
     0,     0,     0,     0,     0,     0,     0,     1,     0,     0,
     2,    -1,     1,     3,    -1,     5,     3,     0,     8,     0,
    -7,   -13,   -31,     0,    47,    53,    36,    -3,   -32,   -25,
   -19,    22,    78,    46,     5,     1,    -1,    11,    -4,   -18,
    20,     1,   -39,   -33,   -43,     2,    36,   -48,   -81,   -62,
   -52,    -6,   -30,   -62,     0,     9,    -3,    11,   -32,   -31,
     1,   -27,   -16,   -19,   -42,    19,    30,    13,    63,    37,
    11,    53,    43,    70,    85,    14,    15,     4,   -26,    35,
    29,     6,    50,    19,    28,    67,     6,     7,    11,   -38,
    12,    16,   -32,   -11,   -55,   -68,   -12,   -59,   -71,   -48,
   -89,   -39,    -8,   -59,   -28,   -45,   -72,    -1,   -12,   -16,
    31,   -16,    -1,    40,    -5,    23,    24,   -26,    32,    42,
    20,    76,    41,    22,    78,    48,    76,   105,    29,    38,
    34,    -2,    62,    39,    -4,    33,   -17,   -10,    49,     0,
    14,    22,   -38,    14,    24,   -23,     1,   -64,  -100,   -31,
   -63,   -61,   -43,  -119,   -77,   -33,   -74,   -32,   -58,   -96,
   -17,   -33,   -32,    21,   -34,    -9,    40,    -3,    43,    38,
   -19,    50,    43,    29,    95,    26,    10,    57,    -3,    44,
    70,    -2,    46,    34,    -3,    66,    22,     1,    48,   -14,
    10,    53,     0,    41,    24,   -41,    25,     6,   -14,    39,
   -34,   -42,     8,   -45,    -7,    -9,   -96,   -44,   -49,   -70,
     0,   -57,   -75,   -21,   -77,   -35,     3,   -68,   -22,   -25,
   -70,     8,   -20,   -43,    18,   -40,   -19,    35,   -22,    25,
    35,   -18,    63,    54,    22,    84,    24,    25,    89,    26,
    55,    67,   -12,    51,    55,    11,    77,    24,    -5,    61,
     8,    31,    66,   -15,    18,    15,   -45,    20,   -11,   -53,
    -3,   -72,   -71,    -9,   -74,   -49,   -35,   -98,   -21,   -12,
   -51,     7,   -43,   -59,    11,   -37,   -20,     5,   -72,   -22,
    -1,   -47,    17,   -13,   -50,    17,   -16,     1,    60,    -2,
    26,    51,     3,    69,    63,    13,    67,    32,    25,    87,
    27,    30,    58,    -2,    44,    55,    -5,    39,    13,   -12,
    52,     9,     0,    31,   -38,   -15,    10,   -43,     1,   -14,
   -70,   -16,   -39,   -50,     1,   -56,   -49,    -5,   -51,    -6,
     6,   -52,    -6,   -20,   -45,    13,   -29,   -45,     0,   -47,
   -18,    15,   -43,   -11,   -12,   -45,    23,     7,   -12,    38,
    -9,     1,    54,    10,    40,    48,    -9,    42,    42,    16,
    69,    24,     7,    59,    14,    32,    59,    -1,    34,    43,
    -1,    45,    16,   -19,    28,   -13,   -14,    24,   -36,   -20,
    -3,   -53,    -3,    -4,   -51,   -10,   -41,   -44,    14,   -32,
   -31,    -8,   -64,   -26,    -9,   -52,    -5,   -27,   -60,    -2,
   -28,   -26,    15,   -42,   -26,     5,   -31,    18,    19,   -22,
    25,     6,    -2,    48,     4,     6,    42,     1,    38,    55,
    11,    48,    33,     7,    62,    33,    21,    56,    10,    26,
    52,     3,    29,    22,   -16,    28,     5,   -18,    18,   -26,
   -25,    10,   -32,    -4,     4,   -45,    -8,   -10,   -29,    17,
   -23,   -47,   -12,   -48,   -29,    -6,   -60,   -34,   -28,   -58,
    -8,   -21,   -41,     1,   -34,   -27,    17,   -19,     3,    16,
   -23,    20,    22,    -5,    34,     6,    -2,    44,    12,    26,
    51,     7,    39,    53,    23,    67,    47,    20,    64,    34,
    32,    59,     6,    17,    33,    -6,    26,    15,   -23,    13,
   -11,   -23,    16,   -25,   -23,     0,   -43,   -15,    -7,   -45,
   -11,   -32,   -61,   -21,   -48,   -49,   -20,   -64,   -43,   -15,
   -48,   -13,   -15,   -42,     5,    -9,   -18,    19,   -15,    -8,
    21,   -13,    16,    26,   -11,    23,    18,     6,    52,    27,
    19,    49,    17,    41,    65,    26,    51,    48,    19,    57,
    35,    13,    39,     2,     5,    28,   -13,     3,     8,   -29,
     4,    -4,   -27,     6,   -23,   -30,     3,   -29,   -19,    -8,
   -50,   -24,   -22,   -50,   -16,   -35,   -51,   -16,   -42,   -32,
    -1,   -35,   -17,    -7,   -34,     4,     1,   -21,     9,   -14,
   -16,    21,    -7,     2,    17,   -16,    15,    23,     1,    35,
    21,     8,    45,    25,    34,    60,    24,    40,    52,    21,
    47,    33,     5,    34,    12,     4,    30,    -5,     1,    18,
   -13,     8,     7,   -22,     5,    -8,   -23,     7,   -22,   -28,
   -11,   -44,   -25,   -14,   -45,   -23,   -32,   -50,   -13,   -28,
   -33,    -7,   -36,   -26,    -6,   -31,    -6,    -5,   -33,    -4,
   -12,   -21,    11,   -13,   -12,    12,   -10,    10,    24,     0,
    27,    27,    13,    50,    35,    31,    55,    28,    39,    54,
    20,    35,    33,     8,    35,    19,     2,    25,     0,     0,
    22,    -6,     5,    10,   -19,     3,    -3,   -23,     0,   -23,
   -33,    -9,   -34,   -23,    -9,   -40,   -23,   -23,   -45,   -16,
   -26,   -39,   -12,   -32,   -27,    -4,   -31,   -18,   -11,   -35,
    -7,   -10,   -28,     0,   -15,   -16,    14,    -5,     6,    23,
     0,    26,    35,    17,    45,    33,    21,    48,    29,    29,
    45,    15,    26,    35,    11,    33,    26,     6,    31,    16,
    10,    31,     5,     6,    16,   -13,     0,     0,   -23,    -6,
   -20,   -34,   -11,   -32,   -35,   -19,   -44,   -32,   -20,   -41,
   -22,   -26,   -42,   -15,   -25,   -32,   -13,   -36,   -28,   -10,
   -31,   -13,    -9,   -27,    -2,    -5,   -10,    17,     4,     6,
    27,    10,    27,    41,    20,    38,    35,    19,    42,    30,
    23,    42,    22,    25,    40,    18,    30,    33,    13,    33,
    24,     8,    25,     6,     0,    14,   -11,    -8,    -5,   -30,
   -17,   -20,   -36,   -16,   -29,   -39,   -19,   -35,   -28,   -12,
   -33,   -24,   -21,   -38,   -17,   -22,   -34,   -16,   -30,   -31,
   -11,   -28,   -19,    -8,   -25,    -3,     2,    -6,    16,     9,
     6,    29,    16,    20,    34,    14,    26,    33,    16,    35,
    30,    19,    39,    26,    24,    40,    21,    27,    35,    17,
    31,    29,    10,    24,    10,    -1,    12,    -8,   -12,    -4,
   -27,   -19,   -15,   -33,   -17,   -22,   -33,   -13,   -23,   -25,
   -12,   -32,   -28,   -18,   -35,   -23,   -25,   -42,   -24,   -28,
   -32,   -11,   -26,   -24,    -6,   -18,    -3,     6,    -5,    12,
    12,     6,    29,    21,    16,    31,    16,    22,    34,    17,
    29,    31,    18,    36,    32,    24,    40,    27,    27,    41,
    24,    28,    30,     9,    19,    12,    -3,     6,    -8,   -18,
    -6,   -22,   -19,   -10,   -28,   -19,   -15,   -27,   -10,   -16,
   -28,   -15,   -28,   -30,   -18,   -34,   -30,   -24,   -39,   -24,
   -22,   -33,   -17,   -22,   -24,    -4,   -12,    -7,     6,    -5,
     7,    17,     6,    20,    16,     7,    25,    19,    18,    32,
    18,    22,    32,    22,    35,    37,    26,    41,    36,    29,
    41,    25,    20,    27,    10,    13,    13,    -6,     0,    -7,
   -20,    -7,   -16,   -20,    -9,   -23,   -20,   -11,   -24,   -16,
   -17,   -30,   -19,   -24,   -32,   -22,   -33,   -34,   -22,   -33,
   -27,   -21,   -31,   -18,   -15,   -21,    -5,    -7,    -8,     6,
     0,     5,    16,     6,    15,    19,    11,    24,    21,    14,
    26,    21,    24,    37,    28,    34,    40,    29,    38,    37,
    27,    34,    24,    17,    24,    11,     7,     7,    -8,    -5,
    -4,   -15,    -8,   -13,   -20,   -10,   -16,   -16,    -9,   -20,
   -18,   -15,   -26,   -19,   -22,   -33,   -27,   -32,   -35,   -25,
   -32,   -31,   -22,   -28,   -18,   -13,   -18,    -7,    -6,    -8,
     3,     0,     1,     9,     1,     6,    14,     8,    16,    17,
    13,    25,    26,    26,    37,    32,    35,    41,    34,    38,
    38,    27,    30,    25,    18,    22,    12,     5,     7,    -3,
    -3,    -1,   -11,    -7,    -7,   -14,    -7,   -12,   -18,   -14,
   -22,   -24,   -21,   -30,   -28,   -29,   -37,   -31,   -32,   -36,
   -27,   -30,   -28,   -18,   -20,   -15,    -9,   -15,    -8,    -5,
    -9,     0,     0,    -1,     8,     6,     8,    15,    10,    16,
    22,    21,    30,    33,    30,    39,    37,    35,    41,    33,
    33,    35,    26,    28,    26,    16,    17,    10,     3,     7,
     0,    -3,    -1,    -9,    -8,    -7,   -15,   -12,   -16,   -24,
   -20,   -24,   -28,   -24,   -31,   -31,   -27,   -34,   -29,   -27,
   -31,   -22,   -21,   -22,   -14,   -17,   -16,    -9,   -13,    -9,
    -6,   -11,    -3,     0,    -1,     7,     6,     6,    14,    12,
    18,    27,    25,    31,    33,    28,    35,    34,    31,    35,
    30,    27,    30,    23,    22,    22,    13,    13,    11,     5,
     7,     1,    -3,     0,    -5,    -7,    -7,   -16,   -15,   -16,
   -23,   -21,   -24,   -28,   -24,   -29,   -30,   -24,   -29,   -26,
   -21,   -25,   -19,   -17,   -21,   -15,   -16,   -18,   -12,   -17,
   -16,   -10,   -12,    -6,     0,    -2,     5,     8,     8,    18,
    20,    22,    28,    24,    27,    33,    28,    32,    31,    25,
    29,    26,    23,    28,    23,    20,    21,    14,    15,    16,
    10,    12,     9,     2,     4,    -2,    -8,    -7,   -15,   -16,
   -15,   -24,   -23,   -24,   -28,   -23,   -26,   -29,   -24,   -27,
   -25,   -20,   -25,   -22,   -19,   -24,   -20,   -19,   -23,   -17,
   -19,   -18,   -10,   -12,    -7,     0,    -1,     5,     9,     9,
    18,    20,    21,    28,    26,    27,    32,    27,    29,    31,
    27,    31,    30,    25,    29,    25,    23,    26,    20,    18,
    19,    12,    11,     9,     0,     0,    -4,   -12,   -11,   -17,
   -21,   -20,   -28,   -28,   -26,   -30,   -25,   -24,   -27,   -21,
   -22,   -23,   -19,   -23,   -23,   -19,   -23,   -20,   -19,   -23,
   -19,   -18,   -18,   -10,    -8,    -6,     1,     1,     6,    13,
    12,    18,    22,    20,    26,    25,    24,    30,    27,    27,
    31,    27,    28,    30,    25,    28,    28,    24,    26,    22,
    18,    19,    11,     7,     6,    -1,    -3,    -6,   -14,   -14,
   -18,   -24,   -23,   -26,   -27,   -23,   -26,   -24,   -20,   -24,
   -21,   -20,   -24,   -19,   -21,   -23,   -19,   -23,   -24,   -21,
   -24,   -20,   -14,   -16,   -10,    -7,    -5,     3,     6,     8,
    15,    15,    18,    23,    20,    23,    26,    23,    26,    25,
    23,    26,    24,    23,    27,    24,    27,    29,    25,    27,
    25,    19,    19,    14,     8,     6,    -1,    -5,    -7,   -15,
   -18,   -20,   -24,   -22,   -23,   -25,   -20,   -21,   -21,   -18,
   -20,   -18,   -17,   -21,   -21,   -21,   -24,   -22,   -24,   -25,
   -21,   -21,   -19,   -14,   -14,    -8,    -3,    -2,     3,     6,
     8,    13,    13,    15,    18,    16,    17,    20,    19,    22,
    22,    20,    23,    24,    25,    29,    29,    30,    32,    29,
    28,    27,    22,    19,    13,     6,     3,    -1,    -5,    -8,
   -14,   -17,   -17,   -20,   -19,   -18,   -19,   -17,   -18,   -19,
   -18,   -20,   -22,   -21,   -24,   -25,   -25,   -28,   -27,   -26,
   -26,   -23,   -22,   -21,   -17,   -14,   -10,    -3,     0,     2,
     5,     6,     9,    12,    13,    15,    16,    15,    18,    18,
    19,    23,    24,    27,    30,    31,    34,    34,    32,    32,
    31,    27,    24,    18,    13,    10,     4,     0,    -3,    -8,
   -10,   -12,   -14,   -14,   -14,   -15,   -14,   -16,   -17,   -17,
   -19,   -21,   -22,   -25,   -25,   -25,   -27,   -28,   -29,   -27,
   -24,   -23,   -20,   -18,   -16,   -12,    -8,    -4,    -1,     0,
     2,     4,     6,     8,    10,    11,    12,    13,    14,    17,
    21,    23,    25,    26,    28,    31,    32,    32,    32,    30,
    29,    27,    23,    19,    15,    11,     8,     5,     2,     0,
    -3,    -6,    -7,    -7,    -9,   -11,   -13,   -15,   -16,   -17,
   -19,   -22,   -25,   -26,   -27,   -27,   -27,   -28,   -29,   -27,
   -25,   -23,   -21,   -19,   -16,   -13,   -10,    -7,    -3,    -2,
     0,     0,     1,     3,     5,     6,     7,     9,    12,    16,
    18,    20,    23,    25,    28,    31,    32,    33,    32,    31,
    31,    28,    25,    22,    18,    16,    13,     9,     6,     2,
    -1,    -2,    -4,    -6,    -7,   -11,   -13,   -15,   -17,   -17,
   -19,   -23,   -24,   -27,   -27,   -27,   -29,   -30,   -29,   -28,
   -24,   -22,   -21,   -18,   -16,   -13,    -9,    -8,    -6,    -5,
    -6,    -4,    -2,     0,     2,     2,     4,     8,    11,    15,
    18,    19,    23,    26,    28,    32,    33,    32,    32,    30,
    29,    29,    25,    21,    18,    14,    14,    11,     7,     4,
     0,    -1,     0,    -1,    -3,    -5,    -9,   -10,   -11,   -15,
   -17,   -21,   -25,   -25,   -26,   -27,   -26,   -28,   -26,   -24,
   -23,   -20,   -18,   -17,   -14,   -12,   -11,    -9,   -10,    -9,
    -8,    -8,    -5,    -3,    -2,     0,     1,     5,    10,    13,
    16,    19,    20,    24,    28,    28,    30,    29,    27,    27,
    26,    24,    23,    19,    17,    16,    14,    13,    11,     8,
     8,     6,     4,     4,     0,    -2,    -3,    -7,    -9,   -12,
   -18,   -20,   -22,   -25,   -24,   -26,   -29,   -27,   -26,   -23,
   -20,   -21,   -19,   -17,   -17,   -13,   -12,   -13,   -11,   -13,
   -13,   -11,   -10,    -7,    -5,    -5,    -1,     2,     5,    10,
    11,    13,    18,    20,    23,    26,    25,    26,    27,    25,
    25,    24,    22,    23,    21,    19,    20,    17,    16,    15,
    11,    11,    10,     7,     6,     2,    -2,    -3,    -8,   -11,
   -13,   -19,   -20,   -21,   -24,   -24,   -25,   -26,   -22,   -22,
   -21,   -19,   -20,   -18,   -16,   -17,   -16,   -17,   -19,   -16,
   -15,   -15,   -12,   -11,   -10,    -6,    -5,     0,     4,     6,
    10,    12,    14,    19,    21,    23,    25,    24,    24,    25,
    24,    25,    24,    22,    23,    22,    20,    22,    20,    19,
    19,    15,    13,    11,     7,     5,     1,    -2,    -4,   -10,
   -14,   -15,   -18,   -19,   -20,   -24,   -23,   -22,   -21,   -18,
   -18,   -19,   -17,   -18,   -19,   -19,   -21,   -21,   -20,   -21,
   -19,   -19,   -19,   -14,   -13,   -11,    -6,    -2,
// Loop Samples:
     0,     3,
     5,     8,    13,    14,    17,    19,    19,    22,    23,    22,
    23,    23,    24,    26,    25,    25,    26,    25,    26,    26,
    22,    22,    20,    17,    15,     9,     4,     1,    -4,    -7,
   -10,   -14,   -16,   -18,   -22,   -21,   -21,   -21,   -19,   -21,
   -21,   -20,   -21,   -21,   -21,   -23,   -23,   -24,   -25,   -23,
   -24,   -23,   -21,   -20,   -16,   -12,   -10,    -5,    -1,     1,
     6,     8,    10,    15,    16,    19,    21,    21,    21,    22,
    22,    25,    27,    28,    30,    29,    29,    32,    30,    29,
    28,    23,    21,    19,    14,    10,     5,     0,    -3,    -8,
   -12,   -13,   -16,   -17,   -18,   -21,   -20,   -20,   -22,   -21,
   -22,   -23,   -22,   -25,   -26,   -25,   -26,   -24,   -24,   -25,
   -24,   -23,   -21,   -17,   -14,   -11,    -7,    -4,    -1,     3,
     4,     8,    10,    11,    14,    15,    16,    18,    18,    19,
    23,    24,    27,    28,    27,    29,    30,    30,    31,    29,
    27,    26,    22,    19,    16,    10,     6,     3,    -2,    -5,
    -8,   -12,   -13,   -16,   -18,   -17,   -19,   -19,   -19,   -21,
   -21,   -21,   -23,   -23,   -25,   -26,   -25,   -26,   -26,   -24,
   -25,   -22,   -19,   -17,   -12,    -9,    -7,    -2,     0,     1,
     6,     6,     8,    10,     9,    12,    13,    13,    15,    16,
    17,    21,    23,    25,    29,    29,    30,    31,    29,    29,
    27,    24,    24,    19,    13,     9,     3,     1,     0,    -4,
    -6,    -8,   -12,   -12,   -13,   -14,   -13,   -17,   -19,   -19,
   -20,   -20,   -21,   -24,   -24,   -24,   -26,   -24,   -24,   -24,
   -21,   -20,   -16,   -11,   -11,    -8,    -5,    -4,     0,     0,
     0,     3,     2,     2,     5,     4,     6,     8,     8,    12,
    16,    17,    22,    23,    24,    28,    27,    27,    29,    26,
    25,    25,    21,    19,    15,    10,    10,     6,     3,     3,
    -1,    -3,    -3,    -5,    -5,    -6,   -10,   -11,   -13,   -15,
   -13,   -16,   -18,   -19,   -24,   -24,   -22,   -23,   -21,   -22,
   -23,   -19,   -18,   -17,   -13,   -13,   -10,    -6,    -7,    -5,
    -4,    -5,    -2,    -1,    -1,     1,     2,     4,     9,    11,
    15,    18,    18,    22,    24,    25,    28,    27,    25,    27,
    25,    24,    24,    18,    16,    15,    12,    12,     9,     5,
     5,     2,     0,     1,    -2,    -5,    -5,   -10,    -9,   -10,
   -15,   -15,   -19,   -23,   -22,   -24,   -25,   -24,   -26,   -25,
   -21,   -21,   -18,   -17,   -18,   -14,   -13,   -12,    -8,    -9,
    -8,    -5,    -6,    -3,     0,    -1,     2,     5,     7,    12,
    12,    13,    17,    18,    21,    25,    23,    25,    26,    24,
    27,    25,    20,    21,    17,    15,    16,    12,    11,    10,
     5,     7,     6,     3,     3,     0,    -4,    -4,    -8,   -11,
   -12,   -18,   -20,   -22,   -24,   -21,   -22,   -25,   -22,   -21,
   -19,   -16,   -18,   -17,   -15,   -15,   -11,   -10,   -12,   -10,
   -10,   -11,    -8,    -8,    -7,    -3,    -3,     1,     5,     5,
     9,    12,    14,    20,    21,    22,    25,    23,    24,    27,
    25,    24,    22,    18,    19,    19,    17,    17,    14,    12,
    13,    10,     9,     7,     1,     0,    -1,    -5,    -6,   -10,
   -14,   -15,   -19,   -20,   -18,   -21,   -21,   -20,   -22,   -19,
   -18,   -19,   -17,   -18,   -18,   -14,   -15,   -15,   -14,   -15,
   -13,   -11,   -12,   -10,    -9,    -8,    -3,     0,     1,     6,
     6,    10,    15,    17,    21,    22,    20,    21,    21,    21,
    23,    20,    19,    20,    19,    20,    21,    18,    18,    17,
    15,    16,    13,    10,     8,     4,     2,     1,    -4,    -7,
   -10,   -14,   -14,   -17,   -20,   -19,   -20,   -20,   -18,   -20,
   -19,   -18,   -20,   -18,   -16,   -17,   -16,   -18,   -20,   -18,
   -18,   -16,   -14,   -14,   -12,    -8,    -5,     0,     2,     3,
     7,    10,    13,    17,    16,    16,    17,    17,    20,    21,
    20,    20,    19,    19,    22,    22,    22,    23,    21,    22,
    22,    18,    16,    12,     8,     8,     4,     0,    -4,   -10,
   -12,   -13,   -15,   -16,   -17,   -20,   -20,   -20,   -20,   -18,
   -19,   -19,   -19,   -20,   -18,   -17,   -19,   -19,   -20,   -21,
   -18,   -17,   -16,   -12,   -10,    -6,    -3,    -1,};

const uint16_t WaveTable_Increment[] ={
     3,     4,     4,     4,     5,     5,     5,     5,     6,     6,
     7,     7,     7,     8,     8,     9,    10,    10,    11,    11,
    12,    13,    14,    15,    15,    16,    17,    18,    20,    21,
    22,    23,    25,    26,    28,    30,    31,    33,    35,    37,
    40,    42,    45,    47,    50,    53,    56,    60,    63,    67,
    71,    75,    80,    85,    90,    95,   101,   107,   113,   120,
   127,   134,   143,   151,   160,   170,   180,   190,   202,   214,
   227,   240,   254,   269,   286,   303,   321,   340,   360,   381,
   404,   428,   454,   481,   509,   539,   572,   606,   642,   680,
   720,   763,   808,   857,   908,   962,  1019,  1079,  1144,  1212,
  1284,  1360,  1441,  1527,  1617,  1714,  1816,  1924,  2038,  2159,
  2288,  2424,  2568,  2721,  2882,  3054,  3235,  3428,  3632,  3848,
  4077,  4319,  4576,  4848,  5136,  5442,  5765,  6108,};
