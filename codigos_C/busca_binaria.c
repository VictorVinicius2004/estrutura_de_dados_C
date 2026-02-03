#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(){
	srand(time(NULL));
	int n; 
	scanf(" %d", &n);
	while(getchar()!='\n');
	
	int vetor[n], cont=0;
	do{
		int num=rand()%(n*2);
		int repetido=0;
		
		for(int j=0; j<cont; j++)
			if(num==vetor[j]){
				repetido=1;
				break;
			}
			
		if(!repetido)
			vetor[cont++]=num;
	}while(cont<n);
	
	for(int i=1; i<n; i++){
		int temp=vetor[i], j;
		
		for(j=i-1; j>=0; j--){
			if(temp>=vetor[j])
				break;
			vetor[j+1]=vetor[j];
		}
		
		vetor[j+1]=temp;
	}
	
	printf("Vetor:\n");
	for(int i=0; i<n; i++)
		printf("%02d: %02d\n", i, vetor[i]);
		
	int num;
	printf("\nEscolha um número.\n");
	scanf(" %d", &num);
	
	int inicio=0, fim=n-1, encontrado=0, meio;
	while(inicio<=fim){
		meio=(fim-inicio)/2+inicio;
		printf("%d ", meio);
		if(vetor[meio]>num)
			fim=meio-1;
		else if(vetor[meio]<num)
			inicio=meio+1;
		else{
			encontrado=1;
			break;
		}
	}
	
	encontrado? printf("\n%d encontrado na posição %d", num, meio) : 
	printf("%d não pertence ao vetor", num);
	return 0;
}
