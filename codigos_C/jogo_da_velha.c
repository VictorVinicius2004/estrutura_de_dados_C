#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gconio.h"

typedef struct{
	int linha;
	int coluna;
	int enter;
}Posicao;

int verificaVencedor(char jogo[3][3], char ponto){
	int winner=0;
	
	for (int i = 0; i < 3; i++){
		if(jogo[i][0]==jogo[i][1] && jogo[i][1]==jogo[i][2] && jogo[i][0]!=' ')
			winner=1;
		if(jogo[0][i]==jogo[1][i] && jogo[1][i]==jogo[2][i] && jogo[0][i]!=' ')
			winner=1;
	}
	
	if(jogo[0][0]==jogo[1][1] && jogo[1][1]==jogo[2][2] && jogo[0][0]!=' ')
		winner=1;
	if(jogo[0][2]==jogo[1][1] && jogo[1][1]==jogo[2][0] && jogo[1][1]!=' ')
		winner=1;
	return winner;	
}

Posicao seletor(int linha, int coluna, char wasd, char jogo[3][3]){
	Posicao posicao;
	posicao.enter=0;
	
	switch(wasd){
		case'w':
			linha--;
			break;
		case'a':
			coluna--;
			break;
		case's':
			linha++;
			break;
		case'd':
			coluna++;
			break;
		case'\n':
			posicao.enter=1;
			break;
	}
	if(linha<0)
		linha++;
	if(linha>2)
		linha--;
	if(coluna<0)
		coluna++;
	if(coluna>2)
		coluna--;
		
	if(posicao.enter==1 && jogo[linha][coluna]!=' '){
		posicao.enter=0;
		printf("Posição já ocupada.\nPRESSIONE ENTER PARA PROSSEGUIR\n");
		getchar();
	}
	
	posicao.linha=linha;
	posicao.coluna=coluna;
	
	return posicao;
}

int main(){
	char player1[50], player2[50], jogo[3][3], vencedor[50];
	Posicao posicao;
	printf("==========JOGO DA VELHA==========\n");
	printf("Digite o nome:\n");
	printf("Jogador 1(x):\n");
	scanf(" %[^\n]", player1);
	printf("Jogador 2(o):\n");
	scanf(" %[^\n]", player2);
	
	for (int i = 0; i < 3; i++){
		for(int j=0; j<3; j++){
			jogo[i][j]=' ';
		}
	}
	
	char ponto, wasd;
	for (int i = 0; i < 9; i++){
		
		posicao.linha=0;
		posicao.coluna=0;
	
		if(i%2==0){
			ponto='x';
			strcpy(vencedor, player1);
		}
		else{
			ponto='o';
			strcpy(vencedor, player2);
		}
			
		do{
			
			do{
				system("clear");
				printf("\nUse wasd para mover o seletor e pressione enter para confirmar\n");
				for (int I = 0; I < 3; I++){
					for (int j = 0; j < 3; j++){
						if(I==posicao.linha && j==posicao.coluna)	
							printf("{%c} ", ponto);
						else
							printf("[%c] ", jogo[I][j]);
					}
					printf("\n");
				}
				wasd=getch();
			}while (wasd!='w' && wasd!='a' && wasd!='s' && wasd!='d' && wasd!='\n');
			
			posicao=seletor(posicao.linha, posicao.coluna, wasd, jogo);
			
			if(posicao.enter)
				jogo[posicao.linha][posicao.coluna]=ponto;
			
		}while (!posicao.enter);
		
		if(verificaVencedor(jogo, ponto)){
			printf("O jogador %s venceu\n", vencedor);
			break;
		}
	}
	if(!verificaVencedor(jogo, ponto))
		printf("Empate.");
	
	return 0;
}

