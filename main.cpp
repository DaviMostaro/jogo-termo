#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

int tamanho(char p[]){
    int i = 0;
    while (p[i] != '\0'){
        i++;
    }
    return i;
}

void copiar(char destino[], char origem[]){
    int i = 0;
    while (origem[i] != '\0'){
        destino[i] = origem[i];
        i++;
    }
    destino[i] = '\0';
}

bool somenteLetras(char chute[]) {
    int i = 0;
    while (chute[i] != '\0') {
        if((chute[i] < 'a' || chute[i] > 'z') && (chute[i] < 'A' || chute[i] > 'Z')) {
            return false;
        }
        i++;
    }
    return true;
}

void verificaSimbolos(char chute[], char palavraSecreta[], char resultado[]) {
    for(int i = 0; i < 6; i++) {
        if(chute[i] == palavraSecreta[i]) {
            resultado[i] = 'O';
        }
        else if(chute[i] != palavraSecreta[i]) {
            bool existeLetra = false;
            for(int j = 0; j < 6; j++) {
                if(chute[i] == palavraSecreta[j]) {
                    existeLetra = true;
                    break;
                }
            }
            if(existeLetra) {
                for(int k = 0; k < 6; k++) {
                    if(chute[i] == palavraSecreta[k] && chute[k] != palavraSecreta[k]) {
                        resultado[i] = 'X';
                        break;
                    } else {
                        resultado[i] = '_';
                    }
                }
            } else {
                resultado[i] = '_';
            }
        }
    }
}

int main(){
    ifstream arquivo("dicionario.txt");

    if (!arquivo.is_open()){
        cout << "Erro ao ler o arquivo!" << endl;
        return 1;
    }

    char palavras[5000][7];
    int total = 0;
    char temp[50];
    
    while (arquivo >> temp){
        if (tamanho(temp) == 6){
            if (total < 5000) {
                copiar(palavras[total], temp);
                total++;
            } else {
                break; 
            }
        }
    }

    arquivo.close();

    if (total == 0){
        cout << "Nenhuma palavra de 6 letras foi encontrada!" << endl;
        return 1;
    }

    srand(time(NULL));
    int indice = rand() % total;

    char palavraSecreta[7];
    copiar(palavraSecreta, palavras[indice]);

    cout << "Seja bem-vindo ao jogo Termo!" << endl;
    cout << "Digite uma palavra de 6 letra e tente adivinhar a palavra secreta: " << endl;

    int tentativas = 0;

    while(tentativas < 10) {
        char chute[7];
        cin >> chute;

        if(tamanho(chute) != 6 || somenteLetras(chute) == false) {
            cout << "Palavra inválida! Digite uma palavra de exatamente 6 LETRAS." << endl;
            continue;
        }

        bool acertou = true;

        for(int i = 0; i < 6; i++) {
            if(chute[i] != palavraSecreta[i]) {
                acertou = false;
                break;
            }
        }

        if(acertou) {
            cout << "Parabéns! Você acertou a palavra secreta em " << tentativas + 1 << " tentativas!" << endl;
            break;
        }

        char resultado[7];
        verificaSimbolos(chute, palavraSecreta, resultado);

        cout << resultado << endl;

        tentativas++;
    }

    if(tentativas == 10) {
        cout << "Suas tentativas acabaram! A palavra secreta era: " << palavraSecreta << endl;
    }

    return 0;
}
