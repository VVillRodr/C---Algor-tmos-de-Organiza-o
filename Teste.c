#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define TAMANHO 30
#define CLOCKS_PER_SEC 1000

typedef struct Pessoa{
    char nome[TAMANHO];
    int rg;
}Ps;

typedef struct Lista{
   Ps** p;
   int tamanho;
}Lista;


int GetTamanho(char nomearquivo[]){
    FILE *arq;
    int i = 0;
    char line[50];
    char *result;

    arq = fopen(nomearquivo, "rt");

    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo!");
        getchar();
        exit(1);
    }

    while (!feof(arq))
    {
        if (fgets(line, TAMANHO, arq) != NULL)
        {
            i++;
        }
    }

    fclose(arq);

    return i;
}

Ps **AlocaLista(int tam){
    Ps **p;
    p = (Ps **)malloc(tam * sizeof(Ps *));

    if (p == NULL)
    {
        printf("Erro na alocação!");
        getchar();
        exit(1);
    }

    return p;
}

void CriaLista(char nomearquivo[], Lista *lista){
    FILE *arq;
    int i;
    char line[TAMANHO];
    char *nome, *srg;
    int *rg;

    arq = fopen(nomearquivo, "rt");

    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo!");
        getchar();
        exit(1);
    }

    for (i = 0; i < (lista->tamanho); i++)
    {
        if (fgets(line, TAMANHO, arq) == NULL)
        { // lê toda a lista e coloca em line
            printf("ERRO AO LER O ARQUIVO!");
            getchar();
            exit(1);
        }

        nome = strtok(line, ","); // atribui à nome tudo antes da vigula
        srg = strtok(NULL, "\n"); // atribui à rg tudo depois da virgula

        lista->p[i] = (Ps *)malloc(sizeof(Ps)); // aloca o espaço para Sessoa no espaço correspondente no vetor de ponteiros

        strcpy(lista->p[i]->nome, nome); // copia os dados para os espaços da struct
        lista->p[i]->rg = atoi(srg); //converte sting em inteiro
        if (nome == NULL || srg == NULL)
        {
            printf("ERRO EM %d", (i + 1));
            exit(1);
        }
    }

    fclose(arq);
}

void Desaloca(Lista *lista){
    int i;

    for (i = 0; i < lista->tamanho; i++)
    {
        free(lista->p[i]);
    }

    free(lista->p);
}

void ImprimeLista(Lista *lista){
    int i;
    for (i = 0; i < lista->tamanho; i++)
    {
        printf("|Nome: %s||RG: %d|\n", lista->p[i]->nome, lista->p[i]->rg);
    }
}

void SalvaArq(Lista *lista){
    FILE *arq;
    int i = 0;
    char novoarq[50];
    printf("\nInsira o nome do novo arquivo:\n");
    scanf("%s", novoarq);
    arq = fopen(novoarq, "w+");

    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo!");
        getchar();
        exit(1);
    }
    for (i = 0; i < ((lista->tamanho) - 1); i++)
    {
        if (i == ((lista->tamanho) - 1) - 1)
        {
            fprintf(arq, "%s,%s", lista->p[i]->nome, lista->p[i]->rg);
        }
        else
        {
            fprintf(arq, "%s,%s\n", lista->p[i]->nome, lista->p[i]->rg);
        }
    }
    fclose(arq);
}
// BUSCAS
void BuscaSeq(Lista *lista){
    int i, buscarg, achou = 0, Cn = 0, Mn = 0;
    printf("Insira o RG de quem deseja procurar: ");
    scanf("%d", &buscarg);
    for (i = 0; i < lista->tamanho && achou != 1; i++)
    {
        Cn++;
        if (lista->p[i]->rg == buscarg)
        {
            printf("Posicao (%d)\n", i + 1);
            printf("Nome: %s\nRG: %d\n", lista->p[i]->nome, lista->p[i]->rg);
            achou = 1;
        }
    }
    if (achou == 0)
    {
        printf("RG não encontrado!");
    }
    printf("C(n): %d\n", Cn);
    printf("M(n): %d\n", Mn);
}

