#include <fstream>
#include <cstring>


int main() {
    int x = 5;
    int y = 0;
    int * ya = new int[10];
    memset(ya, 0, sizeof(int) * 10);

    std::ofstream fil("hej");

    //if(!fil.good()) {
        fil.open("hej", std::ios::out | std::ios::binary);

        for(int i = 0; i < 10; i++) {
            fil.write((char *)&x, sizeof(int));
            x = x + 1;
        }
        printf("WRITE COMPLETE\n");
        fil.close();

    //} else {
        std::ifstream afil;
        afil.open("hej", std::ios::in | std::ios::binary);

        afil.seekg (0, afil.beg);

        printf("READ COMPLETE\n");
        printf("y: %d\n", y);
        for(int n = 0; n < 10; n++) {
            afil.read((char *)&y, sizeof(int));
            ya[n] = y;
        }
        for(int n = 0; n < 10; n++) {
            printf("%d\n", ya[n]);
        }
    //}

    afil.close();
}
