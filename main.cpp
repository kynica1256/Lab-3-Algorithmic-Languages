#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <stdexcept>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <cstdio>

#include <list>
#include <stack>




class Graphic {
    int V;
    list<int>* adj;
    void topologicalSortUtil(int v, bool visited[], stack<int>& Stack);

public:
    Graphic(int V);
    void addEdge(int v, int w);
    void topologicalSort();
};

Graphic::Graphic(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void Graphic::addEdge(int v, int w)
{
    adj[v].push_back(w);
}

void Graphic::topologicalSortUtil(int v, bool visited[],
                                stack<int>& Stack)
{
    visited[v] = true;

    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            topologicalSortUtil(*i, visited, Stack);

    Stack.push(v);
}

void Graphic::topologicalSort()
{
    stack<int> Stack;

    bool* visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    for (int i = 0; i < V; i++)
        if (visited[i] == false)
            topologicalSortUtil(i, visited, Stack);

    while (Stack.empty() == false) {
        cout << Stack.top() << " ";
        Stack.pop();
    }
}



















string title_pl[4] = {"Name: ", "Length(km): ", "Diameters(mm): ", "State(0 - on, 1 - off): "};
string title_cs[5] = {"Name: ", "Length of factory: ", "Length worked factory: ", "Diameter 1: ", "Diameter 2: "};
string title_graphs[3] = {"Compressor station(1): ", "Compressor station(2): ", "Pipeline name: "};
vector<string> title;
struct Pipeline {
    string Name;
    //vector<string> titles;
    int cell1; // Количество цехов, Протяжённость(км)
    int cell2; // Количество цехов в работе, Диаметр
    int cell3; // Диаметр 1, Состояние(0 - on, 1 - off)
    int cell4; // Диаметр 2
    //void display_info(const string& name) const {
    void display_info(string name, string titles[] = nullptr) {
        if (titles != nullptr) {
            if (name == "Pipelines.txt") {
                cout << titles[0] << Name << endl;
                cout << titles[1] << cell1 << endl;
                cout << titles[2] << cell2 << endl;
                cout << titles[3] << cell3 << endl;
            } else if (name == "CompressedStation.txt") {
                cout << titles[0] << Name << endl;
                cout << titles[1] << cell1 << endl;
                cout << titles[2] << cell2 << endl;
                cout << titles[3] << cell3 << endl;
                cout << titles[4] << cell4 << endl;
            }
        } else {
            if (name == "Pipelines.txt") {
                cout << title[0] << Name << endl;
                cout << title[1] << cell1 << endl;
                cout << title[2] << cell2 << endl;
                cout << title[3] << cell3 << endl;
            } else if (name == "CompressedStation.txt") {
                cout << title[0] << Name << endl;
                cout << title[1] << cell1 << endl;
                cout << title[2] << cell2 << endl;
                cout << title[3] << cell3 << endl;
                cout << title[4] << cell4 << endl;
            }
        }
    }
};

struct CompressedStation {
    string Name;
    int LengthFactory;
    int TypeOfStation;
    int LengthFactoryWork;
};

int CommandCode1;
int CommandCode2;
int CommandCode3; // Id
int CommandCode4;
int CommandCode5;
string CommandCycle;
string SubstringCommand;
int CinSpecial;

vector<string> vec(4);
vector<Pipeline> PipeLines;
vector<Pipeline> PipeLinesFocus;
vector<int> ids_Focus;

/**
Pipeline Reader(int indx, string name) {
    PipeLines.clear();
    string text;
    string line;
    bool flag = false;
    string Name;
    int LengthOfFactory;
    int Diameters;
    string OffOn;
    ifstream in(name);
    
    int num = 0;
    int num1 = 0;

    int upFloor;
    if (name == "CompressedStation.txt") {
        upFloor = 5;
    } else if(name == "Pipelines.txt") {
        upFloor = 4;
    }
    if (in.is_open()) {
        while (getline(in, line)) {
            if (line == "-------") {
                if (flag == false) {
                    flag = true;
                    num = 0;
                } else if (flag == true) {
                    flag = false;
                    Pipeline PipeLine;
                    //for(int i = 0; i < upFloor; i++) {
                    //    PipeLine.titles[i] = title[i];
                    //}
                    PipeLine.Name = vec.at(0);
                    try {
                        PipeLine.cell1 = stoi(vec.at(1)); // length
                        PipeLine.cell2 = stoi(vec.at(2)); // diameter
                    } catch (const exception& e) {
                        cerr << "Conversion error: " << e.what() << endl;
                        continue;
                    }
                    PipeLine.cell3 = stoi(vec.at(3));
                    PipeLines.push_back(PipeLine);
                    line = to_string(num1) + ": " + vec.at(0) + "\n";
                    text = text + line;
                    num1++;
                }
            } else if (flag == true) {
                if (num < upFloor) {
                    vec[num] = line;
                    num++;
                }
            }
        }
    }
    in.close();
    //cout << text;
    return PipeLines[indx];
}







void Reader_info(string name) {
    string text;
    string line;
    bool flag = false;
    string Name;
    int LengthOfFactory;
    int Diameters;
    string OffOn;
    ifstream in(name);
    
    vector<string> vec(4);
    int num = 0;
    int num1 = 0;
    int upFloor;
    if (name == "CompressedStation.txt") {
        upFloor = 5;
    } else if(name == "Pipelines.txt") {
        upFloor = 4;
    }
    if (in.is_open()) {
        while (getline(in, line)) {
            if (line == "-------") {
                if (flag == false) {
                    flag = true;
                    num = 0;
                } else if (flag == true) {
                    flag = false;
                    line = to_string(num1) + ": " + vec.at(0) + "\n";
                    text = text + line;
                    num1++;
                }
            } else if (flag == true) {
                if (num < upFloor) {
                    vec[num] = line;
                    cout << line << endl;
                    num++;
                }
            }
        }
    }
    in.close();
    cout << text;
}**/


string info;
void Reader_info(string name) {
    PipeLines.clear();
    info = "";
    //cout << name << endl;
    Pipeline object;
    int counter_global = 0;
    int counter_local = 0;
    bool flag = false;
    string line = "";
    ifstream in(name);
    if (in.is_open()) {
        while (getline(in, line)) {
            if (line == "-------") {
                if (flag == false) {
                    flag = true;
                } else if (flag == true) {
                    counter_local = 0;
                    flag = false;
                    PipeLines.push_back(object);
                    info += to_string(counter_global) + ": " + object.Name + "\n";
                    counter_global++;
                }
            } else {
                if (flag == true) {
                    //cout << counter_local << endl;
                    switch (counter_local)
                    {
                        case 0:
                            object.Name = line;
                            break;
                        case 1:
                            object.cell1 = atoi(line.c_str());
                            break;
                        case 2:
                            object.cell2 = atoi(line.c_str());
                            break;
                        case 3:
                            object.cell3 = atoi(line.c_str());
                            break;
                        case 4:
                            object.cell4 = atoi(line.c_str());
                            break;
                        default:
                            break;
                    }
                    counter_local++;
                }
            }
        }
    }
}









void write(string name) {
    string outtxt;
    string miniouttxt;
    for (Pipeline unit : PipeLines) {
        miniouttxt += "-------\n";
        miniouttxt += unit.Name+"\n";
        miniouttxt += to_string(unit.cell1)+"\n";
        miniouttxt += to_string(unit.cell2)+"\n";
        miniouttxt += to_string(unit.cell3)+"\n";
        if (name == "CompressedStation.txt") {
            miniouttxt += to_string(unit.cell4)+"\n";
        }
        miniouttxt += "-------\n";
        ofstream out;
        out.open(unit.Name+".txt");
        if (out.is_open())
        {
            out << miniouttxt;
        }   
        out.close();
        outtxt += miniouttxt;
        miniouttxt = "";
    }
    ofstream file(name);
    if (file.is_open()) {
        if (PipeLines.size() == 0) {
            outtxt += "-------\n";
            outtxt += "Zero project\n";
            outtxt += "0\n";
            outtxt += "0\n";
            outtxt += "0\n";
            outtxt += "-------\n";
        }
        file << outtxt;
        file.close();
    }
}





struct SideOfGraph {
    Pipeline CompressedStation1;
    Pipeline pipeline;
    Pipeline CompressedStation2;
};
struct Graph {
    string Name;
    SideOfGraph sides[];
};
vector<SideOfGraph> Graph; // For create new
vector<string> NamesGraphs;
void write_graph(string name) {
    string outtxt;
    string miniouttxt;
    //miniouttxt = name+"\n";
    for (SideOfGraph unit : Graph) {
        miniouttxt += "-------\n";
        miniouttxt += unit.CompressedStation1.Name+"\n";
        miniouttxt += unit.pipeline.Name+"\n";
        miniouttxt += unit.CompressedStation2.Name+"\n";
        miniouttxt += "-------\n";
        /**ofstream out;
        out.open(name+".txt");
        if (out.is_open())
        {
            out << miniouttxt;
        }
        out.close();
        outtxt += miniouttxt;
        miniouttxt = "";**/
    }
    ofstream file1(name+".txt");
    if (file1.is_open()) {
        file1 << miniouttxt;
        file1.close();
    }
    outtxt = "-------\n";
    outtxt += name+"\n";
    outtxt += "-------\n";
    ofstream file2("graphs.txt", std::ios::app);
    if (file2.is_open()) {
        file2 << outtxt;
        file2.close();
    }
}
struct DataBag {
    string name_cs1;
    string name_pl;
    string name_cs2;
};
void read_graph(string name) {
    PipeLines.clear();
    Graph.clear();
    info = "";
    //cout << name << endl;
    DataBag object;
    SideOfGraph object1;
    int counter_global = 0;
    int counter_local = 0;
    bool flag = false;
    string line = "";
    ifstream in(name);
    if (in.is_open()) {
        while (getline(in, line)) {
            if (line == "-------") {
                if (flag == false) {
                    flag = true;
                } else if (flag == true) {
                    counter_local = 0;
                    flag = false;
                    //Graph.push_back(object);
                    //info += to_string(counter_global) + ": " + object.Name + "\n";
                    Reader_info("Pipelines.txt");
                    for (const auto& pipeline_ : PipeLines) {
                        if (pipeline_.Name == object.name_pl) {
                            object1.pipeline = pipeline_;
                            break;
                        }
                    }
                    Reader_info("CompressedStation.txt");
                    for (const auto& pipeline_ : PipeLines) {
                        if (pipeline_.Name == object.name_cs1) {
                            object1.CompressedStation1 = pipeline_;
                            break;
                        }
                    }
                    Reader_info("CompressedStation.txt");
                    for (const auto& pipeline_ : PipeLines) {
                        if (pipeline_.Name == object.name_cs2) {
                            object1.CompressedStation2 = pipeline_;
                            break;
                        }
                    }
                    Graph.push_back(object1);
                    counter_global++;
                }
            } else {
                if (flag == true) {
                    //cout << counter_local << endl;
                    switch (counter_local)
                    {
                        case 0:
                            object.name_cs1 = line;
                            break;
                        case 1:
                            object.name_pl = line;
                            break;
                        case 2:
                            object.name_cs2 = line;
                            break;
                        default:
                            break;
                    }
                    counter_local++;
                }
            }
        }
    }
}











void Logging(const std::string& text, const std::string& name) {
    time_t now = time(0);
    tm* timeinfo = localtime(&now);
    
    char time_buffer[80];
    strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    
    ofstream thread_("logs_" + name, std::ios::app);
    if (thread_.is_open()) {
        thread_ << "[" << time_buffer << "] " << text << "\n";
    }
}


int CinFunc(string name) {
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cerr << "Input error." << endl;
        Logging("Error - Input error.", name);
        return 1;
    }
    return 0;
}


