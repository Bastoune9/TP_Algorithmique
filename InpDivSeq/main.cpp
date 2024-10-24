#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>

using namespace std;

// Fonction principale
int main() {
    // Ouverture des fichiers entrée / sortie
    ifstream input("/home/bastien/CLionProjects/InpDivSeq/INPDIVSEQ.TXT");
    if (!input.is_open()) {
        cerr << "Erreur d'ouverture du fichier input : " << strerror(errno) << endl;
        return 1;
    }
    ofstream output("/home/bastien/CLionProjects/InpDivSeq/OUTDIVSEQ.TXT");
    if (!output.is_open()) {
        cerr << "Erreur d'ouverture du fichier output : " << strerror(errno) << endl;
        return 1;
    }

    // Lecture de l'entrée
    int n, k;
    input >> n >> k;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        input >> a[i];
    }

    // dp[i][j] = meilleure longueur de sous-séquence avec une somme de modulo j, jusqu'à l'élément i.
    vector<vector<int>> dp(n+1, vector<int>(k, -1));
    vector<vector<int>> sums(n+1, vector<int>(k, 0));  // Pour stocker la somme associée à dp

    // Cas initial
    dp[0][0] = 0;  // Si aucune chaîne ne satisfait la condition de division, on renvoie 0

    // Parcourir tous les éléments du tableau
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < k; j++) {
            dp[i][j] = dp[i-1][j];  // Copie du cas sans utiliser a[i-1]
            sums[i][j] = sums[i-1][j];
        }

        for (int j = 0; j < k; j++) {
            if (dp[i-1][j] != -1) {
                int new_mod = (j + a[i-1]) % k;
                int new_sum = sums[i-1][j] + a[i-1];

                // Mise à jour si la nouvelle longueur est meilleure
                if (dp[i-1][j] + 1 > dp[i][new_mod]) {
                    dp[i][new_mod] = dp[i-1][j] + 1;
                    sums[i][new_mod] = new_sum;
                }
            }
        }
    }

    // La meilleure sous-séquence est celle avec un reste de 0
    int max_length = dp[n][0];
    int total_sum = sums[n][0];

    // Extraction des éléments de la meilleure sous-séquence
    vector<int> result;
    int mod = 0;

    for (int i = n; i > 0 && max_length > 0; i--) {
        if (dp[i][mod] != dp[i-1][mod]) {
            result.push_back(a[i-1]);
            mod = (mod - a[i-1] % k + k) % k;
            max_length--;
        }
    }

    // Écriture dans le fichier de sortie
    output << result.size() << endl;
    for (int i = result.size() - 1; i >= 0; i--) {
        output << "a[" << i + 1 << "] = " << result[i] << endl;
    }
    output << "Sum = " << total_sum << endl;

    // Fermeture des fichiers
    input.close();
    output.close();

    return 0;
}
