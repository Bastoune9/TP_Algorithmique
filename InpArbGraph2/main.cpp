#include <iostream>
#include <vector>
#include <fstream>
#include <list>
#include <cstring>

using namespace std;

/// Version avec une liste d'adjacence (non aboutie)

// Fonction de parcours en profondeur pour trouver l'arbre couvrant (avec liste d'adjacence)
void dfs(int v, vector<list<int>>& adjList, vector<bool>& visited, vector<pair<int, int>>& treeEdges) {
    visited[v] = true;
    for (int u : adjList[v]) {
        if (!visited[u]) {
            treeEdges.push_back({v, u});
            dfs(u, adjList, visited, treeEdges);
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

    // Création de la liste d'adjacence
    vector<list<int>> adjList(n+1);

    for (int i = 0; i < m; i++) {
        int u, v;
        input >> u >> v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
    input.close();

    // Initialisation des structures de visite pour stocker les arêtes de l'arbre couvrant
    vector<bool> visited(n+1, false);
    vector<pair<int, int>> treeEdges;

    // Lancer le parcours en profondeur à partir du sommet 1 (ou n'importe quel sommet)
    dfs(1, adjList, visited, treeEdges);

    // Écriture des résultats dans le fichier de sortie
    for (auto edge : treeEdges) {
        output << edge.first << " " << edge.second << endl;
    }
    output.close();

    return 0;
}

// En reprenant le même exemple que la partie précédente, je n'obtiens rien en sortie