void EditFunc(string name, Pipeline *pipelines, int *CommandCode3, int size_) {
    cout << endl;
    cout << "[\n 0 - "+title[0]+",\n 1 - "+title[1]+", \n 2 - "+title[2]+",\n 3 - "+title[3]+",\n 4 - Main menu,\n 5 - Finished program,\n 6 - Check info,\n 7 - Delete \n]: ";
    cin >> CommandCode4;
    cout << endl;
    CinSpecial = CinFunc(name);
    if (CinSpecial == 1) {
        return;
    }
    if (CommandCode4 == 0) {
        string Name;
        cout << title[0] << endl;
        cin >> Name;
        CinSpecial = CinFunc(name);
        if (CinSpecial == 1) {
            return;
        }
        cout << endl;
        for (int i = 0; i < size_; i++) {
            Logging("Installation name - "+Name, name);
            if( remove( (pipelines[i].Name+".txt").c_str() ) != 0 ) {
                Logging("Update name Error", name);
            } else {
                Logging("Update name - "+pipelines[i].Name, name);
                pipelines[i].Name = Name;
            }
        }
    } else if (CommandCode4 == 1) {
        int Length;
        cout << title[1] << endl;
        cin >> Length;
        CinSpecial = CinFunc(name);
        if (CinSpecial == 1) {
            return;
        }
        cout << endl;
        for (int i = 0; i < size_; i++) {
            pipelines[i].cell1 = Length;
            Logging("Installation Length - "+to_string(Length), name);
        }
    } else if (CommandCode4 == 2) {
        int Diameter;
        cout << title[2] << endl;
        cin >> Diameter;
        CinSpecial = CinFunc(name);
        if (CinSpecial == 1) {
            return;
        }
        cout << endl;
        for (int i = 0; i < size_; i++) {
            pipelines[i].cell2 = Diameter;
            Logging("Installation Diameter - "+to_string(Diameter), name);
        }
    }  else if (CommandCode4 == 3) {
        int State;
        cout << title[3] << endl;
        cin >> State;
        CinSpecial = CinFunc(name);
        if (CinSpecial == 1) {
            return;
        }
        cout << endl;
        for (int i = 0; i < size_; i++) {
            pipelines[i].cell3 = State;
            Logging("Installation State - "+to_string(State), name);
        }
    } else if (CommandCode4 == 4) {
        return;
    } else if (CommandCode4 == 5) {
        exit(0);
    } else if(CommandCode4 == 6) {
        for (int i = 0; i < size_; i++) {
            pipelines[i].display_info(name);
        }
    } else if(CommandCode4 == 7) {
        for (int i = 0; i < size_; i++) {
            if( remove( (pipelines[i].Name+".txt").c_str() ) != 0 ) {
                Logging("Delete Error", name);
            } else {
                Logging("Delete - "+pipelines[i].Name, name);
                PipeLines.erase(PipeLines.begin() + CommandCode3[i]);
            }
        }
        write(name);
        return;
    } else {
        cerr << "Input error." << endl;
        Logging("Error - Input error.", name);
        return;
    }
    for (int i = 0; i < size_; i++) { 
        PipeLines[CommandCode3[i]] = pipelines[i];
    }
    write(name);
}



