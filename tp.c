// Jouberth Pereira, Enzo Bernardes, Cauã Guenrick
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define MAX_TAM 1000
#define pi 3

void fazInstrucao(int* umaInstrucao, int* RAM)
{
    int opcode = umaInstrucao[0];

    int val1, val2, val3;
    val1 = umaInstrucao[1];
    val2 = umaInstrucao[2];
    val3 = umaInstrucao[3];

    switch (opcode)
    {
    //Somar
    case 1://1 = endereço 2 = endereço 3 = endereço resultado
        int conteudoSomaRam1 = RAM[val1];
        int conteudoSomaRam2 = RAM[val2];	
        int soma = conteudoSomaRam1+conteudoSomaRam2;
        RAM[val3] = soma;
        
        printf("somando %d com %d e gerando %d, salvando no endereço %d\n", conteudoSomaRam1, conteudoSomaRam2, soma, val3);
        break;
    //Subtrair
    case 2://1 = endereço 2 = endereço 3 = endereço resultado
    
        int conteudoSubRam1 = RAM[val1];
        int conteudoSubRam2 = RAM[val2];	
        int subtrai = conteudoSubRam1-conteudoSubRam2;
        RAM[val3] = subtrai;
        
        printf("subtraindo %d de %d e gerando %d, salvando no endereço %d\n", conteudoSubRam2, conteudoSubRam1, subtrai, val3);
        break;
    //Salvar na RAM
    case 3: // 1 = conteudo 2 = endereço 3 = inutilizado
        int content = val1;
        int end = val2;
        RAM[end]=content; 
        printf("O valor %d, foi armazenado no endereço %d\n", content, end);

        break;
    //Trazer da RAM
    case 4: // 
        umaInstrucao[1]=RAM[val2];
        printf("O valor %d foi trazido da RAM\n", RAM[val2]);
        break;
    case -1:

        break;
    
    default:
        printf("Opcode invalido");
        break;
    }
}

int multiplica(int a, int b, int* RAM, int** listaInstrucoes)
{
    //fazendo o store para levar o valor de 'a' para RAM
    int umaInstrucao[4];

    umaInstrucao[0] = 3; //opcode
    umaInstrucao[1] = a; //conteudo
    umaInstrucao[2] = 0; //endereço pra onde vai conteudo
    umaInstrucao[3] = -1;  

    fazInstrucao(umaInstrucao, RAM); 

    for (int i = 0; i < b - 1; i++)
    {
        //Lembrando que as instrucoes so mexem com enderecos.
        listaInstrucoes[i][0] = 1;//OPCODE de soma
        listaInstrucoes[i][1] = 0;
        listaInstrucoes[i][2] = i;
        listaInstrucoes[i][3] = i + 1;
    }//Gera b-1 instruções
    //nessa funcao o resultado vai sendo salvo um a mais na ram e sendo usado.  

    listaInstrucoes[b - 2][3] = 0;//Salvando o restultado da ultima soma em RAM[0]
    

    return b - 1;//Retorna o numero de intruções a serem executadas 
}

void divisao(int a, int b, int* RAM)
{
    printf("Fazendo a divisao de %d por %d\n\n", a, b);
    int resultado = 0;
    RAM[1] = a; //! Essa operações podiam ser feitas usando o STORE
    RAM[2] = b; //! Essa operações podiam ser feitas usando o STORE


    while (1)
    {
        int umaInstrucao[4] = {2, 1, 2, 1};
        fazInstrucao(umaInstrucao, RAM);
        //aqui ele incrementa à variavel resultado ate o valor da menos que 0,
        //resultando no valor da divisao.  
        if (RAM[1] >= 0)
        {
            printf("Aumentando resultado, totalizando: %d\n\n", ++resultado);
        }else{
            break;
        }
    }

    RAM[0] = resultado;
    return;
}

void exponencial(int a, int expoente, int* RAM, int** listaInstrucao){
    
    int nInstrucoes = 0;
    printf("\nIniciando funcao exponencial\n");
    
    RAM[0] = a; //! Essa operações podiam ser feitas usando o STORE

    for (int i = expoente; i > 1; i--) 
    {
        nInstrucoes = multiplica(RAM[0], a, RAM, listaInstrucao);
        
        for (int j = 0; j < nInstrucoes; j++) 
        {
            fazInstrucao(listaInstrucao[j], RAM);
        }
    }

    printf("\n%d elevado a %d é igual a %d.\n", a, expoente, RAM[0]);
    return;
}   

