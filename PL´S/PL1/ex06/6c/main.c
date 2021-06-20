#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    const int NR_OF_CHILDREN = 4;
    pid_t pids[NR_OF_CHILDREN];

    int i;
	int estado_do_processo;
	
    for (i = 0; i < NR_OF_CHILDREN; i++) {
	   
		pids[i] = fork(); //cria um processo filho
		
		if(pids[i]==0){
		printf("Filho this is the end.\n");
		
		exit(0);
		}
		
	}

	for (i = 0; i < NR_OF_CHILDREN; i++){
		waitpid(pids[i], &estado_do_processo, 0); //coloca os processos filho em estado de waiting
	}
	
	printf("Pai this is the end.\n");
    return 0;
}
