#ifndef CONSTANTS_19_5_2024_6_36_AM_H
#define CONSTANTS_19_5_2024_6_36_AM_H
#include <numbers>
inline namespace V1
{
	namespace Constants
	{
		inline constexpr double selectShrinkFactor{ 0.8 };
		inline constexpr double pieceRadius{ 30 };
		inline constexpr double selectionRadius{ 30 * selectShrinkFactor };
		inline constexpr double pieceDiameter{ pieceRadius*2 };
		inline constexpr double yOffset{ std::numbers::sqrt3 * pieceRadius };
		inline constexpr double xOffset{ pieceDiameter };
		inline constexpr unsigned int numOfRows{ 17 };
		inline constexpr unsigned int numOfCols{ 13 };
		inline constexpr unsigned int windowHeight{ static_cast<unsigned int>((numOfRows - 1) * yOffset + pieceDiameter) };
		inline constexpr unsigned int windowWidth{ static_cast<unsigned int>(pieceDiameter * numOfCols) };
	}
}
#endif // !CONSTANTS_19_5_2024_6_36_AM_H
