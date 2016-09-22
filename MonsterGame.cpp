#include <iostream>
#include <windows.h>
#include <time.h>
#include <cstdlib>
#include <conio.h>

class gameEntity
{
public:
    std::string characterName;
    bool isMonster;
    bool isChampion;
    bool isBoss;
    bool isDead;
    int level;
    int experiencePoints;
    int goldWallet;
    int killCounter;
    int baseHP;
    int baseATK;
    int baseDEF;
    int baseLCK;
    int totalHP;
    int maxHP;
    int totalATK;
    int totalDEF;
    int totalLCK;
    bool entityTurn;

    friend void generatePlayer();
    friend void generateMonster();

   // gameEntity();
   // ~gameEntity();
};

class characterProfession
{
public:
    int select;
    std::string professionName;
    int bonusHP;
    int bonusATK;
    int bonusDEF;
    int bonusLCK;
};



class itemEntity
{
    std::string itemName;
    bool isConsumable;
    bool isEquippable;
    bool isEquipped;

    int boostHP;
    int boostATK;
    int boostDEF;
    int boostLCK;
    int boostEXP;
    int boostGOLD;

};

gameEntity player;
characterProfession playerProfession;
gameEntity monster;
characterProfession specialMonster;
bool gameOverFlag = false;
const int LEVELUP = 500;
enum monsterEnum {HARPY = 1, GIANT_RAT = 2, SKELETON = 3, SLIME = 4};




void gameOver()
{
    std::cout << "You died. Game Over. :(" <<std::endl;
    getch();
    gameOverFlag = true;
}

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void screenclear()
{
    for (int a=0;a<300;a++) std::cout << "" << std::endl;
    gotoxy(0,0);
}

void initializeGame()
{
    std::cout << "==== C++ NanoRPG v2 by Noq ====" << std::endl;
}

void generatePlayer()
{


    player.isMonster = false;
    player.isDead = false;
    player.level = 1;
    player.experiencePoints = 0;
    player.goldWallet = 0;
    player.baseHP = 5;
    player.baseATK = 2;
    player.baseDEF = 2;
    player.baseLCK = 2;
    char playerConfirm = 'n';


    while (playerConfirm != 'y')
    {
        std::cout << "What's your character's name? ";
        std::cin >> player.characterName;
        std::cout << std::endl;
        std::cout << "What's your character's class?" << std::endl << "(1) Knight" << std::endl << "(2) Archer" << std::endl << "(3) Wizard" << std::endl;
        std::cin >> playerProfession.select;
        switch (playerProfession.select)
        {
        case 1:
            playerProfession.professionName = "KNIGHT";
            playerProfession.bonusHP = 4;
            playerProfession.bonusATK = 4;
            playerProfession.bonusDEF = 3;
            playerProfession.bonusLCK = 1;
            break;
        case 2:
            playerProfession.professionName = "ARCHER";
            playerProfession.bonusHP = 3;
            playerProfession.bonusATK = 4;
            playerProfession.bonusDEF = 2;
            playerProfession.bonusLCK = 3;
            break;
        case 3:
            playerProfession.professionName = "WIZARD";
            playerProfession.bonusHP = 2;
            playerProfession.bonusATK = 4;
            playerProfession.bonusDEF = 2;
            playerProfession.bonusLCK = 4;
            break;
        default:
            break;

        }

        player.maxHP = player.baseHP * (playerProfession.bonusHP * player.level);
        player.totalATK = player.baseATK * (playerProfession.bonusATK * player.level);
        player.totalDEF = player.baseDEF * (playerProfession.bonusDEF * player.level);
        player.totalLCK = player.baseLCK * (playerProfession.bonusLCK * player.level);
        player.totalHP = player.maxHP;
        screenclear();
        std::cout << "Your character:" << std::endl;
        std::cout <<"[ "<< player.characterName  << " | "
        << playerProfession.professionName << " | "
        << "LVL: " << player.level << " | "
        << "HP: " << player.totalHP << "/" << player.maxHP << " | "
        << "ATK: " << player.totalATK << " | "
        << "DEF: " << player.totalDEF << " | "
        << "LCK: " << player.totalLCK << " ]" << std::endl << std::endl;

        std::cout << "Do you want to keep this character? (Y/N)" << std::endl;
        playerConfirm = getch();
        screenclear();
    }
}

