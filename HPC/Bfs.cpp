#include <omp.h>
#include <iostream>
#include <queue>
#include <vector>
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

void sequential_bfs(Node *root)
{
    if (!root)
        return;
    queue<Node *> q;
    q.push(root);

    while (!q.empty())
    {
        Node *node = q.front();
        q.pop();
        cout << node->value << " -> ";

        if (node->left)
            q.push(node->left);
        if (node->right)
            q.push(node->right);
    }
}

void parallel_bfs(Node *root)
{
    if (!root)
        return;
    queue<Node *> q;
    q.push(root);

    while (!q.empty())
    {
        int level_size = q.size();
        vector<Node *> current_level;

        for (int i = 0; i < level_size; i++)
        {
            Node *node = q.front();
            q.pop();
            current_level.push_back(node);
        }

#pragma omp parallel for
        for (int i = 0; i < current_level.size(); i++)
        {
#pragma omp critical
            cout << current_level[i]->value << " -> ";

#pragma omp critical
            {
                if (current_level[i]->left)
                    q.push(current_level[i]->left);
                if (current_level[i]->right)
                    q.push(current_level[i]->right);
            }
        }
    }
}

int main()
{
    int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    int length = sizeof(values) / sizeof(int);
    Node *root = generateTree(values, length);

    // Sequential BFS
    auto start_seq = high_resolution_clock::now();
    cout << "Sequential BFS: ";
    sequential_bfs(root);
    auto stop_seq = high_resolution_clock::now();
    auto duration_seq = duration_cast<microseconds>(stop_seq - start_seq);
    cout << "\nExecution time for Sequential BFS: " << duration_seq.count() << " microseconds\n";

    // Parallel BFS
    auto start_par = high_resolution_clock::now();
    cout << "Parallel BFS: ";
    parallel_bfs(root);
    auto stop_par = high_resolution_clock::now();
    auto duration_par = duration_cast<microseconds>(stop_par - start_par);
    cout << "\nExecution time for Parallel BFS: " << duration_par.count() << " microseconds\n";

    return 0;
}