void BuscaBin(Lista *lista){
    int meio, inicio, fim, rgbusca, Cn = 0, Mn = 0, achou = 0;
    inicio = 0;
    fim = lista->tamanho;
    meio = (inicio + fim-1)/2;

    printf("Insira o RG que deseja procurar: ");
    scanf("%d", &rgbusca);

    while(achou != 1){
        Cn++;
        if(lista->p[meio]->rg == rgbusca){

            achou++;
            printf("Nome : %s || RG: %d\n",lista->p[meio]->nome,lista->p[meio]->rg);
        } else if(rgbusca < lista->p[meio]->rg){
            Cn++;
            fim = meio;
            meio = (inicio + meio)/2;

        }else{
            inicio = meio;
            meio = (fim + meio)/2;
         }

    }
    printf("\nPosicao é %d",meio);
    printf("\nC(n): %d\n", Cn);
    printf("M(n): %d\n", Mn);
}
// Ordenacao
void SelectionSort(Lista *lista){
    int min, auxrg, Cn = 0, Mn = 0;
    char auxn[TAMANHO];
    for (int i = 0; i < lista->tamanho; i++)
    {
        min = i;
        for (int j = i + 1; j < lista->tamanho; j++)
        {
            Cn++;
            if (lista->p[j]->rg < lista->p[min]->rg)
            {
                min = j;
            }
        }
        strcpy(auxn, lista->p[i]->nome);
        Mn++;
        auxrg = lista->p[i]->rg;
        Mn++;
        strcpy(lista->p[i]->nome, lista->p[min]->nome);
        Mn++;
        lista->p[i]->rg = lista->p[min]->rg;
        Mn++;
        strcpy(lista->p[min]->nome, auxn);
        Mn++;
        lista->p[min]->rg = auxrg;
        Mn++;
    }
    printf("C(n): %d\n", Cn);
    printf("M(n): %d\n", Mn);
}

void InsertionSort(Lista *lista){
    int auxrg, Cn = 0, Mn = 0;
    char auxn[TAMANHO];
    for (int i = 0; i < lista->tamanho; i++)
    {
        for (int j = i; j > 0; j--)
        {
            Cn++;
            if (lista->p[j]->rg < lista->p[j - 1]->rg)
            {

                strcpy(auxn, lista->p[j - 1]->nome);
                Mn++;
                auxrg = lista->p[j - 1]->rg;
                Mn++;

                strcpy(lista->p[j - 1]->nome, lista->p[j]->nome);
                Mn++;
                lista->p[j - 1]->rg = lista->p[j]->rg;
                Mn++;

                strcpy(lista->p[j]->nome, auxn);
                Mn++;
                lista->p[j]->rg = auxrg;
                Mn++;
            }
        }
    }
    printf("C(n): %d\n", Cn);
    printf("M(n): %d\n", Mn);
}

void BubleSort(Lista *lista){
    int troca, tam, auxrg, Cn = 0, Mn = 0;
    char auxn[TAMANHO];
    tam = lista->tamanho - 1;
    do
    {
        troca = 0;
        for (int i = 0; i < tam; i++)
        {
            Cn++;
            if (lista->p[i]->rg > lista->p[i + 1]->rg)
            {

                strcpy(auxn, lista->p[i]->nome);
                Mn++;
                auxrg = lista->p[i]->rg;
                Mn++;

                strcpy(lista->p[i]->nome, lista->p[i + 1]->nome);
                Mn++;
                lista->p[i]->rg = lista->p[i + 1]->rg;
                Mn++;

                strcpy(lista->p[i + 1]->nome, auxn);
                Mn++;
                lista->p[i + 1]->rg = auxrg;
                Mn++;
                troca = 1;
            }
        }
        tam--;

    } while (troca != 0);
    printf("C(n): %d\n", Cn);
    printf("M(n): %d\n", Mn);
}

void ShellSort(Lista *lista){
    int h = 1, j, i, auxrg;
    long int Cn = 1, Mn = 0;
    char auxn[TAMANHO];



        while (h < lista->tamanho/3) //calcula o h inicial
            h= 3 * h+1; //Um vídeo diz que esse é o melhor H para usar

        while(h>0){
                for(i=h ; i<lista->tamanho; i++){

                    auxrg = lista->p[i]->rg; Mn++;
                    strcpy(auxn,lista->p[i]->nome); Mn++;
                    j = i;

                    while(j>=h && auxrg < lista->p[j-h]->rg){ //efetua comparações entre elementos com distancia h
                        Cn++;
                        lista->p[j]->rg = lista->p[j-h]->rg; Mn++;
                        strcpy(lista->p[j]->nome,lista->p[j-h]->nome); Mn++;
                        j = j-h;

                    }
                    lista->p[j]->rg = auxrg; Mn++;
                    strcpy(lista->p[j]->nome , auxn); Mn++;

                }
                h = (h-1)/3;



        }
    printf("C(n): %d\n", Cn);
    printf("M(n): %d\n", Mn);
}

