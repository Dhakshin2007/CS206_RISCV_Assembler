#include <bits/stdc++.h>
using namespace std;

unordered_map<string, int> ud_labels;
long long line_number = 0;
long long line_number2 = 0;

unordered_map<string, int> label_ins_num;

unordered_map<string, string> opcode = {
    {"add", "0110011"},
    {"and", "0110011"},
    {"or", "0110011"},
    {"sll", "0110011"},
    {"slt", "0110011"},
    {"sra", "0110011"},
    {"srl", "0110011"},
    {"sub", "0110011"},
    {"xor", "0110011"},
    {"mul", "0110011"},
    {"div", "0110011"},
    {"rem", "0110011"},
    {"addi", "0010011"},
    {"andi", "0010011"},
    {"ori", "0010011"},
    {"lb", "0000011"},
    {"ld", "0000011"},
    {"lh", "0000011"},
    {"lw", "0000011"},
    {"jalr", "1100111"},
    {"sb", "0100011"},
    {"sw", "0100011"},
    {"sd", "0100011"},
    {"sh", "0100011"},
    {"beq", "1100011"},
    {"bne", "1100011"},
    {"bge", "1100011"},
    {"blt", "1100011"},
    {"auipc", "0010111"},
    {"lui", "0110111"},
    {"jal", "1101111"}

};

unordered_map<string, string> registers = {
    {"x0", "00000"},
    {"x1", "00001"},
    {"x2", "00010"},
    {"x3", "00011"},
    {"x4", "00100"},
    {"x5", "00101"},
    {"x6", "00110"},
    {"x7", "00111"},
    {"x8", "01000"},
    {"x9", "01001"},
    {"x10", "01010"},
    {"x11", "01011"},
    {"x12", "01100"},
    {"x13", "01101"},
    {"x14", "01110"},
    {"x15", "01111"},
    {"x16", "10000"},
    {"x17", "10001"},
    {"x18", "10010"},
    {"x19", "10011"},
    {"x20", "10100"},
    {"x21", "10101"},
    {"x22", "10110"},
    {"x23", "10111"},
    {"x24", "11000"},
    {"x25", "11001"},
    {"x26", "11010"},
    {"x27", "11011"},
    {"x28", "11100"},
    {"x29", "11101"},
    {"x30", "11110"},
    {"x31", "11111"}};

unordered_map<string, string> funct3 = {
    {"add", "000"},
    {"and", "111"},
    {"or", "110"},
    {"sll", "001"},
    {"slt", "010"},
    {"sra", "101"},
    {"srl", "101"},
    {"sub", "000"},
    {"xor", "100"},
    {"mul", "000"},
    {"div", "100"},
    {"rem", "110"},
    {"addi", "000"},
    {"andi", "111"},
    {"ori", "110"},
    {"lb", "000"},
    {"ld", "011"},
    {"lh", "001"},
    {"lw", "010"},
    {"jalr", "000"},
    {"sb", "000"},
    {"sw", "010"},
    {"sd", "011"},
    {"sh", "001"},
    {"beq", "000"},
    {"bne", "001"},
    {"bge", "101"},
    {"blt", "100"},

};
unordered_map<string, string> funct7 = {
    {"add", "0000000"},
    {"and", "0000000"},
    {"or", "0000000"},
    {"sll", "0000000"},
    {"slt", "0000000"},
    {"sra", "0100000"},
    {"srl", "0000000"},
    {"sub", "0100000"},
    {"xor", "0000000"},

};
unordered_map<string, string> ins_type = {
    {"add", "R"}, {"and", "R"}, {"or", "R"}, {"sll", "R"}, {"slt", "R"}, {"sra", "R"}, {"srl", "R"}, {"sub", "R"}, {"xor", "R"}, {"mul", "R"}, {"div", "R"}, {"rem", "R"}, {"addi", "I"}, {"andi", "I"}, {"ori", "I"}, {"lb", "I"}, {"ld", "I"}, {"lh", "I"}, {"lw", "I"}, {"jalr", "I"}, {"sb", "S"}, {"sw", "S"}, {"sd", "S"}, {"sh", "S"}, {"beq", "SB"}, {"bne", "SB"}, {"bge", "SB"}, {"blt", "SB"}, {"auipc", "U"}, {"lui", "U"}, {"jal", "UJ"}};

bool isNumber(const string &str)
{
    try
    {
        stoi(str);
        return true;
    }
    catch (const invalid_argument &)
    {
        return false;
    }
    catch (const out_of_range &)
    {
        return false;
    }
}

string hex2bin(string &h, int length)
{
    string a, b;

    int i = 0;
    while (i < 8)
    {
        switch (h[i])
        {
        case '0':
            a = "0000";
            break;
        case '1':
            a = "0001";
            break;
        case '2':
            a = "0010";
            break;
        case '3':
            a = "0011";
            break;
        case '4':
            a = "0100";
            break;
        case '5':
            a = "0101";
            break;
        case '6':
            a = "0110";
            break;
        case '7':
            a = "0111";
            break;
        case '8':
            a = "1000";
            break;
        case '9':
            a = "1001";
            break;
        case 'a':
        case 'A':
            a = "1010";
            break;
        case 'b':
        case 'B':
            a = "1011";
            break;
        case 'c':
        case 'C':
            a = "1100";
            break;
        case 'd':
        case 'D':
            a = "1101";
            break;
        case 'e':
        case 'E':
            a = "1110";
            break;
        case 'f':
        case 'F':
            a = "1111";
            break;
        }
        b += a;

        a.clear();
        i++;
    }
    while (b.size() < length)
    {
        b = "0" + b;
    }
    return b;
}

int power(int a)
{
    if (a == 0)
    {
        return 1;
    }
    return 10 * power(a - 1);
}

string dec2bin_data(string &h, int l)
{
    string a;
    int i = 0;
    int sum = 0;
    while (i < l)
    {
        char a = h[l - i - 1];
        int b = a - '0';
        sum += power(i) * b;
        i++;
    }
    while (sum > 0)
    {
        int rem = sum % 2;
        sum = sum / 2;
        char c = rem + '0';
        a += c;
    }
    reverse(a.begin(), a.end());
    return a;
}

string dec2bin_20(string &a, int l)
{
    long long temp_tfg = stoll(a);
    bitset<20> tfg(temp_tfg);
    string result_tfg = "";
    for (int i = 19; i >= 0; i--)
    {
        if (tfg[i] == 0)
        {
            result_tfg += "0";
        }
        else
        {
            result_tfg += "1";
        }
    }
    return result_tfg;
}

string dec2bin_12(string &a, int l)
{

    long long temp_tfg = stoll(a);
    bitset<12> tfg(temp_tfg);
    string result_tfg = "";
    for (int i = 11; i >= 0; i--)
    {
        if (tfg[i] == 0)
        {
            result_tfg += "0";
        }
        else
        {
            result_tfg += "1";
        }
    }
    return result_tfg;
}

string dec2bin_32(string &a, int l)
{
    long long temp_tfg = stoll(a);
    bitset<32> tfg(temp_tfg);
    string result_tfg = "";
    for (int i = 31; i >= 0; i--)
    {
        if (tfg[i] == 0)
        {
            result_tfg += "0";
        }
        else
        {
            result_tfg += "1";
        }
    }
    return result_tfg;
}

string dec2bin_8(string &a, int l)
{
    long long temp_tfg = stoll(a);
    bitset<8> tfg(temp_tfg);
    string result_tfg = "";
    for (int i = 7; i >= 0; i--)
    {
        if (tfg[i] == 0)
        {
            result_tfg += "0";
        }
        else
        {
            result_tfg += "1";
        }
    }
    return result_tfg;
}

string dec2bin_16(string &a, int l)
{
    long long temp_tfg = stoll(a);
    bitset<16> tfg(temp_tfg);
    string result_tfg = "";
    for (int i = 15; i >= 0; i--)
    {
        if (tfg[i] == 0)
        {
            result_tfg += "0";
        }
        else
        {
            result_tfg += "1";
        }
    }
    return result_tfg;
}

string dec2bin_64(string &a, int l)
{
    long long temp_tfg = stoll(a);
    bitset<64> tfg(temp_tfg);
    string result_tfg = "";
    for (int i = 63; i >= 0; i--)
    {
        if (tfg[i] == 0)
        {
            result_tfg += "0";
        }
        else
        {
            result_tfg += "1";
        }
    }
    return result_tfg;
}

string dec2bin(const string &a, int l)
{
    int num = stoi(a);
    string binary;
    while (num > 0)
    {
        binary.insert(binary.begin(), '0' + (num & 1));
        num >>= 1;
    }
    while (binary.length() < l)
    {
        binary.insert(binary.begin(), '0');
    }
    if (binary.length() > l)
    {
        binary = binary.substr(binary.length() - l);
    }

    return binary;
}

string bintohex(string &s)
{
    bitset<32> bintohex(s);
    unsigned int intValue = bintohex.to_ulong();
    stringstream hexStream;
    hexStream << hex << uppercase << intValue;
    string hexString = hexStream.str();
    int l = 16 - hexString.length();
    string b(l, '0');
    b += hexString;
    b.insert(0, "0x");
    return b;
}

string bintohex8(string &s)
{
    bitset<32> bintohex(s);
    unsigned int intValue = bintohex.to_ulong();
    stringstream hexStream;
    hexStream << hex << uppercase << intValue;
    string hexString = hexStream.str();
    int l = 8 - hexString.length();
    string b(l, '0');
    b += hexString;
    b.insert(0, "0x");
    return b;
}

long long codeaddress = 0x00000000;  // Address of code segment
long long dataaddress = 0x10000000;  // Address of data segment
long long heapaddress = 0x10008000;  // Address of heap segment
long long stackaddress = 0x7FFFFFDC; // Address of stack segment

string Rformat(string instruction, string rs2, string rs1, string rd) // For R format instructions
{
    string bin = "";
    bin = bin + funct7[instruction];
    bin = bin + rs2;

    bin = bin + rs1;
    bin = bin + funct3[instruction];
    bin = bin + rd;
    bin = bin + opcode[instruction];

    string hex = bintohex8(bin);
    return hex;
}

