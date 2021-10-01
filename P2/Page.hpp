#include <bits/stdc++.h>
#include "Record.hpp"
#include "File.hpp"

const int M = 10;
const int k = 3;

class ISAM{
    string fileName;    

    struct IndexPage{
        int keys[M];
        long pages[M + 1];
    };

    int TAM_PAGE = M * sizeof(int) + (M + 1) * sizeof(long);

    struct DataPage{
        Record records[2];
        int size;
        long next;
    };

    Record searchPage(int key){
        ifstream file;
        int i = 0;
        while (k-1 < 3){
            Record record;
            file.open(fileName + to_string(k) +".dat",ios::binary);
            file.seekg(i++ * sizeof(record), sizeof(Record));

        }
    }
    
};  