#include "Record.hpp"

#define M 5

class Sequential{
protected:
    string name;
    string datafile;
    fstream DATAFILE;
    string auxfile;
    fstream AUXFILE;
    bool empty;

public:
    vector<Record> search(string key){
        if (key.size() > 20)
            key = key.substr(0, 20);
        int pos = lower_bound(key);
        fstream file (this->name,ios::in | ios::binary);
        vector<Record> records;
        Record r;
        int num_records_file = numRecords(datafile,DATAFILE);
        while (pos<num_records_file){
            if(r.nombre == key)
                records.push_back(r);
            else
                break;
            ++pos;
        }
        return records;
    }
    
    void insertAll(vector<Record> &records);
    
    bool compareByKey(Record &r1, Record &r2){
        return (strcmp(r1.nombre,r2.nombre));
    }

    void isFull(){
        int recordAmount = numRecords(this->auxfile,AUXFILE);
        if (recordAmount == M){
            //reBuild file
            return;
        }
    }
    
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
        
        int pos = upper_bound(k) - 1;
        int num_records_datafile = numRecords(this->datafile,DATAFILE);
        int num_records_auxfile = numRecords(this->auxfile,AUXFILE);

        fstream fileAux(this->auxfile + ".dat",ios::binary | ios::out | ios::app);
        fstream fileData(this->datafile + ".dat",ios::binary | ios::in | ios::out);
        fileData.seekg(0,ios::beg);
        fileData.read((char*)&first_pos,sizeof(int));
        fileData.read((char*)&first_ref, sizeof(char));

        if (pos == -1){
            record.nextDel = first_pos;
            record.reference = first_ref;
            initialize_first_values(fileData,num_records_auxfile,'a');
        }
        else{
            Record r1;
            record.nextDel = r1.nextDel;
            record.reference = r1.reference;
            r1.nextDel = r1.reference;
            r1.reference = 'a';
        }
        fileAux.close();
    }
    
private:
    
    int numRecords(string fileName,fstream& file){

    }

    void initialize_first_values(fstream& file, int size, char c){
        file.open(this->name + ".dat", ios::app);
        file.seekg(size * sizeof(Record),ios::beg);
        file << c;
    }
  

    int upper_bound (string key){

    }

    int lower_bound (string key){
        
    }
};
