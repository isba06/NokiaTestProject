#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;
string delCharEndLine(string& st){
    if (st.empty())
        return st;
    if (st.back()=='\r') {
        cout<<"yes"<<endl;
        st.erase(st.size()-1);
    }
    return st;
}

struct Indicies{
    unsigned i;
    unsigned j;
};

class CSVdata{
public:
    vector <vector<string>> table;
    vector<string> formulsInTable, buffVec;
    vector <Indicies> indicesFormuls;
public:
    void writeBufferCSV(string namefile){
        ifstream file(namefile);
        string line, cell;
        Indicies indicies;
        if (file.is_open()){
            while(!file.eof()){
                getline(file, line);
                stringstream line2(line);
                while(getline(line2, cell, ',')) {
                    buffVec.push_back(cell);
                    if (cell[0] == '=') {
                        formulsInTable.push_back(cell);
                        buffVec.empty() ? indicies.j = 0 : indicies.j = buffVec.size() - 1;
                        if (table.empty()) {
                            indicies.i = 0;
                        } else {
                            indicies.i = table.size();
                        }
                        this->indicesFormuls.push_back(indicies);
                    }
                }
                table.push_back(buffVec);
                buffVec.clear();
            }
            file.close();
        }
        else exit(1);
    }
    void getTable(){
        for (const auto& vec : table){
            for (const auto& elem: vec){
                cout << elem << " ";
            }
            cout << endl;
        }
    }

};



int main() {

    string name, line, line3;
    vector <pair<int, int>> indices;
    vector <vector<string>> buffer;
    vector<string> buff3;
    name = "testcsv.csv";
    ifstream fp(name);
    if(fp.is_open()) {
        while (!fp.eof()){
            getline(fp, line);
            stringstream line2(line);
            vector <string> buff2;
            while(getline(line2, line3 , ',')){
                buff2.push_back(line3);
                if(line3[0] == '='){
                    buff3.push_back(line3);
                    indices.push_back(make_pair(buffer.size(), buff2.size()-1));
                }
            }
            buffer.push_back(buff2);

        }
    }
    fp.close();
    long first, second;
    //cout<<buffer[2][2][0]<<endl;
    //можно завернуть в функцию и вместо buff3 подставить параметр

    size_t indexBuff3 = 0;
    long answer=0;
    long i_indexWrite = -1, j_indexWrite = -1;
    unsigned counter = 0; //counter for ARG1 and ARG2
    while(indexBuff3 < buff3.size()) {
        for (size_t i = 1; i < buffer.size(); i++) {
            for (size_t j = 1; j < buffer[i].size(); j++) {
                if (buff3[indexBuff3].find((buffer[0][j] + buffer[i][0])) != std::string::npos) {
                    counter++;
                    answer += stoi(buffer[i][j]);
                    if(counter==2) {
                        buffer[indices[++i_indexWrite].first][indices[++j_indexWrite].second] = to_string(answer);
                        counter = 0;
                        answer = 0;
                    }

                    cout << buffer[i][j]<< " " <<i<<" "<<j<<" "<<buffer[0][j] + buffer[i][0] << " "<< buff3[indexBuff3]<<" count: "<<counter << endl;
                }
            }
        }

        indexBuff3++;
    }
    for(auto i : buffer) {
        for (auto j: i)
            cout << j<<" ";
        cout << endl;
    }
    CSVdata test;
    test.writeBufferCSV("testcsv.csv");
    test.getTable();
    for(auto i : test.formulsInTable)
        cout << i <<endl;
    return 0;
}
