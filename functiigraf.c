#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functiigraf.h"



void generate()
{
    FILE *file=fopen("datain.txt", "w");    // se deschide fisierul datain.txt pentru a scrie in el
    srand(time(NULL));
    int towers,tunnels;
    towers = rand()%20000;  // se genereaza un numar random de turnuri
    tunnels = rand()%(2*towers); // se genereaza un numar random de tunele cuprins intre [0, 2*turnuri]
                                 // deoarece intr-un graf complet, numarul maxim de tunele este egal cu 2*turnuri

    int x,y;        // x, y sunt turnurile intre care exista drum
    fprintf(file, "%d %d\n", towers, tunnels);
    int iterator;
    for(iterator=1;iterator<=tunnels;iterator++)
    {
        x = rand()%towers;
        y = rand()%towers;
        if(x!=y)                // Nu poate exista tunel pentru un singur tutn
            fprintf(file, "%d %d\n", x, y);
        else
            iterator--;
    }
    fclose(file);   // se inchide fisierul datain.txt
}

void set_adj_matrix_value(struct a_graph *graph, int row_index, int column_index, int element_value){       // Se creeaza matricea
    int position;
    position = row_index * graph->no_nodes + column_index;
    *(graph->adj_matrix + position) = element_value;
}


int get_adj_matrix_value(struct a_graph *graph, int row_index, int column_index) {      // Atribuie valoare elementelor din matrice
    int position;
    if (graph->init == 1){
        position = row_index * graph->no_nodes + column_index;
        return *(graph->adj_matrix + position);
    }else
        return -1;
}

void init_graph_file(struct a_graph *graph){
    FILE *file = fopen("datain.txt", "r");      // Se deschide fisierul datain.txt pentru a citi valori din el
    int aux1, aux2;                             // Reprezinta turnurile intre care este un tunel
    int no_tunnles;
    if (file == NULL){      // Se testeaza daca este valori in fisiser
        printf("\n File does not exist.");
        fclose(file);
        return;
    }
    fscanf(file, "%d", &graph->no_nodes);       // Se citeste numarul de turnuri
    fscanf(file, "%d", &no_tunnles);            // Se citeste numarul de tunele
    graph->init = 1;
    graph->adj_matrix = calloc(graph->no_nodes * graph->no_nodes, sizeof(int));     // Se aloca memeorie pentru matricea de adiacenta
    int i;
    for(i=0;i<no_tunnles;i++)
    {
        fscanf(file, "%d ", &aux1);
        fscanf(file, "%d ", &aux2);
        set_adj_matrix_value(graph, aux1, aux2, 1);         // Se creeaza matricea de adiacenta ( adica pe linia aux1 si coloana aux2 se pune 1)
        set_adj_matrix_value(graph, aux2, aux1, 1);         //  Pe linia aux2 si coloana aux1 se pune 1
    }

    fclose(file);
}

void push_begining_list(struct a_list_node *head, int new_element_value){       // Se insereaza un element la inceputul listei
    struct a_list_node *new_element;
    new_element = malloc(sizeof(struct a_list_node));
    new_element->info = new_element_value;
    new_element->next = head->next;
    head->next = new_element;
}

int pop_end_list(struct a_list_node *head) {        // Se elimina un element de la sfarsitul listei
    struct a_list_node *deleted_element;
    struct a_list_node *iterator;
    int aux;

    if (head->next != NULL) {
        for (iterator = head; iterator->next->next != NULL; iterator = iterator->next);
        deleted_element = iterator->next;
        aux = deleted_element->info;
        iterator->next = deleted_element->next;
        free(deleted_element);
        return aux;
    } else
        return -1;      //lista este goala
}

int PozZero(int number)         // Se testeaza daca in vectorul declarat global exista numarul 0 si se returneaza pozitia unde s-a gasit acesta.
                                // Aceasta functie este necesara in cazul in care exista mai multe componente conexe.
{
    int iterator;
    for(iterator=1;iterator<=number;iterator++)
        if(vector[iterator]==0)
            return iterator;
    return 0;
}


void graph_bfs(struct a_graph *graph, int start_node){      // Se parcurge graful si se testeaza daca respecta regula de a exista tunele intre turnurile de atac si cele de aparare a
    struct a_list_node *head_queue;
    int *visited;
    int count=0;        // Variabila count este ultilizata pt a vedea daca exista noduri izolate
    int column_index;
    int aux;
    int current_node;
    int k=2,check=0;
    head_queue = calloc(1, sizeof(struct a_list_node));     // Se aloca memorie pentru crearea unei cozi
    head_queue->next = NULL;
    visited = calloc((graph->no_nodes), sizeof(int));      // Se aloca memorie pentru crearea unui vector care sa retina prin ce noduri s-a trcut
    push_begining_list(head_queue, start_node);            // Se insereaza in coada nodul de la care se pleaca cand se parcurge
    visited[start_node] = 1;            // Start_node-ul a fost vizitat
    vector[start_node]=1;
 //   printf("\nBFS traversal: ");
    while (head_queue->next != NULL){           // Se parcurge lista
        current_node = pop_end_list(head_queue);      // Se sterge ultimul   element din lista
 //      printf("%d,",current_node);
        count++;
        for(column_index = 0; column_index < graph->no_nodes; column_index++){
            aux = get_adj_matrix_value(graph, current_node, column_index);

            if ( (aux != 0) && ( (visited[column_index]) == 0 )){       // Se testeaza daca valoare din matrice de pe linia data de curent_node si coloana data de
                                                                        // column_index este diferita de 0 si nu a fost vizitata inainte.
                push_begining_list(head_queue, column_index);           // Se adauga la coada
                visited[column_index] = 1;                              // Si visited de pe pozitia indexului coloanei se face 1, ceea ce inseamna ca tocmai a fost vizitat.
                vector[column_index]=k;          // De fiecare data cand se mai adauga un copil in lista, in vectorul nostru se adauga un iterator ( k ) care se mareste constant.
                check=1;                   // Variabila check este folosita pentru a verifica daca se intra in if
            }
        }
        if(check==1)        // Daca s-a intrat in if
            k++;            // Iteratorul nostru se mareste cu o unitate.
        check=0;            // check revine la valoarea initala
    }
    int ok=1;
    int iterator1;
    int iterator2;
    if(graph->init == 1)
    {
        if(count==1)        // Daca este doar un nod izolat se respecta conditia de a fi de atac/aparare
            ok=1;
        else
        {
            for(iterator1=0;iterator1<graph->no_nodes;iterator1++)      // Se parcurge matricea
                for(iterator2=0;iterator2<graph->no_nodes;iterator2++)
                {
                    aux = get_adj_matrix_value(graph, iterator1, iterator2);
                    if(aux == 1 && (vector[iterator1] == vector[iterator2]) && vector[iterator1]!=0 && vector[iterator2]!=0)    // Daca elementul din matrice este 1 si elementul din vector
                                                                                                            // de pe pozitia iterator1 este egal cu elementul din vector
                                                                                                            // de pe pozitia iterator2 si sunt diferite de 0, atunci nu se
                                                                                                            // pot alege turnurile si tunelele astfel incat sa exista tunel
                                                                                                            // doar intre un turn de atac si unul de aparare
                        ok=0;
                }
        }
    }
    if(ok != 1)
        done++; // Daca se gaseste o componenta conexa la care nu se respecta regula de a avea un tunel intre atac si aparare variabila done se mareste;

    free(head_queue);
    free(visited);
}


