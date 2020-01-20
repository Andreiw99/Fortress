#include <stdio.h>
#include <stdlib.h>
#include "functiigraf.h"
#include <time.h>
int main() {
    FILE *out_file = fopen ("dataout.txt", "w");
    struct a_graph *graph;        // Se declara structura de graf
    int start_node;
    clock_t start,finish;
    double duration;
    start=clock();
    printf("Introduceti nodul de la care porneste parcurgerea: ");
    scanf("%d", &start_node);
    generate();                     // Se genereaza numarul de turnuri si de tunele random
    graph = calloc(1, sizeof(struct a_graph));
    init_graph_file(graph);
    graph_bfs(graph, start_node);     // Se parcurge grafu de la start_node
    while(PozZero(graph->no_nodes-1) != 0)    // Se testeaza daca are compopente conexe
        graph_bfs(graph,PozZero(graph->no_nodes));  // Se parcurge fiecare componenta conexa
    if(done != 0)     // Daca variabila done este diferita de 0 inseamna ca s-a gasit o componenta conexa care nu respecta regula
        fprintf(out_file,"NU");
    else
        fprintf(out_file,"DA");
    finish=clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    fprintf(out_file, "\nduration: %.3fs ", duration);
    fclose(out_file);
    return 0;
}