int TypesOfState[2] = {0, 1};
vector<int> ids_;
vector<Pipeline> pipelines_;





int num_;
int* ids_1;
Pipeline* pipelines_1;
string buffer_;

void CycelCoreFunction(string name) {
    num_ = 0;
    cout << "To stop the transfer, enter - stop. To select all available options - all." << endl;
    for (int i = 0; i < PipeLines.size(); i++) {
        cout << "[Id]: ";
        cin >> CommandCycle;
        CinSpecial = CinFunc(name);
        if (CinSpecial == 1) {
            break;
        }
        cout << endl;
        if (CommandCycle == "stop") {
            break;
        }
        if (CommandCycle == "all") {
            ids_ = ids_Focus;
            pipelines_ = PipeLinesFocus;
            break;
        }
        try {
            num_ = stoi(CommandCycle);
            ids_.push_back(num_);
            pipelines_.push_back(PipeLines[num_]);
            num_ = 0;
        } catch (const invalid_argument& e) {
            cerr << "Input error." << endl;
            Logging("Error - Input error.", name);
            break;
        } catch (const out_of_range& e) {
            cerr << "Input error." << endl;
            Logging("Error - Input error.", name);
            break;
        }
    }
    int size_ = ids_.size();
    if (size_ == 0) {
        return;
    }
    ids_1 = new int[size_];
    for (int i = 0; i < size_; i++) {
        ids_1[i] = ids_[i];
    }
    pipelines_1 = new Pipeline[size_];
    for (int i = 0; i < size_; i++) {
        pipelines_1[i] = pipelines_[i];
    }
    EditFunc(name, pipelines_1, ids_1, size_);
    delete[] ids_1;
    delete[] pipelines_1;
    Reader_info(name);
}