void generateMonster()
{


    monster.isMonster = true;
    monster.isDead = false;
    monster.level = player.level + (rand() % 2);

    monsterEnum randomMonster = static_cast<monsterEnum>(rand() % 4 + 1);

    int monsterDiceRoll = rand() % 100;

    if (monsterDiceRoll > 75 && monsterDiceRoll < 95)
    {
        monster.isChampion = true;
        monster.isBoss = false;
        specialMonster.professionName = "Champion ";
        specialMonster.bonusHP = 3;
        specialMonster.bonusATK = 2;
        specialMonster.bonusDEF = 1;
        specialMonster.bonusLCK = 1;
    }
    else if (monsterDiceRoll >= 95)
    {
        monster.isChampion = false;
        monster.isBoss = true;
        specialMonster.professionName = "Boss ";
        specialMonster.bonusHP = 10;
        specialMonster.bonusATK = 5;
        specialMonster.bonusDEF = 3;
        specialMonster.bonusLCK = 3;
    }
    else
    {
        monster.isChampion = false;
        monster.isBoss = false;
        specialMonster.professionName = "";
        specialMonster.bonusHP = 1;
        specialMonster.bonusATK = 1;
        specialMonster.bonusDEF = 1;
        specialMonster.bonusLCK = 1;
    }

    switch(randomMonster)
    {
    case HARPY:
        monster.characterName = "Harpy";
        monster.baseHP = 10;
        monster.baseATK = 2;
        monster.baseDEF = 2;
        monster.baseLCK = 1;
        break;
    case GIANT_RAT:
        monster.characterName = "Giant Rat";
        monster.baseHP = 5;
        monster.baseATK = 2;
        monster.baseDEF = 1;
        monster.baseLCK = 1;
        break;
    case SKELETON:
        monster.characterName = "Skeleton";
        monster.baseHP = 6;
        monster.baseATK = 3;
        monster.baseDEF = 0;
        monster.baseLCK = 1;
        break;
    case SLIME:
        monster.characterName = "Slime";
        monster.baseHP = 10;
        monster.baseATK = 2;
        monster.baseDEF = 0;
        monster.baseLCK = 1;
        break;
    }


    monster.maxHP = monster.baseHP * monster.level * specialMonster.bonusHP;
    monster.totalHP = monster.maxHP;
    monster.totalATK = monster.baseATK * monster.level * specialMonster.bonusATK;
    monster.totalDEF = monster.baseDEF * monster.level * specialMonster.bonusDEF;
    monster.totalLCK = monster.baseLCK * monster.level * specialMonster.bonusLCK;



}

void monsterEncounter()
{
    screenclear();
    std::cout << "============= C++ NanoRPG v2 =============" << std::endl;
    std::cout << "You have encountered a " << specialMonster.professionName << monster.characterName << " [Level " << monster.level << "]" << std::endl << std::endl;
}

