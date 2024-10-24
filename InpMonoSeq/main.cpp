#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cerrno>
#include <cstring>

using namespace std;

int main() {
    // Ouverture des fichiers entrée / sortie
    ifstream input("/home/bastien/CLionProjects/InpMonoSeq/INPMONOSEQ.TXT");
    if (!input.is_open()) {
        cerr << "Erreur d'ouverture du fichier input : " << strerror(errno) << endl;
        return 1;
    }
    ofstream output("/home/bastien/CLionProjects/InpMonoSeq/OUTMONOSEQ.TXT");
    if (!output.is_open()) {
        cerr << "Erreur d'ouverture du fichier output : " << strerror(errno) << endl;
        return 1;
    }
    // Lecture de l'entrée
    int n;
    input >> n;

    vector<int> a(n);
    for (int i=0; i<n; i++) {
        input >> a[i];
    }

    vector<int> tab(n, 1);  // Pour stocker la longueur max de la chaîne terminée par l'élément
    vector<int> prev(n, -1);  // Pour stocker les indices des éléments précédents

    for (int i=1; i<n; i++) {
        // On détermine la chaîne la plus longue terminée par cet élément à partir des résultats des éléments précédents
        for (int j=0; j<i; j++) {
            if (a[i] > a[j] && tab[i] < tab[j] + 1) {
                tab[i] = tab[j] + 1;
                prev[i] = j;
            }
        }
    }
    // Longueur de la sous-séquence la plus longue
    int lenMax = *max_element(tab.begin(), tab.end());
    // Index de la fin de la séquence la plus longue
    int lastIndex = max_element(tab.begin(), tab.end()) - tab.begin();

    // Reconstruction de la sous-séquence de la fin vers le début (à partir du dernier élément)
    vector<int> longestSubsequence;
    vector<int> indices;

    for (int i = lastIndex; i != -1; i = prev[i]) {
        longestSubsequence.push_back(a[i]);
        indices.push_back(i + 1);
    }

    // Inverser la séquence pour obtenir l'ordre correct
    reverse(longestSubsequence.begin(), longestSubsequence.end());
    reverse(indices.begin(), indices.end());

    // Écrire les résultats dans le fichier de sortie
    output << lenMax << endl;
    for (size_t i = 0; i < longestSubsequence.size(); i++) {
        output << "a[" << indices[i] << "] = " << longestSubsequence[i] << endl;
    }

    input.close();
    output.close();
    return 0;
}