string Iformat(string instruction, string immediate, string rs1, string rd) // For I format instructions
{
    string bin = "";
    bin = bin + immediate;
    bin = bin + rs1;
    bin = bin + funct3[instruction];
    bin = bin + rd;
    bin = bin + opcode[instruction];

    string hex = bintohex8(bin);
    return hex;
}

string Sformat(string instruction, string rs2, string rs1, string immediate) // For S format instructions
{
    string bin = "";
    bin = bin + immediate[0] + immediate[1] + immediate[2] + immediate[3] + immediate[4] + immediate[5] + immediate[6];
    bin = bin + rs2;
    bin = bin + rs1;
    bin = bin + funct3[instruction];
    bin = bin + immediate[7] + immediate[8] + immediate[9] + immediate[10] + immediate[11];
    bin = bin + opcode[instruction];
    string hex = bintohex8(bin);
    return hex;
}

string SBformat(string instruction, string rs2, string rs1, string immediate) // For SB format instructions
{
    immediate = immediate.substr(7);
    string bin = "";
    bin = bin + immediate[0] + immediate[2] + immediate[3] + immediate[4] + immediate[5] + immediate[6] + immediate[7];
    bin = bin + rs2;
    bin = bin + rs1;
    bin = bin + funct3[instruction];
    bin = bin + immediate[8] + immediate[9] + immediate[10] + immediate[11] + immediate[1];
    bin = bin + opcode[instruction];
    string hex = bintohex8(bin);
    return hex;
}

string Uformat(string instruction, string immediate, string rd) // For U format instructions
{
    string bin = "";
    bin = bin + immediate;
    bin = bin + rd;
    bin = bin + opcode[instruction];
    string hex = bintohex8(bin);
    return hex;
}

string UJformat(string instruction, string immediate, string rd) // For UJ format instructions
{
    reverse(immediate.begin(), immediate.end());
    immediate = immediate.substr(0, 21);
    string bin = "";
    bin = bin + immediate[20];
    bin = bin + immediate[10] + immediate[9] + immediate[8] + immediate[7] + immediate[6] + immediate[5] + immediate[4] + immediate[3] + immediate[2] + immediate[1];
    bin = bin + immediate[11];
    bin = bin + immediate[19] + immediate[18] + immediate[17] + immediate[16] + immediate[15] + immediate[14] + immediate[13] + immediate[12];
    bin = bin + rd;
    bin = bin + opcode[instruction];
    string hex = bintohex8(bin);
    return hex;
}

int check(string instruction)
{

    regex lw(R"(^([Ll][Ww]\s+x\d{1,2}\s+\d+\s+x\d{1,2})|([Ll][Ww]\s+x\d{1,2}\s+\d+\s*\(\s*x\d{1,2}\s*\))|([Ll][Ww]\s+x\d{1,2}\s+\w+)$)");
    // cout<<regex_match(instruction, lw);
    if (regex_match(instruction, lw))
    {
        return 1;
    }
    regex addi(R"(^[Aa][Dd][Dd][Ii]\s+x\d{1,2}\s+x\d{1,2}\s+\d+$)");
    if (regex_match(instruction, addi))
    {
        return 1;
    }
    regex andi(R"(^[Aa][Nn][Dd][Ii]\s+x\d{1,2}\s+x\d{1,2}\s+\d+$)");
    if (regex_match(instruction, andi))
    {
        return 1;
    }

    regex ori(R"(^[Oo][Rr][Ii]\s+x\d{1,2}\s+x\d{1,2}\s+\d+$)");
    if (regex_match(instruction, ori))
    {
        return 1;
    }

    regex lb(R"(^[Ll][Bb]\s+x\d{1,2}\s+\d{1}\s*\(\s*x\d{1,2}\s*\)|[Ll][bB]\s+x\d{1,2}\s+\w+$)");
    if (regex_match(instruction, lb))
    {
        return 1;
    }

    regex ld(R"(^[Ll][Dd]\s+x\d{1,2}\s+\d{1}\s*\(\s*x\d{1,2}\s*\)|[Ll][Dd]\s+x\d{1,2}\s+\w+$)");
    if (regex_match(instruction, ld))
    {
        return 1;
    }

    regex lh(R"(^[Ll][Hh]\s+x\d{1,2}\s+\d{1}\s*\(\s*x\d{1,2}\s*\)|[Ll][Hh]\s+x\d{1,2}\s+\w+$)");
    if (regex_match(instruction, lh))
    {
        return 1;
    }

    // sb format
    regex beq(R"(^[Bb][Ee][Qq]\s+x\d{1,2}\s+x\d{1,2}\s+\w+$)");
    // cout<<regex_match(instruction, beq);
    if (regex_match(instruction, beq))
    {
        return 1;
    }

    regex bne(R"(^[Bb][nN][Ee]\s+x\d{1,2}\s+x\d{1,2}\s+\w+$)");
    if (regex_match(instruction, bne))
    {
        return 1;
    }

    regex bge(R"(^[Bb][Gg][Ee]\s+x\d{1,2}\s+x\d{1,2}\s+\w+$)");
    if (regex_match(instruction, bge))
    {
        return 1;
    }

    regex blt(R"(^[Bb][Ll][Tt]\s+x\d{1,2}\s+x\d{1,2}\s+\w+$)");
    if (regex_match(instruction, blt))
    {
        return 1;
    }

    regex auipc(R"(^[aA][Uu][Ii][Pp][Cc]\s+x\d{1,2}\s+\d+$)");
    if (regex_match(instruction, auipc))
    {
        return 1;
    }

    regex lui(R"(^[Ll][Uu][iI]\s+x\d{1,2}\s+\d+$)");
    if (regex_match(instruction, lui))
    {
        return 1;
    }

    regex add(R"(^[Aa][Dd][Dd]\s+x\d{1,2}\s+x\d{1,2}\s+x\d{1,2}$)");
    if (regex_match(instruction, add))
    {
        return 1;
    }
    // cout<<instruction<<endl;
    regex andf(R"(^[Aa][Nn][Dd]\s+x\d{1,2}\s+x\d{1,2}\s+x\d{1,2}$)");
    if (regex_match(instruction, andf))
    {
        return 1;
    }

    regex orf(R"(^[Oo][Rr]\s+x\d{1,2}\s+x\d{1,2}\s+x\d{1,2}$)");
    if (regex_match(instruction, orf))
    {
        return 1;
    }

    regex sll(R"(^[Ss][Ll][Ll]\s+x\d{1,2}\s+x\d{1,2}\s+x\d{1,2}$)");
    if (regex_match(instruction, sll))
    {
        return 1;
    }

    regex slt(R"(^[Ss][Ll][Tt]\s+x\d{1,2}\s+x\d{1,2}\s+x\d{1,2}$)");
    if (regex_match(instruction, slt))
    {
        return 1;
    }

    regex sra(R"(^[Ss][Rr][Aa]\s+x\d{1,2}\s+x\d{1,2}\s+x\d{1,2}$)");
    if (regex_match(instruction, sra))
    {
        return 1;
    }

    regex srl(R"(^[Ss][Rr][Ll]\s+x\d{1,2}\s+x\d{1,2}\s+x\d{1,2}$)");
    if (regex_match(instruction, srl))
    {
        return 1;
    }

    regex subf(R"(^[Ss][Uu][Bb]\s+x\d{1,2}\s+x\d{1,2}\s+x\d{1,2}$)");
    if (regex_match(instruction, subf))
    {
        return 1;
    }

    regex xorf(R"(^[Xx][Oo][Rr]\s+x\d{1,2}\s+x\d{1,2}\s+x\d{1,2}$)");
    if (regex_match(instruction, xorf))
    {
        return 1;
    }

    regex mul(R"(^[Mm][Uu][Ll]\s+x\d{1,2}\s+x\d{1,2}\s+x\d{1,2}$)");
    if (regex_match(instruction, mul))
    {
        return 1;
    }

    regex div(R"(^[Dd][Ii][Vv]\s+x\d{1,2}\s+x\d{1,2}\s+x\d{1,2}$)");
    if (regex_match(instruction, div))
    {
        return 1;
    }

    regex rem(R"(^[Rr][Ee][Mm]\s+x\d{1,2}\s+x\d{1,2}\s+x\d{1,2}$)");
    if (regex_match(instruction, rem))
    {
        return 1;
    }

    regex jal(R"(^[jJ][Aa][Ll]\s+x\d{1,2}\s+\w+$)");
    if (regex_match(instruction, jal))
    {
        return 1;
    }

    regex jalr(R"(^[jJ][Aa][Ll][Rr]\s+x\d{1,2}\s+x\d{1,2}\s+\d+$|[jJ][Aa][Ll][Rr]\s+x\d{1,2}\s+\w+$)");
    if (regex_match(instruction, jalr))
    {
        return 1;
    }

    regex sb(R"(^[Ss][Ww]\s+x\d{1,2}\s+\d+\s*\(\s*x\d{1,2}\s*\)|[Ss][wW]\s+x\d{1,2}\s+\d+\s+x\d{1,2}$)");
    if (regex_match(instruction, sb))
    {
        return 1;
    }

    regex sw(R"(^[Ss][Ww]\s+x\d{1,2}\s+\d+\s*\(\s*x\d{1,2}\s*\)|[Ss][wW]\s+x\d{1,2}\s+\d+\s+x\d{1,2}$)");
    if (regex_match(instruction, sw))
    {
        return 1;
    }

    regex sd(R"(^[Ss][Dd]\s+x\d{1,2}\s+\d+\s*\(\s*x\d{1,2}\s*\)|[Ss][Dd]\s+x\d{1,2}\s+\d+\s+x\d{1,2}$)");
    if (regex_match(instruction, sd))
    {
        return 1;
    }

    regex sh(R"(sh = ^[Ss][Hh]\s+x\d{1,2}\s+\d+\s*\(\s*x\d{1,2}\s*\)|[Ss][Hh]\s+x\d{1,2}\s+\d+\s+x\d{1,2}$)");
    if (regex_match(instruction, sh))
    {
        return 1;
    }

    return -1;
}

