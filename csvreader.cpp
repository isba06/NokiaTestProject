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
    void writeBufferCSV(const string& namefile){
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
    char searchOperator(string& cellWithFormula) {
        if (cellWithFormula.find("+") != string::npos)
            return '+';
        else if(cellWithFormula.find('*') != string::npos)
            return '*';
        else if(cellWithFormula.find('-') != string::npos)
            return '-';
        else if(cellWithFormula.find('/') != string::npos)
            return '/';
        else exit(1);
    }
    string searchCellsAndCalculate(string& cellWithFormula){
        vector<int> arguments;
        string answer;
        long counter = 0;
        for(int i = 1; i<table.size();i++){
            for(int j = 1; j<table[0].size(); j++) {
                if (cellWithFormula.find(table[0][j] + table[i][0]) != string::npos) {
                    counter++;
                    arguments.push_back(stoi(table[i][j]));
                    if (counter == 2) {

                        counter = 0;
                        switch (searchOperator(cellWithFormula)) {
                            case '+':
                                answer = to_string(arguments[0] + arguments[1]);
                                break;
                            case '-':
                                answer = to_string(arguments[0] - arguments[1]);
                                break;
                            case '*':
                                answer = to_string(arguments[0] * arguments[1]);
                                break;
                            case '/':
                                if (arguments[1] == 0) {
                                    cout << "Error division by 0! Cell " << table[0][j] + table[i][0] <<endl ;
                                    answer = cellWithFormula;
                                    break;
                                }
                                answer = to_string(arguments[0] / arguments[1]);
                                break;
                            default: answer = cellWithFormula;
                        }
                    }
                }

            }
        }
        if (arguments.size() == 1) {
            cout << "Incorrect address cell!"<<endl;
            return cellWithFormula;

        }
        return answer;
    }
    void replaceFormuls(){
        size_t i = -1;
        for(auto index : indicesFormuls)
            table[index.i][index.j] = searchCellsAndCalculate(formulsInTable[++i]);
    }
};



int main(int argc, char* argv[]) {

    CSVdata test;
    test.writeBufferCSV(argv[1]);
    test.replaceFormuls();
    test.getTable();
    return 0;
}