int CoreFunc(string name) {
    num_ = 0;
    buffer_ = "";
    Pipeline pipeline;
    /**int num_;
    int* ids_1;
    Pipeline* pipelines_1;
    string buffer_;*/
    while (true) {
        cout << "[\n 0 - Edit,\n 1 - Create new,\n 2 - Delete,\n 3 - Check info,\n 4 - Main menu,\n 5 - Finished program,\n 6 - Filter\n]: ";
        cin >> CommandCode2;
        cout << endl;
        CinSpecial = CinFunc(name);
        if (CinSpecial == 1) {
            break;
        }
        if (CommandCode2 == 0) {
            cout << name << endl;
            Reader_info(name);
            cin >> CommandCode3;
            cout << endl;
            CinSpecial = CinFunc(name);
            if (CinSpecial == 1) {
                break;
            }
            Pipeline pipeline;
            try {
                //pipeline = Reader(CommandCode3, name);
                Reader_info(name);
                pipeline = PipeLines[CommandCode3];
                pipeline.display_info(name);
            } catch (const std::bad_alloc& e) {
                cerr << "Input error." << endl;
                Logging("Error - Input error.", name);
                break;
            }
            if (CommandCode3 == 4) {
                break;
            } else if (CommandCode3 == 5) {
                exit(0);
            } else {
                int size_ = PipeLines.size();
                if (size_ < CommandCode3 || CommandCode3 < 0) {
                    cerr << "Input error." << endl;
                    Logging("Error - Input error.", name);
                    break;
                }
            }
            Pipeline* pipelines = new Pipeline[1];
            pipelines[0] = pipeline;
            int* CommandCode3_ = new int[1];
            CommandCode3_[0] = CommandCode3;
            EditFunc(name, pipelines, CommandCode3_, 1);
            delete[] pipelines;
            delete[] CommandCode3_;
        } else if(CommandCode2 == 1) {
            //cout << name << endl;
            /**for (int i = 0; i < title.size(); i++)
            {
                cout << title[i] << endl;
                CinSpecial = CinFunc(name);
                if (CinSpecial == 1) {
                    break;
                }
            }**/
            Reader_info(name);
            pipeline = PipeLines[0];
            //Pipeline pipeline = Reader(0, name);
            string Name;
            int FocusVar;
            cout << title[0] << endl;
            cin >> Name;
            CinSpecial = CinFunc(name);
            if (CinSpecial == 1) {
                break;
            }
            cout << endl;
            pipeline.Name = Name;

            cout << title[1] << endl;
            cin >> FocusVar;
            CinSpecial = CinFunc(name);
            if (CinSpecial == 1) {
                break;
            }
            cout << endl;
            pipeline.cell1 = FocusVar;

            cout << title[2] << endl;
            cin >> FocusVar;
            CinSpecial = CinFunc(name);
            if (CinSpecial == 1) {
                break;
            }
            cout << endl;
            pipeline.cell2 = FocusVar;

            cout << title[3] << endl;
            cin >> FocusVar;
            CinSpecial = CinFunc(name);
            if (CinSpecial == 1) {
                break;
            }
            cout << endl;
            pipeline.cell3 = FocusVar;

            if (name == "CompressedStation.txt") {
                cout << title[4] << endl;
                cin >> FocusVar;
                CinSpecial = CinFunc(name);
                if (CinSpecial == 1) {
                    break;
                }
                cout << endl;
                pipeline.cell4 = FocusVar;
            }


            PipeLines.push_back(pipeline);
            Logging("Create project - "+Name, name);
            write(name);
        } else if(CommandCode2 == 2) {
            Reader_info(name);
            cin >> CommandCode3;
            cout << endl;
            CinSpecial = CinFunc(name);
            if (CinSpecial == 1) {
                break;
            }
            if( remove( (PipeLines[CommandCode3].Name+".txt").c_str() ) != 0 ) {
                Logging("Delete Error", name);
            } else {
                Reader_info(name);
                Pipeline pipeline = PipeLines[CommandCode3];
                //Pipeline pipeline = Reader(CommandCode3, name);
                Logging("Delete - "+PipeLines[CommandCode3].Name, name);
                PipeLines.erase(PipeLines.begin() + CommandCode3);
                write(name);
                Reader_info(name);
            }
        } else if(CommandCode2 == 3) {
            Reader_info(name);
            cout << info << endl;
            cin >> CommandCode3;
            cout << endl;
            CinSpecial = CinFunc(name);
            if (CinSpecial == 1) {
                break;
            }
            try {
                Reader_info(name);
                Pipeline pipeline = PipeLines[CommandCode3];
                pipeline.display_info(name);
            } catch (const bad_alloc& e) {
                cerr << "Input error." << endl;
                Logging("Error - Input error.", name);
                break;
            }
            break;
        } else if (CommandCode2 == 4) {
            break;
        } else if (CommandCode2 == 5) {
            exit(0);
        } else if(CommandCode2 == 6) {
            num_ = 0;
            if (name == "Pipelines.txt" | name == "CompressedStation.txt") {
                if (name == "Pipelines.txt") {
                    cout << "[\n 0 - Name,\n 1 - State,\n 2 - all\n]: ";
                } else if(name == "CompressedStation.txt") {
                    cout << "[\n 0 - Name,\n 1 - percentage of idle mini-factory,\n 2 - all\n]: ";
                }
                cin >> CommandCode3;
                CinSpecial = CinFunc(name);
                if (CinSpecial == 1) {
                    break;
                }
                cout << endl;
                if (CommandCode3 == 0) {
                    ids_.clear();
                    pipelines_.clear();
                    PipeLinesFocus.clear();
                    ids_Focus.clear();
                    Reader_info(name);
                    Pipeline pipeline = PipeLines[0];
                    num_ = 0;
                    cout << "[Substring]: ";
                    cin >> SubstringCommand;
                    CinSpecial = CinFunc(name);
                    if (CinSpecial == 1) {
                        return 0;
                    }
                    cout << endl;
                    for (Pipeline i : PipeLines) {
                        buffer_ = i.Name;
                        if(buffer_.find(SubstringCommand) != string::npos) {
                            cout << num_ << ": " << buffer_ << endl;
                            PipeLinesFocus.push_back(i);
                            ids_Focus.push_back(num_);
                        }
                        num_++;
                    }
                    CycelCoreFunction(name);
                }
                if(CommandCode3 == 1 & name == "Pipelines.txt") {
                    ids_.clear();
                    pipelines_.clear();
                    PipeLinesFocus.clear();
                    ids_Focus.clear();
                    Reader_info(name);
                    Pipeline pipeline = PipeLines[0];
                    num_ = 0;
                    cout << "[\n 0 - On,\n 1 - Off\n]: ";
                    cin >> CommandCode4;
                    CinSpecial = CinFunc(name);
                    if (CinSpecial == 1) {
                        break;
                    }
                    cout << endl;
                    for (const auto& pipeline_ : PipeLines) {
                        if (pipeline_.cell3 == TypesOfState[CommandCode4]) {
                            cout << num_ << ": " << pipeline_.Name << endl;
                            PipeLinesFocus.push_back(pipeline_);
                            ids_Focus.push_back(num_);
                        }
                        num_++;
                    }
                    CycelCoreFunction(name);
                }
                if(CommandCode3 == 1 & name == "CompressedStation.txt") {
                    ids_.clear();
                    pipelines_.clear();
                    PipeLinesFocus.clear();
                    ids_Focus.clear();
                    Reader_info(name);
                    Pipeline pipeline = PipeLines[0];
                    vector<Pipeline> Pipelines = PipeLines;
                    vector<int> indices(Pipelines.size());
                    for (int i = 0; i < Pipelines.size(); ++i) {
                        indices[i] = i;
                    }
                    sort(indices.begin(), indices.end(),
                              [&Pipelines](int i, int j) {
                                  if (Pipelines[i].cell1 == 0 || Pipelines[j].cell1 == 0) {
                                    return Pipelines[i].cell1 > Pipelines[j].cell1;
                                  }
                                  return (double(Pipelines[i].cell2) / double(Pipelines[i].cell1)) * 100 < 
                                         (double(Pipelines[j].cell2) / double(Pipelines[j].cell1)) * 100;
                              });
                    for (int idx : indices) {
                        ids_Focus.push_back(idx);
                        PipeLinesFocus.push_back(Pipelines[idx]);
                        cout << idx << ": " << Pipelines[idx].Name << ", " << double(Pipelines[idx].cell2)/double(Pipelines[idx].cell1) * 100 << "%" << std::endl;
                    }
                    CycelCoreFunction(name);
                }
                if (CommandCode3 == 2) {
                    ids_.clear();
                    pipelines_.clear();
                    Reader_info(name);
                    Pipeline pipeline = PipeLines[0];
                    int i = 0;
                    for (i = 0; i < PipeLines.size(); i++) {
                        cout << i << ": " << PipeLines[i].Name << endl;
                    }
                    i++;
                    cout << i << ": " << "all objects" << endl;
                    num_ = 0;
                    cout << "To stop the transfer, enter - stop." << endl;
                    for (int j = 0; j < PipeLines.size(); j++) {
                        cout << "[Id]: ";
                        cin >> CommandCycle;
                        CinSpecial = CinFunc(name);
                        if (CinSpecial == 1) {
                            break;
                        }
                        cout << endl;
                        if (CommandCycle == "stop") {
                            break;
                        }
                        try {
                            num_ = stoi(CommandCycle);
                            if (num_ == i) {
                                for (int k = 0; k < PipeLines.size(); ++k) {
                                    ids_.push_back(k);
                                }
                                pipelines_ = PipeLines;
                                break;
                            }
                            ids_.push_back(num_);
                            pipelines_.push_back(PipeLines[num_]);
                            num_ = 0;
                        } catch (const invalid_argument& e) {
                            cerr << e.what() << endl;
                            break;
                        } catch (const out_of_range& e) {
                            cerr << e.what() << endl;
                            break;
                        }
                    }
                    int size_ = ids_.size();
                    if (size_ == 0) {
                        break;
                    }
                    ids_1 = new int[size_];
                    for (int i = 0; i < size_; i++) {
                        ids_1[i] = ids_[i];
                    }
                    pipelines_1 = new Pipeline[size_];
                    for (int i = 0; i < size_; i++) {
                        pipelines_1[i] = pipelines_[i];
                    }

                    EditFunc(name, pipelines_1, ids_1, size_);
                    delete[] ids_1;
                    delete[] pipelines_1;
                    //pipeline = Reader(0, name);
                    Reader_info(name);
                    pipeline = PipeLines[0];
                }
            }
        } else {
            cerr << "Input error." << endl;
            continue;
        }
    }
    return 0;
}






