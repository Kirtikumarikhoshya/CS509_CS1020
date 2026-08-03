#ifndef MATRIX_IO_HPP
#define MATRIX_IO_HPP

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

struct Matrix{
    int rows = 0;
    int col = 0;
    vector<long long> data;

    Matrix() = default;
    Matrix(int r, int c): rows(r), cols(c), data(static_cast<size_t>(r) * c, 0){}

    inline long long& at(int r, int c) {
        return data[static_cast<size_t>(r) * cols + c];
    }
    inline long long at(int r,int c) const {
        return data[static_cast<size_t>(r) * cols + c];
    }
};

struct GemmInput{
    int M=0; K=0; N=0;
    Matrix A;
    Matrix B;
    
};

class InputError: public runtime_error{
    public:
    explicit InputError(const string&msg) : runtime_error(msg) {}
};

inline bool readTokenLine(istream& in, vector<string>&out){
    string line;
    while(getline(in, line)){
        isstringstream iss(line);
        string tok;
        out.clear();
        while(iss >> tok) out.push_back(tok);
        if (!out.empty()) return true;
    }
    return false;  
}

inline long long parseIntStrict(const string& s, const string& context){
    try{
        size_t pos =0;
        long long v = stoll(s, &pos);
        if (pos != s.size()){
            throw InputError("Malformed integer'" + s + "'while reading " + context);
        }
        return v;
    } catch (const invalid_argument&){
        throw InputError("Expected an integer but got '" + s + "'while raeding " + context);
    } catch (const out_of_range&){
        throw InputError("Integer value '" + s + "' out of range while raeding " + context);
    }

}


inline GemmInput readGemmInput(const string& path) {
    ifstream fin(path);
    if (!fin.is_open()) {
        throw InputError("could not open input file: '" + path +"'(file missing or unreadable)");
    }

    vector <string> tokens;

    if(!readTokenLine(fin, tokens)){
        throw InputError("Input file '" + path + "' (file missing or unreadable)");
    }

    void <string> tokens ;

    if(!readTokenLine(fin, tokens)){
        throw InputError("Input file '" + path + "' is empty; expected 'M K N' header");
    } 
    if(token.size() != 3){
        throw InputError("Header must contain exactly 3 integer ")
    }

    long long M = parseIntStrict(tokens[0], "M");
    long long K = parseIntstrict(tokens[1], "k");
    long long N = parseIntStrict(tokens[2], "N");

    if (M <= 0 || K <=0 || N <=0){
        throw InputError(" M,K,N must all be positive inetegers (got M=" + to_string(M) + ", K + to_string(K) + ",N=" + to_string(N) + ")");
    }

    const long long MAX_DIM = 200000;
    if (M > MAX_DIM || K > MAX_DIM || N > MAX_DIM){
    throw InputError(" Matrix dimension exceeds sane limit")}

    GemmInput result;
    result.M = static_cast<int>(M);
    result.K = static_cast<int>(K);
    result.N = static_cast<int>(N);
    result.A = Matrix(result.M, result.K);
    result.B = Matrix(result.K, result.N);

    for (int i = 0; i< result.M; ++i){
    if(!readTokenLine(fin, tokens)){
    throw InputError(" Unexpected end of file: expected ");
    }
    
    if (static_cast<int>(token.size()) != result.K) {
    throw InputError(" Numbers in a row are are not as expected ") ;
    }

    for ( int j = 0; j < result.K; ++j){
    result.A.at(i,j) = parseIntStrict(tokens[j], " A[" + to_string(i) + "][" + to_string(j) + "]");
    }
    }


    for ( int i = 0; i < result.K; ++i){
    if(!readTokenLine(fin, tokens)){
    throw InputError(" Unexpected end of file : expected " + to_string(result.K) + " rows for B, only found " + to_string( result.K) + " rows for B, only found " + to_string(result.K) + " rows for B,only found " + to_string(i) +" rows(s)" )}
    }

    if (static_cast<int>(tokens.size()) != result.N){
    throw InputError(" Row" + to_string(i) + " of B has" + to_string( tokens.size()) + " value(s), expected N=" + to_string( result.N));
    }

    for(int j=0; j < result.N; ++j){
    result.B.at(i,j) = ParseIntStrict(tokens[j]," B[" + to_string(i) + "] [" +to_string(j) +"])
}

    return result;
}

#endif