void battleMode()
{
    std::string turnPlayerIndicator;
    std::string turnMonsterIndicator;
    char battleChoice;
    int damageDealt = 0;
    int criticalAttack = 0;

    int defendValue = player.totalDEF * 2 + player.totalLCK;
    bool defendFlag;
    player.entityTurn = true;


    screenclear();
    if (player.totalLCK > monster.totalLCK)
    {
        player.entityTurn = true;
        std::cout << player.characterName << " acts first!" << std::endl << std::endl;
    }
    else
    {
        player.entityTurn = false;
        std::cout << specialMonster.professionName << monster.characterName << " acts first!" << std::endl << std::endl;
    }

    while (player.totalHP > 0 && monster.totalHP > 0)
    {
        if (player.entityTurn == true)
        {
            turnPlayerIndicator = "--> ";
            turnMonsterIndicator = "    ";
        }
        else if (player.entityTurn == false)
        {
            turnPlayerIndicator = "    ";
            turnMonsterIndicator = "--> ";
        }
        std::cout << "=================== B A T T L E ===================" << std::endl << std::endl;
        std::cout << turnPlayerIndicator << player.characterName  << " | " << playerProfession.professionName << " | " << "LVL: " << player.level << std::endl;
        std::cout << "    HP: " << player.totalHP << "/" << player.maxHP << std::endl;
        std::cout << "    A: " << player.totalATK << " | " << "D: " << player.totalDEF << " | " << "L: " << player.totalLCK << std::endl;

        std::cout << "-----------------------versus----------------------" << std::endl;

        std::cout << turnMonsterIndicator << specialMonster.professionName << monster.characterName << " | " << "LVL: " << monster.level << std::endl;
        std::cout << "    HP: " << monster.totalHP << "/" << monster.maxHP << std::endl;
        std::cout << "    A: " << monster.totalATK << " | " << "D: " << monster.totalDEF << " | " << "L: " << monster.totalLCK << std::endl << std::endl;

        if (player.entityTurn == true) // ---- PLAYER'S TURN ----
        {
            std::cout << "It's " << player.characterName <<"'s turn!" << std::endl;
            std::cout << std::endl << "Choose an action: (A)ttack, (D)efend" << std::endl;
            battleChoice = getch();
            switch(battleChoice)
            {
            case 'a':

                criticalAttack = (rand() % 10 + 1) + player.totalLCK;
                if (criticalAttack <= 10)
                {
                    if (player.totalATK <= monster.totalDEF)
                    {
                        damageDealt = 0;
                    }
                    else
                    {
                        damageDealt = player.totalATK - monster.totalDEF;
                    }
                    std::cout << "You have dealt " << damageDealt << " damage to " << specialMonster.professionName << monster.characterName << std::endl;
                }
                else if (criticalAttack > 10)
                {
                    if (player.totalATK*2 <= monster.totalDEF)
                    {
                        damageDealt = 0;
                    }
                    else
                    {
                        damageDealt = (player.totalATK * 2) - monster.totalDEF;
                    }
                    std::cout << "CRITICAL ATTACK! You have dealt " << damageDealt << " damage to " << specialMonster.professionName << monster.characterName << std::endl;
                }
                monster.totalHP = monster.totalHP - damageDealt;
                std::cout << specialMonster.professionName << monster.characterName << " has " << monster.totalHP << " HP left." << std::endl << std::endl;
                break;

            case 'd':
                defendFlag = true;
                std::cout << "Your defense rose to " << defendValue << " for the enemy's next attack!" << std::endl;
                break;

            }
        }
        else if (player.entityTurn == false) // ---- MONSTER'S TURN ----
        {
            std::cout << "It's " << specialMonster.professionName << monster.characterName <<"'s turn!" << std::endl;

            criticalAttack = (rand() % 20 + 1) + monster.totalLCK;
            if (criticalAttack <= 20)
            {
                if (defendFlag == true)
                {
                    if (monster.totalATK < defendValue)
                    {
                        damageDealt = 0;
                    }
                    else
                    {
                        damageDealt = monster.totalATK - defendValue;
                    }
                }
                else
                {
                    if (monster.totalATK < player.totalDEF)
                    {
                        damageDealt = 0;
                    }
                    else
                    {
                        damageDealt = monster.totalATK - player.totalDEF;
                    }
                }
                defendFlag = false;
                std::cout << specialMonster.professionName << monster.characterName << " has dealt " << damageDealt << " damage to " << player.characterName << std::endl;
            }
            else if (criticalAttack > 20)
            {
                if (defendFlag == true)
                {
                    if ((monster.totalATK*2) < defendValue)
                    {
                        damageDealt = 0;
                    }
                    else
                    {
                        damageDealt = (monster.totalATK * 2) - defendValue;
                    }
                }
                else
                {
                    if ((monster.totalATK*2) < player.totalDEF)
                    {
                        damageDealt = 0;
                    }
                    else
                    {
                        damageDealt = (monster.totalATK * 2) - player.totalDEF;
                    }
                }
                defendFlag = false;
                std::cout << "CRITICAL ATTACK! " << specialMonster.professionName << monster.characterName << " has dealt " << damageDealt << " damage to " << player.characterName << std::endl;
            }
            player.totalHP = player.totalHP - damageDealt;
            defendFlag = false;
        }
        if (player.entityTurn == true)
        {
            player.entityTurn = false;
        }
        else if (player.entityTurn == false)
        {
            player.entityTurn = true;
        }

        damageDealt = 0;
        criticalAttack = 0;
        getch();
        screenclear();
    }

    if (player.totalHP <= 0)
    {
        gameOver();
    }

    if (monster.totalHP <= 0)
    {
        player.totalHP = player.maxHP;
        player.experiencePoints = player.experiencePoints + (monster.maxHP * 3);
        player.goldWallet = player.goldWallet + (monster.totalDEF * monster.totalLCK * 2);

        std::cout << "You have slain a " << specialMonster.professionName << monster.characterName << "!" << std::endl;
        std::cout << "You receive " << (monster.maxHP * 3) << " experience points and " << (monster.totalDEF * monster.totalLCK * 2) << " gold." << std::endl << std::endl;

        if (player.experiencePoints >= (LEVELUP * player.level))
        {
            player.experiencePoints = player.experiencePoints - (LEVELUP * player.level);
            player.level++;
            std::cout << "You are now level " << player.level << "!" << std::endl;
            getch();
        }
        else
        {
            std::cout << "Just " << ((LEVELUP * player.level) - player.experiencePoints) << " more experience points until next level!" << std::endl;
            getch();
        }
    }


}

