#include <SFML/Graphics.hpp>
#include<iostream>
#include<string>
#include<fstream>

using namespace std;
class tetris
{
public:
    virtual void drawshape(sf::RenderWindow& window) = 0;
    virtual void rotate(int **arr) = 0;
    virtual void moveLeft(int **arr) = 0;
    virtual void moveRight(int **arr) = 0;
    virtual void moveDown(int **arr) = 0;
    virtual bool isTouchedbottom(int **arr) = 0;
    virtual void reset(int **arr)=0;
    virtual bool canspawn(int **arr) = 0;
    virtual ~tetris()
    {} 
    
};
class well 
{
public:

    void drawBoard(sf::RenderWindow& window, int **arr)
    {
        int x = 0;
        int y = 0;
        for (int i = 0; i < 20; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                sf::RectangleShape cell(sf::Vector2f(40.f, 40.f));
                cell.setPosition(x, y);
                cell.setOutlineThickness(2.f);

                if (arr[i][j] == 0)
                {
                    cell.setOutlineColor(sf::Color::White);
                    cell.setFillColor(sf::Color::Black);
                }
                else if (arr[i][j] == 1)
                {
                    cell.setOutlineColor(sf::Color::Black);
                    cell.setFillColor(sf::Color(255, 0, 0));
                }
                else if (arr[i][j] == 2)
                {
                    cell.setOutlineColor(sf::Color::Black);
                    cell.setFillColor(sf::Color(0, 255, 0));
                }
                else if (arr[i][j] == 3)
                {
                    cell.setOutlineColor(sf::Color::Black);
                    cell.setFillColor(sf::Color(0, 0, 255));
                }
                else if (arr[i][j] == 4)
                {
                    cell.setOutlineColor(sf::Color::Black);
                    cell.setFillColor(sf::Color(255, 97, 0));
                }
                else if (arr[i][j] == 5)
                {
                    cell.setOutlineColor(sf::Color::Black);
                    cell.setFillColor(sf::Color(240, 0, 255));
                }
                else if (arr[i][j] == 6)
                {
                    cell.setOutlineColor(sf::Color::Black);
                    cell.setFillColor(sf::Color(0, 255, 255));
                }
                else if (arr[i][j] == 7)
                {
                    cell.setOutlineColor(sf::Color::Black);
                    cell.setFillColor(sf::Color(255, 255, 0));
                }
                window.draw(cell);
                x += 40;
            }
            y += 40;
            x = 0;
        }
    }
    void islinecomp(int** arr,int &score,int &lvl,int &lines)
    {
        for (int i = 0; i < 20; i++)
        {
            bool all_nonzero = true;
            for (int j = 0; j < 10; j++)
            {
                if (arr[i][j] == 0)
                {
                    all_nonzero = false;
                    break;
                }
            }
            if (all_nonzero)
            {
                lines++;
                score += 100;
                for (int j = 0; j < 10; j++)
                {
                    arr[i][j] = 0;
                }
                for (int k = i - 1; k >= 0; k--)
                {
                    for (int d = 0; d < 10; d++)
                    {
                        arr[k + 1][d] = arr[k][d];
                    }
                }
            }
        }
        lvl = (score / 1000) +1;
        if (lvl == 8)
        {
            lvl = 0;
        }
    }
    ~well()
    {

    }
};
class Ishape : public tetris
{
    int x = 0;
    int y = 0;
    int xcord = 0;
    int ycord = 0;
    sf::Color c = sf::Color(255, 0, 0);
    int currentrotation = 0;
    int rotations = 0;
public:
    ~Ishape()
    {

    }
    virtual bool canspawn(int **arr)
    {
        int txcord = 0;
        int tycord = 0;
        int check1 = 0;
        int check2 = 0;
        for (int i = 0; i < 4; i++)
        {
            if (arr[txcord + i][tycord] != 0)
            {
                check1 = 1;
            }
        }
        if (check1 == 1)
        {
            for (int i = 0; i < 4; i++)
            {
                if (arr[txcord][tycord+i] != 0)
                {
                    check2 = 1;
                }
            }
            if (check2 == 0)
            {
                currentrotation = 1;
            }
        }
        if (check1 == 1 && check2 == 1)
        {
            return 0;
        }
        return 1;
    }
    virtual void reset(int **arr)
    {
        x = 0;
        y = 0;
        xcord = 0;
        ycord = 0;
        currentrotation = 0;
        rotations = 0;
    }
    virtual void drawshape(sf::RenderWindow& window)
    {
        int fx = x;
        int fy = y;
        if (currentrotation == 0)
        {
            for (int i = 0; i < 4; i++)
            {
                sf::RectangleShape I(sf::Vector2f(40.f, 40.f));
                I.setPosition(fx, fy);
                I.setOutlineColor(sf::Color::Black);
                I.setFillColor(c);
                I.setOutlineThickness(2.f);
                window.draw(I);
                fy = fy + 40;
            }
        }
        else
        {
            for (int i = 0; i < 4; i++)
            {
                sf::RectangleShape I(sf::Vector2f(40.f, 40.f));
                I.setPosition(fx, fy);
                I.setOutlineColor(sf::Color::Black);
                I.setFillColor(c);
                I.setOutlineThickness(2.f);
                window.draw(I);
                fx = fx + 40;
            }
        }
    }
    virtual bool isTouchedbottom(int **arr)
    {
        xcord = y / 40;
        ycord = x / 40;
        int txcord = (y+40) / 40;
        int tycord = x / 40;
        int check = 0;
        if (currentrotation == 0)
        {
            if (txcord + 3 >= 20)
            {
                check = 1;
            }
            for (int i = 0; i < 4 && check==0; i++)
            {
                if (arr[txcord + i][tycord] != 0)
                {
                    check = 1;
                }
            }
            if (check == 1)
            {
                for (int i = 0; i < 4 ; i++)
                {
                    arr[xcord + i][ycord] = 1;
                }
                return 1;
            }
        }
        else if (currentrotation == 1)
        {
            if (txcord >= 20)
            {
                check = 1;
            }
            for (int i = 0; i < 4 && check==0; i++)
            {
                if (arr[txcord][tycord+i] != 0)
                {
                    check = 1;
                }
            }
            if (check == 1)
            {
                for (int i = 0; i < 4; i++)
                {
                    arr[xcord][ycord+i] = 1;
                }
                return 1;
            }
        }
        return 0;
    }
    virtual void rotate(int **arr)
    {
        xcord = y / 40;
        ycord = x / 40;
        int check = 0;
        if (isTouchedbottom(arr) == 0)
        {
            if (currentrotation == 0  && ycord<=6)
            {
                for (int i = 0; i < 4 && check==0; i++)
                {
                    if (arr[xcord][ycord + i] != 0)
                    {
                        check = 1;
                    }
                }
                if (check == 0)
                {
                    rotations++;
                    currentrotation = rotations % 2;
                }
            }
            else if (currentrotation == 1 && xcord<=16)
            {
                for (int i = 0; i < 4 && check == 0; i++)
                {
                    if (arr[xcord+i][ycord] != 0)
                    {
                        check = 1;
                    }
                }
                if (check==0)
                {
                    rotations++;
                    currentrotation = rotations % 2;
                }
            }
        }
    }
    virtual void moveLeft(int **arr)
    {
        int txcord = y / 40;
        int tycord = (x - 40) / 40;
        xcord = y / 40;
        ycord = x / 40;
        int check = 0;
        if (isTouchedbottom(arr) == 0)
        {
            if (currentrotation == 0)
            {
                for (int i = 0; i < 4 && check == 0; i++)
                {
                    if (arr[txcord + i][tycord] != 0)
                    {
                        check = 1;
                    }
                }
                if (x - 40 >= 0 && check==0)
                {
                    x = x - 40;
                }
            }
            else if(currentrotation==1)
            {
                for (int i = 0; i < 4 && check == 0; i++)
                {
                    if (arr[txcord][tycord + i] != 0)
                    {
                        check = 1;
                    }
                }
                if (x - 40 >= 0 && check==0)
                {
                    x = x - 40;
                }
            }
        }
    }
    virtual void moveRight(int **arr)
    {
        int txcord = y / 40;
        int tycord = (x + 40) / 40;
        xcord = y / 40;
        ycord = x / 40;
        int check = 0;
        if (isTouchedbottom(arr) == 0)
        {
            if (currentrotation == 0)
            {
                if(tycord>10)
                {
                    check = 1;
                }
                for (int i = 0; i < 4 && check==0; i++)
                {
                    if (arr[txcord + i][tycord] != 0)
                    {
                        check = 1;
                    }
                }
                if (check==0)
                {
                    x = x + 40;
                }
            }
            else if (currentrotation == 1)
            {
                if (ycord >= 6)
                {
                    check = 1;
                }
                for (int i = 0; i < 4 && check==0; i++)
                {
                    if (arr[txcord][tycord +i] != 0)
                    {
                        check = 1;
                    }
                }
                if (check==0)
                {
                    x = x + 40;
                }
            }
        }

    }
    virtual void moveDown(int **arr)
    {
        xcord = y / 40;
        ycord = x / 40;
        if (currentrotation == 1 && isTouchedbottom(arr) == 0)
        {
            if (y + 40 < 20 * 40)
            {
                y = y + 40;
            }
        }
        else if (currentrotation == 0 && isTouchedbottom(arr) == 0)
        {
            if (y + 160 < 20 * 40)
            {
                y = y + 40;
            }
        }
    }
};
class Jshape : public tetris
{
    int x = 0;
    int y = 0;
    int xcord = 0;
    int ycord = 0;
    sf::Color c = sf::Color(0, 255, 0);
    int rotations = 0;
    int currentrotation = 0;
public:
    ~Jshape()
    {
    }
    virtual bool canspawn(int** arr)
    {
        int txcord = 0;
        int tycord = 0;
        int check1 = 0;
        int check2 = 0;
        for (int i = 0; i < 4; i++)
        {
            if (arr[txcord + 2][tycord] != 0)
            {
                check1 = 1;
            }

            for (int i = 0; i < 3 && check1 == 0; i++)
            {
                if (arr[txcord + i][tycord + 1] != 0)
                {
                    check1 = 1;
                }
            }
        }
        if (check1 == 1)
        {
            if (arr[txcord][tycord] != 0)
            {
                check2 = 1;
            }

            for (int i = 0; i < 3 && check2 == 0; i++)
            {
                if (arr[txcord + 1][tycord + i] != 0)
                {
                    check2 = 1;
                }
            }
            if (check2 == 0)
            {
                currentrotation = 1;
            }
        }
        if (check1 == 1 && check2 == 1)
        {
            return 0;
        }
        return 1;
    }
    virtual void reset(int **arr)
    {
         x = 0;
         y = 0;
         xcord = 0;
         ycord = 0;
         rotations = 0;
         currentrotation = 0;
    }
    virtual void drawshape(sf::RenderWindow& window)
    {
        int fx = x;
        int fy = y;
        if (currentrotation == 0)
        {
            for (int i = 0; i < 3; i++)
            {
                sf::RectangleShape J(sf::Vector2f(40.f, 40.f));
                J.setPosition(fx + 40, fy);
                J.setOutlineColor(sf::Color::Black);
                J.setFillColor(c);
                J.setOutlineThickness(2.f);
                window.draw(J);
                fy = fy + 40;
            }
            sf::RectangleShape J(sf::Vector2f(40.f, 40.f));
            J.setPosition(fx, fy - 40);
            J.setOutlineColor(sf::Color::Black);
            J.setFillColor(c);
            J.setOutlineThickness(2.f);
            window.draw(J);
        }
        else if (currentrotation == 1)
        {
            sf::RectangleShape J(sf::Vector2f(40.f, 40.f));
            J.setPosition(fx, fy);
            J.setOutlineColor(sf::Color::Black);
            J.setFillColor(c);
            J.setOutlineThickness(2.f);
            window.draw(J);
            for (int i = 0; i < 3; i++)
            {
                sf::RectangleShape J(sf::Vector2f(40.f, 40.f));
                J.setPosition(fx, fy + 40);
                J.setOutlineColor(sf::Color::Black);
                J.setFillColor(c);
                J.setOutlineThickness(2.f);
                window.draw(J);
                fx = fx + 40;
            }
        }
        else if (currentrotation == 2)
        {
            sf::RectangleShape J(sf::Vector2f(40.f, 40.f));
            J.setPosition(fx + 40, fy);
            J.setOutlineColor(sf::Color::Black);
            J.setFillColor(c);
            J.setOutlineThickness(2.f);
            window.draw(J);
            for (int i = 0; i < 3; i++)
            {
                sf::RectangleShape I(sf::Vector2f(40.f, 40.f));
                I.setPosition(fx, fy);
                I.setOutlineColor(sf::Color::Black);
                I.setFillColor(c);
                I.setOutlineThickness(2.f);
                window.draw(I);
                fy = fy + 40;
            }
        }
        else if(currentrotation==3)
        {
            for (int i = 0; i < 3; i++)
            {
                sf::RectangleShape J(sf::Vector2f(40.f, 40.f));
                J.setPosition(fx, fy);
                J.setOutlineColor(sf::Color::Black);
                J.setFillColor(c);
                J.setOutlineThickness(2.f);
                window.draw(J);
                fx = fx + 40;
            }
            sf::RectangleShape J(sf::Vector2f(40.f, 40.f));
            J.setPosition(fx - 40, fy + 40);
            J.setOutlineColor(sf::Color::Black);
            J.setFillColor(c);
            J.setOutlineThickness(2.f);
            window.draw(J);
        }
    }
    virtual bool isTouchedbottom(int **arr)
    {
        xcord = y / 40;
        ycord = x / 40;
        int txcord = (y + 40) / 40;
        int tycord = x / 40;
        int check = 0;
        if (currentrotation == 0)
        {//cr0
            if (txcord + 2 >= 20)
            {
                check = 1;
            }
            if (check == 0)
            {
                if (arr[txcord + 2][tycord] != 0)
                {
                    check = 1;
                }
            }
            for (int i = 0; i < 3 && check==0; i++)
            {
                if (arr[txcord + i][tycord + 1] != 0)
                {
                    check = 1;
                }
            }
            if (check == 1)
            {
                for (int i = 0; i < 3 ; i++)
                {
                    arr[xcord + i][ycord + 1] = 2;
                }
                arr[xcord + 2][ycord] = 2;
                return 1;
            }
        }
        if (currentrotation == 1)
        {//cr1
            if (txcord + 1 >= 20)
            {
                check = 1;
            }
            if (check == 0)
            {
                if (arr[txcord][tycord] != 0)
                {
                    check = 1;
                }
            }
            for (int i = 0; i < 3 && check==0 ; i++)
            {
                if (arr[txcord+1][tycord +i] != 0)
                {
                    check = 1;
                }
            }
            if (check == 1)
            {
                for (int i = 0; i < 3; i++)
                {
                    arr[xcord +1][ycord + i] = 2;
                }
                arr[xcord][ycord] = 2;
                return 1;
            }
        }
        if (currentrotation == 2)
        {//cr2
            if (txcord + 2 >= 20)
            {
                check = 1;
            }
            if (check == 0)
            {
                if (arr[txcord][tycord + 1] != 0)
                {
                    check = 1;
                }
            }
            for (int i = 0; i < 3 && check==0; i++)
            {
                if (arr[txcord + i][tycord] != 0)
                {
                    check = 1;
                }
            }
            if (check == 1)
            {
                for (int i = 0; i < 3; i++)
                {
                    arr[xcord + i][ycord] = 2;
                }
                arr[xcord][ycord+1] = 2;
                return 1;
            }
        }
        if (currentrotation == 3)
        {//cr3
            if (txcord + 1 >= 20)
            {
                check = 1;
            }
            if (check == 0)
            {
                if (arr[txcord + 1][tycord + 2] != 0)
                {
                    check = 1;
                }
            }
            for (int i = 0; i < 3 && check==0; i++)
            {
                if (arr[txcord][tycord+i] != 0)
                {
                    check = 1;
                }
            }
            if (check == 1)
            {
                for (int i = 0; i < 3; i++)
                {
                    arr[xcord][ycord+i] = 2;
                }
                arr[xcord+1][ycord + 2] = 2;
                return 1;
            }  
        }
        return 0;
    }
    virtual void rotate(int **arr)
    {
        xcord = y / 40;
        ycord = x / 40;
        int check = 0;
        if (isTouchedbottom(arr) == 0)
        {   
            if (currentrotation == 0 && ycord<8)
            {                          
                if (arr[xcord][ycord + 1] != 0)
                {
                    check = 1;
                }
                for (int i = 0; i < 3 && check == 0; i++)
                {
                    if (arr[xcord + 1][ycord + i] != 0)
                    {
                        check = 1;
                    }
                }
                if (check==0)
                {
                    currentrotation = 1;
                }
            }
            if (currentrotation == 2 && ycord < 8)
            {
                if (arr[xcord + 1][ycord + 2] != 0)
                {
                    check = 1;    
                }
                for (int i = 0; i < 3 && check == 0; i++)
                {
                    if (arr[xcord][ycord + i] != 0)
                    {
                        check = 1;
                    }
                }
                if (check==0)
                {
                    rotations++;
                    currentrotation = rotations % 4;
                }
            }
            else if (currentrotation == 1 || currentrotation == 3)
            {
                rotations++;
                currentrotation = rotations % 4;
            }
        }
    }
    virtual void moveLeft(int **arr)
    {
        xcord = y / 40;
        ycord = x / 40;
        int txcord = y / 40;
        int tycord = (x-40) / 40 ;
        int check = 0;
        if (isTouchedbottom(arr) == 0)
        {
            if (currentrotation == 0)
            {  //cr0
                if (arr[txcord + 2][tycord] != 0)
                {
                    check = 1;
                }
                for (int i = 0; i < 3 && check == 0; i++)
                {
                    if (arr[txcord + i][tycord + 1] != 0)
                    {
                        check = 1;
                    }
                }
                if (x - 40 >= 0 && check == 0)
                {
                    x = x - 40;
                }
            }
            if (currentrotation == 1)
            {//cr1
                
                if (arr[txcord][tycord] != 0)
                {
                   check = 1;
                }
                for (int i = 0; i < 3 && check == 0; i++)
                {
                    if (arr[txcord + 1][tycord + i] != 0)
                    {
                        check = 1;
                    }
                }
                if (x - 40 >= 0 && check == 0)
                {
                    x = x - 40;
                }
            }
            if (currentrotation == 2)
            {//cr2
                if (arr[txcord][tycord + 1] != 0)
                {
                    check = 1;
                }
                for (int i = 0; i < 3 && check == 0; i++)
                {
                    if (arr[txcord + i][tycord] != 0)
                    {
                         check = 1;
                    }
                }
                if (x - 40 >= 0 && check == 0)
                {
                    x = x - 40;
                }
            }
            if (currentrotation == 3)
            {
                //cr3
                if (arr[txcord + 1][tycord + 2] != 0)
                {
                    check = 1;
                }
                for (int i = 0; i < 3 && check == 0; i++)
                {
                    if (arr[txcord][tycord + i] != 0)
                    {
                        check = 1;
                    }
                }
                if (x - 40 >= 0 && check == 0)
                {
                    x = x - 40;
                }
            }
        }
    }
    virtual void moveRight(int **arr)
    {
        xcord = y / 40;
        ycord = x / 40;
        int txcord = y / 40;
        int tycord = (x+40) / 40 ;
        int check = 0;
        if (isTouchedbottom(arr) == 0)
        {
            if (currentrotation == 0)
            {
                //cr0
                if (arr[txcord + 2][tycord] != 0)
                {
                    check = 1;
                }
                for (int i = 0; i < 3 && check == 0; i++)
                {
                    if (arr[txcord + i][tycord + 1] != 0)
                    {
                        check = 1;
                    }
                }
                if (check==0)
                {
                    x = x + 40;
                }
            }
            if (currentrotation == 1)
            {
                //cr1
                if (arr[txcord][tycord] != 0)
                {
                    check = 1;
                }
                for (int i = 0; i < 3 && check == 0; i++)
                {
                    if (arr[txcord + 1][tycord + i] != 0)
                    {
                        check = 1;
                    }
                }
                if (check==0)
                {
                    x = x + 40;
                }
            }
            if (currentrotation == 2)
            {
                //cr2
                if (arr[txcord][tycord + 1] != 0)
                {
                    check = 1;
                }
                for (int i = 0; i < 3 && check == 0; i++)
                {
                    if (arr[txcord + i][tycord] != 0)
                    {
                        check = 1;
                    }
                }
                if (check==0)
                {
                    x = x + 40;
                }
            }
            if (currentrotation == 3)
            {
                //cr3
                if (arr[txcord + 1][tycord + 2] != 0)
                {
                    check = 1;
                }
                for (int i = 0; i < 3 && check == 0; i++)
                {
                    if (arr[txcord][tycord + i] != 0)
                    {
                        check = 1;
                    }
                }
                if (check==0)
                {
                    x = x + 40;
                }
            }
        }
    }
    virtual void moveDown(int **arr)
    {
        if (isTouchedbottom(arr) == 0)
        {
            if (currentrotation == 0)
            {
                if (y + 160 <= 20 * 40)
                {
                    y = y + 40;
                }
            }
            if (currentrotation == 1)
            {
                if (y + 120 <= 20 * 40)
                {
                    y = y + 40;
                }
            }
            if (currentrotation == 2)
            {
                if (y + 160 <= 20 * 40)
                {
                    y = y + 40;
                }
            }
            if (currentrotation == 3)
            {
                if (y + 120 <= 20 * 40)
                {
                    y = y + 40;
                }
            }
        }
    }
};
class Lshape : public tetris
{
    int x = 0;
    int y = 0;
    int xcord = 0;
    int ycord = 0;
    sf::Color c = sf::Color(0, 0, 255);
    int rotations = 0;
    int currentrotation = 0;
public:
    ~Lshape()
    {

    }
    virtual bool canspawn(int** arr)
    {
        int txcord = 0;
        int tycord = 0;
        int check1 = 0;
        int check2 = 0;
        for (int i = 0; i < 4; i++)
        {
            if (arr[txcord + 2][tycord + 1] != 0)
            {
                check1 = 1;
            }
            for (int i = 0; i < 3 && check1 == 0; i++)
            {
                if (arr[txcord + i][tycord] != 0)
                {
                    check1 = 1;
                }
            }
        }
        if (check1 == 1)
        {
            if (arr[txcord + 1][tycord] != 0)
            {
                check2 = 1;
            }
            for (int i = 0; i < 3 && check2 == 0; i++)
            {
                if (arr[txcord][tycord + i] != 0)
                {
                    check2 = 1;
                }
            }
            if (check2 == 0)
            {
                currentrotation = 1;
            }
        }
        if (check1 == 1 && check2 == 1)
        {
            return 0;
        }
        return 1;
    }
    virtual void reset(int **arr)
    {
         x = 0;
         y = 0;
         xcord = 0;
         ycord = 0;
         rotations = 0;
         currentrotation = 0;
    }
    virtual void drawshape(sf::RenderWindow& window)
    {
        int fx = x;
        int fy = y;
        if (currentrotation == 0)
        {
            for (int i = 0; i < 3; i++)
            {
                sf::RectangleShape L(sf::Vector2f(40.f, 40.f));
                L.setPosition(fx, fy);
                L.setOutlineColor(sf::Color::Black);
                L.setFillColor(c);
                L.setOutlineThickness(2.f);
                window.draw(L);
                fy = fy + 40;
            }
            sf::RectangleShape L(sf::Vector2f(40.f, 40.f));
            L.setPosition(fx + 40, fy - 40);
            L.setOutlineColor(sf::Color::Black);
            L.setFillColor(c);
            L.setOutlineThickness(2.f);
            window.draw(L);
        }
        else if (currentrotation == 1)
        {
            sf::RectangleShape L(sf::Vector2f(40.f, 40.f));
            L.setPosition(fx, fy + 40);
            L.setOutlineColor(sf::Color::Black);
            L.setFillColor(c);
            L.setOutlineThickness(2.f);
            window.draw(L);
            for (int i = 0; i < 3; i++)
            {
                sf::RectangleShape L(sf::Vector2f(40.f, 40.f));
                L.setPosition(fx, fy);
                L.setOutlineColor(sf::Color::Black);
                L.setFillColor(c);
                L.setOutlineThickness(2.f);
                window.draw(L);
                fx = fx + 40;
            }
        }
        else if (currentrotation == 2)
        {
            sf::RectangleShape L(sf::Vector2f(40.f, 40.f));
            L.setPosition(fx, fy);
            L.setOutlineColor(sf::Color::Black);
            L.setFillColor(c);
            L.setOutlineThickness(2.f);
            window.draw(L);
            for (int i = 0; i < 3; i++)
            {
                sf::RectangleShape L(sf::Vector2f(40.f, 40.f));
                L.setPosition(fx + 40, fy);
                L.setOutlineColor(sf::Color::Black);
                L.setFillColor(c);
                L.setOutlineThickness(2.f);
                window.draw(L);
                fy = fy + 40;
            }
        }
        else
        {

            for (int i = 0; i < 3; i++)
            {
                sf::RectangleShape L(sf::Vector2f(40.f, 40.f));
                L.setPosition(fx, fy + 40);
                L.setOutlineColor(sf::Color::Black);
                L.setFillColor(c);
                L.setOutlineThickness(2.f);
                window.draw(L);
                fx = fx + 40;
            }
            sf::RectangleShape L(sf::Vector2f(40.f, 40.f));
            L.setPosition(fx - 40, fy);
            L.setOutlineColor(sf::Color::Black);
            L.setFillColor(c);
            L.setOutlineThickness(2.f);
            window.draw(L);
        }
    }
    virtual bool isTouchedbottom(int **arr)
    {
        xcord = y / 40;
        ycord = x / 40;
        int txcord = (y + 40) / 40;
        int tycord = x / 40;
        int check = 0;
        if (currentrotation == 0)
        {//cr0
            if (txcord + 2 >= 20)
            {
                check = 1;
            }
            if (check == 0)
            {
                if (arr[txcord + 2][tycord + 1] != 0)
                {
                    check = 1;
                }
            }
            for (int i = 0; i < 3 && check==0; i++)
            {
                if (arr[txcord + i][tycord] != 0)
                {
                    check = 1;
                }
            }
            if (check == 1)
            {
                for (int i = 0; i < 3; i++)
                {
                    arr[xcord + i][ycord] = 3;
                }
                arr[xcord + 2][ycord+1] = 3;
                return 1;
            }
            
        }
        if (currentrotation == 1)
        {//cr1
            if (txcord + 1 >= 20)
            {
                check = 1;
            }
            if (check == 0)
            {
                if (arr[txcord + 1][tycord] != 0)
                {
                    check = 1;
                }
            }
            for (int i = 0; i < 3 && check==0; i++)
            {
                if (arr[txcord][tycord + i] != 0)
                {
                    check = 1;
                }
            }
            if (check == 1)
            {
                for (int i = 0; i < 3; i++)
                {
                    arr[xcord][ycord + i] = 3;
                }
                arr[xcord+1][ycord] = 3;
                return 1;
            }
        }
        if (currentrotation == 2)
        {//cr2
            if (txcord + 2 >= 20)
            {
                check = 1;
            }
            if (check == 0)
            {
                if (arr[txcord][tycord] != 0)
                {
                    check = 1;
                }
            }
            for (int i = 0; i < 3 && check==0; i++)
            {
                if (arr[txcord + i][tycord+1] != 0)
                {
                    check = 1;
                }
            }
            if (check == 1)
            {
                for (int i = 0; i < 3; i++)
                {
                    arr[xcord + i][ycord+1] = 3;
                }
                arr[xcord][ycord] = 3;
                return 1;
            }
        }
        if (currentrotation == 3)
        {//cr3
            if (txcord + 1 >= 20)
            {
                check = 1;
            }
            if (check == 0)
            {
                if (arr[txcord][tycord + 2] != 0)
                {
                    check = 1;
                }
            }
            for (int i = 0; i < 3 && check==0; i++)
            {
                if (arr[txcord+1][tycord + i] != 0)
                {
                    check = 1;
                }
            }
            if (check == 1)
            {
                for (int i = 0; i < 3; i++)
                {
                    arr[xcord+1][ycord + i] = 3;
                }
                arr[xcord][ycord + 2] = 3;
                return 1;
            }
        }
        return 0;
    }
    virtual void rotate(int **arr)
    {
        xcord = y / 40;
        ycord = x / 40;
        int check = 0;
        if (isTouchedbottom(arr) == 0)
        {
            if (currentrotation == 0 && ycord < 8)
            {
                //cr1

                if (arr[xcord + 1][ycord] != 0)
                {
                    check = 1;
                }
                for (int i = 0; i < 3 && check == 0; i++)
                {
                    if (arr[xcord][ycord + i] != 0)
                    {
                        check = 1;
                    }
                }
                if (check==0)
                {
                    currentrotation = 1;
                }
            }
            if (currentrotation == 2 && ycord < 8)
            {
                //cr3
                if (arr[xcord][ycord + 2] != 0)
                {
                    check = 1;
                }
                for (int i = 0; i < 3 && check == 0; i++)
                {
                    if (arr[xcord + 1][ycord + i] != 0)
                    {
                        check = 1;
                    }
                }
                if (check==0)
                {
                    currentrotation = 3;
                }
            }
            if(currentrotation == 1 || currentrotation == 3)
            {
                rotations++;
                currentrotation = rotations % 4;
            }
        }
    }
    virtual void moveLeft(int **arr)
    {
        xcord = y / 40;
        ycord = x / 40;
        int txcord = y / 40;
        int tycord = (x - 40) / 40;
        int check = 0;
        if (isTouchedbottom(arr) == 0)
        {
            if (currentrotation == 0)
            {
                //cr0
                if (arr[txcord + 2][tycord + 1] != 0)
                {
                    check = 1;
                }
                for (int i = 0; i < 3 && check == 0; i++)
                {
                    if (arr[txcord + i][tycord] != 0)
                    {
                        check = 1;
                    }
                }
                if (x - 40 >= 0 && check==0)
                {
                    x = x - 40;
                }
            }
            if (currentrotation == 1)
            {
                //cr1

                if (arr[txcord + 1][tycord] != 0)
                {
                    check = 1;           
                }
                for (int i = 0; i < 3 && check == 0; i++)
                {
                    if (arr[txcord][tycord + i] != 0)
                    {
                        check = 1;
                    }
                }
                if (x - 40 >= 0 && check == 0)
                {
                    x = x - 40;
                }
            }
            if (currentrotation == 2)
            {
                //cr2
                if (arr[txcord][tycord] != 0)
                {
                    check = 1;
                }
                for (int i = 0; i < 3 && check == 0; i++)
                {
                    if (arr[txcord + i][tycord + 1] != 0)
                    {
                        check = 1;
                    }
                }
                if (x - 40 >= 0 && check == 0)
                {
                    x = x - 40;
                }
            }
            if (currentrotation == 3)
            {
                //cr3
                
                if (arr[txcord][tycord + 2] != 0)
                {
                    check = 1;

                }
                for (int i = 0; i < 3 && check == 0; i++)
                {
                    if (arr[txcord + 1][tycord + i] != 0)
                    {
                        check = 1;
                    }
                }
                if (x - 40 >= 0 && check == 0)
                {
                    x = x - 40;
                }
            }
            
        }
    }
    virtual void moveRight(int **arr)
    {
        xcord = y / 40;
        ycord = x / 40;
        int txcord = y / 40;
        int tycord = (x + 40) / 40;
        int check = 0;
        if (isTouchedbottom(arr) == 0)
        {
            if (currentrotation == 0)
            {
                //cr0
                if (arr[txcord + 2][tycord + 1] != 0)
                {
                    check = 1;
                }
                for (int i = 0; i < 3 && check == 0; i++)
                {
                    if (arr[txcord + i][tycord] != 0)
                    {
                        check = 1;
                    }
                }
                if (check==0)
                {
                    x = x + 40;
                }
            }
            if (currentrotation == 1)
            {
                //cr1
                if (arr[txcord + 1][tycord] != 0)
                {
                    check = 1;
                }
                for (int i = 0; i < 3 && check == 0; i++)
                {
                    if (arr[txcord][tycord + i] != 0)
                    {
                        check = 1;
                    }
                }
                if (check == 0)
                {
                    x = x + 40;
                }
            }
            if (currentrotation == 2)
            {
                //cr2
                if (arr[txcord][tycord] != 0)
                {
                    check = 1;
                }
                for (int i = 0; i < 3 && check == 0; i++)
                {
                    if (arr[txcord + i][tycord + 1] != 0)
                    {
                        check = 1;
                    }
                }
                if (check == 0)
                {
                    x = x + 40;
                }
            }
            if (currentrotation == 3)
            {
                //cr3
                if (arr[txcord][tycord + 2] != 0)
                {
                    check = 1;
                }
                for (int i = 0; i < 3 && check == 0; i++)
                {
                    if (arr[txcord + 1][tycord + i] != 0)
                    {
                        check = 1;
                    }
                }
                if (check == 0)
                {
                    x = x + 40;
                }
            }
        }
    }
    virtual void moveDown(int **arr)
    {
        if (isTouchedbottom(arr) == 0)
        {
            if (currentrotation == 0)
            {
                if (y + 160 <= 20 * 40)
                {
                    y = y + 40;
                }
            }
            if (currentrotation == 1)
            {
                if (y + 120 <= 20 * 40)
                {
                    y = y + 40;
                }
            }
            if (currentrotation == 2)
            {
                if (y + 160 <= 20 * 40)
                {
                    y = y + 40;
                }
            }
            if (currentrotation == 3)
            {
                if (y + 120 <= 20 * 40)
                {
                    y = y + 40;
                }
            }
        }
    }
};
class Oshape : public tetris
{
    int x = 0;
    int y = 0;
    int xcord = 0;
    int ycord = 0;
    sf::Color c = sf::Color(255, 97, 0);
    int rotations = 0;
    int currentrotation = 0;
public:
    ~Oshape()
    {

    }
    virtual bool canspawn(int** arr)
    {
        int txcord = 0;
        int tycord = 0;
        int check1 = 0;
        
        for (int i = 0; i < 2 && check1 == 0; i++)
        {
            if (arr[txcord][tycord + i] != 0)
            {
                check1 = 1;
            }
        }
        for (int i = 0; i < 2 && check1== 0; i++)
        {
            if (arr[txcord + 1][tycord + i] != 0)
            {
                check1= 1;
            }
        }
        if (check1 == 1 )
        {
            return 0;
        }
        return 1;
    }
    virtual void reset(int **arr)
    {
        x = 0;
        y = 0;
        xcord = 0;
        ycord = 0;
        rotations = 0;
        currentrotation = 0;

    }
    virtual void drawshape(sf::RenderWindow& window)
    {
        int fx = x;
        int fy = y;
        int tx = fx;
        int ty = fy;
        for (int i = 0; i < 2; i++)
        {
            sf::RectangleShape O(sf::Vector2f(40.f, 40.f));
            O.setPosition(tx, fy);
            O.setOutlineColor(sf::Color::Black);
            O.setFillColor(c);
            O.setOutlineThickness(2.f);
            window.draw(O);
            tx = tx + 40;
        }
        for (int i = 0; i < 2; i++)
        {
            sf::RectangleShape O(sf::Vector2f(40.f, 40.f));
            O.setPosition(fx, fy + 40);
            O.setOutlineColor(sf::Color::Black);
            O.setFillColor(c);
            O.setOutlineThickness(2.f);
            window.draw(O);
            fx = fx + 40;
        }
    }
    virtual bool isTouchedbottom(int **arr)
    {
        xcord = y / 40;
        ycord = x / 40;
        int txcord = (y + 40) / 40;
        int tycord = x / 40;
        int check = 0;
        if (txcord + 1 >= 20)
        {
            check = 1;
        }
        for (int i = 0; i < 2 && check==0; i++)
        {
            if (arr[txcord][tycord+i] != 0)
            {
                check = 1;
            }
        }
        for (int i = 0; i < 2 && check==0; i++)
        {
            if (arr[txcord+1][tycord + i] != 0)
            {
                check = 1;
            }
        }
        if (check == 1)
        {
            for (int i = 0; i < 2 ; i++)
            {
                arr[xcord][ycord + i] = 4;
                
            }
            for (int i = 0; i < 2 ; i++)
            {
                arr[xcord + 1][ycord + i] = 4;
            }
            return 1;
        }
        return 0;
    }
    virtual void rotate(int **arr)
    {
        return;
    }
    virtual void moveLeft(int **arr)
    {
        xcord = y / 40;
        ycord = x / 40;
        int txcord = y / 40;
        int tycord = (x - 40) / 40;
        int check = 0;
        if (isTouchedbottom(arr) == 0)
        {
            for (int i = 0; i < 2 && check == 0; i++)
            {
                if (arr[txcord][tycord + i] != 0)
                {
                    check = 1;
                }
            }
            for (int i = 0; i < 2 && check == 0; i++)
            {
                if (arr[txcord + 1][tycord + i] != 0)
                {
                    check = 1;
                }
            }
            if (x - 40 >= 0 && check==0)
            {
                x = x - 40;
            }
        }
    }
    virtual void moveRight(int **arr)
    {
        xcord = y / 40;
        ycord = x / 40;
        int txcord = y / 40;
        int tycord = (x + 40) / 40;
        int check = 0;
        if (isTouchedbottom(arr) == 0)
        {
            for (int i = 0; i < 2 && check == 0; i++)
            {
                if (arr[txcord][tycord + i] != 0)
                {
                    check = 1;
                }
            }
            for (int i = 0; i < 2 && check == 0; i++)
            {
                if (arr[txcord + 1][tycord + i] != 0)
                {
                    check = 1;
                }
            }
            if (check==0)
            {
                x = x + 40;
            }
        }
    }
    virtual void moveDown(int **arr)
    {
        if (isTouchedbottom(arr) == 0)
        {
            if (y + 120 <= 20 * 40)
            {
                y = y + 40;
            }
        }
    }
};
class Sshape : public tetris
{
    int x = 0;
    int y = 0;
    int xcord = 0;
    int ycord = 0;
    sf::Color c = sf::Color(240, 0, 255);
    int rotations = 0;
    int currentrotation = 0;
public:
    ~Sshape()
    {

    }
    virtual bool canspawn(int** arr)
    {
        int txcord = 0;
        int tycord = 0;
        int check1 = 0;
        int check2 = 0;
        for (int i = 0; i < 2 && check1 == 0; i++)
        {
            if (arr[txcord][tycord + i + 1] != 0)
            {
                check1 = 1;
            }
        }
        for (int i = 0; i < 2 && check1 == 0; i++)
        {
            if (arr[txcord + 1][tycord + i] != 0)
            {
                check1 = 1;
            }
        }
        if (check1 == 1)
        {
            for (int i = 0; i < 2 && check2 == 0; i++)
            {
                if (arr[txcord + i][tycord] != 0)
                {
                    check2 = 1;
                }
            }
            for (int i = 0; i < 2 && check2 == 0; i++)
            {
                if (arr[txcord + 1 + i][tycord + 1] != 0)
                {
                    check2 = 1;
                }
            }
            if (check2 == 0)
            {
                currentrotation = 1;
            }
        }
        if (check1 == 1 && check2 == 1)
        {
            return 0;
        }
        return 1;
    }
    virtual void reset(int **arr)
    {
        x = 0;
        y = 0;
        xcord = 0;
        ycord = 0;
        rotations = 0;
        currentrotation = 0;
    }
    virtual void drawshape(sf::RenderWindow& window) {
        int fx = x;
        int fy = y;
        if (currentrotation == 0)
        {
            int tx = fx + 40;
            for (int i = 0; i < 2; i++)
            {
                sf::RectangleShape S(sf::Vector2f(40.f, 40.f));
                S.setPosition(tx, fy);
                S.setOutlineColor(sf::Color::Black);
                S.setFillColor(c);
                S.setOutlineThickness(2.f);
                window.draw(S);
                tx = tx + 40;

            }
            for (int i = 0; i < 2; i++)
            {
                sf::RectangleShape S(sf::Vector2f(40.f, 40.f));
                S.setPosition(fx, fy + 40);
                S.setOutlineColor(sf::Color::Black);
                S.setFillColor(c);
                S.setOutlineThickness(2.f);
                window.draw(S);
                fx = fx + 40;
            }
        }
        if(currentrotation==1)
        {
            int ty = fy;
            for (int i = 0; i < 2; i++)
            {
                sf::RectangleShape S(sf::Vector2f(40.f, 40.f));
                S.setPosition(fx, ty);
                S.setOutlineColor(sf::Color::Black);
                S.setFillColor(c);
                S.setOutlineThickness(2.f);
                window.draw(S);
                ty = ty + 40;
            }
            for (int i = 0; i < 2; i++)
            {
                sf::RectangleShape S(sf::Vector2f(40.f, 40.f));
                S.setPosition(fx + 40, ty);
                S.setOutlineColor(sf::Color::Black);
                S.setFillColor(c);
                S.setOutlineThickness(2.f);
                window.draw(S);
                ty = fy + 40;
            }

        }
    }
    virtual bool isTouchedbottom(int **arr)
    {
        xcord = y / 40;
        ycord = x / 40;
        int txcord = (y + 40) / 40;
        int tycord = x / 40;
        int check = 0;
        if (currentrotation == 0)
        {   //cr0
            if (txcord + 1 >= 20)
            {
                check = 1;
            }
            for (int i = 0; i < 2 && check == 0; i++)
            {
                if (arr[txcord][tycord + i +1] != 0)
                {
                    check = 1;
                }
            }
            for (int i = 0; i < 2 && check == 0; i++)
            {
                if (arr[txcord+1][tycord + i] != 0)
                {
                    check = 1;
                }
            }
            if (check==1)
            {
                for (int i = 0; i < 2 ; i++)
                {
                    arr[xcord][ycord + i + 1] = 5;
                } 
                for (int i = 0; i < 2 ; i++)
                {
                    arr[xcord + 1][ycord + i] = 5;   
                }
                return 1;
            }
        }
        if(currentrotation==1)
        {
            //cr1
            if (txcord + 2 >= 20)
            {
                check = 1;
            }
            for (int i = 0; i < 2 && check == 0; i++)
            {
                if (arr[txcord+i][tycord] != 0)
                {
                    check = 1;
                }
            }
            for (int i = 0; i < 2 && check == 0; i++)
            {
                if (arr[txcord + 1+i][tycord + 1] != 0)
                {
                    check = 1;
                }
            }
            if (check==1)
            {
                for (int i = 0; i < 2 ; i++)
                {
                    arr[xcord + i][ycord] = 5;
                }
                for (int i = 0; i < 2 ; i++)
                {
                    arr[xcord + 1 + i][ycord + 1] = 5;
                }
                return 1;
            }
        }
        return 0;
    }
    virtual void rotate(int **arr)
    {
        xcord = y / 40;
        ycord = x / 40;
        int check = 0;
        if (isTouchedbottom(arr) == 0)
        {
            if (currentrotation == 0 && ycord<8)
            {
                for (int i = 0; i < 2 && check == 0; i++)
                {
                    if (arr[xcord + i][ycord] != 0)
                    {
                        check = 1;
                    }
                }
                for (int i = 0; i < 2 && check == 0; i++)
                {
                    if (arr[xcord + 1 + i][ycord + 1] != 0)
                    {
                        check = 1;
                    }
                }
                if (check==0)
                {
                    rotations++;
                    currentrotation =rotations%2;
                }
            }
            else if(currentrotation==1)
            {
                for (int i = 0; i < 2 && check == 0; i++)
                {
                    if (arr[xcord][ycord + i + 1] != 0)
                    {
                        check = 1;
                    }
                }
                for (int i = 0; i < 2 && check == 0; i++)
                {
                    if (arr[xcord + 1][ycord + i] != 0)
                    {
                        check = 1;
                    }
                }
                if (check == 0)
                {
                    rotations++;
                    currentrotation = rotations % 2;
                }
            }
        }
    }
    virtual void moveLeft(int **arr)
    {
        xcord = y / 40;
        ycord = x / 40;
        int txcord = y / 40;
        int tycord = (x - 40) / 40;
        int check = 0;
        if (isTouchedbottom(arr) == 0)
        {
            if (currentrotation == 0)
            {
                for (int i = 0; i < 2 && check == 0; i++)
                {
                    if (arr[txcord][tycord + i + 1] != 0)
                    {
                        check = 1;
                    }
                }
                for (int i = 0; i < 2 && check == 0; i++)
                {
                    if (arr[txcord + 1][tycord + i] != 0)
                    {
                        check = 1;
                    }
                }
                if (x - 40 >= 0 && check==0)
                {
                    x = x - 40;
                }
            }
            if (currentrotation == 1)
            {
                for (int i = 0; i < 2 && check == 0; i++)
                {
                    if (arr[txcord + i][tycord] != 0)
                    {
                        check = 1;
                    }
                }
                for (int i = 0; i < 2 && check == 0; i++)
                {
                    if (arr[txcord + 1 + i][tycord + 1] != 0)
                    {
                        check = 1;
                    }
                }
                if (x - 40 >= 0 && check == 0)
                {
                    x = x - 40;
                }
            }
        }
    }
    virtual void moveRight(int **arr)
    {
        xcord = y / 40;
        ycord = x / 40;
        int txcord = y / 40;
        int tycord = (x + 40) / 40;
        int check = 0;
        if (isTouchedbottom(arr) == 0)
        {
            if (currentrotation == 0)
            {
                for (int i = 0; i < 2 && check == 0; i++)
                {
                    if (arr[txcord][tycord + i + 1] != 0)
                    {
                        check = 1;
                    }
                }
                for (int i = 0; i < 2 && check == 0; i++)
                {
                    if (arr[txcord + 1][tycord + i] != 0)
                    {
                        check = 1;
                    }
                }
                if (check==0)
                {
                    x = x + 40;
                }
            }
            if(currentrotation==1)
            {
                for (int i = 0; i < 2 && check == 0; i++)
                {
                    if (arr[txcord + i][tycord] != 0)
                    {
                        check = 1;
                    }
                }
                for (int i = 0; i < 2 && check == 0; i++)
                {
                    if (arr[txcord + 1 + i][tycord + 1] != 0)
                    {
                        check = 1;
                    }
                }
                if (check == 0)
                {
                    x = x + 40;
                }
            }
        }
    }
    virtual void moveDown(int **arr)
    {
        if (isTouchedbottom(arr) == 0)
        {
            if (currentrotation == 0)
            {
                if (y + 120 <= 20 * 40)
                {
                    y = y + 40;
                }
            }
            else
            {
                if (y + 160 <= 20 * 40)
                {
                    y = y + 40;
                }
            }
        }
    }
};
class Tshape : public tetris
{
    int x = 0;
    int y = 0;
    int xcord = 0;
    int ycord = 0;
    sf::Color c = sf::Color(0, 255, 255);
    int rotations = 0;
    int currentrotation = 0;
public:
    ~Tshape()
    {

    }
    virtual bool canspawn(int** arr)
    {
        int txcord = 0;
        int tycord = 0;
        int check1 = 0;
        int check2 = 0;
        if (arr[txcord + 1][tycord + 1] != 0)
        {
            check1 = 1;
        }
        for (int i = 0; i < 3 && check1 == 0; i++)
        {
            if (arr[txcord][tycord + i] != 0)
            {
                check1 = 1;
            }
        }
        if (check1 == 1)
        {
            if (arr[txcord + 1][tycord] != 0)
            {
                check2 = 1;
            }
            for (int i = 0; i < 3 && check2 == 0; i++)
            {
                if (arr[txcord + i][tycord + 1] != 0)
                {
                    check2 = 1;
                }
            }
            if (check2 == 0)
            {
                currentrotation = 1;
            }
        }
        if (check1 == 1 && check2 == 1)
        {
            return 0;
        }
        return 1;
    }
    virtual void reset(int **arr)
    {
        x = 0;
        y = 0;
        xcord = 0;
        ycord = 0;
        rotations = 0;
        currentrotation = 0;
    }
    virtual void drawshape(sf::RenderWindow& window)
    {
        int fx = x;
        int fy = y;
        if (currentrotation == 0)
        {
            sf::RectangleShape T(sf::Vector2f(40.f, 40.f));
            T.setPosition(fx + 40, fy + 40);
            T.setOutlineColor(sf::Color::Black);
            T.setFillColor(c);
            T.setOutlineThickness(2.f);
            window.draw(T);
            for (int i = 0; i < 3; i++)
            {
                sf::RectangleShape T(sf::Vector2f(40.f, 40.f));
                T.setPosition(fx, fy);
                T.setOutlineColor(sf::Color::Black);
                T.setFillColor(c);
                T.setOutlineThickness(2.f);
                window.draw(T);
                fx = fx + 40;
            }

        }
        else if (currentrotation == 1)
        {
            sf::RectangleShape T(sf::Vector2f(40.f, 40.f));
            T.setPosition(fx, fy + 40);
            T.setOutlineColor(sf::Color::Black);
            T.setFillColor(c);
            T.setOutlineThickness(2.f);
            window.draw(T);
            for (int i = 0; i < 3; i++)
            {
                sf::RectangleShape T(sf::Vector2f(40.f, 40.f));
                T.setPosition(fx + 40, fy);
                T.setOutlineColor(sf::Color::Black);
                T.setFillColor(c);
                T.setOutlineThickness(2.f);
                window.draw(T);
                fy = fy + 40;
            }
        }
        else if (currentrotation == 2)
        {
            sf::RectangleShape T(sf::Vector2f(40.f, 40.f));
            T.setPosition(fx + 40, fy);
            T.setOutlineColor(sf::Color::Black);
            T.setFillColor(c);
            T.setOutlineThickness(2.f);
            window.draw(T);
            for (int i = 0; i < 3; i++)
            {
                sf::RectangleShape T(sf::Vector2f(40.f, 40.f));
                T.setPosition(fx, fy + 40);
                T.setOutlineColor(sf::Color::Black);
                T.setFillColor(c);
                T.setOutlineThickness(2.f);
                window.draw(T);
                fx = fx + 40;
            }
        }
        else
        {
            sf::RectangleShape T(sf::Vector2f(40.f, 40.f));
            T.setPosition(fx + 40, fy + 40);
            T.setOutlineColor(sf::Color::Black);
            T.setFillColor(c);
            T.setOutlineThickness(2.f);
            window.draw(T);
            for (int i = 0; i < 3; i++)
            {
                sf::RectangleShape T(sf::Vector2f(40.f, 40.f));
                T.setPosition(fx, fy);
                T.setOutlineColor(sf::Color::Black);
                T.setFillColor(c);
                T.setOutlineThickness(2.f);
                window.draw(T);
                fy = fy + 40;
            }
        }
    }
    virtual bool isTouchedbottom(int **arr)
    {
        xcord = y / 40;
        ycord = x / 40;
        int txcord = (y + 40) / 40;
        int tycord = x / 40;
        int check = 0;
        if (currentrotation == 0)
        {//cr0
            if (txcord + 1 >= 20)
            {
                check = 1;
            }
            if (check == 0)
            {
                if (arr[txcord + 1][tycord + 1] != 0)
                {
                    check = 1;
                }
            }
            for (int i = 0; i < 3 && check==0; i++)
            {
                if (arr[txcord][tycord + i] != 0)
                {
                    check = 1;
                }
            }
            if (check == 1)
            {
                arr[xcord + 1][ycord + 1] = 6;
                for (int i = 0; i < 3 ; i++)
                {
                    arr[xcord][ycord + i] = 6;
                }
                return 1;
            }
            
        }
        else if(currentrotation==1)
        {//cr1
            if (txcord + 2 >= 20)
            {
                check = 1;
            }
            if (check == 0)
            {
                if (arr[txcord + 1][tycord] != 0)
                {
                    check = 1;
                }
            }
            for (int i = 0; i < 3 && check==0; i++)
            {
                if (arr[txcord + i][tycord + 1] != 0)
                {
                    check = 1;
                }
            }
            if (check == 1)
            {
                arr[xcord + 1][ycord] = 6;
                for (int i = 0; i < 3; i++)
                {
                    arr[xcord+i][ycord + 1] = 6;
                }
                return 1;
            }
        }
        else if (currentrotation == 2)
        {//cr2
            if (txcord + 1 >= 20)
            {
                check = 1;
            }
            if (check == 0)
            {
                if (arr[txcord][tycord+1] != 0)
                {
                    check = 1;
                }
            }
            for (int i = 0; i < 3 && check == 0; i++)
            {
                if (arr[txcord+1][tycord + i] != 0)
                {
                    check = 1;
                }
            }
            if (check == 1)
            {
                arr[xcord][ycord+1] = 6;
                for (int i = 0; i < 3; i++)
                {
                    arr[xcord + 1][ycord + i] = 6;
                }
                return 1;
            }
        }
        else if (currentrotation == 3)
        {//cr3
            if (txcord + 2 >= 20)
            {
                check = 1;
            }
            if (check == 0)
            {
                if (arr[txcord+1][tycord + 1] != 0)
                {
                    check = 1;
                }
            }
            for (int i = 0; i < 3 && check == 0; i++)
            {
                if (arr[txcord+i][tycord] != 0)
                {
                    check = 1;
                }
            }
            if (check == 1)
            {
                arr[xcord+1][ycord + 1] = 6;
                for (int i = 0; i < 3; i++)
                {
                    arr[xcord + i][ycord] = 6;
                }
                return 1;
            }
        }
        return 0;
    }
    virtual void rotate(int **arr)
    {
        xcord = y / 40;
        ycord = x / 40;
        int check = 0;
        if (isTouchedbottom(arr) == 0)
        {
            if (currentrotation == 1 && ycord<8)
            {
                //cr2
                if (arr[xcord][ycord + 1] != 0)
                {
                    check = 1;
                }
                for (int i = 0; i < 3 && check == 0; i++)
                {
                    if (arr[xcord + 1][ycord + i] != 0)
                    {
                        check = 1;
                    }
                }
                if (check == 0)
                {
                    rotations++;
                    currentrotation = rotations % 4;
                }
            }
            else if (currentrotation == 3 && ycord<8)
            {
                //cr0
                if (arr[xcord + 1][ycord + 1] != 0)
                {
                    check = 1;
                }
                for (int i = 0; i < 3 && check == 0; i++)
                {
                    if (arr[xcord][ycord + i] != 0)
                    {
                        check = 1;
                    }
                }
                if (check == 0)
                {
                    rotations++;
                    currentrotation = rotations % 4;
                }
            }
            else if(currentrotation==0 || currentrotation==2)
            {
                rotations++;
                currentrotation = rotations % 4;
            }
        }
    }
    virtual void moveLeft(int **arr)
    {
        xcord = y / 40;
        ycord = x / 40;
        int txcord = y / 40;
        int tycord = (x - 40) / 40;
        int check = 0;
        if (isTouchedbottom(arr) == 0)
        {
            if (currentrotation == 0)
            {
                //cr0
                if (arr[txcord + 1][tycord + 1] != 0)
                {
                    check = 1;
                }
                for (int i = 0; i < 3 && check == 0; i++)
                {
                    if (arr[txcord][tycord + i] != 0)
                    {
                        check = 1;
                    }
                }
                if (x - 40 >= 0 && check==0)
                {
                    x = x - 40;
                }
            }
            if(currentrotation==1)
            {
                //cr1
                if (check == 0)
                {
                    if (arr[txcord + 1][tycord] != 0)
                    {
                        check = 1;
                    }
                }
                for (int i = 0; i < 3; i++)
                {
                    if (arr[txcord + i][tycord + 1] != 0)
                    {
                        check = 1;
                    }
                }
                if (x - 40 >= 0 && check == 0)
                {
                    x = x - 40;
                }
            }
            if (currentrotation == 2)
            {
                //cr2
                if (arr[txcord][tycord + 1] != 0)
                {
                    check = 1;
                }
                for (int i = 0; i < 3 && check == 0; i++)
                {
                    if (arr[txcord + 1][tycord + i] != 0)
                    {
                        check = 1;
                    }
                }
                if (x - 40 >= 0 && check == 0)
                {
                    x = x - 40;
                }
            }
            if (currentrotation == 3)
            {
                if (arr[txcord + 1][tycord + 1] != 0)
                {
                    check = 1;
                }
                for (int i = 0; i < 3 && check == 0; i++)
                {
                    if (arr[txcord + i][tycord] != 0)
                    {
                        check = 1;
                    }
                }
                if (x - 40 >= 0 && check == 0)
                {
                    x = x - 40;
                }
            }    
        }
    }
    virtual void moveRight(int **arr)
    {
        xcord = y / 40;
        ycord = x / 40;
        int txcord = y / 40;
        int tycord = (x + 40) / 40;
        int check = 0;
        if (isTouchedbottom(arr) == 0)
        {
            if (currentrotation == 0)
            {
                //cr0
                if (arr[txcord + 1][tycord + 1] != 0)
                {
                    check = 1;
                }
                for (int i = 0; i < 3 && check == 0; i++)
                {
                    if (arr[txcord][tycord + i] != 0)
                    {
                        check = 1;
                    }
                }
                if (check == 0)
                {
                    x = x + 40;
                }
            }
            if (currentrotation == 1)
            {
                //cr1
                if (check == 0)
                {
                    if (arr[txcord + 1][tycord] != 0)
                    {
                        check = 1;
                    }
                }
                for (int i = 0; i < 3; i++)
                {
                    if (arr[txcord + i][tycord + 1] != 0)
                    {
                        check = 1;
                    }
                }
                if (check == 0)
                {
                    x = x + 40;
                }
            }
            if (currentrotation == 2)
            {
                //cr2
                if (arr[txcord][tycord + 1] != 0)
                {
                    check = 1;
                }
                for (int i = 0; i < 3 && check == 0; i++)
                {
                    if (arr[txcord + 1][tycord + i] != 0)
                    {
                        check = 1;
                    }
                }
                if (check == 0)
                {
                    x = x + 40;
                }
            }
            if (currentrotation == 3)
            {
                if (arr[txcord + 1][tycord + 1] != 0)
                {
                    check = 1;
                }
                for (int i = 0; i < 3 && check == 0; i++)
                {
                    if (arr[txcord + i][tycord] != 0)
                    {
                        check = 1;
                    }
                }
                if (check == 0)
                {
                    x = x + 40;
                }
            }
        }
    }
    virtual void moveDown(int **arr)
    {
        if (isTouchedbottom(arr) == 0)
        {
            if (currentrotation == 0 || currentrotation == 2)
            {
                if (y + 120 <= 20 * 40)
                {
                    y = y + 40;
                }
            }
            else
            {
                if (y + 160 <= 20 * 40)
                {
                    y = y + 40;
                }
            }
        }
    }
};
class Zshape : public tetris
{
    int x = 0;
    int y = 0;
    int xcord = 0;
    int ycord = 0;
    sf::Color c = sf::Color(255, 255, 0);
    int rotations = 0;
    int currentrotation = 0;
public:
    ~Zshape()
    {

    }
    virtual bool canspawn(int** arr)
    {
        int txcord = 0;
        int tycord = 0;
        int check1 = 0;
        int check2 = 0;
        for (int i = 0; i < 2 && check1 == 0; i++)
        {
            if (arr[txcord][tycord + i] != 0)
            {
                check1 = 1;
            }
        }
        for (int i = 0; i < 2 && check1 == 0; i++)
        {
            if (arr[txcord + 1][tycord + i + 1] != 0)
            {
                check1 = 1;
            }
        }
        if (check1 == 1)
        {
            for (int i = 0; i < 2 && check2 == 0; i++)
            {
                if (arr[txcord + 1 + i][tycord] != 0)
                {
                    check2 = 1;
                }
            }
            for (int i = 0; i < 2 && check2 == 0; i++)
            {
                if (arr[txcord + i][tycord + 1] != 0)
                {
                    check2 = 1;
                }
            }
            
            if (check2 == 0)
            {
                currentrotation = 1;
            }
        }
        if (check1 == 1 && check2 == 1)
        {
            return 0;
        }
        return 1;
    }
    virtual void reset(int **arr)
    {
        x = 0;
        y = 0;
        xcord = 0;
        ycord = 0;
        rotations = 0;
        currentrotation = 0;
    }
    virtual void drawshape(sf::RenderWindow& window)
    {
        int fx = x;
        int fy = y;
        if (currentrotation == 0)
        {
            int tx = fx;
            for (int i = 0; i < 2; i++)
            {
                sf::RectangleShape Z(sf::Vector2f(40.f, 40.f));
                Z.setPosition(tx, fy);
                Z.setOutlineColor(sf::Color::Black);
                Z.setFillColor(c);
                Z.setOutlineThickness(2.f);
                window.draw(Z);
                tx = tx + 40;
            }
            int t2x = fx + 40;
            for (int i = 0; i < 2; i++)
            {
                sf::RectangleShape Z(sf::Vector2f(40.f, 40.f));
                Z.setPosition(t2x, fy + 40);
                Z.setOutlineColor(sf::Color::Black);
                Z.setFillColor(c);
                Z.setOutlineThickness(2.f);
                window.draw(Z);
                t2x = t2x + 40;
            }

        }
        else if (currentrotation == 1)
        {
            int ty = fy + 40;
            for (int i = 0; i < 2; i++)
            {
                sf::RectangleShape Z(sf::Vector2f(40.f, 40.f));
                Z.setPosition(fx, ty);
                Z.setOutlineColor(sf::Color::Black);
                Z.setFillColor(c);
                Z.setOutlineThickness(2.f);
                window.draw(Z);
                ty = ty + 40;
            }
            for (int i = 0; i < 2; i++)
            {
                sf::RectangleShape Z(sf::Vector2f(40.f, 40.f));
                Z.setPosition(fx + 40, fy);
                Z.setOutlineColor(sf::Color::Black);
                Z.setFillColor(c);
                Z.setOutlineThickness(2.f);
                window.draw(Z);
                fy = fy + 40;
            }
        }
    }
    virtual bool isTouchedbottom(int **arr)
    {
        xcord = y / 40;
        ycord = x / 40;
        int txcord = (y + 40) / 40;
        int tycord = x / 40;
        int check = 0;
        if (currentrotation == 0)
        {
            if (txcord + 1 >= 20)
            {
                check = 1;
            }
            for (int i = 0; i < 2 && check==0; i++)
            {
                if (arr[txcord][tycord + i] != 0)
                {
                    check = 1;
                }
            }
            for (int i = 0; i < 2 && check == 0; i++)
            {
                if (arr[txcord+1][tycord + i+1] != 0)
                {
                    check = 1;
                }
            }
            if (check == 1)
            {
                for (int i = 0; i < 2 ; i++)
                {
                    arr[xcord][ycord + i] = 7;
                }
                for (int i = 0; i < 2 ; i++)
                {
                    arr[xcord + 1][ycord + i + 1] = 7;
                }
                return 1;

            }

        }
        else if(currentrotation==1)
        {
            if (txcord + 2 >= 20)
            {
                check = 1;
            }
            for (int i = 0; i < 2 && check == 0; i++)
            {
                if (arr[txcord+1+i][tycord] != 0)
                {
                    check = 1;
                }
            }
            for (int i = 0; i < 2 && check == 0; i++)
            {
                if (arr[txcord+i][tycord  + 1] != 0)
                {
                    check = 1;
                }
            }
            if (check == 1)
            {
                    for (int i = 0; i < 2; i++)
                {
                    arr[xcord+1+i][ycord] = 7;
                }
                for (int i = 0; i < 2; i++)
                {
                    arr[xcord + i][ycord  + 1] = 7;
                }
                return 1;

            }
        }
        return 0;
    }
    virtual void rotate(int **arr)
    {
        xcord = y / 40;
        ycord = x / 40;
        int check = 0;
        if (isTouchedbottom(arr) == 0)
        {
            if (currentrotation == 0)
            {
                for (int i = 0; i < 2 && check == 0; i++)
                {
                    if (arr[xcord + 1 + i][ycord] != 0)
                    {
                        check = 1;
                    }
                }
                for (int i = 0; i < 2 && check == 0; i++)
                {
                    if (arr[xcord + i][ycord + 1] != 0)
                    {
                        check = 1;
                    }
                }
                if (check == 0)
                {
                    rotations++;
                    currentrotation = rotations % 2;
                }
                
            }
            else if(currentrotation==1 && ycord<8)
            {
                for (int i = 0; i < 2 && check == 0; i++)
                {
                    if (arr[xcord][ycord + i] != 0)
                    {
                        check = 1;
                    }
                }
                for (int i = 0; i < 2 && check == 0; i++)
                {
                    if (arr[xcord + 1][ycord + i + 1] != 0)
                    {
                        check = 1;
                    }
                }
                if (check == 0)
                {
                    rotations++;
                    currentrotation = rotations % 2;
                }
            }
        }
    }
    virtual void moveLeft(int **arr)
    {
        xcord = y / 40;
        ycord = x / 40;
        int txcord = y / 40;
        int tycord = (x - 40) / 40;
        int check = 0;
        if (isTouchedbottom(arr) == 0)
        {
            if (currentrotation == 0)
            {
                for (int i = 0; i < 2 && check == 0; i++)
                {
                    if (arr[txcord][tycord + i] != 0)
                    {
                        check = 1;
                    }
                }
                for (int i = 0; i < 2 && check == 0; i++)
                {
                    if (arr[txcord + 1][tycord + i + 1] != 0)
                    {
                        check = 1;
                    }
                }
                if (x - 40 >= 0 && check==0)
                {
                    x = x - 40;
                }
            }
            else if (currentrotation == 1)
            {
                for (int i = 0; i < 2 && check == 0; i++)
                {
                    if (arr[txcord + 1 + i][tycord] != 0)
                    {
                        check = 1;
                    }
                }
                for (int i = 0; i < 2 && check == 0; i++)
                {
                    if (arr[txcord + i][tycord + 1] != 0)
                    {
                        check = 1;
                    }
                }
                if (x - 40 >= 0 && check == 0)
                {
                    x = x - 40;
                }
            }
        }
    }
    virtual void moveRight(int **arr)
    {
        xcord = y / 40;
        ycord = x / 40;
        int txcord = y / 40;
        int tycord = (x + 40) / 40;
        int check = 0;
        if (isTouchedbottom(arr) == 0)
        {
            if (currentrotation == 0)
            {
                for (int i = 0; i < 2 && check == 0; i++)
                {
                    if (arr[txcord][tycord + i] != 0)
                    {
                        check = 1;
                    }
                }
                for (int i = 0; i < 2 && check == 0; i++)
                {
                    if (arr[txcord + 1][tycord + i + 1] != 0)
                    {
                        check = 1;
                    }
                }
                if (check == 0)
                {
                    x = x + 40;
                }
            }
            else if(currentrotation==1)
            {
                for (int i = 0; i < 2 && check == 0; i++)
                {
                    if (arr[txcord + 1 + i][tycord] != 0)
                    {
                        check = 1;
                    }
                }
                for (int i = 0; i < 2 && check == 0; i++)
                {
                    if (arr[txcord + i][tycord + 1] != 0)
                    {
                        check = 1;
                    }
                }
                if (check == 0)
                {
                    x = x + 40;
                }
            }
        }
    }
    virtual void moveDown(int **arr)
    {
        if (isTouchedbottom(arr) == 0)
        {
            if (currentrotation == 0)
            {
                if (y + 120 <= 20 * 40)
                {
                    y = y + 40;
                }
            }
            else
            {
                if (y + 160 <= 20 * 40)
                {
                    y = y + 40;
                }
            }
        }
    }
};
class game {
private:
    string name;
    int tlines = 0;
    int lvl = 1;
    int score = 0;
    tetris* b[7];
    int **arr ;
    well w;
public:
    game()
    {
        arr = new int* [20];
        for (int i = 0; i < 20; i++)
        {
            arr[i] = new int[10];
        }
        for (int i = 0; i < 20; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                arr[i][j] = 0;
            }
        }
        b[0] = new Ishape;
        b[1] = new Jshape;
        b[2] = new Lshape;
        b[3] = new Oshape;
        b[4] = new Sshape;
        b[5] = new Tshape;
        b[6] = new Zshape;
    }
    void play()
    {
        sf::RectangleShape rectangle1(sf::Vector2f(500.f, 100.f));
        rectangle1.setFillColor(sf::Color::Transparent);
        rectangle1.setOutlineThickness(5.f);
        rectangle1.setOutlineColor(sf::Color::White);
        rectangle1.setPosition(1000, 100);
        sf::RectangleShape rectangle2(sf::Vector2f(500.f, 100.f));
        rectangle2.setFillColor(sf::Color::Transparent);
        rectangle2.setOutlineThickness(5.f);
        rectangle2.setOutlineColor(sf::Color::White);
        rectangle2.setPosition(1000, 300);
        sf::RectangleShape rectangle3(sf::Vector2f(500.f, 100.f));
        rectangle3.setFillColor(sf::Color::Transparent);
        rectangle3.setOutlineThickness(5.f);
        rectangle3.setOutlineColor(sf::Color::White);
        rectangle3.setPosition(1000, 500);
        sf::RectangleShape rectangle4(sf::Vector2f(500.f, 100.f));
        rectangle4.setFillColor(sf::Color::Transparent);
        rectangle4.setOutlineThickness(5.f);
        rectangle4.setOutlineColor(sf::Color::White);
        rectangle4.setPosition(1000, 700);

        sf::Font font;
        font.loadFromFile("arial.ttf");
        sf::Text lines, levels, names, scores;
        lines.setFont(font); levels.setFont(font); names.setFont(font); scores.setFont(font);
        lines.setCharacterSize(20); levels.setCharacterSize(20); names.setCharacterSize(20); scores.setCharacterSize(20);
        lines.setStyle(sf::Text::Bold); levels.setStyle(sf::Text::Bold); names.setStyle(sf::Text::Bold); scores.setStyle(sf::Text::Bold);
        lines.setFillColor(sf::Color::White); levels.setFillColor(sf::Color::White); names.setFillColor(sf::Color::White); scores.setFillColor(sf::Color::White);
        lines.setPosition(1000, 100); levels.setPosition(1000, 300); names.setPosition(1000, 500); scores.setPosition(1000, 700);
        sf::Vector2<float> lines_scale(2.f, 2.f);
        lines.setScale(lines_scale); levels.setScale(lines_scale); names.setScale(lines_scale); scores.setScale(lines_scale);
      
        srand(time(NULL));
        sf::Clock clock;
        sf::Time timeSinceLastUpdate = sf::Time::Zero;
        sf::Time timePerFrame = sf::seconds(1*pow(0.9,lvl));
        sf::RenderWindow window(sf::VideoMode(1920, 1080), "Tetris");
        int num = rand() % 7;
        int gamerun = 1;
        while (window.isOpen() && gamerun == 1)
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Up) {
                        b[num]->rotate(arr);
                    }
                    if (event.key.code == sf::Keyboard::Left) {
                        b[num]->moveLeft(arr);
                    }
                    if (event.key.code == sf::Keyboard::Right) {
                        b[num]->moveRight(arr);
                    }
                    if (event.key.code == sf::Keyboard::Down) {
                        b[num]->moveDown(arr);
                    }
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        gamerun = 0;
                    }
                }

            }
            timeSinceLastUpdate += clock.restart();
            if (timeSinceLastUpdate >= timePerFrame)
            {
                timeSinceLastUpdate -= timePerFrame;
                b[num]->moveDown(arr);
            }
            if (b[num]->isTouchedbottom(arr) == 1)
            {
                b[num]->reset(arr);
                w.islinecomp(arr, score, lvl,tlines);
                num = rand() % 7;
                if (b[num]->canspawn(arr) == 0)
                {
                    gamerun = 0;
                }
            }
            lines.setString("LINES: " + to_string(tlines)); levels.setString("LEVEL: " + to_string(lvl)); names.setString("NAME: " + name); scores.setString("SCORE: " + to_string(score));
            window.clear();
            window.draw(lines); window.draw(levels); window.draw(names); window.draw(scores);
            window.draw(rectangle1); window.draw(rectangle2); window.draw(rectangle3); window.draw(rectangle4);
            w.drawBoard(window, arr);
            b[num]->drawshape(window);
            window.display();
        }
    }
    void setname(string n)
    {
        name=n;
    }
    int getscore()
    {
        return score;
    }
    ~game()
    {
        for (int i = 0; i < 20; i++)
        {
            delete[]arr[i];
        }
        for (int i = 0; i < 7; i++)
            delete b[i];
    }
};

