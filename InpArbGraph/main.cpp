#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>

using namespace std;

/// Version avec la matrice d'adjacence

// Fonction de parcours en profondeur pour trouver l'arbre couvrant
void dfs(int v, vector<vector<int>>& adjMatrix, vector<bool>& visited, vector<pair<int, int>>& treeEdges) {
    visited[v] = true;
    for (int u = 1; u < adjMatrix.size(); u++) {
        if (adjMatrix[v][u] && !visited[u]) {
            treeEdges.push_back({v, u});
            dfs(u, adjMatrix, visited, treeEdges);
        }
    }
}

int main() {
    // Ouverture des fichiers entrée / sortie
    ifstream input("/home/bastien/CLionProjects/InpArbGraph/INPARBGRAPH.TXT");
    if (!input.is_open()) {
        cerr << "Erreur d'ouverture du fichier input." << strerror(errno) << endl;
        return 1;
    }

    ofstream output("/home/bastien/CLionProjects/InpArbGraph/OUTARBGRAPH.TXT");
    if (!output.is_open()) {
        cerr << "Erreur d'ouverture du fichier output." << strerror(errno) << endl;
        return 1;
    }


    // Lecture de l'entrée
    int n, m;
    input >> n >> m;

    // Création de la matrice d'adjacence (n+1 pour indices 1-based)
    vector<vector<int>> adjMatrix(n+1, vector<int>(n+1, 0));

    for (int i = 0; i < m; i++) {
        int u, v;
        input >> u >> v;
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;
    }
    input.close();

    // Initialisation des structures de visite et pour stocker les arêtes de l'arbre couvrant
    vector<bool> visited(n+1, false);
    vector<pair<int, int>> treeEdges;

    // Lancer le parcours en profondeur à partir du sommet 1 (choisi arbitrairement)
    dfs(1, adjMatrix, visited, treeEdges);

    // Écriture des résultats dans le fichier de sortie
    for (auto edge : treeEdges) {
        output << edge.first << " " << edge.second << endl;
    }

    output.close();

    return 0;
}