void characterSheet()
{
    screenclear();
    std::cout << "============= C++ NanoRPG v2 =============" << std::endl;
    std::cout << "---          Character  Sheet          ---" << std::endl << std::endl;

    std::cout << player.characterName << std::endl;
    std::cout << "------------------------------------------" << std::endl;
    std::cout << "Class        :" << playerProfession.professionName << std::endl;
    std::cout << "Level        :" << player.level << std::endl;
    std::cout << "Experience   :" << player.experiencePoints << "/" << (player.level * LEVELUP) << std::endl << std::endl;

    std::cout << "Health       :" << player.baseHP << " + " << (playerProfession.bonusHP * player.level) << std::endl;
    std::cout << "Attack       :" << player.baseATK << " + " << (playerProfession.bonusATK * player.level) << std::endl;
    std::cout << "Defense      :" << player.baseDEF << " + " << (playerProfession.bonusDEF * player.level) << std::endl;
    std::cout << "Luck         :" << player.baseLCK << " + " << (playerProfession.bonusLCK * player.level) << std::endl;

    std::cout << "Gold         :" << player.goldWallet << std::endl;
    std::cout << "Kills        :" << player.killCounter << std::endl << std::endl;

    std::cout << "INVENTORY" << std::endl;
    std::cout << "[ ] empty" << std::endl;
    std::cout << "[ ] empty" << std::endl;
    std::cout << "[ ] empty" << std::endl;
    std::cout << "[ ] empty" << std::endl;
    std::cout << "[ ] empty" << std::endl;

    getch();
}



int main()
{
    SetConsoleTitle("The Legend of VapeKnight v0.420");

    srand(time(NULL));
    char hubChoice = '0';
    char encounterChoice = '0';
    initializeGame();
    generatePlayer();
    while (hubChoice != 'q' && gameOverFlag == false)
    {
        screenclear();
        std::cout << "============= C++ NanoRPG v2 =============" << std::endl;
        std::cout << "---         WELCOME TO THE HUB         ---" << std::endl << std::endl;
        std::cout << "        What would you like to do?        " << std::endl;
        std::cout << "    (F)ight (C)haracter (S)hop (Q)uit     " << std::endl;
        hubChoice = getch();
        switch (hubChoice)
        {
        case 'f':
            generateMonster();
            monsterEncounter();
            std::cout << "What will you do?" << std::endl;
            std::cout << "(F)ight?   (R)un?" << std::endl;
            encounterChoice = getch();
            if (encounterChoice == 'r')
            {
                int runRoll;
                runRoll = rand () % 10;
                if (runRoll < (player.totalLCK*5 - monster.totalLCK))
                {
                    screenclear();
                    std::cout << "You have successfully escaped!";
                    getch();
                }
                else
                {
                    screenclear();
                    std::cout << "You could not escape! Prepare to fight";
                    getch();
                    battleMode();
                }
            }
            else if (encounterChoice == 'f')
            {
                battleMode();
            }

            break;
        case 'c':
            characterSheet();
            break;
        case 's':
            break;
        case 'q':
            screenclear();
            std::cout << "Thank you for playing :)";
            return 0;
            break;
        default:
            break;

        }
    }

    return 0;
}