void QuickSort(Lista *lista, int ini, int fim, int *Cn, int *Mn){
    int i, j, pivo, auxrg;
    char auxn[TAMANHO];
    i = ini;
    j = fim;
    pivo = lista->p[(ini+fim) / 2]->rg;
    do{

        while (lista->p[i]->rg < pivo && i < fim){
            *Cn = *Cn + 1;
            i++;
        }

        while (lista->p[j]->rg > pivo && j > ini){
            *Cn = *Cn + 1;
            j--;
        }
        if (i <= j){

            strcpy(auxn, lista->p[i]->nome);
            *Mn = *Mn + 1;
            auxrg = lista->p[i]->rg;
            *Mn = *Mn + 1;
            strcpy(lista->p[i]->nome, lista->p[j]->nome);
            *Mn = *Mn + 1;
            lista->p[i]->rg = lista->p[j]->rg;
            *Mn = *Mn + 1;
            strcpy(lista->p[j]->nome, auxn);
            *Mn = *Mn + 1;
            lista->p[j]->rg = auxrg;
            *Mn = *Mn + 1;
            i++;
            j--;
        }

    } while (i <= j);
    if (j > ini)
    {
        QuickSort(lista, ini, j, Cn, Mn);
    };
    if (i < fim)
    {
        QuickSort(lista, i, fim, Cn, Mn);
    };
}


void Merge(Lista *lista, int ini, int meio, int fim, int *Mn, int *Cn)
{
    int i, j, k;
    int n1 = meio - ini + 1;
    int n2 = fim - meio;


    // Cria Vetores temporarios
    int INIRG[n1], FIMRG[n2];
    char ININ[n1][TAMANHO], FIMN[n2][TAMANHO];


    for (i = 0; i < n1; i++)  // Copia dados para os vetores temporarios
    {
        INIRG[i] = lista->p[ini + i]->rg;

        *Mn = *Mn + 1;
        strcpy(ININ[i], lista->p[ini + i]->nome);
        *Mn = *Mn + 1;

    }
    for (j = 0; j < n2; j++)
    {
        FIMRG[j] = lista->p[meio + 1 + j]->rg;
        *Mn = *Mn + 1;
        strcpy(FIMN[j], lista->p[meio + 1 + j]->nome);
        *Mn = *Mn + 1;

    }

    i = 0;   // Inicio do primeiro vetor temporario
    j = 0;   // Inicio do segundo vetor temporario
    k = ini; // Inicio do vetor unificado

    while (i < n1 && j < n2)
    {

        *Cn = *Cn + 1;
        if (INIRG[i] <= FIMRG[j])
        {
            lista->p[k]->rg = INIRG[i];
            *Mn = *Mn + 1;
            strcpy(lista->p[k]->nome, ININ[i]);
            *Mn = *Mn + 1;

            i++;
        }
        else
        {
            lista->p[k]->rg = FIMRG[j];
            *Mn = *Mn + 1;
            strcpy(lista->p[k]->nome, FIMN[j]);
            *Mn = *Mn + 1;
            j++;
        }
        k++;
    }

    //Copia os elementos dos vetores temporarios, se restaram
    *Cn = *Cn + 1;

    while (i < n1)

    {
        *Cn = *Cn + 1;
        lista->p[k]->rg = INIRG[i];
        *Mn = *Mn + 1;
        strcpy(lista->p[k]->nome, ININ[i]);
        *Mn = *Mn + 1;

        i++;
        k++;
    }


    *Cn = *Cn + 1;
    while (j < n2)
    {
        *Cn = *Cn + 1;
        lista->p[k]->rg = FIMRG[j];
        *Mn = *Mn + 1;
        strcpy(lista->p[k]->nome, FIMN[j]);
        *Mn = *Mn + 1;
        j++;
        k++;
    }

}

void MerSort(Lista *lista, int ini, int fim, int *Cn, int *Mn)
{
    if (ini < fim) // Checagem
    {
        // Evita Overflow
        int meio = ini + (fim - ini) / 2;
        // Se divide em duas partes
        // Se chama para as duas partes
        // Unifica as duas partes ordenadas
        MerSort(lista, ini, meio, Cn, Mn);
        MerSort(lista, meio + 1, fim, Cn, Mn);
        Merge(lista, ini, meio, fim, Cn, Mn);
    }
}






