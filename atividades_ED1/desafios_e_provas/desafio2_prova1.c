/*O h-index é uma métrica bastante famosa para qualificar a 
produtividade e o impacto de cientistas ao redor do mundo, 
baseando-se na quantidade e qualidade dos artigos científicos produzidos. 
O h-index é calculado através da quantidade de artigos com 
número de citações maiores ou iguais a essa quantidade. Considerando isso, 
faça um programa que dada uma quantidade N de artigos, sorteie N valores que 
representam o número de citações de cada um destes artigos. Os valores sorteados 
devem ser no intervalo entre 0 e N. Imprima o array sorteado e calcule o h-index 
desse cenário.

P.Ex.: [3,1,6,7,3,2,2,3,4,6]
h-index:    4
Explicação: Existem pelo menos 4 artigos com número de citações maior ou igual a 4.*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(){
	srand(time(NULL));
	int n;
	printf("Digite o número de artigos.\n");
	scanf(" %d", &n);
	
	//preenchendo o vetor
	int vetor[n];
	for(int i=0; i<n; i++){
		vetor[i]=rand()%n;
		printf("%02d, ", vetor[i]);
	}printf("\n");
		
	//h-index
	int hindex=-1;
	for(int i=0; i<n; i++){
		int cont=0;

		for(int j=0; j<n; j++){
      if(vetor[j]>=vetor[i]){
        cont++;
      }
    }
		if(cont>=vetor[i] && vetor[i]>hindex)
			hindex=vetor[i];
	}
	
	printf("h-index: %d \nExistem pelo menos %d artigos com número de citações maiores ou iguais a %d", hindex, hindex, hindex);
	return 0;
}
