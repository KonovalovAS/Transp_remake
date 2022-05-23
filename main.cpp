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
    //cin >> fname;
    fname = "vrp_30_3_1";

    auto P = problem_reader(fname);
    Solution S(P);

    //double P1(0.4), P2(0.9);
    double P1(0.7), P2(0.98);

    string cmd = "h";

    while(cmd!="end"){
        cin >> P1 >> P2;

        double best = -1;
        int fails(0);

        for(int i=0; i<100; i++){
            auto res = S.Calculate(P1,P2);
            if(res>0){
                //cout << "RESULT: " << res << "\n";
                best = (best<0) ? res : min(best,res);
            }
            else{
                //cout << "FAILURE\n";
                fails++;
            }
        }
        cout << fails;
        cout << "\n" << best << "\n\n";
        cin >> cmd;
    }

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
    Random_solution rs = Random_solution();
    int i=0;
    while(rs(0.9999)){
        cout << i << " ";
        i++;
    }

    Random_solution rs = Random_solution();
    for(int i=0; i<1000; i++)
        if(rs(0.001))
            cout << 1 << "\n";
    cout << "end!";
    */

    return 0;
}
