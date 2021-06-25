#include <iostream>
#include <string>
#include <array>

using namespace std;

//vetores auxiliares de comparação
std::array<std::string, 9> numbers  { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
std::array<std::string, 9> digit  { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

//display do jgo da velha
void display()
{
    cout << endl;
    cout << "  " << numbers[0] << "   |   " << numbers[1] << "   |   " << numbers[2] << endl;
    cout << "----------------------\n";
    cout << "  " << numbers[3] << "   |   " << numbers[4] << "   |   " << numbers[5] << endl;
    cout << "----------------------\n";
    cout << "  " << numbers[6] << "   |   " << numbers[7] << "   |   " << numbers[8] << endl;
    cout << "----------------------\n";
    cout << endl;
}


//classe dos jogadores
class Players
{
public:
    //procedimento recebe o numero escolhido no tabuleiro(display) e o valor referente a qual jogado;
    //relação: player 1 - valor 1 - simbolo X | player 2 - valor 2 - simbolo O

    void player(string num, int value)
    {
        for (int i = 0; i < 9; i++)
        {
            if (num ==  numbers[i] && value == 1)
            {
                numbers[i] = 'X';
            }
            else if (num == numbers[i] && value == 2)
            {
                numbers[i] = 'O';
            }
        }
        display();
    }

    void check(int value)
    {
        if (numbers[value] == "X")
        {
            cout << "==> Player 1 venceu" << endl;
            exit(0);
        }
        else if (numbers[value] == "O")
        {
            cout << "==> Player 2 venceu" << endl;
            exit(0);
        }
    }


    void win()
    {
        int x = 0;
        for (int i = 0; i < 9; i++)
        {
            //verificando linhas horizontais
            if (i == 0 || i == 3 || i == 6)
            {
                if (numbers[i] == numbers[i + 2] && numbers[i] == numbers[i + 2]) 
                {
                    check(i);
                }
            }
            if (i == 8)
            {
                break;
            }
            //verificado linhas verticais
            else if (i == 0 || i == 1 || i == 2)
            {
                if (numbers[i] == numbers[i + 3] && numbers[i] == numbers[i + 3])
                {
                    check(i);
                }
                else
                {
                    x++;
                    switch (x)
                    {
                    case 1:
                        i = 0;
                        break;
                    case 2:
                        i = 1;
                        break;
                    case 3:
                        break;
                    }
                }
            }
        }

        //verificado linha diagonal direita e esquerda
        if (numbers[0] == numbers[4] && numbers[0] == numbers[8])
        {
            check(0);
        }
        else if (numbers[2] == numbers[4] && numbers[2] == numbers[6])
        {
            check(2);
        }
    }
};

