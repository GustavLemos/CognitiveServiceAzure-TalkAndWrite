#include <iostream>
#include <fstream>
#include <string>
#include <speechapi_cxx.h>
#include "jogo.h"

using namespace std;
using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Audio;

auto autenticacao = SpeechConfig::FromSubscription("chave do recurso azure", "regiao do recurso azure"); // DECLARAÇÃO DA AUTENTICAÇÃO DO RECURSO
auto requisicao_textofala = SpeechSynthesizer::FromConfig(autenticacao); // DECLARAÇÃO DO OBJETO DE REQUISIÇÃO DE TEXTO EM FALA DO RECURSO
auto audio_config = AudioConfig::FromDefaultMicrophoneInput(); // DECLARAÇÃO DA ENTRADA DO MICROFONE
auto requisicao_falatexto = SpeechRecognizer::FromConfig(autenticacao, audio_config); // DECLARAÇÃO DO OBJETO DE REQUISIÇÃO DE FALA EM TEXTO DO RECURSO

// PROCEDIMENTO QUE REQUISITA DA API A TRANSFORMAÇÃO DE UM TEXTO EM FALA
void texto_em_fala(string Texto)
{
    cout << Texto + "\n";
    requisicao_textofala->SpeakTextAsync(Texto).get(); // REQUISIÇÃO DA SINTETIZAÇÃO DE TEXTO EM FALA
}
// FUNÇÃO QUE REQUISITA DA API O RECONHECIMENTO DE UMA FALA E A TRANSFORMAÇÃO DESSA FALA EM UM TEXTO
string fala_em_texto() {
    auto resultado = requisicao_falatexto->RecognizeOnceAsync().get(); // REQUISIÇÃO DO RECONHEIMENTO DE FALA EM TEXTO
    cout << resultado->Text + "\n";
    return resultado->Text; //CONVERSÃO DO RESULTADO DO RECONHECIMENTO EM TEXTO
}


int main()
{
   
    //Variaveis de conexao já preenchidas
    string key = "<chave azureFala fornecida no portal da azure>", region = "<regiao do recurso azureFala  fornecida no portal da azure>";
    
    //Teste de conexão Manual
    /*
    cout << "Informe a key do recurso: ";
    cin >> key;                 // ENTRADA DA CHAVE DO RECURSO
    cout << "Informe a regiao em que o recurso e hospedado: ";
    cin >> region;              // ENTRADA DA REGIÃO EM QUE O RECURSO FOI HOSPEDADO
    cout << "--------------------------------------------------------------\n";
    */

    autenticacao = SpeechConfig::FromSubscription(key, region);         //  AUTENTICAÇÃO DO RECURSO COM A CHAVE E REGIÃO INFORMADOS PELO USUÁRIO 
    autenticacao->SetSpeechRecognitionLanguage("pt-BR");                //  CONFIGURAÇÃO DA AUTENTICAÇÃO PARA O RECONHECIMENTO DE FALA EM PORTUGUÊS 
    autenticacao->SetSpeechSynthesisLanguage("pt-BR");                  //  CONFIGURAÇÃO DA AUTENTICAÇÃO PARA A SINTETIZAÇÃO DE FALA EM PORTUGUÊS 
    autenticacao->SetSpeechSynthesisVoiceName("pt-BR-HeloisaRUS"); //pt-BR-Daniel  // CONFIGURAÇÃO DA AUTENTICAÇÃO COM UMA VOZ ESPECÍFICA 
    requisicao_textofala = SpeechSynthesizer::FromConfig(autenticacao); //  REDEFINIÇÃO DO OBJETO REQUISICAO_TEXTOFALA COM AS NOVAS CONFIGURAÇÕES 
    requisicao_falatexto = SpeechRecognizer::FromConfig(autenticacao, audio_config); //  REDEFINIÇÃO DO OBJETO REQUISICAO_FALATEXTO COM AS NOVAS CONFIGURAÇÕES


    try
    {
        texto_em_fala("JOGO INICIADO");
        texto_em_fala("Qual e o seu nome?");
        string nome = fala_em_texto();
        texto_em_fala("Ola " + nome + "! A jogabilidade do jogo da velha funciona da seguinte forma cada jogador fala um numero referente a uma posissao do tabuleiro e o mesmo sera preenchido!");


        string number;
        string teste;
        Players player1;
        Players player2;

        cout << "\tJogo da Velha" << endl;
        cout << "Player 1 (X)  -  Player 2 (O)" << endl;
        display();

        //switch between players
        for (int n = 0; n < 5; n++)
        {
            for (int i = 1; i < 3; i++)
            {
                cout << "Player " << i << ", enter a number: ";
               //recebendo numero do tabuleiro
                number = fala_em_texto();

                //limpando o ponto do retorno sistema de fala
                 number.replace(number.find("."), 2, "");
                

                //teste de verificação de numero falado
                //cout << number;

         
                for (int q = 0; q < 9; q++)
                {
                    //verificando se a entrada é válida
                    if (number !=  digit[q] && q == 8)
                    {
                        cout << "Valor invalido!" << endl;
                        exit(0);
                    }
                    if (number == digit[q])
                    {
                        break;
                    }
                }
                if (i == 1)
                {
                    player1.player(number, i);
                    player1.win();
                }
                if (i == 1 && n == 4)
                {
                    cout << "==> He um empate!" << endl;
                    break;
                }
                else if (i == 2)
                {
                    player2.player(number, i);
                    player2.win();
                }
            }
        }
    }
    catch (exception e)
    {
        cout << e.what();
    }
    return 0;
}