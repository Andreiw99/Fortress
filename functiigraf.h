
#ifndef CODE_SKELETON_GRPAPHS_GRAPHS_H
#define CODE_SKELETON_GRPAPHS_GRAPHS_H

struct a_graph {
    int no_nodes;
    int init;
    int *adj_matrix;
};

struct a_list_node{
    int info;
    struct a_list_node *next;
};
int vector[100000];
int done;
void set_adj_matrix_value(struct a_graph *graph, int row_index, int column_index, int element_value);
void init_graph_file(struct a_graph *graph);
void push_begining_list(struct a_list_node *head, int new_element_value);
void graph_bfs(struct a_graph *graph, int start_node);
int pop_end_list(struct a_list_node *head);
int get_adj_matrix_value(struct a_graph *graph, int row_index, int column_index);
int PozZero(int n);
void generate();

#endif //CODE_SKELETON_GRPAPHS_GRAPHS_H
