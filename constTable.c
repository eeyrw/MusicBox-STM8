#include <stdint.h>
//--------------------------------------------------------------------//
// Pitch number to angular speed conversion table
//--------------------------------------------------------------------//
//Since sustain area of wave table, a cycle of fundamental frequency, is sampled
//in 128 points, the base frequency becomes 32000/128 = 250 Hz. The wave table
//lookup pointer, 16.8 fraction, is increased every sample by these 8.8 fractional
//angular speed values.
const uint16_t PitchIncrementTable[] = {
	//   A     B     H     C    Cis    D    Dis    E     F    Fis    G    Gis
	225, 239, 253, 268, 284, 301, 319, 338, 358, 379, 401, 425,				// 220Hz..
	451, 477, 506, 536, 568, 601, 637, 675, 715, 758, 803, 851,				// 440Hz..
	901, 955, 1011, 1072, 1135, 1203, 1274, 1350, 1430, 1515, 1606, 1701,   // 880Hz..
	1802, 1909, 2023, 2143, 2271, 2406, 2549, 2700, 2861, 3031, 3211, 3402, // 1760Hz..
	3604, 3818, 4046, 4286, 4542, 4812, 5098, 5400};						// 3520Hz

const uint8_t EnvelopeTable[] = {
	255, 252, 250, 247, 245, 243, 240, 238, 235, 233, 231, 228, 226, 224, 222, 219,
	217, 215, 213, 211, 209, 207, 205, 203, 201, 199, 197, 195, 193, 191, 189, 187,
	185, 183, 182, 180, 178, 176, 174, 173, 171, 169, 168, 166, 164, 163, 161, 159,
	158, 156, 155, 153, 152, 150, 149, 147, 146, 144, 143, 141, 140, 139, 137, 136,
	134, 133, 132, 130, 129, 128, 127, 125, 124, 123, 122, 120, 119, 118, 117, 116,
	115, 113, 112, 111, 110, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100, 99,
	98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 87, 86, 85, 84,
	83, 82, 82, 81, 80, 79, 78, 78, 77, 76, 75, 75, 74, 73, 72, 72,
	71, 70, 69, 69, 68, 67, 67, 66, 65, 65, 64, 64, 63, 62, 62, 61,
	60, 60, 59, 59, 58, 57, 57, 56, 56, 55, 55, 54, 54, 53, 53, 52,
	51, 51, 50, 50, 49, 49, 48, 48, 48, 47, 47, 46, 46, 45, 45, 44,
	44, 43, 43, 43, 42, 42, 41, 40, 40, 39, 39, 38, 38, 37, 37, 36,
	35, 35, 34, 34, 33, 33, 32, 31, 31, 30, 30, 29, 29, 28, 28, 27,
	26, 26, 25, 25, 24, 24, 23, 22, 22, 21, 21, 20, 20, 19, 19, 18,
	17, 17, 16, 16, 15, 15, 14, 13, 13, 12, 12, 11, 11, 10, 10, 9,
	8, 8, 7, 7, 6, 6, 5, 4, 4, 3, 3, 2, 2, 1, 1, 0};

const int8_t WaveTable[] = {1, 23};

const unt8_t Score[] = {1, 23};