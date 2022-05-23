#include "transp_header.h"
#include <fstream>

using namespace std;

Problem problem_reader(string fname){
    vector<pt> pt_data(0);
    int n,v,c;

    ifstream in(fname);

    in >> n >> v >> c;
    double x,y,demand;
    for(int i=0; i<n; i++){
        in >> demand >> x >> y;
        pt_data.push_back({i,x,y,demand});
    }
    Problem P(pt_data,v,c);
    in.close();
    return P;
}

int main()
{
    string fname;
    cin >> fname;

    auto P = problem_reader(fname);
    Solution S(P);

    auto res = S.Calculate();
    cout << res;
    /*
    /// Random_solution usage:
    int counter = 0;
    Random_solution RS(0.75);
    for(int i=0; i<100; i++)
        if(RS()){
            cout << counter << "\n";;
            counter++;
        }

    /// Another example^
    Random_solution RS(0.99);
    int i=0;
    while(RS()){
        cout << i << " ";
        i++;
    }
    */


    return 0;
}