void assemble(string inputf, string outputf) // Function to take input and write into the output file
{
    long long instruction_counter = 0;

    ifstream infile(inputf);
    ofstream outfile(outputf);

    if (!infile.is_open() || !outfile.is_open())
    {
        cout << "Error opening files" << endl;
        return;
    }
    string line;

    while (getline(infile, line))
    {
        line = regex_replace(line, regex("^\\s+|\\s+$"), ""); // Removing spaces leading or trailing
        line = regex_replace(line, regex(","), " ");          // Removing commas

        size_t pos_tv = line.find('#');
        if (pos_tv != string::npos)
        {
            line = line.substr(0, pos_tv);
        }

        if (line.empty())
        {
            continue;
        }

        line_number++;

        if (line[0] == '.')
        {
            istringstream iss(line);
            string token;
            iss >> token;
            if (token == ".text")
            {

                long long instruction_counter_i = 0;
                while (getline(infile, line))
                {
                    // cout << "lol" << endl;
                    line = regex_replace(line, regex("^\\s+|\\s+$"), ""); // Removing spaces leading or trailing
                    line = regex_replace(line, regex(","), " ");          // Removing commas

                    size_t pos_tv = line.find('#');
                    if (pos_tv != string::npos)
                    {
                        line = line.substr(0, pos_tv);
                    }

                    if (line.empty())
                    {
                        continue;
                    }

                    line_number++;

                    // Handling the labels
                    size_t colonPos = line.find(':');

                    if (colonPos != string::npos)
                    {
                        string token_tmp = line.substr(0, colonPos); // Extract substring up to colon
                        line = line.substr(colonPos + 1);
                        ud_labels[token_tmp] = line_number;
                    }

                    if (line.empty())
                    {
                        continue;
                    }

                    istringstream iss(line);
                    vector<string> tokens;
                    for (string token; iss >> token;)
                    {
                        tokens.push_back(token);
                    }

                    if (tokens[0] == ".data")
                    {
                        // Implement for .data
                        token = ".data";
                        break;
                    }
                    int ch = check(line);
                    if (ch == -1)
                    {
                        cout << "Syntax Error" << endl;
                    }

                    string inst = ins_type[tokens[0]];
                    string machinecode;
                    if (inst == "R")
                    {
                        instruction_counter_i++;
                        machinecode = Rformat(tokens[0], registers[tokens[3]], registers[tokens[2]], registers[tokens[1]]);
                        outfile << "0x" << hex << uppercase << codeaddress << " " << machinecode << endl;
                        codeaddress += 4;
                    }
                    else if (inst == "I")
                    {

                        // cout << tokens[0] << " " << tokens[1] << " " << tokens[2] << " " << tokens[3] << endl;

                        size_t colonPos = line.find('(');
                        // cout << "Yeswanth" << endl;
                        if (colonPos == string::npos)
                        {
                            // cout << "Dhakshin" << endl;
                            // cout << tokens[0] << " " << tokens[1] << " " << tokens[2] << endl;
                            if ((isNumber(tokens[3]) && (tokens[0] == "jalr")))
                            {
                                machinecode = Iformat(tokens[0], dec2bin_12(tokens[3], 12), registers[tokens[2]], registers[tokens[1]]);
                            }
                            else if (tokens[0] == "jalr")
                            {
                                long long label_ln = 0;
                                auto temp_iter = ud_labels.find(tokens[3]);
                                if (temp_iter != ud_labels.end())
                                {
                                    string label_upto = temp_iter->first;
                                    long long insyt = label_ins_num[label_upto];

                                    insyt = insyt * 4;
                                    string hg = to_string(insyt);
                                    machinecode = Iformat(tokens[0], dec2bin_12(hg, 12), registers[tokens[2]], registers[tokens[1]]);
                                    // if (label_ln == line_number)
                                    // {
                                    //     string hg = "0";
                                    //     machinecode = Iformat(tokens[0], dec2bin_12(hg, 12), registers[tokens[2]], registers[tokens[1]]);
                                    // }
                                    // else if (label_ln < line_number)
                                    // {

                                    //     long long value_tds = line_number - label_ln - 1;
                                    //     value_tds *= -4;
                                    //     string hg = to_string(value_tds);
                                    //     cout << hg << " hg" << endl;
                                    //     machinecode = Iformat(tokens[0], dec2bin_12(hg, 12), registers[tokens[2]], registers[tokens[1]]);
                                    // }
                                    // else
                                    // {

                                    //     long long value_tds = label_ln - line_number;

                                    //     value_tds *= 4;
                                    //     outfile<<value_tds<<endl;
                                    //     string hg = to_string(value_tds);
                                    //     machinecode = Iformat(tokens[0], dec2bin_12(hg, 12), registers[tokens[2]], registers[tokens[1]]);
                                    // }
                                }
                                else
                                {
                                    // cout << "line " << line_number << endl;
                                    outfile << "Error Label " << tokens[3] << " not Found on line :" << endl;
                                }
                            }
                            else if (tokens[0] != "jalr")
                            {
                                if ((tokens[0] == "lw") || (tokens[0] == "lb") || (tokens[0] == "lh") || (tokens[0] == "ld"))
                                {
                                    machinecode = Iformat(tokens[0], dec2bin_12(tokens[2], 12), registers[tokens[3]], registers[tokens[1]]);
                                }
                                else
                                {
                                    machinecode = Iformat(tokens[0], dec2bin_12(tokens[3], 12), registers[tokens[2]], registers[tokens[1]]);
                                    // cout << machinecode << endl;
                                }
                            }
                            else
                            {
                                machinecode = Iformat(tokens[0], dec2bin_12(tokens[3], 12), registers[tokens[2]], registers[tokens[1]]);
                                // cout << machinecode << endl;
                            }
                        }
                        else
                        {

                            string a_token = "";
                            string b_token = "";
                            string c_token;
                            string d_token;

                            string concatenated;

                            for (int index = 2; index < tokens.size(); index++)
                            {
                                concatenated += tokens[index];
                            }
                            concatenated.erase(std::remove(concatenated.begin(), concatenated.end(), ' '), concatenated.end());
                            concatenated.erase(std::remove(concatenated.begin(), concatenated.end(), '{'), concatenated.end());
                            concatenated.erase(std::remove(concatenated.begin(), concatenated.end(), '}'), concatenated.end());
                            int index = 0;
                            for (index = 0; index < concatenated.size(); index++)
                            {
                                if (concatenated[index] == '(')
                                {
                                    break;
                                }
                                a_token += concatenated[index];
                            }
                            index++;
                            for (; index < concatenated.size(); index++)
                            {
                                if (concatenated[index] == ')')
                                {
                                    break;
                                }
                                b_token += concatenated[index];
                            }

                            if ((tokens[0] == "lw") || (tokens[0] == "lb") || (tokens[0] == "lh") || (tokens[0] == "ld"))
                            {
                                machinecode = Iformat(tokens[0], dec2bin_12(a_token, 12), registers[b_token], registers[tokens[1]]);
                            }
                            else
                            {
                                machinecode = Iformat(tokens[0], dec2bin_12(tokens[3], 12), registers[tokens[2]], registers[tokens[1]]);
                                // cout << machinecode << endl;
                            }
                        }
                        instruction_counter_i++;
                        outfile << "0x" << hex << uppercase << codeaddress << " " << machinecode << endl;
                        codeaddress += 4;
                    }
                    else if (inst == "S")
                    {
                        string a_token = "";
                        string b_token = "";
                        string c_token;
                        string d_token;

                        string concatenated;

                        for (int index = 2; index < tokens.size(); index++)
                        {
                            concatenated += tokens[index];
                        }
                        concatenated.erase(std::remove(concatenated.begin(), concatenated.end(), ' '), concatenated.end());
                        concatenated.erase(std::remove(concatenated.begin(), concatenated.end(), '{'), concatenated.end());
                        concatenated.erase(std::remove(concatenated.begin(), concatenated.end(), '}'), concatenated.end());
                        int index = 0;
                        for (index = 0; index < concatenated.size(); index++)
                        {
                            if (concatenated[index] == '(')
                            {
                                break;
                            }
                            a_token += concatenated[index];
                        }
                        index++;
                        for (; index < concatenated.size(); index++)
                        {
                            if (concatenated[index] == ')')
                            {
                                break;
                            }
                            b_token += concatenated[index];
                        }
                        instruction_counter_i++;
                        machinecode = Sformat(tokens[0], registers[tokens[1]], registers[b_token], dec2bin_12(a_token, 12));
                        outfile << "0x" << hex << uppercase << codeaddress << " " << machinecode << endl;
                        codeaddress += 4;
                    }
                    else if (inst == "SB")
                    {
                        if (!isNumber(tokens[3]))
                        {
                            long long label_ln = 0;
                            auto temp_iter = ud_labels.find(tokens[3]);
                            if (temp_iter != ud_labels.end())
                            {
                                label_ln = temp_iter->second;
                                if (label_ln == line_number)
                                {
                                    string hg = "0";
                                    machinecode = SBformat(tokens[0], registers[tokens[2]], registers[tokens[1]], dec2bin_20(hg, 13));
                                }
                                else if (label_ln < line_number)
                                {

                                    long long value_tds = line_number - label_ln - 1;
                                    value_tds *= -4;
                                    string hg = to_string(value_tds);
                                    // cout << hg << " hg" << endl;
                                    machinecode = SBformat(tokens[0], registers[tokens[2]], registers[tokens[1]], dec2bin_20(hg, 13));
                                }
                                else
                                {
                                    long long value_tds = label_ln - line_number;
                                    value_tds *= 4;
                                    string hg = to_string(value_tds);
                                    machinecode = SBformat(tokens[0], registers[tokens[2]], registers[tokens[1]], dec2bin_20(hg, 13));
                                }
                            }
                            else
                            {
                                // cout << "line " << line_number << endl;
                                outfile << "Error Label " << tokens[3] << " not Found on line :" << endl;
                            }
                        }
                        else
                        {
                            machinecode = SBformat(tokens[0], registers[tokens[2]], registers[tokens[1]], dec2bin_20(tokens[3], 12));
                        }
                        instruction_counter_i++;
                        outfile << "0x" << hex << uppercase << codeaddress << " " << machinecode << endl;
                        codeaddress += 4;
                    }
                    else if (inst == "U")
                    {
                        instruction_counter_i++;
                        machinecode = Uformat(tokens[0], dec2bin_20(tokens[2], 20), registers[tokens[1]]);
                        outfile << "0x" << hex << uppercase << codeaddress << " " << machinecode << endl;
                        codeaddress += 4;
                    }
                    else if (inst == "UJ")
                    {
                        // cout << tokens[0] << " " << tokens[1] << " " << tokens[2] << endl;
                        if (!isNumber(tokens[2]))
                        {
                            long long label_ln = 0;
                            auto temp_iter = ud_labels.find(tokens[2]);
                            if (temp_iter != ud_labels.end())
                            {
                                label_ln = temp_iter->second;
                                if (label_ln == line_number)
                                {
                                    string hg = "0";
                                    machinecode = UJformat(tokens[0], dec2bin_32(hg, 20), registers[tokens[1]]);
                                }
                                else if (label_ln < line_number)
                                {

                                    long long value_tds = line_number - label_ln - 1;
                                    value_tds *= -4;
                                    string hg = to_string(value_tds);
                                    // cout << hg << " hg" << endl;
                                    machinecode = UJformat(tokens[0], dec2bin_32(hg, 20), registers[tokens[1]]);
                                }
                                else
                                {
                                    long long value_tds = label_ln - line_number;
                                    value_tds *= 4;
                                    string hg = to_string(value_tds);
                                    machinecode = UJformat(tokens[0], dec2bin_32(hg, 20), registers[tokens[1]]);
                                }
                            }
                            else
                            {
                                outfile << "Error Label " << tokens[2] << " not Found on line :" << endl;
                            }
                        }
                        else
                        {

                            machinecode = UJformat(tokens[0], dec2bin_32(tokens[2], 20), registers[tokens[1]]);
                        }
                        instruction_counter_i++;
                        outfile << "0x" << hex << uppercase << codeaddress << " " << machinecode << endl;
                        codeaddress += 4;
                    }

                    // Decode the instructions
                }
            }
            outfile << endl;
            outfile << "Section ended ------" << endl;

            if (token == ".data") // Writing to the output file in big endian format
            {
                outfile << endl;
                outfile << "  Address "
                        << " "
                        << "+0"
                        << " "
                        << "+1"
                        << " "
                        << "+2"
                        << " "
                        << "+3" << endl;
                int count_of_bytes = 0;
                int data_address_temporary = dataaddress;
                outfile << "0x" << hex << uppercase << data_address_temporary << " ";
                while (getline(infile, line))
                {
                    line = regex_replace(line, regex("^\\s+|\\s+$"), ""); // Removing spaces leading or trailing
                    line = regex_replace(line, regex(","), " ");          // Removing commas

                    size_t pos_tv = line.find('#');
                    if (pos_tv != string::npos)
                    {
                        line = line.substr(0, pos_tv);
                    }

                    if (line.empty())
                    {
                        continue;
                    }
                    line_number++;

                    // Handling the labels
                    size_t colonPos = line.find(':');

                    if (colonPos != string::npos)
                    {
                        string token_tmp = line.substr(0, colonPos); // Extract substring up to colon
                        line = line.substr(colonPos + 1);
                        ud_labels[token_tmp] = line_number;
                    }

                    istringstream iss(line);
                    vector<string> data_tokens;
                    string token_temp;
                    for (string token; iss >> token_temp;)
                    {
                        data_tokens.push_back(token_temp);
                    }

                    if (data_tokens[0] == ".text")
                    {
                        token = ".text";
                        outfile << endl;
                        outfile << endl;
                        break;
                    }

                    if (data_tokens[0] == ".byte")
                    {
                        int size_dt = data_tokens.size();
                        for (int i = 1; i < size_dt; i++)
                        {
                            string data_token_temporary = data_tokens[i];
                            int length_dtt = data_token_temporary.size();
                            string binary_data_token_temporary = dec2bin_8(data_token_temporary, length_dtt);
                            string binary_data_token_temporary2 = bintohex(binary_data_token_temporary);
                            outfile << binary_data_token_temporary2.substr(binary_data_token_temporary2.size() - 2) << " ";
                            count_of_bytes += 1;
                            if (count_of_bytes == 4)
                            {
                                count_of_bytes = 0;
                                data_address_temporary += 4;
                                outfile << endl;
                                outfile << "0x" << hex << uppercase << data_address_temporary << " ";
                            }
                        }
                    }
                    else if (data_tokens[0] == ".half")
                    {
                        int size_dt = data_tokens.size();
                        vector<string> output_memory;
                        for (int i = 1; i < size_dt; i++)
                        {
                            string data_token_temporary = data_tokens[i];
                            int length_dtt = data_token_temporary.size();
                            string binary_data_token_temporary = dec2bin_16(data_token_temporary, length_dtt);
                            string binary_data_token_temporary2 = bintohex(binary_data_token_temporary);
                            int it = 1;
                            while (it < 3)
                            {
                                output_memory.push_back(binary_data_token_temporary2.substr(binary_data_token_temporary2.size() - 2 * it, 2));
                                it++;
                            }
                        }
                        int size_om = output_memory.size();
                        for (int i = 0; i < size_om; i++)
                        {
                            outfile << output_memory[i] << " ";
                            count_of_bytes++;
                            if (count_of_bytes == 4)
                            {
                                count_of_bytes = 0;
                                data_address_temporary += 4;
                                outfile << endl;
                                outfile << "0x" << hex << uppercase << data_address_temporary << " ";
                            }
                        }
                    }
                    else if (data_tokens[0] == ".word")
                    {
                        int size_dt = data_tokens.size();
                        vector<string> output_memory;
                        for (int i = 1; i < size_dt; i++)
                        {
                            string data_token_temporary = data_tokens[i];
                            int length_dtt = data_token_temporary.size();
                            string binary_data_token_temporary = dec2bin_32(data_token_temporary, length_dtt);
                            string binary_data_token_temporary2 = bintohex(binary_data_token_temporary);
                            int it = 1;
                            while (it < 5)
                            {
                                output_memory.push_back(binary_data_token_temporary2.substr(binary_data_token_temporary2.size() - 2 * it, 2));
                                it++;
                            }
                        }
                        int size_om = output_memory.size();
                        for (int i = 0; i < size_om; i++)
                        {
                            outfile << output_memory[i] << " ";
                            count_of_bytes++;
                            if (count_of_bytes == 4)
                            {
                                count_of_bytes = 0;
                                data_address_temporary += 4;
                                outfile << endl;
                                outfile << "0x" << hex << uppercase << data_address_temporary << " ";
                            }
                        }
                    }
                    else if (data_tokens[0] == ".dword")
                    {
                        int size_dt = data_tokens.size();
                        vector<string> output_memory;
                        for (int i = 1; i < size_dt; i++)
                        {
                            string data_token_temporary = data_tokens[i];
                            int length_dtt = data_token_temporary.size();
                            string binary_data_token_temporary = dec2bin_64(data_token_temporary, length_dtt);
                            string binary_data_token_temporary2 = bintohex(binary_data_token_temporary);
                            int it = 1;
                            while (it < 9)
                            {
                                output_memory.push_back(binary_data_token_temporary2.substr(binary_data_token_temporary2.size() - 2 * it, 2));
                                it++;
                            }
                        }
                        int size_om = output_memory.size();
                        for (int i = 0; i < size_om; i++)
                        {
                            outfile << output_memory[i] << " ";
                            count_of_bytes++;
                            if (count_of_bytes == 4)
                            {
                                count_of_bytes = 0;
                                data_address_temporary += 4;
                                outfile << endl;
                                outfile << "0x" << hex << uppercase << data_address_temporary << " ";
                            }
                        }
                    }
                    else if (data_tokens[0] == ".asciiz")
                    {
                        int size_dt = data_tokens.size();
                        for (int i = 1; i < size_dt; i++)
                        {
                            string temporary_string_asciiz = data_tokens[i];
                            temporary_string_asciiz.erase(remove(temporary_string_asciiz.begin(), temporary_string_asciiz.end(), '"'), temporary_string_asciiz.end());
                            int size_tas = temporary_string_asciiz.size();
                            // cout << temporary_string_asciiz << endl;
                            for (int j = 0; j < size_tas; j++)
                            {
                                count_of_bytes++;
                                char ch = temporary_string_asciiz[j];
                                int value_ch = ch;
                                outfile << hex << uppercase << setw(2) << setfill('0') << value_ch << " ";
                                if (count_of_bytes == 4)
                                {
                                    count_of_bytes = 0;
                                    data_address_temporary += 4;
                                    outfile << endl;
                                    outfile << "0x" << hex << uppercase << data_address_temporary << " ";
                                }
                            }
                            int filler_value = 0;
                            outfile << hex << uppercase << setw(2) << setfill('0') << filler_value << " ";
                            count_of_bytes++;
                            if (count_of_bytes == 4)
                            {
                                count_of_bytes = 0;
                                data_address_temporary += 4;
                                outfile << endl;
                                outfile << "0x" << hex << uppercase << data_address_temporary << " ";
                            }
                        }
                    }
                }
            }
            outfile << endl;
            outfile << "Section ended ------" << endl;
            outfile << endl;
            if (token == ".text")
            {
                // cout << "ghello" << endl;
                long long instruction_counter_i = 0;
                while (getline(infile, line))
                {

                    line = regex_replace(line, regex("^\\s+|\\s+$"), ""); // Removing spaces leading or trailing
                    line = regex_replace(line, regex(","), " ");          // Removing commas

                    size_t pos_tv = line.find('#');
                    if (pos_tv != string::npos)
                    {
                        line = line.substr(0, pos_tv);
                    }

                    if (line.empty())
                    {
                        continue;
                    }

                    line_number++;

                    // Handling the labels
                    size_t colonPos = line.find(':');

                    if (colonPos != string::npos)
                    {
                        string token_tmp = line.substr(0, colonPos); // Extract substring up to colon
                        line = line.substr(colonPos + 1);
                        ud_labels[token_tmp] = line_number;
                    }

                    if (line.empty())
                    {
                        continue;
                    }

                    istringstream iss(line);
                    vector<string> tokens;
                    for (string token; iss >> token;)
                    {
                        tokens.push_back(token);
                    }

                    if (tokens[0] == ".data")
                    {
                        // Implement for .data
                        token = ".data";
                        break;
                    }
                    int ch = check(line);
                    if (ch == -1)
                    {
                        cout << "Syntax Error" << endl;
                    }

                    string inst = ins_type[tokens[0]];
                    string machinecode;
                    if (inst == "R")
                    {
                        instruction_counter_i++;
                        machinecode = Rformat(tokens[0], registers[tokens[3]], registers[tokens[2]], registers[tokens[1]]);
                        outfile << "0x" << hex << uppercase << codeaddress << " " << machinecode << endl;
                        codeaddress += 4;
                    }
                    else if (inst == "I")
                    {
                        // cout << tokens[0] << " " << tokens[1] << " " << tokens[2] << " " << tokens[3] << endl;

                        size_t colonPos = line.find('(');

                        if (colonPos == string::npos)
                        {
                            if ((isNumber(tokens[3]) && (tokens[0] == "jalr")))
                            {
                                machinecode = Iformat(tokens[0], dec2bin_12(tokens[3], 12), registers[tokens[2]], registers[tokens[1]]);
                            }
                            else if (tokens[0] == "jalr")
                            {
                                long long label_ln = 0;
                                auto temp_iter = ud_labels.find(tokens[3]);
                                if (temp_iter != ud_labels.end())
                                {
                                    string label_upto = temp_iter->first;
                                    long long insyt = label_ins_num[label_upto];

                                    insyt = insyt * 4;
                                    // cout<<insyt<<endl;
                                    string hg = to_string(insyt);
                                    machinecode = Iformat(tokens[0], dec2bin_12(hg, 12), registers[tokens[2]], registers[tokens[1]]);

                                    // if (label_ln == line_number)
                                    // {
                                    //     string hg = "0";
                                    //     machinecode = Iformat(tokens[0], dec2bin_12(hg, 12), registers[tokens[2]], registers[tokens[1]]);
                                    // }
                                    // else if (label_ln < line_number)
                                    // {

                                    //     long long value_tds = line_number - label_ln - 1;
                                    //     value_tds *= -4;
                                    //     string hg = to_string(value_tds);
                                    //     cout << hg << " hg" << endl;
                                    //     machinecode = Iformat(tokens[0], dec2bin_12(hg, 12), registers[tokens[2]], registers[tokens[1]]);
                                    // }
                                    // else
                                    // {

                                    //     long long value_tds = label_ln - line_number;

                                    //     value_tds *= 4;
                                    //     outfile<<value_tds<<endl;
                                    //     string hg = to_string(value_tds);
                                    //     machinecode = Iformat(tokens[0], dec2bin_12(hg, 12), registers[tokens[2]], registers[tokens[1]]);
                                    // }
                                }
                                else
                                {
                                    // cout << "line " << line_number << endl;
                                    outfile << "Error Label " << tokens[3] << " not Found on line :" << endl;
                                }
                            }
                            else if (tokens[0] != "jalr")
                            {
                                if ((tokens[0] == "lw") || (tokens[0] == "lb") || (tokens[0] == "lh") || (tokens[0] == "ld"))
                                {
                                    machinecode = Iformat(tokens[0], dec2bin_12(tokens[2], 12), registers[tokens[3]], registers[tokens[1]]);
                                }
                                else
                                {
                                    machinecode = Iformat(tokens[0], dec2bin_12(tokens[3], 12), registers[tokens[2]], registers[tokens[1]]);
                                    // cout << machinecode << endl;
                                }
                            }
                            else
                            {
                                machinecode = Iformat(tokens[0], dec2bin_12(tokens[3], 12), registers[tokens[2]], registers[tokens[1]]);
                                // cout << machinecode << endl;
                            }
                        }
                        else
                        {

                            string a_token = "";
                            string b_token = "";
                            string c_token;
                            string d_token;

                            string concatenated;

                            for (int index = 2; index < tokens.size(); index++)
                            {
                                concatenated += tokens[index];
                            }
                            concatenated.erase(std::remove(concatenated.begin(), concatenated.end(), ' '), concatenated.end());
                            concatenated.erase(std::remove(concatenated.begin(), concatenated.end(), '{'), concatenated.end());
                            concatenated.erase(std::remove(concatenated.begin(), concatenated.end(), '}'), concatenated.end());
                            int index = 0;
                            for (index = 0; index < concatenated.size(); index++)
                            {
                                if (concatenated[index] == '(')
                                {
                                    break;
                                }
                                a_token += concatenated[index];
                            }
                            index++;
                            for (; index < concatenated.size(); index++)
                            {
                                if (concatenated[index] == ')')
                                {
                                    break;
                                }
                                b_token += concatenated[index];
                            }

                            if ((tokens[0] == "lw") || (tokens[0] == "lb") || (tokens[0] == "lh") || (tokens[0] == "ld"))
                            {
                                machinecode = Iformat(tokens[0], dec2bin_12(a_token, 12), registers[b_token], registers[tokens[1]]);
                            }
                            else
                            {
                                machinecode = Iformat(tokens[0], dec2bin_12(tokens[3], 12), registers[tokens[2]], registers[tokens[1]]);
                                // cout << machinecode << endl;
                            }
                        }
                        instruction_counter_i++;
                        outfile << "0x" << hex << uppercase << codeaddress << " " << machinecode << endl;
                        codeaddress += 4;
                    }
                    else if (inst == "S")
                    {
                        string a_token = "";
                        string b_token = "";
                        string c_token;
                        string d_token;

                        string concatenated;

                        for (int index = 2; index < tokens.size(); index++)
                        {
                            concatenated += tokens[index];
                        }
                        concatenated.erase(std::remove(concatenated.begin(), concatenated.end(), ' '), concatenated.end());
                        concatenated.erase(std::remove(concatenated.begin(), concatenated.end(), '{'), concatenated.end());
                        concatenated.erase(std::remove(concatenated.begin(), concatenated.end(), '}'), concatenated.end());
                        int index = 0;
                        for (index = 0; index < concatenated.size(); index++)
                        {
                            if (concatenated[index] == '(')
                            {
                                break;
                            }
                            a_token += concatenated[index];
                        }
                        index++;
                        for (; index < concatenated.size(); index++)
                        {
                            if (concatenated[index] == ')')
                            {
                                break;
                            }
                            b_token += concatenated[index];
                        }
                        instruction_counter_i++;
                        machinecode = Sformat(tokens[0], registers[tokens[1]], registers[b_token], dec2bin_12(a_token, 12));
                        outfile << "0x" << hex << uppercase << codeaddress << " " << machinecode << endl;
                        codeaddress += 4;
                    }
                    else if (inst == "SB")
                    {
                        if (!isNumber(tokens[3]))
                        {
                            long long label_ln = 0;
                            auto temp_iter = ud_labels.find(tokens[3]);
                            if (temp_iter != ud_labels.end())
                            {
                                label_ln = temp_iter->second;
                                if (label_ln == line_number)
                                {
                                    string hg = "0";
                                    machinecode = SBformat(tokens[0], registers[tokens[2]], registers[tokens[1]], dec2bin_20(hg, 13));
                                }
                                else if (label_ln < line_number)
                                {

                                    long long value_tds = line_number - label_ln - 1;
                                    value_tds *= -4;
                                    string hg = to_string(value_tds);
                                    // cout << hg << " hg" << endl;
                                    machinecode = SBformat(tokens[0], registers[tokens[2]], registers[tokens[1]], dec2bin_20(hg, 13));
                                }
                                else
                                {
                                    long long value_tds = label_ln - line_number;
                                    value_tds *= 4;
                                    string hg = to_string(value_tds);
                                    machinecode = SBformat(tokens[0], registers[tokens[2]], registers[tokens[1]], dec2bin_20(hg, 13));
                                }
                            }
                            else
                            {
                                // cout << "line " << line_number << endl;
                                outfile << "Error Label " << tokens[3] << " not Found on line :" << endl;
                            }
                        }
                        else
                        {
                            machinecode = SBformat(tokens[0], registers[tokens[2]], registers[tokens[1]], dec2bin_20(tokens[3], 12));
                        }
                        instruction_counter_i++;
                        outfile << "0x" << hex << uppercase << codeaddress << " " << machinecode << endl;
                        codeaddress += 4;
                    }
                    else if (inst == "U")
                    {
                        instruction_counter_i++;
                        machinecode = Uformat(tokens[0], dec2bin_20(tokens[2], 20), registers[tokens[1]]);
                        outfile << "0x" << hex << uppercase << codeaddress << " " << machinecode << endl;
                        codeaddress += 4;
                    }
                    else if (inst == "UJ")
                    {
                        // cout << tokens[0] << " " << tokens[1] << " " << tokens[2] << endl;
                        if (!isNumber(tokens[2]))
                        {
                            long long label_ln = 0;
                            auto temp_iter = ud_labels.find(tokens[2]);
                            if (temp_iter != ud_labels.end())
                            {
                                label_ln = temp_iter->second;
                                if (label_ln == line_number)
                                {
                                    string hg = "0";
                                    machinecode = UJformat(tokens[0], dec2bin_32(hg, 20), registers[tokens[1]]);
                                }
                                else if (label_ln < line_number)
                                {

                                    long long value_tds = line_number - label_ln - 1;
                                    value_tds *= -4;
                                    string hg = to_string(value_tds);
                                    // cout << hg << " hg" << endl;
                                    machinecode = UJformat(tokens[0], dec2bin_32(hg, 20), registers[tokens[1]]);
                                }
                                else
                                {
                                    long long value_tds = label_ln - line_number;
                                    value_tds *= 4;
                                    string hg = to_string(value_tds);
                                    machinecode = UJformat(tokens[0], dec2bin_32(hg, 20), registers[tokens[1]]);
                                }
                            }
                            else
                            {
                                outfile << "Error Label " << tokens[2] << " not Found on line :" << endl;
                            }
                        }
                        else
                        {

                            machinecode = UJformat(tokens[0], dec2bin_32(tokens[2], 20), registers[tokens[1]]);
                        }
                        instruction_counter_i++;
                        outfile << "0x" << hex << uppercase << codeaddress << " " << machinecode << endl;
                        codeaddress += 4;
                    }

                    // Decode the instructions
                }
            }

            outfile << endl;
            outfile << "Section ended ------" << endl;
        }
    }
}