int main()
{
    
    cout << "Enter name :";
    string name;
    getline(cin, name);
    game g;
    g.setname(name);
    g.play();
    int score = g.getscore();
      int count = 0;
    string namelist[5] = {" "};
    int scorelist[5] = {0};
    ifstream read;
    read.open("Score.txt");
    while (!read.eof())
    {
        for (int i = 0; i < 5; i++)
        {
            read >> namelist[i] >> scorelist[i];
        }
    }
    read.close();
    for (int i = 0; i < 5 - 1; i++) {
        for (int j = 0; j < 5 - i - 1; j++) {
            if (scorelist[j] < scorelist[j + 1]) 
            {
                swap(scorelist[j], scorelist[j+1]);
                swap(namelist[j], namelist[j+1]);
            }
        }
    }

    if (score > scorelist[4])
    {
        scorelist[4] = score;
        namelist[4] = name;
    }

    ofstream write;
    write.open("SCORE.txt");
    for (int i = 0; i < 5; i++)
    {
        write << namelist[i] << " " << scorelist[i] << endl;
        cout << namelist[i] << " has scored : " << scorelist[i] << endl;
    }
    write.close();

    sf::Font font;
    font.loadFromFile("arial.ttf");

    sf::Text Title;
    Title.setFont(font);
    Title.setCharacterSize(40);
    Title.setStyle(sf::Text::Bold);
    Title.setFillColor(sf::Color::White);
    Title.setPosition(500, 100);
    sf::Vector2<float> names_scale(2.f, 2.f);
    Title.setScale(names_scale);

    sf::Text names, scores;
    names.setFont(font), scores.setFont(font);
    names.setCharacterSize(20), scores.setCharacterSize(20);
    names.setStyle(sf::Text::Bold), scores.setStyle(sf::Text::Bold);
    names.setFillColor(sf::Color::White), scores.setFillColor(sf::Color::White);
    names.setPosition(500, 300), scores.setPosition(700, 300);

    sf::Vector2<float> scores_scale(2.f, 2.f);
    names.setScale(names_scale), scores.setScale(scores_scale);

    sf::Text names2, scores2;
    names2.setFont(font), scores2.setFont(font);
    names2.setCharacterSize(20), scores2.setCharacterSize(20);
    names2.setStyle(sf::Text::Bold), scores2.setStyle(sf::Text::Bold);
    names2.setFillColor(sf::Color::White), scores2.setFillColor(sf::Color::White);
    names2.setPosition(500, 400), scores2.setPosition(700, 400);
    names2.setScale(names_scale), scores2.setScale(scores_scale);

    sf::Text names3, scores3;
    names3.setFont(font), scores3.setFont(font);
    names3.setCharacterSize(20), scores3.setCharacterSize(20);
    names3.setStyle(sf::Text::Bold), scores3.setStyle(sf::Text::Bold);
    names3.setFillColor(sf::Color::White), scores3.setFillColor(sf::Color::White);
    names3.setPosition(500, 500), scores3.setPosition(700, 500);
    names3.setScale(names_scale), scores3.setScale(scores_scale);

    sf::Text names4, scores4;
    names4.setFont(font), scores4.setFont(font);
    names4.setCharacterSize(20), scores4.setCharacterSize(20);
    names4.setStyle(sf::Text::Bold), scores4.setStyle(sf::Text::Bold);
    names4.setFillColor(sf::Color::White), scores4.setFillColor(sf::Color::White);
    names4.setPosition(500, 600), scores4.setPosition(700, 600);
    names4.setScale(names_scale), scores4.setScale(scores_scale);

    sf::Text names5, scores5;
    names5.setFont(font), scores5.setFont(font);
    names5.setCharacterSize(20), scores5.setCharacterSize(20);
    names5.setStyle(sf::Text::Bold), scores5.setStyle(sf::Text::Bold);
    names5.setFillColor(sf::Color::White), scores5.setFillColor(sf::Color::White);
    names5.setPosition(500, 700), scores5.setPosition(700, 700);
    names5.setScale(names_scale), scores5.setScale(scores_scale);

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "ScoreBoard");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        string lb = "The Top 5 ";
        Title.setString(lb);
        names.setString(namelist[0]); scores.setString( to_string(scorelist[0]));
        names2.setString(namelist[1]); scores2.setString(to_string(scorelist[1]));
        names3.setString(namelist[2]); scores3.setString(to_string(scorelist[2]));
        names4.setString(namelist[3]); scores4.setString(to_string(scorelist[3]));
        names5.setString( namelist[4]); scores5.setString(to_string(scorelist[4]));
        window.draw(Title);
        window.draw(names), window.draw(names2),window.draw(names3), window.draw(names4), window.draw(names5);
        window.draw(scores), window.draw(scores2), window.draw(scores3), window.draw(scores4), window.draw(scores5);
        window.display();
    }
    return 0;
}
