#include <omp.h>
#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

class Node
{
public:
    int value;
    Node *left;
    Node *right;
    Node() {}
    Node(int value)
    {
        this->value = value;
        this->left = NULL;
        this->right = NULL;
    }
};

Node *generateTree(int values[], int length)
{
    if (length == 0)
        return NULL;
    Node *treeNodes[length];
    for (int i = 0; i < length; i++)
        treeNodes[i] = (values[i] != -1) ? new Node(values[i]) : NULL;

    int parent = 0, child = 1;
    while (child < length)
    {
        if (treeNodes[parent] != NULL)
        {
            treeNodes[parent]->left = treeNodes[child++];
            if (child < length)
                treeNodes[parent]->right = treeNodes[child++];
        }
        parent++;
    }
    return treeNodes[0];
}

void sequential_dfs(Node *root)
{
    if (root == NULL)
        return;

    cout << root->value << " -> ";
    sequential_dfs(root->left);
    sequential_dfs(root->right);
}

void parallel_dfs(Node *root)
{
    if (root == NULL)
        return;

#pragma omp critical
    cout << root->value << " -> ";

#pragma omp parallel sections
    {
#pragma omp section
        parallel_dfs(root->left);
#pragma omp section
        parallel_dfs(root->right);
    }
}

int main()
{
    int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    int length = sizeof(values) / sizeof(int);
    Node *root = generateTree(values, length);

    // Sequential DFS
    auto start_seq = high_resolution_clock::now();
    cout << "Sequential DFS: ";
    sequential_dfs(root);
    auto stop_seq = high_resolution_clock::now();
    auto duration_seq = duration_cast<microseconds>(stop_seq - start_seq);
    cout << "\nExecution time for Sequential DFS: " << duration_seq.count() << " microseconds\n";

    // Parallel DFS
    auto start_par = high_resolution_clock::now();
    cout << "Parallel DFS: ";
    parallel_dfs(root);
    auto stop_par = high_resolution_clock::now();
    auto duration_par = duration_cast<microseconds>(stop_par - start_par);
    cout << "\nExecution time for Parallel DFS: " << duration_par.count() << " microseconds\n";

    return 0;
}