void potenciaEletrica(int tensao, int resistencia, int* RAM, int** listaInstrucao){
    exponencial(tensao, 2, RAM, listaInstrucao);
    tensao = RAM[0]; //! Essa operações podiam ser feitas usando o LOAD
    divisao(tensao, resistencia, RAM);
}

void areaTrapezio(int base, int BASE, int h, int* RAM, int** listaInstrucoes)
{ //BASE+base * h / 2
    RAM[0] = base;
    RAM[1] = BASE;


    listaInstrucoes[1][0] = 1;
    listaInstrucoes[1][1] = 0;
    listaInstrucoes[1][2] = 1;
    listaInstrucoes[1][3] = 3;
    fazInstrucao(listaInstrucoes[1], RAM);

    
    int baseMaisBase = RAM[3]; //! Essa operações podiam ser feitas usando o LOAD
    int nIntrucoes = multiplica(baseMaisBase, h, RAM, listaInstrucoes);
    for (int i = 0; i < nIntrucoes; i++)
    {
        fazInstrucao(listaInstrucoes[i], RAM);
    }
    divisao(RAM[0], 2, RAM);
    return;
}

void areaLosango(int Diagonal, int diagonal,int* RAM,int** listaInstrucoes)
{
    int nIntrucoes = multiplica(Diagonal, diagonal, RAM, listaInstrucoes);
        for (int i = 0; i < nIntrucoes; i++)
        {
        fazInstrucao(listaInstrucoes[i], RAM);
        }
    
    divisao(RAM[0], 2, RAM);
    printf("\nA área do losango é: %d\n", RAM[0]);

}

void areaCirculo(int raio, int* RAM, int** listaInstrucoes)
{
    exponencial(raio, 2, RAM, listaInstrucoes);

    int nIntrucoes = multiplica(RAM[0], pi,RAM,listaInstrucoes);
    
    for (int i = 0; i < nIntrucoes; i++)
    {
        fazInstrucao(listaInstrucoes[i], RAM);
    }
    printf("A área do ciruculo de raio 4 é aproximadamente: %d", RAM[0]);
}

int main(){
    //vetor RAM sendo alocado como ponteiro
    int* RAM = malloc(MAX_TAM * sizeof(int));
    int nIntrucoes = 0;
    int** listaInstrucoes;

    listaInstrucoes = malloc(100 * sizeof(int*));
    for (int i = 0; i < 100; i++)
    {
        listaInstrucoes[i] = malloc(4 * sizeof(int));
    }

    //bota lixo na RAM 
    srand(time(NULL));
    for (int i = 0; i < MAX_TAM; i++)
    {
        RAM[i] = (rand() % 10) + 90;
    }


    //? Função multiplica
    
    nIntrucoes = multiplica(2, 98, RAM, listaInstrucoes);
    for (int i = 0; i < nIntrucoes; i++)
    {
        fazInstrucao(listaInstrucoes[i], RAM);
    }
    printf("O resultado da multiplicação é %d", RAM[0]);
    

    //? Função divisão
    /*
    divisao(9, 2, RAM, listaInstrucoes);
    printf("O resultado é %d", RAM[0]);
    */
    
    //? Função exponencial
    // exponencial(5, 3, RAM, listaInstrucoes);
    
    //? Função potencia eletrica 
    
    // potenciaEletrica(20, 2, RAM, listaInstrucoes);
    // printf("\nA potencia para uma tensao de 20 e uma resitencia de 2 eh %d watts", RAM[0]);
    

    //? Função da área do circulo 
    //areaCirculo(4, RAM, listaInstrucoes);
    
    //? Função da área do trapézio
    /*
    areaTrapezio(4, 8, 4, RAM, listaInstrucoes);
    printf("\nA área do trapezio é %d\n\n", RAM[0]);
    */
    
    
    //? Função da área losango
    // areaLosango(8, 6, RAM, listaInstrucoes);

    printf("\n\nO programa será encerrado\n\n");

    return 0;
}
