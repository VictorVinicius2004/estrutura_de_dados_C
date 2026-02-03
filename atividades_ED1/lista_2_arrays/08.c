#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/*O algoritmo LRU (Least Recently Used) é uma política de gerenciamento de memória cache que invalida o
item que foi acessado menos recentemente. Isso significa que se um item não foi acessado há muito
tempo, ele terá prioridade na remoção. Considere um vetor com N elementos, sorteados no intervalo
entre X e Y (inclusive). Considerando que os primeiros índices foram os acessados recentemente, exclua
da lista o elemento conforme algoritmo LRU (todos os itens iguais devem ser excluídos na mesma
iteração). Solução in-place (não deve-se usar vetor auxiliar). Execute essa operação N vezes, ou seja, até
que o array esteja vazio novamente. Imprima o conteúdo da “memória cache” em cada iteração.*/

int main(){
	srand(time(NULL));
	int n, x, y;
  printf("Excluir o processo menos recentemente usado\n");
	printf("Digite o valor de n.\n");
	scanf(" %d", &n);
	printf("Digite o min e o max.\n");
	scanf(" %d %d", &x, &y);
	int array[n];
	
	for (int i = 0; i < n; i++)
		array[i]=rand()%(y-x+1)+x;
		
  int EXCLUIDO=x-1;
  int qntdExcluidos=0;
  do{
    //print dos elementos
    for(int j=0; j<n; j++){
      if(array[j]!=EXCLUIDO)
        printf("[%d] ",array[j]);
    }printf("\n");

    //verifica o menos recentemente acessado para excluir
    int ultimo;
    for(int i=0; i<n; i++){
      //pule espaços excluídos
      if(array[i]==EXCLUIDO) continue;

      if(i==0){//se for a primeira repetição
        ultimo=i;
      }
      else{
        //verifica se o número atual foi acessado mais recentemente(no início do vetor)
        int maisRecente=0;
        for(int j=0; j<ultimo; j++){
          if(array[j]==array[i]){
            maisRecente=1;
            break;
          }
        }

        //se o número atual não for diferente do último e nem foi acessado mais ao inicio do vetor
        //ele é o menos recentemente acessado
        if(array[i]!=array[ultimo] && !maisRecente){
          ultimo = i;
        }
      }
    }


    //exclui o menos recentemente acessado
    int aExcluir=array[ultimo];
    for(int i=0; i<n; i++)
      if(array[i]==aExcluir){
        array[i]=EXCLUIDO;
        qntdExcluidos++;
      }

    //se excluiu tudo termina o código
    if(qntdExcluidos==n)
      break;
  }while(1);
	return 0;
}

