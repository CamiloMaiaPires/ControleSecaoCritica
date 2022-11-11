#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// flags
#define true 1
#define NThreads 2

//struct para argumentos das threads
struct arguments{
  int id;
};

// variáveis acessadas pelo cliente e servidor para fazer controle do sc
int request = 0;
int respond = 0;
int soma = 0;

// código seção crítica definida no enunciado
void critialSection(int i){
  int local = soma;
  soma = local + 1;
}

// função que representa o cliente
void *client(void *arguments){
  int i = ((struct arguments*) arguments)->id;
  
  while(soma < 1000000000){
    
    // este while a seguir que faz o controle para entrada da thread na seção crítica
    // se apagar as threads não irão respeitar o acesso e haverá inconsistências na soma
    // basicamente que faz com que somente a thread que tenha em seu valor de id igual ao valor 
    // de respond não irá existir e qualquer uma poderá acessar a variável soma quando for possível
    
    while(respond != i){
      request = i;
    }
    
    critialSection(i);
    respond = 0;
  }
}

// fução que representa o servidor 
void *server(){
  while(soma < 1000000000){
    while(request == 0); 
    respond = request;
    while(respond != 0);
    request = 0;
  }
}

int main(void) {

  int i = 0; 
  
  printf("Testando execução com seção crítica\n");
  
  //criando número de thread conforme definido na flag
  pthread_t id[NThreads + 1];
  struct arguments array_arguments[NThreads + 1];

  pthread_create(&id[i], NULL, server, NULL);
  
  // instanciando as threads de cliente
  for(i = 1; i < NThreads; i++){
    array_arguments[i].id = i;
    pthread_create(&id[i], NULL, client, (void*) &array_arguments[i]);
  }

  // espera as threads terminarem
  // como estão executando infinamente, o programa fica executando de forma
  // initerrupta
  for(i = 0; i < NThreads; i++){
    pthread_join(id[i], NULL);
  }
  printf("soma: %d\n", soma);
  return 0;
}