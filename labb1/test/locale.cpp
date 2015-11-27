#include <cstring>
#include <sstream>
#include <stdio.h>

std::string toIso(std::string input) {
    std::string output = "";
    for (int i = 0; i < input.length(); i++) {
        char back = input.at(i);
        printf("Back: %d\n", (int)back);
        if(back >= 65 and back <= 90) {
            output.push_back(back + 32);
        } else if(back >= 97 and back <= 122) {
            output.push_back(back);
        } else if(back == -61) {
            i++;
            back = input.at(i);
            printf("Back2: %d\n", (int)back);
            if(back == -91 or back == -123) {
                output.push_back(-27);
            } else if (back == -92 or back == -124) {
                output.push_back(-28);
            } else if (back == -74 or back == -106) {
                output.push_back(-10);
            } else {
                output.push_back(32);
            }
        } else {
            output.push_back(32);
        }

        printf("%s\n", output.c_str());
    }
    return output;
}

int main(int argc, char** argv) {
    char buffer [30];
    FILE * fil;
    fil = fopen("aaotestiso", "r");

    if (fgets(buffer, 30, fil) != NULL) {
        std::string str(buffer);
        printf("%s", str.c_str());
        for(int i = 0; i < str.length(); i++) {
            printf("%d ", (int)str.at(i));
        }
        printf("\n");
        std::string str2(argv[1]);
        printf("%s\n", str2.c_str());
        for(int i = 0; i < str2.length(); i++) {
            printf("%d ", (int)str2.at(i));
        }
        printf("\n");
        printf("%s\n", str2.c_str());
        if(std::strcoll(str.c_str(), (str2 + "\n").c_str()) == 0) {
            printf("MATCH\n");
        }
        std::string argvIso = toIso(argv[1]);
        printf("ISO: %s\n", argvIso.c_str());
        for(int i = 0; i < argvIso.length(); i++) {
            printf("%d ", (int)argvIso.at(i));
        }
        printf("\n");
    }
}
