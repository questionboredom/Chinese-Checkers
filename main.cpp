#include <SFML/Graphics.hpp>
#include "main.h"
int main()
{
    app();
    return 0;
}
inline namespace V1
{
    void app()
    {
        using namespace Constants;
        std::vector<int> m{
            -1,-1,-1,-1,-1,-1, 1,-1,-1,-1,-1,-1,-1,
             -1,-1,-1,-1,-1, 1, 1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1, 1, 1, 1,-1,-1,-1,-1,-1,
             -1,-1,-1,-1, 1, 1, 1, 1,-1,-1,-1,-1,
             6, 6, 6, 6, 0, 0, 0, 0, 0, 2, 2, 2, 2,
              6, 6, 6, 0, 0, 0, 0, 0, 0, 2, 2, 2,
            -1, 6, 6, 0, 0, 0, 0, 0, 0, 0, 2, 2,-1,
             -1, 6, 0, 0, 0, 0, 0, 0, 0, 0, 2,-1,
            -1,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,-1,
             -1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 3,-1,
            -1, 5, 5, 0, 0, 0, 0, 0, 0, 0, 3, 3,-1,
              5, 5, 5, 0, 0, 0, 0, 0, 0, 3, 3, 3,
             5, 5, 5, 5, 0, 0, 0, 0, 0, 3, 3, 3, 3,
             -1,-1,-1,-1, 4, 4, 4, 4,-1,-1,-1,-1,
            -1,-1,-1,-1,-1, 4 ,4, 4,-1,-1,-1,-1,-1,
             -1,-1,-1,-1,-1, 4, 4,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1, 4,-1,-1,-1,-1,-1,-1
        };
        int currPiece{-1};
        int prevPiece{ -1 };
        std::vector<Piece> p{generate(m)};
        std::vector<sf::CircleShape> circles(p.size());
        for (int i{}; i < static_cast<int>(p.size()); ++i)
        {
            sf::CircleShape& circle{ circles.at(i) };
            circle.setRadius(static_cast<float>(pieceRadius));
            circle.setOrigin(static_cast<float>(pieceRadius), static_cast<float>(pieceRadius));
            circle.setFillColor(pieceColors.at(p.at(i).value));
            circle.setPosition(static_cast<float>(p.at(i).x), static_cast<float>(p.at(i).y));
        }
        sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Chinese Checkers");
        std::vector<bool> possMoves(p.size(), false);
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                {
                    mouseButtonPressEvent(event.mouseButton.x, event.mouseButton.y, p, m, currPiece, prevPiece, possMoves);
                }
            }
            // update circles
            for (int i{}; i < static_cast<int>(circles.size()); ++i)
            {
                
                circles.at(i).setFillColor(pieceColors.at(p.at(i).value));
                float r{static_cast<float>(pieceRadius*(possMoves.at(i)?selectShrinkFactor:1))};
                circles.at(i).setOrigin(r, r);
                circles.at(i).setRadius(r);
            }
            if (currPiece != -1)
            {
                float r{ static_cast<float>(pieceRadius*selectShrinkFactor) };
                circles.at(currPiece).setOrigin(r, r);
                circles.at(currPiece).setRadius(r);
            }
            window.clear(backgroundColor);
            for(const sf::CircleShape& c: circles)
                window.draw(c);
            window.display();
        }
    }
    std::vector<Piece> generate(std::vector<int>& values)
    {
        using namespace Constants;
        int size{ static_cast<int>(values.size()) };
        assert(size > numOfRows);
        assert(((size + numOfRows / 2) % numOfRows) == 0);
        //std::cout << "num of columns: " << maxNumOfColumns << '\n';
        std::vector<Piece> p{};
        p.reserve(size);
        // set ids, values and positions of pieceArray, and set id to values array
        int c{0}; bool oddRow{false};
        double xPos{ pieceRadius + pieceRadius * static_cast<int>(oddRow)}, yPos{pieceRadius};
        for (int& v: values)
        {
            if (v != -1)
            {
                p.push_back(Piece{
                    .id{static_cast<int>(p.size())},
                    .value{v},
                    .x{xPos},
                    .y{yPos}
                    });
                //std::cout << p.back().id << ": " << p.back().value << p.back()
                v = p.back().id;
            }
            if (c + 1 == (static_cast<int>(numOfCols) - static_cast<int>(oddRow)))
            {
                c = 0;
                oddRow = !oddRow;
                xPos = pieceRadius + pieceRadius * static_cast<int>(oddRow);
                yPos += yOffset;
            }
            else
            {
                ++c;
                xPos += xOffset;
            }
        }
        // set side ids to piece arr using id array
        oddRow = 0;
        c = 0;
        std::vector<int>& ids{values};
        for (int i{}; i<size; ++i)
        {
            assert(c >= 0 && c < static_cast<int>(numOfCols) - oddRow);
            if (ids.at(i) != -1)
            {
                if (c > 0 && ids.at(i - 1) != -1) p.at(ids.at(i)).sideIds.at(si_left) = ids.at(i - 1);
                if (c < static_cast<int>(numOfCols) - oddRow -1 && ids.at(i + 1) != -1) p.at(ids.at(i)).sideIds.at(si_right) = ids.at(i + 1);
                if(i>=static_cast<int>(numOfCols) -1 && c >= static_cast<int>(!oddRow) && ids.at(i - static_cast<int>(numOfCols)) != -1)p.at(ids.at(i)).sideIds.at(si_topLeft) = ids.at(i - static_cast<int>(numOfCols));
                if (i >= static_cast<int>(numOfCols) && c < static_cast<int>(numOfCols) - !oddRow && ids.at(i - static_cast<int>(numOfCols) + 1) != -1) p.at(ids.at(i)).sideIds.at(si_topRight) = ids.at(i - static_cast<int>(numOfCols) + 1);
                if (i + static_cast<int>(numOfCols) - 1 < size && c>=static_cast<int>(!oddRow) && ids.at(i + static_cast<int>(numOfCols) - 1)!=-1)p.at(ids.at(i)).sideIds.at(si_bottomLeft) = ids.at(i + static_cast<int>(numOfCols) - 1);
                if (i+static_cast<int>(numOfCols)<size && c<static_cast<int>(numOfCols)-static_cast<int>(!oddRow) && ids.at(i+static_cast<int>(numOfCols))!=-1) p.at(ids.at(i)).sideIds.at(si_bottomRight) = ids.at(i+static_cast<int>(numOfCols));
            }
            if (c == static_cast<int>(numOfCols) - oddRow - 1)
            {
                c = 0;
                oddRow = !oddRow;
            }
            else
            {
                ++c;
            }
        }
        return p;
    }
    int getId(int mouseX, int mouseY, std::vector<Piece>& p, std::vector<int>& ids)
    {
        using namespace Constants;
        // check if mouse position is within 
        // approx pos from above
        int y{ static_cast<int>(static_cast<double>(mouseY)/yOffset)};
        int x{-1};
        if (y % 2)
        {
            if (mouseX > pieceRadius && mouseX <static_cast<int>(numOfCols)*xOffset-pieceRadius)
            {
                x = static_cast<int>((mouseX + pieceRadius) / xOffset);
            }
        }
        else
        {
            x = static_cast<int>(mouseX / xOffset);
        }
        //std::cout << "mouse position: " << x << ' ' << y << '\n';
        if (x >= 0 && x < static_cast<int>(numOfCols) && y>=0 && y < numOfRows)
        {
            int i{ (y / 2) * (static_cast<int>(numOfCols) * 2 - 1) + (y % 2) * (static_cast<int>(numOfCols) - 1) + x };
            if (int id{ ids.at(i) }; id != -1)
            {
                if (Piece& ap{ p.at(id) }; withinCircle(mouseX, mouseY, pieceRadius, ap.x, ap.y))
                {
                    return id;
                }
            }
        }
        // approx pos from below
        y = static_cast<int>(static_cast<double>(mouseY-xOffset+yOffset) / yOffset);
        x = -1;
        if (y % 2)
        {
            if (mouseX > pieceRadius && mouseX < static_cast<int>(numOfCols) * xOffset - pieceRadius)
            {
                x = static_cast<int>((mouseX + pieceRadius) / xOffset);
            }
        }
        else
        {
            x = static_cast<int>(mouseX / xOffset);
        }
        //std::cout << "mouse position: " << x << ' ' << y << '\n';
        if (x >= 0 && x < static_cast<int>(numOfCols) && y >= 0 && y < numOfRows)
        {
            int i{ (y / 2) * (static_cast<int>(numOfCols) * 2 - 1) + (y % 2) * (static_cast<int>(numOfCols) - 1) + x };
            if (int id{ ids.at(i) }; id != -1)
            {
                if (Piece& ap{ p.at(id) }; withinCircle(mouseX, mouseY, pieceRadius, ap.x, ap.y))
                {
                    return id;
                }
            }
        }
        return -1;
    }
    bool withinCircle(double cx, double cy, double cr, double px, double py)
    {
        double x{ cx - px }, y{ cy - py };
        return x * x + y * y <= cr * cr;
    }
    void mouseButtonPressEvent(int mouseX, int mouseY, std::vector<Piece>& p, std::vector<int>& ids, int& currPiece, int& prevPiece, std::vector<bool>& possMoves)
    {
        using namespace Constants;
        // update currPiece
        prevPiece = currPiece;
        currPiece = getId(mouseX, mouseY, p, ids);
        /*
        // test side ids
        std::fill(possMoves.begin(), possMoves.end(), false);
        if (currPiece != -1)
        {
            for (int sideId : p.at(currPiece).sideIds)
            {
                if (sideId != -1)
                    possMoves.at(sideId) = true;
            }
        }
        //*/
        //*
        
        // if currPiece In PossibleMoves
        if (currPiece != -1 && possMoves.at(currPiece))
        {
            std::swap(p.at(currPiece).value, p.at(prevPiece).value);
            std::fill(possMoves.begin(), possMoves.end(), false);
        }
        // else find possible moves
        else 
            updatePossibleMoves(currPiece, p, possMoves);
        //*/
    }
    void updatePossibleMoves(int currPiece, std::vector<Piece>& p, std::vector<bool>& possMoves)
    {
        std::fill(possMoves.begin(), possMoves.end(), false);
        std::vector<int> stack{};
        stack.reserve(p.size());
        // depth first search for jump moves
        if (currPiece != -1 && p.at(currPiece).value != 0)
            stack.push_back(currPiece);
        else
        {
            return;
        }
        pushJumpMovesToStack(p, currPiece, stack, possMoves);

        while(stack.size())
        {
            int pieceI{ stack.back() };
            stack.pop_back();
            pushJumpMovesToStack(p, pieceI, stack, possMoves);
        }
        // set possMoves to true for empty pieces around curr piece
        for (int id1 : p.at(currPiece).sideIds)
        {
            if (id1 != -1 && p.at(id1).value == 0)
                possMoves.at(id1) = true;
        }
        return;
    }
    void pushJumpMovesToStack(const std::vector<Piece>& p, int i, std::vector<int>& stack, std::vector<bool>& possMoves)
    {
        for (int dir1{0}; dir1 < si_count; ++dir1)
        {
            if (int id1{ p.at(i).sideIds.at(dir1) }; id1 != -1)
            {
                if (const Piece& p1{ p.at(id1) }; p1.value > 0)
                {
                    if (int id2{p1.sideIds.at(dir1)}; id2 != -1)
                    {
                        if (const Piece& p2{ p.at(id2) }; p2.value == 0)
                        {
                            if (!possMoves.at(id2))
                            {
                                stack.push_back(id2);
                                possMoves.at(id2) = true;
                            }
                        }
                    }
                    
                }
            }
        }
    }
}
