// Jouberth Matheus, Enzo Bernardes, Cauã Guenrik
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_TAM 100

typedef struct{
    int memoriaInstrucoes[10][100];
    int RAM[MAX_TAM];
} Memory;

void montarMemoriaRAM(Memory *memory){
    for (int i = 0; i < MAX_TAM; i++){
        memory->RAM[i] = rand() % 100 + 1;
    } 
    //debug
    //for (int j = 0; j < 100; j++){
    //    printf("%d|%d ", j, memory->RAM[j]);
    //}
    
}

void preencherInstrucoes(Memory *memory){
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 100; j++){
            memory->memoriaInstrucoes[i][j] = rand() % 4 + 1;
        }
    }
    // (opcode -1) teste
    memory->memoriaInstrucoes[0][99] = -1;
}

void maquinaInterpretada(int opcode, Memory memory);

void maquina(Memory *memory){
    int PC = 0;
    int opcode=0;

    while(opcode != -1){
        int j;
        scanf("%d", &j);
        opcode = memory->memoriaInstrucoes[0][j];
        maquinaInterpretada(opcode, *memory);
        PC++;
    }
}

void maquinaInterpretada(int opcode, Memory memory){
    int endereco1, endereco2, endereco3;
    int  soma, sub, valoresRam1, valoresRam2;


    printf("OPCODE: %d\n", opcode);
    int x = rand() % 97;
    switch (opcode){
        case 1: 
            //soma
            endereco1 = x;
            endereco2 = x+1;
            //buscando na RAM
            valoresRam1 = memory.RAM[endereco1];
            valoresRam2 = memory.RAM[endereco2];
            soma = valoresRam1 + valoresRam2;
            //salvando resultado na RAM
            endereco3 = x+2;
            memory.RAM[endereco3] = soma;
            printf("Somando %d com %d e gerando %d\n\t Resultado armazenado na próxima posição %d da RAM\n", memory.RAM[endereco1], memory.RAM[endereco2], soma, x+2);
            break;
        case 2:
            //subtração
            endereco1 = x;
            endereco2 = x+1;
            //buscando na RAM
            valoresRam1 = memory.RAM[endereco1];
            valoresRam2 = memory.RAM[endereco2];
            sub = valoresRam1 - valoresRam2;
            //salvando resultado na RAM
            endereco3 = x+2;
            memory.RAM[endereco3] = sub;
            printf("Subtraindo %d com %d e gerando %d\n\t Resultado armazenado na posição %d da RAM\n", valoresRam1, valoresRam2, sub, x+2);
            
            break;
        case 3:
            //armazenar/levar valor para RAM
                int valor, posi;
                printf("Digite o valor para enviar para a memória e a localização na memória RAM: ");
                scanf("%d %d", &valor, &posi);
                
                while(posi<0 || posi > 100){
                    printf("0 < Pos < 100");
                    scanf("%d", &posi);
                }
                memory.RAM[posi] = valor;
                printf("Valor %d foi armazenado na posição %d da RAM\n", valor, posi);
                //printf("RAM \n\n");
                //for (int j = 0; j < 100; j++){
                //    printf("%d ", memory.RAM[j]);
                //}
            break;
        case 4:
            //trazer da ram
            printf("Posição que queira trazer da RAM?: ");
            scanf("%d", &posi);
            while(posi<0 || posi > 100){
                printf("0 < Pos < 100");
                scanf("%d", &posi);
            }
            int aux = memory.RAM[posi];
            printf("|%d|\n", aux);
          
            break;
        case -1:
            ///parar
            printf("HALT!\n\n");
            break;
        default:
            printf("Opcode desconhecido: %d\n", opcode);
            break;
    }
}

int main() {
    Memory memory;
    srand(time(NULL));

    // Gerando valores para RAM e instruções
    montarMemoriaRAM(&memory);
    preencherInstrucoes(&memory);
    
    maquina(&memory);
    return 0;
}


