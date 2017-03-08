#include <cstdio>
#include <unistd.h>
#include <ctime>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm> //För std::replace
#include <iostream>

#define DEBUG 0

std::string seek(int position, FILE * file, int offset, int length) {
    char buffer [length];
    std::string completeBuffer = "";

    if (file == NULL) {
        perror ("Öppningen misslyckades.");
    } else {
        if(position + offset < 0) {
            fseek(file, 0, SEEK_SET);
        } else {
            fseek(file, position + offset, SEEK_SET);
        }
        long int currentPosition = ftell(file);
        while(currentPosition - (position + offset) < length) {
            if (fgets(buffer, length - (currentPosition - (position + offset)), file) != NULL) {
                std::string str(buffer);
                completeBuffer = completeBuffer + str;
            }
            if (currentPosition == ftell(file)) {
                break;
            } else {
                currentPosition = ftell(file);
            }
        }
    }
    return completeBuffer;
}

int converter(std::string buffer) {
    int wprefix[3] = {0};

    for(int i = 0; i < 3; i++) {
        if (buffer[i] >= 65 and buffer[i] <= 90) {
            wprefix[i] = buffer[i] - 64;
        } else if (buffer[i] >= 97 and buffer[i] <= 122) {
            wprefix[i] = buffer[i] - 96;
        } else if (buffer[i] == -27) {
            wprefix[i] = 26;
        } else if (buffer[i] == -28) {
            wprefix[i] = 27;
        } else if (buffer[i] == -10) {
            wprefix[i] = 28;
        } else {
            wprefix[i] = 0;
        }
    }

    return wprefix[0] * 900 + wprefix[1] * 30 + wprefix[2];
}

