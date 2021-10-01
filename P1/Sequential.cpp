#include "Record.hpp"

class Sequential{
protected:
    string name;
    string datafile;
    string auxfile;
    int nextDel;
    char reference;
    bool empty;
public:
    explicit Sequential(string _name, string _auxfile, string _datafile) : name(_name), auxfile(_auxfile), datafile(_datafile) {}

    vector<Record> search(string key){
        if (key.size() > 20)
            key = key.substr(0, 20);
        int pos = bs_lower_bound(key);
        fstream file (this->name,ios::in | ios::binary);
        vector<Record> records;
        int num_records_file = numRecords(file,datafile);
    }
    
    void insertAll(vector<Record> &records);
    bool compareByKey(Record &r1, Record &r2);
    void isFull();
    
    void add(Record record){
        if (this->empty){
            fstream fData(this->name, ios::binary | ios::out);
            initialize_first_values(fData,0,'d');
            this->empty = false;
            fData.close();
            return;
        }
        isFull();

        string k = record.nombre;
        int first_pos;
        char first_ref;
        

    }
    
private:
    
    int numRecords(fstream& file, string AUX){
        
    }

    void initialize_first_values(fstream& file, int pos, char c){
        file.open(this->name + ".dat", ios::app);
        file.seekg(pos * sizeof(Record),ios::beg);
        file << c;
    }

    int bs_lower_bound(string key){

    }


};