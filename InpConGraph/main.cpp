#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>

using namespace std;

/// Version avec la matrice d'adjacence

// Fonction de parcours en profondeur pour explorer une composante connexe
void dfs(int v, vector<vector<int>>& adjMatrix, vector<bool>& visited, vector<int>& component) {
    visited[v] = true;
    component.push_back(v);  // Ajouter ce sommet à la composante
    for (int u = 1; u < adjMatrix.size(); u++) {
        if (adjMatrix[v][u] && !visited[u]) {
            dfs(u, adjMatrix, visited, component);
        }
    }
}

int main() {
    // Ouverture des fichiers entrée / sortie
    ifstream input("/home/bastien/CLionProjects/InpConGraph/INPCONGRAPH.TXT");
    if (!input.is_open()) {
        cerr << "Erreur d'ouverture du fichier input." << strerror(errno) << endl;
        return 1;
    }

    ofstream output("/home/bastien/CLionProjects/InpConGraph/OUTCONGRAPH.TXT");
    if (!output.is_open()) {
        cerr << "Erreur d'ouverture du fichier output." << strerror(errno) << endl;
        return 1;
    }

    // Lecture du nombre de sommets et d'arêtes
    int n, m;
    input >> n >> m;

    // Création de la matrice d'adjacence
    vector<vector<int>> adjMatrix(n+1, vector<int>(n+1, 0));

    // Lecture des arêtes
    for (int i = 0; i < m; i++) {
        int u, v;
        input >> u >> v;
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;
    }
    input.close();

    // Initialisation des structures de visite
    vector<bool> visited(n+1, false);
    vector<vector<int>> components;

    // Exploration des composantes connexes avec un parcours en profondeur
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            vector<int> component;
            dfs(i, adjMatrix, visited, component);
            components.push_back(component);
        }
    }

    // Écriture du nombre de composantes connexes
    output << components.size() << endl;

    // Écriture des composantes connexes
    for (int i = 0; i < components.size(); i++) {
        output << "composante connexe " << i+1 << endl;
        for (int v : components[i]) {
            output << v << " ";
        }
        output << endl;
    }
    output.close();

    return 0;
}

