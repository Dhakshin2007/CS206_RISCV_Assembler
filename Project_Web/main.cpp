// main.cpp
// Minimal wrapper to let Assembler.cpp's assemble() be used via stdin/stdout.
// It writes stdin to a temp input file, calls assemble(inputFile, outputFile),
// then prints the output file to stdout.

#include <bits/stdc++.h>
#include<thread>
using namespace std;

// assemble is implemented in Assembler.cpp (uploaded).
// Declaration here so we can link both files together.
extern void assemble(const string &inputf, const string &outputf);

static string make_temp_name(const string &prefix) {
    std::ostringstream ss;
    ss << prefix << "_" << std::time(nullptr) << "_" << rand();
    return ss.str();
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read all stdin into a string
    string code;
    string line;
    bool first = true;
    while (std::getline(cin, line)) {
        if (!first) code += "\n";
        code += line;
        first = false;
    }

    // Generate temp filenames in working directory
    string unique = make_temp_name("tmp");
    string inFile = unique + "_input.s";
    string outFile = unique + "_output.txt";

    // Write code to input file
    {
        ofstream ofs(inFile);
        if (!ofs) {
            cerr << "ERROR: cannot create temp input file\n";
            return 2;
        }
        ofs << code << "\n";
    }

    // Call assembler (function from Assembler.cpp)
    // Note: assemble(...) prints errors to its own cout/outputs to outFile
    try {
        assemble(inFile, outFile);
    } catch (const std::exception &e) {
        cerr << "ERROR: assemble() threw exception: " << e.what() << "\n";
    } catch (...) {
        cerr << "ERROR: assemble() threw unknown exception\n";
    }

    // Read output file and print to stdout
    ifstream ifs(outFile);
    if (!ifs) {
        cerr << "ERROR: assembler did not produce output file\n";
        // Try to be helpful: attempt to read any partial output from cout? can't.
        // Exit with non-zero.
        return 3;
    }
    string outLine;
    while (getline(ifs, outLine)) {
        cout << outLine << "\n";
    }

    // Clean up temp files (best-effort)
    remove(inFile.c_str());
    remove(outFile.c_str());

    return 0;
}
