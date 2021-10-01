#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <string>
#include <algorithm>
#include <unordered_map>

struct Registro{
  char codigo[5];
  char nombre[20];
  char carrera[15];
  int ciclo;
};

struct Page{
  Registro registro[10];
};

class Handler{
  std::vector<Registro> registros;
  std::unordered_map<std::string, int> indexR;
  std::string dataFile;
  std::string indexFile;
  std::string inputFile;

public:

  Handler(std::string dataFile, std::string indexFile, std::string inputFile) {
    this->dataFile = dataFile;
    this->indexFile = indexFile;
    this->inputFile = inputFile;
    Registro reg;
    std::fstream inputStream;
    inputStream.open(dataFile, std::ios::in | std::ios::binary);

    if(inputStream.is_open()){
      while(inputStream.read((char*)& reg, sizeof(Registro))) {
        registros.push_back(reg);
      }
		}else
      std::cout << "Can't open the file";
  }

  void writeRecord(Page obj) {
    std::ofstream outFile;
    outFile.open(dataFile, std::ios::binary | std::ios::app);        
    outFile.write((char *) &obj, sizeof(obj));
    outFile.close();
  }

  void writeIndex() {
    std::ofstream indexFile;
    indexFile.open(dataFile, std::ios::binary | std::ios::app);        
    for(auto &x: indexR){
      indexFile.write((char *) &x, sizeof(x));
    }
    indexFile.close();
  }
	
	
	bool sort_reg(Registro r1, Registro r2){
    std::string s1 = {r1.codigo[2], r1.codigo[3], r1.codigo[4]};
    std::string s2 = {r2.codigo[2], r2.codigo[3], r2.codigo[4]};

    if(r1.codigo[1] < r2.codigo[1])
      return true;
    else if(r1.codigo[1] > r2.codigo[1])
      return false;
    else{
      return stoi(s1) < stoi(s2);
    }
  }

  void readIndex(){
    //todo
  }

  void readData(std::string file) {
		Registro reg;
		std::fstream infile;
		infile.open(file, std::ios::in | std::ios::binary);
		if(infile.is_open()){
      int c = 0;
      while(infile.read((char*)& reg, sizeof(Registro))) {
				registros.push_back(reg);
        if(c % 10 == 0){
          std::string temp = reg.codigo;
          indexR[temp] = c;
        }
        c++;
      }
		}else
      std::cout << "Can't open the file";
    
    std::sort(registros.begin(), registros.end(), sort_reg);
    infile.close();
  }
  
  void insertAll(){
    std::ofstream salida;
    salida.open(dataFile, std::ios::app | std::ios::binary);
    for(auto &x: registros){
      salida.write((char *)&x, sizeof(Registro));
    }
    salida.close();
  }

};

int main(){
  std::string data = "data.txt";
  std::string ind = "index.txt";
  std::string aux = "aux.txt";
  Handler handler(data, ind, aux);
  return 0;
}
