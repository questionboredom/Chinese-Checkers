#ifndef MAIN_6_49_AM_19_5_2024_H
#define MAIN_6_49_AM_19_5_2024_H
#include "Constants.h"
#include <cassert>
#include <array>
#include <vector>
#include <iostream>
#include "SFML/Graphics.hpp"
inline namespace V1
{
	enum SidesIdEnum
	{
		si_topLeft,
		si_topRight,
		si_left,
		si_right,
		si_bottomLeft,
		si_bottomRight,
		si_count
	};
	struct Piece
	{
		int id{-1};
		int value{-1};
		// side ids
		std::array<int, si_count> sideIds{ -1,-1,-1,-1,-1,-1 };
		/*int topLeft{-1};
		int topRight{ -1 };
		int left{ -1 };
		int right{ -1 };
		int bottomLeft{ -1 };
		int bottomRight{ -1 };*/
		// position
		double x{};
		double y{};
	};
	const std::array<sf::Color, 7> pieceColors{
		sf::Color{200, 200, 200, 255}, sf::Color::Black, sf::Color::Yellow, sf::Color::Green, sf::Color::White, sf::Color::Blue, sf::Color::Red
	};
	const sf::Color backgroundColor{ 180,180,180,255 };
	void app();
	//void handleEvents();

	std::vector<Piece> generate(std::vector<int>& values);
	bool withinCircle(double cx, double cy, double cr, double px, double py);
	int getId(int mouseX, int mouseY, std::vector<Piece>& p, std::vector<int>& ids);
	void mouseButtonPressEvent(int mouseX, int mouseY, std::vector<Piece>& p, std::vector<int>& ids, int& currPiece, int& prevPiece, std::vector<bool>& possMoves);
	//void updateGraphics();
	//void updateData();
	void updatePossibleMoves(int currPiece, std::vector<Piece>& p,  std::vector<bool>& possMoves);
	void pushJumpMovesToStack(const std::vector<Piece>& p, int i, std::vector<int>& stack, std::vector<bool>& possMove);
}

#endif // !MAIN_6_49_AM_19_5_2024_H
