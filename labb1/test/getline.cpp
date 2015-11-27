#include <stdio.h>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm> //För std::replace
#include <iostream>
int main()
{
       /*
    FILE* file = fopen("text", "r");
    char temp	[100];

    fgets(temp,99,file);
    for (int i = 0; i< 100; ++i){
        std::cout << temp[i]<< std::endl;
    }*/
    std::string buffer;
    std:: string intervalString = "csaaca\nadasdas\nsdggvs\naga";
    std::stringstream ss(intervalString);
    std::vector<std::string> sword;
    for(int q ; std::getline(ss, buffer); q++) {
        sword.push_back(buffer);
        printf("buffer == %s\n",buffer.c_str());
    }
    return 0;
}