int main(){
    char nomearquivo[30];
    Lista lista;
    int eini, op, Cn = 0, Mn = 0;
    ;
    clock_t ini, fim;
    double time;

        printf("Insira o Nome do Arquivo que deseja ler:\n");
        scanf("%s", nomearquivo);
        ini = clock();
        lista.tamanho = GetTamanho(nomearquivo);
        lista.p = AlocaLista(lista.tamanho);
        CriaLista(nomearquivo, &lista);
        fim = clock();
        time = ((double)(fim - ini)) / CLOCKS_PER_SEC;
        printf("Tempo de execucao: %f\n", time);


    do
    {
        printf("\n\t1- Imprimir Lista\n\t2- Recarregar arquivo original\n\t3-Salvar a lista em um arquivo\n\t4-Ler a lista de um arquivo");
        printf("\n|BUSCA|\n\t5-Busca Sequencial\n\t6-Busca Binaria");
        printf("\n|ORDENACAO|\n\t7-Selection Sort\n\t8-Insertion Sort\n\t9-Bubble Sort\n\t10-Shell Sort\n\t11-Quick Sort\n\t12-Merge Sort\n-> sair do programa\nR: ");

        scanf("%d", &op);
        switch (op)
        {

        case 1:
            ini = clock();
            ImprimeLista(&lista);
            fim = clock();
            time = ((double)(fim - ini)) / CLOCKS_PER_SEC;
            printf("Tempo de execucao: %f\n", time);
            break;
        case 2:
            Desaloca(&lista);
            ini = clock();
            lista.tamanho = GetTamanho(nomearquivo);
            lista.p = AlocaLista(lista.tamanho);
            CriaLista(nomearquivo, &lista);
            fim = clock();
            time = ((double)(fim - ini)) / CLOCKS_PER_SEC;
            printf("Tempo de execucao: %f\n", time);
            break;
        case 3:
            ini = clock();

            printf("\nSalvando Arquivo!\n");
            SalvaArq(&lista);
            printf("\nPronto!\n");
            fim = clock();
            time = ((double)(fim - ini)) / CLOCKS_PER_SEC;
            printf("Tempo de execucao: %f\n", time);
            break;
        case 4:
            Desaloca(&lista);
            printf("Insira o Nome do Arquivo que deseja ler:\n");
            scanf("%s", nomearquivo);
            ini = clock();
            lista.tamanho = GetTamanho(nomearquivo);
            lista.p = AlocaLista(lista.tamanho);
            CriaLista(nomearquivo, &lista);
            fim = clock();
            time = ((double)(fim - ini)) / CLOCKS_PER_SEC;
            printf("Tempo de execucao: %f\n", time);
            break;
        // Busca
        case 5:
            ini = clock();
            BuscaSeq(&lista);
            fim = clock();
            time = ((double)(fim - ini)) / CLOCKS_PER_SEC;
            printf("Tempo de execucao: %f\n", time);
            break;
        case 6:
            ini = clock();
            fim = clock();
            BuscaBin(&lista);
            time = ((double)(fim - ini)) / CLOCKS_PER_SEC;
            printf("Tempo de execucao: %f\n", time);
            break;
        // algoritmos de ordenaçao
        case 7:
            ini = clock();
            SelectionSort(&lista);
            fim = clock();
            time = ((double)(fim - ini)) / CLOCKS_PER_SEC;
            printf("Tempo de execucao: %f\n", time);
            break;
        case 8:
            ini = clock();
            InsertionSort(&lista);
            fim = clock();
            time = ((double)(fim - ini)) / CLOCKS_PER_SEC;
            printf("Tempo de execucao: %f\n", time);
            break;
        case 9:
            ini = clock();
            BubleSort(&lista);
            fim = clock();
            time = ((double)(fim - ini)) / CLOCKS_PER_SEC;
            printf("Tempo de execucao: %f\n", time);
            break;
        case 10:
            ini = clock();
            ShellSort(&lista);
            fim = clock();
            time = ((double)(fim - ini)) / CLOCKS_PER_SEC;
            printf("Tempo de execucao: %f\n", time);
            break;
        case 11:

            ini = clock();
            Cn = 0;
            Mn = 0;
            QuickSort(&lista, 0, lista.tamanho - 1, &Cn, &Mn);
            printf("C(n): %d\n", Cn);
            printf("M(n): %d\n", Mn);

            fim = clock();
            time = ((double)(fim - ini)) / CLOCKS_PER_SEC;
            printf("Tempo de execucao: %f\n", time);
            break;

        case 12:

            ini = clock();
            Cn = 0;
            Mn = 0;
            MerSort(&lista, 0, lista.tamanho - 1, &Cn, &Mn);
            printf("C(n): %d\n", Cn);
            printf("M(n): %d\n", Mn);

            fim = clock();
            time = ((double)(fim - ini)) / CLOCKS_PER_SEC;
            printf("Tempo de execucao: %f\n", time);

            break;

        case -1:
            exit(1);
            break;
        default:
            ("\n Não Existe(\n");
            break;
        }

    } while (op != -1);
}


