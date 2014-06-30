#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>

using namespace std;
typedef map<string, string> opt_t;

void print_usage() {
    cout << "Coverts file to a C++ header gahsdfkajsdf";
}

static bool formatted;

void add_tabs(const int level ){
    if(formatted) {
        for(int i =0; i < level; i++) {
            cout << "\t";
        }
    }
}

int main(int argc, const char * const * const argv)
{
    vector<string> args(argv, argv+argc);

    opt_t options;
    options["--name"]       = "";
    options["--type"]       = "";
    options["--file"]       = "";
    options["--output"]     = "";
    options["--namespace"]  = "";

    //Parse Arguments
    string curr_opt;
    bool verbose;
    for(auto arg : args) {
        if(arg == "--verbose") {
            verbose = true;
        }
        else if(arg == "--formatted") {
            formatted = true;
        }
        else if(arg == "--version") {
            cout << argv[0] << " By Umar Arshad" << endl;
        }
        else if(arg == "--help") {
            print_usage();
        }
        else if(options.find(arg) != options.end()) {
            curr_opt = arg;
        }
        else if(curr_opt.empty()) {
            cerr << "Invalid Argument: " << arg << endl;
        }
        else {
            if(options[curr_opt] != "") {
                options[curr_opt] += " " + arg;
            }
            else {
                options[curr_opt] += arg;
            }
        }
    }

    if(verbose) {
        for(auto opts : options) {
            cout << get<0>(opts) << " " << get<1>(opts) << endl;
        }
    }

    unique_ptr<ofstream> outfile;
    // Set defaults
    if(options["--name"] == "")     { options["--name"]     = "var"; }
    if(options["--output"] != "")   {
        outfile.reset(new ofstream(options["--output"]));
        cout.rdbuf(outfile->rdbuf());
    }
    int ns_cnt = 0;
    int level = 0;
    if(options["--namespace"] != "") {
        std::stringstream namespaces(options["--namespace"]);
        string name;
        namespaces >> name;
        do {
            add_tabs(level++);
            cout << "namespace " << name << " { \n";
            ns_cnt++;
            namespaces >> name;
        } while(!namespaces.fail());
    }

    if(options["--type"] == "") {
        options["--type"]     = "char";
    }
    add_tabs(level);
    cout << "static const " << options["--type"] << " " << options["--name"] << "[] = {\n";


    ifstream input(options["--file"]);
    size_t char_cnt = 0;
    add_tabs(++level);
    for(char i; input.get(i);) {
        cout << "0x" << std::hex << static_cast<int>(i) << ",\t";
        char_cnt++;
        if(!(char_cnt % 10)) {
            cout << endl;
            add_tabs(level);
        }
    }
    cout << "};\n";
    add_tabs(--level);
    cout << "static const size_t " << options["--name"] << "_len" << " = " << std::dec << char_cnt << ";\n";

    while(ns_cnt--) {
        add_tabs(--level);
        cout << "}\n";
    }
}
