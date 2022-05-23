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
    string fname = "vrp_5_4_1";
    auto P = problem_reader(fname);
    P.show();

    Solution S(P);
    S.show();

    S.Calculate();

    return 0;
}
