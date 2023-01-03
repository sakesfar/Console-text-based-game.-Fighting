#include <iostream>
#include<string>
#include<vector>
#include<cassert>
#include<array>
#include <random> // for std::mt19937
#include <ctime> // for std::time

namespace MyRandom
{
    // Initialize our mersenne twister with a random seed based on the clock (once at system startup)
    std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
}

int getRandomNumber(int min, int max)
{
    std::uniform_int_distribution die{ min, max }; // we can create a distribution in any function that needs it
    return die(MyRandom::mersenne); // and then generate a random number from our global generator
}

class Location
{
private:
    int m_x;
    int m_y;
public:
    Location(int x = 0, int y = 0) : m_x{ x }, m_y{ y } {}
    void move(int y) { m_y += y;  }
    int getLocationX() { return m_x; }
    int getLocationY() { return m_y; }

    friend std::ostream& operator<<(std::ostream& out, Location& loc)
    {
        out << '(' << loc.m_x << ',' << loc.m_y << ')\n';
        return out;
    }
};
class Creature :public Location
{
protected:
    std::string m_name;
    int m_health;
    int m_power;

public:
    Creature() = default;
    Creature(const std::string_view name, int health, int power, int x = 0, int y = 0) :m_name{ name }, m_health{ health }, m_power{ power }, Location(x, y) {}
    void healthReduced(int x) { m_health -= x; }
    std::string getName() const { return m_name; }
    int getHealth() { return m_health; }
    int getPower() { return m_power; }

};

class Monster :public Creature
{
private:
    static const Creature& getDefaultCreature()
    {
        static const std::array< Creature, 5> monsterBox{ {
             {"Orc", 4,1,1,2},
             {"Skeleton",4,1,1,3},
             {"Gremlins",6,2,1,4},
             {"Minotaur",10,5,1,8},
             {"The Great Dragon",18,8,1,10},
         } };

        return monsterBox.at(static_cast<std::size_t>(getRandomNumber(0, 4)));
    }

public:

    Monster(std::string name, int h, int p, int x, int y) :Creature(name,h,p,x,y) {}


};

class Player :public Creature
{
public:
    Player(std::string name, int h = 6, int p = 3, int x = 1, int y = 0) : Creature(name, h, p, x, y) {}
    void levelUp(int health, int power)
    {
        m_health += health;
        m_power += power;
    }
};

bool PlayerAttacks(Player& arsen, Monster& enemy)

{
    Player newArsen{ arsen };
    while (true)
    {
        std::cout << "Attacking monster!\n";
        enemy.healthReduced(arsen.getPower());
        std::cout << "Monster is still alive and attacks you back!\n";
        arsen.healthReduced(enemy.getPower());
        if (arsen.getHealth() <= 0)
        {
            
            return false;
        }
        else if (enemy.getHealth() <= 0)
        {
            arsen.levelUp(2, 2);
            std::cout << "You killed the monster and upgraded your skills. Your health: " << arsen.getHealth() << '\n';
            break;
        }

    }



}

bool gameStart()
{
    std::string name;
    std::cout << "Enter your name: ";
    std::cin >> name;
    Player arsen{ name };
    std::cout << arsen.getName() << ", your job is to reach top of the Tower 2 alive. Find the secret door to tower 2.Good luck!\n";
    std::cout << "Right now you are on tower: " << arsen.getLocationX() << " and level:" << arsen.getLocationY() << '\n';

    while (true)
    {
        Monster enemy1{ "Orc", 4,1,1,2 };
        Monster enemy2{ "Skeleton",4,1,1,3 };
        Monster enemy3{ "Gremlins",6,2,1,4 };
        Monster enemy4{ "Minotaur",10,5,1,8 };
        Monster enemy5{ "The Great Dragon",18,8,1,10 };
        int one{ enemy1.getLocationY() };
        int two{ enemy2.getLocationY() };
        int three{ enemy3.getLocationY() };
        int four{ enemy4.getLocationY() };
        int five{ enemy5.getLocationY() };

        for (int i{ 1 }; i < 12; ++i)
        {
            arsen.move(1);
            std::cout << "You have ascended to level " << arsen.getLocationY();
            if (one == i)
            {
                std::cout << " and you have encountered " << enemy1.getName() << '\n';
                char choice{};
                std::cout << "Fight or run? (f/r): ";
                std::cin >> choice;
                switch (choice)
                {
                case 'f':
                {
                    PlayerAttacks(arsen, enemy1);
                    break;
                }
                case'r':
                {
                    std::cout << "\nYou run away like a coward\n";
                    break;
                }
                }
            }

            else if (two == i)
            {
                std::cout << " and you have encountered " << enemy2.getName() << '\n';
                char choice{};
                std::cout << "Fight or run? (f/r): ";
                std::cin >> choice;
                switch (choice)
                {
                case 'f':
                {
                    PlayerAttacks(arsen, enemy2);
                    break;
                }
                case'r':
                {
                    std::cout << "\nYou run away like a coward\n";
                    break;
                }
                }
            }

            else if (three == i)
            {
                std::cout << " and you have encountered " << enemy3.getName() << '\n';
                char choice{};
                std::cout << "Fight or run? (f/r): ";
                std::cin >> choice;
                switch (choice)
                {
                case 'f':
                {
                    PlayerAttacks(arsen, enemy3);
                    break;
                }
                case'r':
                {
                    std::cout << "\nYou run away like a coward\n";
                    break;
                }
                }
            }

            else if (four == i)
            {
                std::cout << " and you have encountered " << enemy4.getName() << '\n';
                char choice{};
                std::cout << "Fight or run? (f/r): ";
                std::cin >> choice;
                switch (choice)
                {
                case 'f':
                {
                    if (PlayerAttacks(arsen, enemy4) == false)
                    {
                        return false;
                    }
                    else
                        break;
                    
                }
                case'r':
                {
                    std::cout << "\nYou run away like a coward\n";
                    break;
                }
                }
            }

            else if (five == i)
            {
                std::cout << " and you have encountered " << enemy5.getName() << '\n';
                char choice{};
                std::cout << "Fight or run? (f/r): ";
                std::cin >> choice;
                switch (choice)
                {
                case 'f':
                {
                    PlayerAttacks(arsen, enemy5);
                    break;
                }
                case'r':
                {
                    std::cout << "\nYou run away like a coward\n";
                    break;
                }
                }
            }
            

            if (i == 10)
            {
                std::cout << "You have reachede the top safely! Congrats!\n";
                return true;
            }

            else
                std::cout << "\nNothing is up here.Moving on\n";
           
        }


    }

}



int main()


{
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // set initial seed value to system clock
    std::rand(); // get rid of first result

    if (gameStart() == true)
        std::cout << "You won\n";
    else
        std::cout << "You lost!";


    return 0;
}

