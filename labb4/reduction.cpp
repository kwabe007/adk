
#include <iostream>


int main () {
    // Två trick för att göra cin/cout lite snabbare.
    // Se http://kattis.csc.kth.se/doc/iostreamio
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    unsigned int v, e, m, n, s, k;
    std::cin >> v >> e >> m;

    // The values below are derived from converting from the most trivial colouring case to the most trivial casting case
    n = v + 2; //roles equal to vertices plus two
    s = e + 2; //scenes are edges plus two
    k = m + 2; //actors are colours plus two

    // Print obligatory roles for divas and one random to make sure they dont have a beef
    std::cout << n << " " << s << " " << k << "\n";
    std::cout << "1 " << "1\n";
    std::cout << "1 " << "2\n";
    std::cout << "1 " << "3\n";

    // Print rest of roles for all the randoms
    for (unsigned int i = 0; i < v-1; ++i) {
        std::cout << m;
        for (unsigned int j = 3; j <= k; ++j) std::cout << " " << j;
        std::cout << "\n";
    }

    // Print obligatory scenes
    std::cout << "2 1 3\n";
    std::cout << "2 2 3\n";

    // Print rest of scenes for all the randoms
    for (unsigned int i = 0; i < e; ++i) {
        unsigned int x, y = 0; //edges denoted by vertex x and y
        std::cout << "2";
        std::cin >> x >> y;
        x += 2; //for all vertices, vertex z corresponds to role z+2
        y += 2;
        std::cout << " " << x << " " << y << "\n";
    }

    //KOMPLEXITET BIG OH N^2

    return 0;

}
