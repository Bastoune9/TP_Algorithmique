#include <iostream>
#include <vector>
#include <fstream>
#include <list>
#include <cstring>

using namespace std;

/// Version avec la liste d'adjacence

// Fonction de parcours en profondeur pour explorer une composante connexe
void dfs(int v, vector<list<int>>& adjList, vector<bool>& visited, vector<int>& component) {
    visited[v] = true;
    component.push_back(v);  // Ajouter ce sommet à la composante
    for (int u : adjList[v]) {
        if (!visited[u]) {
            dfs(u, adjList, visited, component);
        }
    }
}

int main() {
    // Ouverture des fichiers entrée / sortie
    ifstream input("/home/bastien/CLionProjects/InpConGraph2/INPCONGRAPH.TXT");
    if (!input.is_open()) {
        cerr << "Erreur d'ouverture du fichier input." << strerror(errno) << endl;
        return 1;
    }

    ofstream output("/home/bastien/CLionProjects/InpConGraph2/OUTCONGRAPH.TXT");
    if (!output.is_open()) {
        cerr << "Erreur d'ouverture du fichier output." << strerror(errno) << endl;
        return 1;
    }

    // Lecture du nombre de sommets et d'arêtes
    int n, m;
    input >> n >> m;

    // Création de la liste d'adjacence
    vector<list<int>> adjList(n+1);

    // Lecture des arêtes
    for (int i = 0; i < m; i++) {
        int u, v;
        input >> u >> v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
    input.close();

    // Initialisation des structures de visite
    vector<bool> visited(n+1, false);
    vector<vector<int>> components;

    // Exploration des composantes connexes avec le parcours en profondeur
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            vector<int> component;
            dfs(i, adjList, visited, component);
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