std::string toIso(std::string input) {
    std::string output = "";
    for (unsigned int i = 0; i < input.length(); i++) {
        char back = input.at(i);
        if(back >= 65 and back <= 90) {
            output.push_back(back + 32);
        } else if(back >= 97 and back <= 122) {
            output.push_back(back);
        } else if(back == -61) {
            i++;
            back = input.at(i);
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
    }

    return output;
}

int * binSearch(std::string word, int * indexArray, FILE * file) {
    int wprefix = converter(word);
    unsigned int n = 1;
    while (indexArray[wprefix + n] == -1) {
        n++;
    }
    int i = indexArray[wprefix];
    int j = indexArray[wprefix + n];

    int m;
    int chunkSize = 1101; //Sets breakpoint for when to switch to linear search

    std::vector<std::string> sword;
    while (j-i > chunkSize) {
        m = (i+j)/2;
        std::string buffer;

        std::stringstream ss(seek(m, file, 0, chunkSize));
        //printf("intervall from m is: %s\n",seek(m, file, 0, chunkSize).c_str());

        while(std::getline(ss, buffer)) {
            sword.push_back(buffer);
        }
        if (std::strcoll(word.c_str(), sword[1].c_str()) > 0) {
            //större än noll = str1 är alfabetiskt större än str2
            i = m;
        } else {
            j = m;

        }
        sword.clear();
    }

    int * positionArray = new int[1000000];
    memset(positionArray, -1, sizeof(int)*1000000);
    int k = 0;
    //printf("BinSearch DONE i: %d, interval is %d\n",i,j-i);
    int found = 0;
    int foundAll = 0;
    int lastLength = 1;
    char ch = ' ';
    std::string lastLine;

    for(int p = 0; foundAll == 0; p++) {
        std::string buffer;
        std::string intervalString = seek(i + (p*(chunkSize)-lastLength), file, 0, chunkSize);
        ch = *intervalString.rbegin();
        if (ch == '\n') {
            intervalString.append("l");
        }
        std::stringstream ss(intervalString);
        std::vector<std::string> sword;

        //printf("intervall from i beginning at %d  to %d is:\n%s\n",i+(p*chunkSize)-lastLength,i+(p*chunkSize)-lastLength+chunkSize-2,intervalString.c_str());
        for(int q ; std::getline(ss, buffer); q++) {
            sword.push_back(buffer);
        }
        if ((int)sword.size() > 0) {
            lastLine = sword.back();
            sword.pop_back();
        } else {
            return positionArray;
        }
        lastLength = lastLength + lastLine.length()+1;
        int numberBuffer;

        for(n = 0; n < sword.size(); n++) {
            std::stringstream temp(sword[n]);
            while(temp >> buffer) {
                if (std::strcoll(word.c_str(), buffer.c_str()) == 0) {
                   if(temp >> numberBuffer) {
                       positionArray[k] = numberBuffer;
                       k++;
                   } else {
                       printf("Fel - siffra saknas.\n");
                   }
                   found = 1;
               } else {
                   if(found == 1) {
                       //printf("Stopped at %s == %s\n",word.c_str(),buffer.c_str());
                       foundAll = 1;
                       return positionArray;
                   }
                }
            }
        }
        if (!found) {
            return positionArray;
           }
    }
    return positionArray;
}

int * createIndexArray()
{
    const int indexSize = 27930;
    int position = 0;
    int * indexArray = new int[indexSize];
    memset(indexArray, -1, sizeof(int)*indexSize);

    //std::ifstream index("text2");
    std::ifstream index("/var/tmp/i_stands_for_index");
    std::string buffer;

    std::fstream arrayFile;
    if (0 || access("indextest.bin", F_OK) != 0) {
        printf("Skapar ny fil.\n");
        arrayFile.open("indextest.bin", std::fstream::out | std::fstream::binary);
        index.seekg(0, std::ios::end);
        position = index.tellg();
        indexArray[indexSize-1] = position;
        index.seekg(0, std::ios::beg);
        position = index.tellg();

        for (int p = 0; std::getline(index, buffer); p++) {
            int locationInIndexArray = converter(buffer);
            if(indexArray[locationInIndexArray] == -1) {
                indexArray[locationInIndexArray] = position;
            }
            position = index.tellg();
        }
        for(int i = 0; i < indexSize; i++) {
            arrayFile.write((char*)&indexArray[i], sizeof(int));
        }
        arrayFile.flush();
        printf("Fil skapad.\n");
        system("date +%S.%9N");
    } else {
        printf("Filen finns.\n");
        arrayFile.open("indextest.bin", std::fstream::in | std::fstream::binary);
        for(int i = 0; i < indexSize; i++) {
            arrayFile.read((char*)&position, sizeof(int));
            indexArray[i] = position;
        }
        printf("Filen har lästs.\n");
    }
    arrayFile.close();
    return indexArray;
}

int main(int argc, char** argv)
{
    int * indexArray = createIndexArray();


    FILE * indexFile;
    //indexFile = fopen("text2", "r");
    indexFile = fopen("/var/tmp/i_stands_for_index", "r");

    FILE * textFile;
    //textFile = fopen("text", "r");
    textFile = fopen("/info/adk15/labb1/korpus", "r");

    if (argc < 2) {
        std::cerr << "FEL: Inget sökord har angivits som argument!" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    std::string word(argv[1]);
    word = toIso(word);
    printf("Sökta ordet: %s\n", word.c_str());
    clock_t begin = clock();
    int * result = binSearch(word, indexArray, indexFile);
    clock_t end = clock();
    double estimated_elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    if(result[0] == -1) {
        printf("Hittade inte ordet.\n");
    } else {
        int i;
        for(i = 0; i < 10000000; i++) {
            if(result[i] == -1) {
                printf("Det finns %d förekomst(er) av ordet.\n", i);
                printf("Ungefärlig tid: %f.\n",estimated_elapsed_secs);
                break;
            }
        }
        std::string answer = "n";
        if(i > 25) {
            std::cout << "Det finns fler än 25 förekomster. Vill du visa? [y/n] ";
            std::cin >> answer;
        }
        if(i <= 25 || answer == "y"){
            for(int i = 0; i < 1000000; i++) {
                if(result[i] == -1) {
                    break;
                }
                std::string foundString = seek(result[i], textFile, -30, 80).c_str();
                std::replace(foundString.begin(), foundString.end(), '\n', ' ');
                printf("%s\n", foundString.c_str());
            }
        }
    }
    fclose(indexFile);
    fclose(textFile);

    delete(indexArray);
    delete(result);

    return 0;
}