void assemble_loader(string inputf, string outputf) // Function to take input and write into the output file
{
    long long DK_YT_count = 0;
    //Why DK_YT , Dk Means Dhakshin Kotha and Yt = Yeswanth Teja dude
    ifstream infile(inputf);
    ofstream outfile(outputf);

    if (!infile.is_open() || !outfile.is_open())
    {
        cout << "Error opening files" << endl;
        return;
    }
    string line;

    while (getline(infile, line))
    {
        line = regex_replace(line, regex("^\\s+|\\s+$"), ""); // Removing spaces leading or trailing
        line = regex_replace(line, regex(","), " ");          // Removing commas

        size_t pos_tv = line.find('#');
        if (pos_tv != string::npos)
        {
            line = line.substr(0, pos_tv);
        }

        if (line.empty())
        {
            continue;
        }
        line_number2++;

        if (line[0] == '.')
        {
            istringstream iss(line);
            string token;
            iss >> token;
            if (token == ".text")
            {

                while (getline(infile, line))
                {

                    line = regex_replace(line, regex("^\\s+|\\s+$"), ""); // Removing spaces leading or trailing
                    line = regex_replace(line, regex(","), " ");          // Removing commas

                    size_t pos_tv = line.find('#');
                    if (pos_tv != string::npos)
                    {
                        line = line.substr(0, pos_tv);
                    }

                    if (line.empty())
                    {
                        continue;
                    }
                    line_number2++;

                    // Handling the labels
                    size_t colonPos = line.find(':');

                    if (colonPos != string::npos)
                    {

                        string token_tmp = line.substr(0, colonPos); // Extract substring up to colon
                        line = line.substr(colonPos + 1);
                        ud_labels[token_tmp] = line_number2;
                        label_ins_num[token_tmp] = DK_YT_count;
                    }

                    if (line.empty())
                    {
                        continue;
                    }

                    istringstream iss(line);
                    vector<string> tokens;
                    for (string token; iss >> token;)
                    {
                        tokens.push_back(token);
                    }

                    if (tokens[0] == ".data")
                    {
                        // Implement for .data
                        token = ".data";
                        break;
                    }

                    string inst = ins_type[tokens[0]];
                    string machinecode;
                    if (inst == "R")
                    {
                        machinecode = Rformat(tokens[0], registers[tokens[3]], registers[tokens[2]], registers[tokens[1]]);
                        DK_YT_count++;
                        outfile << "0x" << hex << uppercase << codeaddress << " " << machinecode << endl;
                        codeaddress += 4;
                    }
                    else if (inst == "I")
                    {

                        cout << tokens[0] << " " << tokens[1] << " " << tokens[2] << " " << tokens[3] << endl;

                        size_t colonPos = line.find('(');
                        // cout << "Yeswanth" << endl;
                        if (colonPos == string::npos)
                        {
                            // cout << "DK_YT" << endl;
                            // cout << tokens[0] << " " << tokens[1] << " " << tokens[2] << endl;
                            if ((isNumber(tokens[3]) && (tokens[0] == "jalr")))
                            {
                                machinecode = Iformat(tokens[0], dec2bin_12(tokens[3], 12), registers[tokens[2]], registers[tokens[1]]);
                            }
                            else if (tokens[0] == "jalr")
                            {
                                long long label_ln = 0;
                                auto temp_iter = ud_labels.find(tokens[3]);
                                if (temp_iter != ud_labels.end())
                                {
                                    string label_upto = temp_iter->first;
                                    long long insyt = label_ins_num[label_upto];
                                    insyt = insyt * 4;
                                    string hg = to_string(insyt);
                                    machinecode = Iformat(tokens[0], dec2bin_12(hg, 12), registers[tokens[2]], registers[tokens[1]]);
                                    // if (label_ln == line_number)
                                    // {
                                    //     string hg = "0";
                                    //     machinecode = Iformat(tokens[0], dec2bin_12(hg, 12), registers[tokens[2]], registers[tokens[1]]);
                                    // }
                                    // else if (label_ln < line_number)
                                    // {

                                    //     long long value_tds = line_number - label_ln - 1;
                                    //     value_tds *= -4;
                                    //     string hg = to_string(value_tds);
                                    //     cout << hg << " hg" << endl;
                                    //     machinecode = Iformat(tokens[0], dec2bin_12(hg, 12), registers[tokens[2]], registers[tokens[1]]);
                                    // }
                                    // else
                                    // {

                                    //     long long value_tds = label_ln - line_number;

                                    //     value_tds *= 4;
                                    //     outfile<<value_tds<<endl;
                                    //     string hg = to_string(value_tds);
                                    //     machinecode = Iformat(tokens[0], dec2bin_12(hg, 12), registers[tokens[2]], registers[tokens[1]]);
                                    // }
                                }
                                else
                                {
                                    // cout << "line " << line_number << endl;
                                    outfile << "Error Label " << tokens[3] << " not Found on line :" << endl;
                                }
                            }
                            else if (tokens[0] != "jalr")
                            {
                                if ((tokens[0] == "lw") || (tokens[0] == "lb") || (tokens[0] == "lh") || (tokens[0] == "ld"))
                                {
                                    machinecode = Iformat(tokens[0], dec2bin_12(tokens[2], 12), registers[tokens[3]], registers[tokens[1]]);
                                }
                                else
                                {
                                    machinecode = Iformat(tokens[0], dec2bin_12(tokens[3], 12), registers[tokens[2]], registers[tokens[1]]);
                                    // cout << machinecode << endl;
                                }
                            }
                            else
                            {
                                machinecode = Iformat(tokens[0], dec2bin_12(tokens[3], 12), registers[tokens[2]], registers[tokens[1]]);
                                // cout << machinecode << endl;
                            }
                        }
                        else
                        {

                            string a_token = "";
                            string b_token = "";
                            string c_token;
                            string d_token;

                            string concatenated;

                            for (int index = 2; index < tokens.size(); index++)
                            {
                                concatenated += tokens[index];
                            }
                            concatenated.erase(std::remove(concatenated.begin(), concatenated.end(), ' '), concatenated.end());
                            concatenated.erase(std::remove(concatenated.begin(), concatenated.end(), '{'), concatenated.end());
                            concatenated.erase(std::remove(concatenated.begin(), concatenated.end(), '}'), concatenated.end());
                            int index = 0;
                            for (index = 0; index < concatenated.size(); index++)
                            {
                                if (concatenated[index] == '(')
                                {
                                    break;
                                }
                                a_token += concatenated[index];
                            }
                            index++;
                            for (; index < concatenated.size(); index++)
                            {
                                if (concatenated[index] == ')')
                                {
                                    break;
                                }
                                b_token += concatenated[index];
                            }

                            if ((tokens[0] == "lw") || (tokens[0] == "lb") || (tokens[0] == "lh") || (tokens[0] == "ld"))
                            {
                                machinecode = Iformat(tokens[0], dec2bin_12(a_token, 12), registers[b_token], registers[tokens[1]]);
                            }
                            else
                            {
                                machinecode = Iformat(tokens[0], dec2bin_12(tokens[3], 12), registers[tokens[2]], registers[tokens[1]]);
                                // cout << machinecode << endl;
                            }
                        }
                        // instruction_counter_i++;
                        DK_YT_count++;
                        outfile << "0x" << hex << uppercase << codeaddress << " " << machinecode << endl;
                        codeaddress += 4;
                    }
                    else if (inst == "S")
                    {
                        string a_token = "";
                        string b_token = "";
                        string c_token;
                        string d_token;

                        string concatenated;

                        for (int index = 2; index < tokens.size(); index++)
                        {
                            concatenated += tokens[index];
                        }
                        concatenated.erase(std::remove(concatenated.begin(), concatenated.end(), ' '), concatenated.end());
                        concatenated.erase(std::remove(concatenated.begin(), concatenated.end(), '{'), concatenated.end());
                        concatenated.erase(std::remove(concatenated.begin(), concatenated.end(), '}'), concatenated.end());
                        int index = 0;
                        for (index = 0; index < concatenated.size(); index++)
                        {
                            if (concatenated[index] == '(')
                            {
                                break;
                            }
                            a_token += concatenated[index];
                        }
                        index++;
                        for (; index < concatenated.size(); index++)
                        {
                            if (concatenated[index] == ')')
                            {
                                break;
                            }
                            b_token += concatenated[index];
                        }
                        DK_YT_count++;
                        machinecode = Sformat(tokens[0], registers[tokens[1]], registers[b_token], dec2bin_12(a_token, 12));
                        outfile << "0x" << hex << uppercase << codeaddress << " " << machinecode << endl;
                        codeaddress += 4;
                    }
                    else if (inst == "SB")
                    {
                        if (!isNumber(tokens[3]))
                        {
                            long long label_ln = 0;
                            auto temp_iter = ud_labels.find(tokens[3]);
                            if (temp_iter != ud_labels.end())
                            {
                                label_ln = temp_iter->second;
                                if (label_ln == line_number2)
                                {
                                    string hg = "0";
                                    machinecode = SBformat(tokens[0], registers[tokens[2]], registers[tokens[1]], dec2bin_20(hg, 13));
                                }
                                else if (label_ln < line_number2)
                                {

                                    long long value_tds = line_number2 - label_ln - 1;
                                    value_tds *= -4;
                                    string hg = to_string(value_tds);
                                    // cout << hg << " hg" << endl;
                                    machinecode = SBformat(tokens[0], registers[tokens[2]], registers[tokens[1]], dec2bin_20(hg, 13));
                                }
                                else
                                {
                                    long long value_tds = label_ln - line_number2;
                                    value_tds *= 4;
                                    string hg = to_string(value_tds);
                                    machinecode = SBformat(tokens[0], registers[tokens[2]], registers[tokens[1]], dec2bin_20(hg, 13));
                                }
                            }
                            else
                            {

                                // cout << "line " << line_number2 << endl;
                                outfile << "Error Label " << tokens[3] << " not Found on line :" << endl;
                            }
                        }
                        else
                        {
                            machinecode = SBformat(tokens[0], registers[tokens[2]], registers[tokens[1]], dec2bin_20(tokens[3], 12));
                        }
                        DK_YT_count++;
                        outfile << "0x" << hex << uppercase << codeaddress << " " << machinecode << endl;
                        codeaddress += 4;
                    }
                    else if (inst == "U")
                    {
                        DK_YT_count++;
                        machinecode = Uformat(tokens[0], dec2bin_20(tokens[2], 20), registers[tokens[1]]);
                        outfile << "0x" << hex << uppercase << codeaddress << " " << machinecode << endl;
                        codeaddress += 4;
                    }
                    else if (inst == "UJ")
                    {
                        if (!isNumber(tokens[2]))
                        {
                            long long label_ln = 0;
                            auto temp_iter = ud_labels.find(tokens[2]);
                            if (temp_iter != ud_labels.end())
                            {
                                label_ln = temp_iter->second;
                                if (label_ln == line_number2)
                                {
                                    string hg = "0";
                                    machinecode = UJformat(tokens[0], dec2bin_32(hg, 20), registers[tokens[1]]);
                                }
                                else if (label_ln < line_number2)
                                {

                                    long long value_tds = line_number2 - label_ln - 1;
                                    value_tds *= -4;
                                    string hg = to_string(value_tds);
                                    // cout << hg << " hg" << endl;
                                    machinecode = UJformat(tokens[0], dec2bin_32(hg, 20), registers[tokens[1]]);
                                }
                                else
                                {
                                    long long value_tds = label_ln - line_number2;
                                    value_tds *= 4;
                                    string hg = to_string(value_tds);
                                    machinecode = UJformat(tokens[0], dec2bin_32(hg, 20), registers[tokens[1]]);
                                }
                            }
                            else
                            {
                                outfile << "Error Label " << tokens[2] << " not Found on line :" << endl;
                            }
                        }
                        else
                        {
                            // cout << tokens[0] << " " << tokens[1] << " " << tokens[2] << endl;
                            machinecode = UJformat(tokens[0], dec2bin_32(tokens[2], 20), registers[tokens[1]]);
                        }
                        DK_YT_count++;
                        outfile << "0x" << hex << uppercase << codeaddress << " " << machinecode << endl;
                        codeaddress += 4;
                    }
                    else
                    {
                        break;
                    }
                }
                // Decode the instructions
            }
            if (token == ".data") // Writing to the output file in big endian format
            {
                outfile << endl;
                outfile << "  Address "
                        << " "
                        << "+0"
                        << " "
                        << "+1"
                        << " "
                        << "+2"
                        << " "
                        << "+3" << endl;
                int count_of_bytes = 0;
                int data_address_temporary = dataaddress;
                outfile << "0x" << hex << uppercase << data_address_temporary << " ";
                while (getline(infile, line))
                {
                    line = regex_replace(line, regex("^\\s+|\\s+$"), ""); // Removing spaces leading or trailing
                    line = regex_replace(line, regex(","), " ");          // Removing commas

                    size_t pos_tv = line.find('#');
                    if (pos_tv != string::npos)
                    {
                        line = line.substr(0, pos_tv);
                    }

                    if (line.empty())
                    {
                        continue;
                    }
                    line_number2++;

                    // Handling the labels
                    size_t colonPos = line.find(':');

                    if (colonPos != string::npos)
                    {
                        string token_tmp = line.substr(0, colonPos); // Extract substring up to colon
                        line = line.substr(colonPos + 1);
                        ud_labels[token_tmp] = line_number2;
                    }

                    istringstream iss(line);
                    vector<string> data_tokens;
                    string token_temp;
                    for (string token; iss >> token_temp;)
                    {
                        data_tokens.push_back(token_temp);
                    }

                    if (data_tokens[0] == ".text")
                    {
                        token = ".text";
                        outfile << endl;
                        outfile << endl;
                        break;
                    }

                    if (data_tokens[0] == ".byte")
                    {
                        int size_dt = data_tokens.size();
                        for (int i = 1; i < size_dt; i++)
                        {
                            string data_token_temporary = data_tokens[i];
                            int length_dtt = data_token_temporary.size();
                            string binary_data_token_temporary = dec2bin_8(data_token_temporary, length_dtt);
                            string binary_data_token_temporary2 = bintohex(binary_data_token_temporary);
                            outfile << binary_data_token_temporary2.substr(binary_data_token_temporary2.size() - 2) << " ";
                            count_of_bytes += 1;
                            if (count_of_bytes == 4)
                            {
                                count_of_bytes = 0;
                                data_address_temporary += 4;
                                outfile << endl;
                                outfile << "0x" << hex << uppercase << data_address_temporary << " ";
                            }
                        }
                    }
                    else if (data_tokens[0] == ".half")
                    {
                        int size_dt = data_tokens.size();
                        vector<string> output_memory;
                        for (int i = 1; i < size_dt; i++)
                        {
                            string data_token_temporary = data_tokens[i];
                            int length_dtt = data_token_temporary.size();
                            string binary_data_token_temporary = dec2bin_16(data_token_temporary, length_dtt);
                            string binary_data_token_temporary2 = bintohex(binary_data_token_temporary);
                            int it = 1;
                            while (it < 3)
                            {
                                output_memory.push_back(binary_data_token_temporary2.substr(binary_data_token_temporary2.size() - 2 * it, 2));
                                it++;
                            }
                        }
                        int size_om = output_memory.size();
                        for (int i = 0; i < size_om; i++)
                        {
                            outfile << output_memory[i] << " ";
                            count_of_bytes++;
                            if (count_of_bytes == 4)
                            {
                                count_of_bytes = 0;
                                data_address_temporary += 4;
                                outfile << endl;
                                outfile << "0x" << hex << uppercase << data_address_temporary << " ";
                            }
                        }
                    }
                    else if (data_tokens[0] == ".word")
                    {
                        int size_dt = data_tokens.size();
                        vector<string> output_memory;
                        for (int i = 1; i < size_dt; i++)
                        {
                            string data_token_temporary = data_tokens[i];
                            int length_dtt = data_token_temporary.size();
                            string binary_data_token_temporary = dec2bin_32(data_token_temporary, length_dtt);
                            string binary_data_token_temporary2 = bintohex(binary_data_token_temporary);
                            int it = 1;
                            while (it < 5)
                            {
                                output_memory.push_back(binary_data_token_temporary2.substr(binary_data_token_temporary2.size() - 2 * it, 2));
                                it++;
                            }
                        }
                        int size_om = output_memory.size();
                        for (int i = 0; i < size_om; i++)
                        {
                            outfile << output_memory[i] << " ";
                            count_of_bytes++;
                            if (count_of_bytes == 4)
                            {
                                count_of_bytes = 0;
                                data_address_temporary += 4;
                                outfile << endl;
                                outfile << "0x" << hex << uppercase << data_address_temporary << " ";
                            }
                        }
                    }
                    else if (data_tokens[0] == ".dword")
                    {
                        int size_dt = data_tokens.size();
                        vector<string> output_memory;
                        for (int i = 1; i < size_dt; i++)
                        {
                            string data_token_temporary = data_tokens[i];
                            int length_dtt = data_token_temporary.size();
                            string binary_data_token_temporary = dec2bin_64(data_token_temporary, length_dtt);
                            string binary_data_token_temporary2 = bintohex(binary_data_token_temporary);
                            int it = 1;
                            while (it < 9)
                            {
                                output_memory.push_back(binary_data_token_temporary2.substr(binary_data_token_temporary2.size() - 2 * it, 2));
                                it++;
                            }
                        }
                        int size_om = output_memory.size();
                        for (int i = 0; i < size_om; i++)
                        {
                            outfile << output_memory[i] << " ";
                            count_of_bytes++;
                            if (count_of_bytes == 4)
                            {
                                count_of_bytes = 0;
                                data_address_temporary += 4;
                                outfile << endl;
                                outfile << "0x" << hex << uppercase << data_address_temporary << " ";
                            }
                        }
                    }
                    else if (data_tokens[0] == ".asciiz")
                    {
                        int size_dt = data_tokens.size();
                        for (int i = 1; i < size_dt; i++)
                        {
                            string temporary_string_asciiz = data_tokens[i];
                            temporary_string_asciiz.erase(remove(temporary_string_asciiz.begin(), temporary_string_asciiz.end(), '"'), temporary_string_asciiz.end());
                            int size_tas = temporary_string_asciiz.size();
                            // cout << temporary_string_asciiz << endl;
                            for (int j = 0; j < size_tas; j++)
                            {
                                count_of_bytes++;
                                char ch = temporary_string_asciiz[j];
                                int value_ch = ch;
                                outfile << hex << uppercase << setw(2) << setfill('0') << value_ch << " ";
                                if (count_of_bytes == 4)
                                {
                                    count_of_bytes = 0;
                                    data_address_temporary += 4;
                                    outfile << endl;
                                    outfile << "0x" << hex << uppercase << data_address_temporary << " ";
                                }
                            }
                            int filler_value = 0;
                            outfile << hex << uppercase << setw(2) << setfill('0') << filler_value << " ";
                            count_of_bytes++;
                            if (count_of_bytes == 4)
                            {
                                count_of_bytes = 0;
                                data_address_temporary += 4;
                                outfile << endl;
                                outfile << "0x" << hex << uppercase << data_address_temporary << " ";
                            }
                        }
                    }
                }
            }
            if (token == ".text")
            {
                long long y_ins_num = 0;
                while (getline(infile, line))
                {

                    line = regex_replace(line, regex("^\\s+|\\s+$"), ""); // Removing spaces leading or trailing
                    line = regex_replace(line, regex(","), " ");          // Removing commas

                    size_t pos_tv = line.find('#');
                    if (pos_tv != string::npos)
                    {
                        line = line.substr(0, pos_tv);
                    }

                    if (line.empty())
                    {
                        continue;
                    }

                    line_number2++;

                    // Handling the labels
                    size_t colonPos = line.find(':');

                    if (colonPos != string::npos)
                    {

                        string token_tmp = line.substr(0, colonPos); // Extract substring up to colon
                        line = line.substr(colonPos + 1);
                        ud_labels[token_tmp] = line_number2;
                        label_ins_num[token_tmp] = DK_YT_count;
                    }

                    if (line.empty())
                    {
                        continue;
                    }

                    istringstream iss(line);
                    vector<string> tokens;
                    for (string token; iss >> token;)
                    {
                        tokens.push_back(token);
                    }

                    if (tokens[0] == ".data")
                    {
                        // Implement for .data
                        token = ".data";
                        break;
                    }

                    string inst = ins_type[tokens[0]];
                    string machinecode;
                    if (inst == "R")
                    {
                        DK_YT_count++;
                        machinecode = Rformat(tokens[0], registers[tokens[3]], registers[tokens[2]], registers[tokens[1]]);
                        outfile << "0x" << hex << uppercase << codeaddress << " " << machinecode << endl;
                        codeaddress += 4;
                    }
                    else if (inst == "I")
                    {
                        // cout << tokens[0] << " " << tokens[1] << " " << tokens[2] << " " << tokens[3] << endl;

                        size_t colonPos = line.find('(');

                        if (colonPos == string::npos)
                        {
                            if ((isNumber(tokens[3]) && (tokens[0] == "jalr")))
                            {
                                machinecode = Iformat(tokens[0], dec2bin_12(tokens[3], 12), registers[tokens[2]], registers[tokens[1]]);
                            }
                            else if (tokens[0] == "jalr")
                            {
                                long long label_ln = 0;
                                auto temp_iter = ud_labels.find(tokens[3]);
                                if (temp_iter != ud_labels.end())
                                {
                                    label_ln = temp_iter->second;

                                    // if (label_ln == line_number2)
                                    // {
                                    //     string hg = "0";
                                    //     machinecode = Iformat(tokens[0], dec2bin_12(hg, 12), registers[tokens[2]], registers[tokens[1]]);
                                    // }
                                    // else if (label_ln < line_number2)
                                    // {

                                    //     long long value_tds = line_number2 - label_ln - 1;
                                    //     value_tds *= -4;
                                    //     string hg = to_string(value_tds);
                                    //     cout << hg << " hg" << endl;
                                    //     machinecode = Iformat(tokens[0], dec2bin_12(hg, 12), registers[tokens[2]], registers[tokens[1]]);
                                    // }
                                    // else
                                    // {

                                    //     long long value_tds = label_ln - line_number2;

                                    //     value_tds *= 4;
                                    //     string hg = to_string(value_tds);
                                    //     machinecode = Iformat(tokens[0], dec2bin_12(hg, 12), registers[tokens[2]], registers[tokens[1]]);
                                    // }
                                }
                                else
                                {
                                    // cout << "line " << line_number2 << endl;
                                    outfile << "Error Label " << tokens[3] << " not Found on line :" << endl;
                                }
                            }
                            else if (tokens[0] != "jalr")
                            {
                                if ((tokens[0] == "lw") || (tokens[0] == "lb") || (tokens[0] == "lh") || (tokens[0] == "ld"))
                                {
                                    machinecode = Iformat(tokens[0], dec2bin_12(tokens[2], 12), registers[tokens[3]], registers[tokens[1]]);
                                }
                                else
                                {
                                    machinecode = Iformat(tokens[0], dec2bin_12(tokens[3], 12), registers[tokens[2]], registers[tokens[1]]);
                                    // cout << machinecode << endl;
                                }
                            }
                            else
                            {
                                machinecode = Iformat(tokens[0], dec2bin_12(tokens[3], 12), registers[tokens[2]], registers[tokens[1]]);
                                // cout << machinecode << endl;
                            }
                        }
                        else
                        {

                            string a_token = "";
                            string b_token = "";
                            string c_token;
                            string d_token;

                            string concatenated;

                            for (int index = 2; index < tokens.size(); index++)
                            {
                                concatenated += tokens[index];
                            }
                            concatenated.erase(std::remove(concatenated.begin(), concatenated.end(), ' '), concatenated.end());
                            concatenated.erase(std::remove(concatenated.begin(), concatenated.end(), '{'), concatenated.end());
                            concatenated.erase(std::remove(concatenated.begin(), concatenated.end(), '}'), concatenated.end());
                            int index = 0;
                            for (index = 0; index < concatenated.size(); index++)
                            {
                                if (concatenated[index] == '(')
                                {
                                    break;
                                }
                                a_token += concatenated[index];
                            }
                            index++;
                            for (; index < concatenated.size(); index++)
                            {
                                if (concatenated[index] == ')')
                                {
                                    break;
                                }
                                b_token += concatenated[index];
                            }

                            if ((tokens[0] == "lw") || (tokens[0] == "lb") || (tokens[0] == "lh") || (tokens[0] == "ld"))
                            {
                                machinecode = Iformat(tokens[0], dec2bin_12(a_token, 12), registers[b_token], registers[tokens[1]]);
                            }
                            else
                            {
                                machinecode = Iformat(tokens[0], dec2bin_12(tokens[3], 12), registers[tokens[2]], registers[tokens[1]]);
                                // cout << machinecode << endl;
                            }
                        }
                        DK_YT_count++;
                        outfile << "0x" << hex << uppercase << codeaddress << " " << machinecode << endl;
                        codeaddress += 4;
                    }
                    else if (inst == "S")
                    {
                        string a_token = "";
                        string b_token = "";
                        string c_token;
                        string d_token;

                        string concatenated;

                        for (int index = 2; index < tokens.size(); index++)
                        {
                            concatenated += tokens[index];
                        }
                        concatenated.erase(std::remove(concatenated.begin(), concatenated.end(), ' '), concatenated.end());
                        concatenated.erase(std::remove(concatenated.begin(), concatenated.end(), '{'), concatenated.end());
                        concatenated.erase(std::remove(concatenated.begin(), concatenated.end(), '}'), concatenated.end());
                        int index = 0;
                        for (index = 0; index < concatenated.size(); index++)
                        {
                            if (concatenated[index] == '(')
                            {
                                break;
                            }
                            a_token += concatenated[index];
                        }
                        index++;
                        for (; index < concatenated.size(); index++)
                        {
                            if (concatenated[index] == ')')
                            {
                                break;
                            }
                            b_token += concatenated[index];
                        }
                        DK_YT_count++;
                        machinecode = Sformat(tokens[0], registers[tokens[1]], registers[b_token], dec2bin_12(a_token, 12));
                        outfile << "0x" << hex << uppercase << codeaddress << " " << machinecode << endl;
                        codeaddress += 4;
                    }
                    else if (inst == "SB")
                    {
                        if (!isNumber(tokens[3]))
                        {
                            long long label_ln = 0;
                            auto temp_iter = ud_labels.find(tokens[3]);
                            if (temp_iter != ud_labels.end())
                            {
                                label_ln = temp_iter->second;
                                if (label_ln == line_number2)
                                {
                                    string hg = "0";
                                    machinecode = SBformat(tokens[0], registers[tokens[2]], registers[tokens[1]], dec2bin_20(hg, 13));
                                }
                                else if (label_ln < line_number2)
                                {

                                    long long value_tds = line_number2 - label_ln - 1;
                                    value_tds *= -4;
                                    string hg = to_string(value_tds);
                                    // cout << hg << " hg" << endl;
                                    machinecode = SBformat(tokens[0], registers[tokens[2]], registers[tokens[1]], dec2bin_20(hg, 13));
                                }
                                else
                                {
                                    long long value_tds = label_ln - line_number2;
                                    value_tds *= 4;
                                    string hg = to_string(value_tds);
                                    machinecode = SBformat(tokens[0], registers[tokens[2]], registers[tokens[1]], dec2bin_20(hg, 13));
                                }
                            }
                            else
                            {
                                // cout << "line " << line_number2 << endl;
                                outfile << "Error Label " << tokens[3] << " not Found on line :" << endl;
                            }
                        }
                        else
                        {
                            machinecode = SBformat(tokens[0], registers[tokens[2]], registers[tokens[1]], dec2bin_20(tokens[3], 12));
                        }
                        DK_YT_count++;
                        outfile << "0x" << hex << uppercase << codeaddress << " " << machinecode << endl;
                        codeaddress += 4;
                    }
                    else if (inst == "U")
                    {
                        DK_YT_count++;
                        machinecode = Uformat(tokens[0], dec2bin_20(tokens[2], 20), registers[tokens[1]]);
                        outfile << "0x" << hex << uppercase << codeaddress << " " << machinecode << endl;
                        codeaddress += 4;
                    }
                    else if (inst == "UJ")
                    {
                        // cout << tokens[0] << " " << tokens[1] << " " << tokens[2] << endl;
                        if (!isNumber(tokens[2]))
                        {
                            long long label_ln = 0;
                            auto temp_iter = ud_labels.find(tokens[2]);
                            if (temp_iter != ud_labels.end())
                            {
                                label_ln = temp_iter->second;
                                if (label_ln == line_number2)
                                {
                                    string hg = "0";
                                    machinecode = UJformat(tokens[0], dec2bin_32(hg, 20), registers[tokens[1]]);
                                }
                                else if (label_ln < line_number2)
                                {

                                    long long value_tds = line_number2 - label_ln - 1;
                                    value_tds *= -4;
                                    string hg = to_string(value_tds);
                                    // cout << hg << " hg" << endl;
                                    machinecode = UJformat(tokens[0], dec2bin_32(hg, 20), registers[tokens[1]]);
                                }
                                else
                                {
                                    long long value_tds = label_ln - line_number2;
                                    value_tds *= 4;
                                    string hg = to_string(value_tds);
                                    machinecode = UJformat(tokens[0], dec2bin_32(hg, 20), registers[tokens[1]]);
                                }
                            }
                            else
                            {
                                outfile << "Error Label " << tokens[2] << " not Found on line :" << endl;
                            }
                        }
                        else
                        {

                            machinecode = UJformat(tokens[0], dec2bin_32(tokens[2], 20), registers[tokens[1]]);
                        }
                        DK_YT_count++;
                        outfile << "0x" << hex << uppercase << codeaddress << " " << machinecode << endl;
                        codeaddress += 4;
                    }

                    // Decode the instructions
                }
            }
        }
    }
}

int main()
{
    assemble_loader("input.asm", "output.mc");
    assemble("input.asm", "output.mc");

    for (auto it = label_ins_num.begin(); it != label_ins_num.end(); it++)
    {
        // cout << it->first << "  " << it->second << endl;
    }
    return 0;
}
