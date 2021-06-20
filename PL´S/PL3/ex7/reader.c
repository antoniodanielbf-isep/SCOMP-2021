#include "asm.h"

int main() {

    //Criar e abrir a memória partilhada
    int fileDescriptor = shm_open(FICHEIRO_PARTILHADO, OPEN_READER_OFLAG, OPEN_READER_MODE);

    if (fileDescriptor == -1) {
        perror("ERRO no shm_open()!\n\nA terminar execução!\n\n");
        exit(EXIT_FAILURE);
    }

    //Definir tamanho da memória partilhada (tamanho da estrutura)

    ftruncate(fileDescriptor, TAMANHO_ESTRUTURA);

    //Obter o pointer para os dados

    Numbers *memoriaPartilhada = (Numbers *) mmap(NULL, TAMANHO_ESTRUTURA, PROT_READ | PROT_WRITE, MAP_SHARED, fileDescriptor, 0);

    //Imprimir a informação no monitor
    int *ptr = memoriaPartilhada->n;


    int i;

    double media = 0;
    for (i = 0; i < TOTAL_NUMEROS; i++) {
        media += *ptr;
        ptr++;
    }
    media = media / TOTAL_NUMEROS;

    printf("Média: %.2f\n", media);

    //Desfazer o Mapping
    int test = munmap((void *) memoriaPartilhada, TAMANHO_ESTRUTURA);

    if (test < 0) {
        perror("Erro ao Desfazer o Mapping!\n");
        exit(EXIT_FAILURE);
    }

    //Fechar o fileDescriptor

    test = close(fileDescriptor);

    if (test < 0) {
        perror("Erro ao fechar o FIle Descriptor!\n");
        exit(EXIT_FAILURE);
    }

    //Remover o Ficheiro
    test = shm_unlink(FICHEIRO_PARTILHADO);

    if (test < 0) {
        perror("Erro ao remover o Ficheiro!\n");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}