int CoreFuncGraphs() {
    string name = "";
    int local_counter = 0;
    SideOfGraph side;
    num_ = 0;
    buffer_ = "";
    Pipeline pipeline;
    Pipeline pipeline_dup;
    Pipeline CS1;
    Pipeline CS2;
    Pipeline PL;
    int CodeCS1;
    int CodeCS2;
    int CodePL;
    int CodeGraph;
    Reader_info("CompressedStation.txt");
    Pipeline arr_cs[2*PipeLines.size()];
    while (true) {
        cout << "[\n 0 - Create new,\n 1 - Delete,\n 2 - Check info,\n 3 - Main menu,\n 4 - Finished program,\n 5 - Topological Sorting\n]: ";
        cin >> CommandCode2;
        cout << endl;
        CinSpecial = CinFunc(name);
        if (CinSpecial == 1) {
            break;
        }
        if (CommandCode2 == 0) {
            for (const auto& pipeline_ : PipeLines) {
                arr_cs[num_] = pipeline_;
                arr_cs[num_].cell4 = -1;
                num_++;
                arr_cs[num_] = pipeline_;
                arr_cs[num_].cell3 = -1;
                num_++;
            }
            num_ = 0;
            while (true) {
                Reader_info("CompressedStation.txt");
                pipeline = PipeLines[0];
                //pipeline = Reader(0, "CompressedStation.txt");
                /**for (const auto& pipeline_ : PipeLines) {
                    //cout << pipeline_.Name << endl << "_______________" << endl;
                    //pipeline_.display_info(name);
                    cout << "Name: " << pipeline_.Name << endl << "_______________" << endl;
                    cout << "Diameters:" << endl;
                    //if (find(arr_cs.begin(), arr_cs.end(), *pipeline_) == arr_cs.end()) {

                    //}
                    cout << num_ << ": " << pipeline_.cell3 << "(mm)" << endl;
                    arr_cs[num_] = pipeline_;
                    arr_cs[num_].cell4 = -1;
                    num_++;
                    cout << num_ << ": " << pipeline_.cell4 << "(mm)" << endl;
                    arr_cs[num_] = pipeline_;
                    arr_cs[num_].cell3 = -1;
                    num_++;
                    cout << "_______________" << endl;
                }**/
                bool flag = false;
                for (int i = 0; i < 2*PipeLines.size(); i++)
                {
                    pipeline = arr_cs[i];
                    if (pipeline.cell3 == -1 & pipeline.cell4 == -1) {
                        if (flag == false) {
                            flag = true;
                        } else {
                            flag = false;
                        }
                        continue;
                    }
                    if (flag == false) {
                        cout << "_______________" << endl << "Name: " << pipeline.Name << endl << "_______________" << endl;
                        cout << "Diameters:" << endl;
                        flag = true;
                    } else {
                        flag = false;
                    }
                    if(pipeline.cell3 == -1) {
                        cout << i << ": " << pipeline.cell4 << "(mm)" << endl;
                    } else {
                        cout << i << ": " << pipeline.cell3 << "(mm)" << endl;
                    }
                }
                
                num_ = 0;
                cout << title[0]+"[stop - '-1']" << endl;
                cin >> CodeCS1;
                CinSpecial = CinFunc("CompressedStation.txt");
                if (CinSpecial == 1) {
                    break;
                }
                if (CodeCS1 == -1) {
                    break;
                }
                cout << endl;
                CS1 = arr_cs[CodeCS1];
                arr_cs[CodeCS1].cell3 = -1;
                arr_cs[CodeCS1].cell4 = -1;
                Reader_info("CompressedStation.txt");
                pipeline = PipeLines[0];
                //pipeline = Reader(0, "CompressedStation.txt");
                /**for (const auto& pipeline_ : PipeLines) {
                    cout << "Name: " << pipeline_.Name << endl << "_______________" << endl;
                    cout << "Diameters:" << endl;
                    if (num_ != CodeCS1) {
                        cout << num_ << ": " << pipeline_.cell3 << "(mm)" << endl;
                    }
                    num_++;
                    if (num_ != CodeCS1) {
                        cout << num_ << ": " << pipeline_.cell4 << "(mm)" << endl;
                    }
                    num_++;
                    cout << "_______________" << endl;
                }**/
                for (int i = 0; i < 2*PipeLines.size(); i++)
                {
                    pipeline = arr_cs[i];
                    if (pipeline.cell3 == -1 & pipeline.cell4 == -1) {
                        if (flag == false) {
                            flag = true;
                        } else {
                            flag = false;
                        }
                        continue;
                    }
                    if (flag == false) {
                        cout << "_______________" << endl << "Name: " << pipeline.Name << endl << "_______________" << endl;
                        cout << "Diameters:" << endl;
                        flag = true;
                    } else {
                        flag = false;
                    }
                    if(pipeline.cell3 == -1) {
                        cout << i << ": " << pipeline.cell4 << "(mm)" << endl;
                    } else {
                        cout << i << ": " << pipeline.cell3 << "(mm)" << endl;
                    }
                }
                num_ = 0;
                cout << title[1]+"[stop - '-1']" << endl;
                cin >> CodeCS2;
                CinSpecial = CinFunc("CompressedStation.txt");
                if (CinSpecial == 1) {
                    break;
                }
                if (CodeCS2 == -1) {
                    break;
                }
                cout << endl;
                CS2 = arr_cs[CodeCS2];
                arr_cs[CodeCS2].cell3 = -1;
                arr_cs[CodeCS2].cell4 = -1;
                Reader_info("Pipelines.txt");
                pipeline = PipeLines[0];
                for (const auto& pipeline_ : PipeLines) {
                    cout << num_ << ": " << pipeline_.Name << " " << pipeline_.cell2 << "(mm)" << endl;
                    num_++;
                }
                num_ = 0;
                cout << title[2]+"[stop - '-1']" << endl;
                cin >> CodePL;
                CinSpecial = CinFunc("Pipelines.txt");
                if (CinSpecial == 1) {
                    break;
                }
                if (CodePL == -1) {
                    break;
                }
                cout << endl;
                PL = PipeLines[CodePL];
                if (CS1.cell1 == CS2.cell1 & CS1.cell2 == CS2.cell2 & CS1.cell3 == CS2.cell3 & CS1.Name == CS2.Name) {
                    cerr << "Input error." << endl;
                    Logging("Error - Input error.", name);
                    break;
                }
                side.CompressedStation1 = CS1;
                side.CompressedStation2 = CS2;
                side.pipeline = PL;
                Graph.push_back(side);
                cout << "Save changes? [y/n]: ";
                cin >> buffer_;
                CinSpecial = CinFunc(name);
                if (CinSpecial == 1) {
                    break;
                }
                cout << endl;
                if (buffer_ == "y") {
                    cout << "Name of graph: ";
                    cin >> name;
                    write_graph(name);
                    break;
                }
                buffer_ = "";
            }
        } else if (CommandCode2 == 1) {
            /**Pipeline pipeline = Reader_info(PipeLines[CodeGraph].Name+".txt");
            Reader_info("graphs.txt");
            cout << info;
            cin >> CommandCode3;
            cout << endl;
            CinSpecial = CinFunc(name);
            if (CinSpecial == 1) {
                break;
            }**/
            Reader_info("graphs.txt");
            cout << info;
            cin >> CodeGraph;
            cout << endl;
            buffer_ = PipeLines[CodeGraph].Name;
            PipeLines.erase(PipeLines.begin() + CodeGraph);
            info = "";
            for (const auto& pipeline_ : PipeLines) {
                info += "-------\n" + pipeline_.Name + "\n-------\n";
            }
            if (info == "") {
                info = "-------\n-------\n";
            }
            ofstream file("graphs.txt");
            if (file.is_open()) {
                file << info;
                file.close();
            }
            if( remove( (buffer_+".txt").c_str() ) != 0 ) {
                Logging("Delete Error", "graphs.txt");
            }
            info = "";
        } else if (CommandCode2 == 2) {
            string name_cs_1;
            string name_cs_2;
            int diameter;
            Reader_info("graphs.txt");
            cout << info;
            cin >> CodeGraph;
            cout << endl;
            read_graph(PipeLines[CodeGraph].Name+".txt");
            for (SideOfGraph i : Graph) {
                /**i.CompressedStation1.Name;
                i.pipeline.Name;
                i.pipeline.cell2;
                i.CompressedStation2.Name;**/
                cout << endl << "branch " << i.CompressedStation1.Name << " <-> " << i.CompressedStation2.Name << " have diameter = " << to_string(i.pipeline.cell2) << endl;
            }
            //Reader_info(PipeLines[CodeGraph].Name+".txt");
            //read_graph(PipeLines[CodeGraph].Name+".txt");
            //PipeLines[CodeGraph].Name
        } else if (CommandCode2 == 3) {
            break;
        } else if (CommandCode2 == 4) {
            exit(0);
        } else if (CommandCode2 == 5) {
            Reader_info("graphs.txt");
            cout << info;
            cin >> CodeGraph;
            cout << endl;
            read_graph(PipeLines[CodeGraph].Name+".txt");
            // Create a graph given in the above diagram
            //string titles[Graph.size() * 2];  // Увеличиваем размер в 2 раза
            /**num_ = 0;
            vector<string> titles_;
            titles_.reserve(Graph.size());
            for (const auto& graph_ : Graph) {
                // Ищем элемент в уже заполненной части массива
                auto it = find(begin(titles_), begin(titles_) + num_, graph_.CompressedStation1.Name);
                if (it != begin(titles_) + num_) {
                    //cout << "Элемент " << graph_.CompressedStation1.Name << " найден!" << endl;
                } else {
                    //cout << "Элемент " << graph_.CompressedStation1.Name << " не найден." << endl;
                    titles_[num_] = graph_.CompressedStation1.Name;
                    num_++;
                }

                // Проверяем второй элемент
                it = find(begin(titles_), begin(titles_) + num_, graph_.CompressedStation2.Name);
                if (it != begin(titles_) + num_) {
                    //cout << "Элемент " << graph_.CompressedStation2.Name << " найден!" << endl;
                } else {
                    //cout << "Элемент " << graph_.CompressedStation2.Name << " не найден." << endl;
                    titles_[num_] = graph_.CompressedStation2.Name;
                    num_++;
                }
            }
            Graphic g(2*Graph.size());
            int index1 = 0;
            int index2 = 0;
            num_ = 0;
            for (const auto& graph_ : Graph) {
                auto it = find(titles_.begin(), titles_.end(), graph_.CompressedStation1.Name);
                if (it != titles_.end()) {
                    index1 = distance(titles_.begin(), it);
                }
                auto it2 = find(titles_.begin(), titles_.end(), graph_.CompressedStation2.Name);
                if (it2 != titles_.end()) {
                    index2 = distance(titles_.begin(), it2);
                }
                cout << index1 << " " << index2 << endl;
                g.addEdge(index1, index2);
            }
            g.topologicalSort();
            //cout << endl;**/
            vector<string> titles_;
            titles_.reserve(Graph.size() * 2);
            for (const auto& graph_ : Graph) {
                auto it = find(titles_.begin(), titles_.end(), graph_.CompressedStation1.Name);
                if (it != titles_.end()) {
                } else {
                    titles_.push_back(graph_.CompressedStation1.Name);
                }
                it = find(titles_.begin(), titles_.end(), graph_.CompressedStation2.Name);
                if (it != titles_.end()) {
                } else {
                    titles_.push_back(graph_.CompressedStation2.Name);
                }
            }
            Graphic g(titles_.size());
            for (const auto& graph_ : Graph) {
                auto it1 = find(titles_.begin(), titles_.end(), graph_.CompressedStation1.Name);
                auto it2 = find(titles_.begin(), titles_.end(), graph_.CompressedStation2.Name);

                if (it1 != titles_.end() && it2 != titles_.end()) {
                    int index1 = distance(titles_.begin(), it1);
                    int index2 = distance(titles_.begin(), it2);
                    cout << index1 << " " << index2 << endl;
                    g.addEdge(index1, index2);
                }
            }
            g.topologicalSort();
            cout << endl;
        }
    }
    return 0;
}


int main() {
    while (true) {
        cin.clear();
        cout << "[0 - Pipeline, 1 - Compressed station, 2 - grpahs, 3 - Finished program]: ";
        cin >> CommandCode1;
        cout << endl;
        CinSpecial = CinFunc(".txt");
        if (CinSpecial == 1) {
            continue;
        }
        if (CommandCode1 == 0) {
            title = {"Name: ", "Length(km): ", "Diameters(mm): ", "State(0 - on, 1 - off): "};
            CoreFunc("Pipelines.txt");
        } else if(CommandCode1 == 1) {
            title = {"Name: ", "Length of factory: ", "Length worked factory: ", "Diameter 1: ", "Diameter 2: "};
            CoreFunc("CompressedStation.txt");
        } else if(CommandCode1 == 2) {
            title = {"Compressor station(1): ", "Compressor station(2): ", "Pipeline name: "};
            CoreFuncGraphs();
        } else if(CommandCode1 == 3) {
            exit(0);
        } else {
            cerr << "Input error." << endl;
        }
    }
    return 0;
}