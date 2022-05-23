#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

#include <random>
#include <ctime>

using namespace std;

class Random_solution{
    public:
        Random_solution(double p = 0.5);
        bool operator()();

    private:
        double P;
        static mt19937 Mersenne;
        static uniform_real_distribution<> rnd;
};

struct pt{
    int id;
    double x,y;
    int demand;

    bool operator==(const pt& right);
    pt& operator=(const pt& right);
};

double dist(const pt& p1, const pt& p2);

class Problem{
    public:
        Problem();
        Problem(vector<pt>& pts, int v, int c);

        void show();

    //private:
        int pt_Num, veh_Num, capacity;
        pt source;
        vector<pt> points;

    //friend Solution;
};

class Solution{
    public:
        Solution();
        Solution(const Problem& P);
        void show();
        double sol_cost;

        double Calculate();

    private:
        int pt_Num, veh_Num, capacity;
        pt source;
        vector<pt> points;
        vector<pt> order;
};
