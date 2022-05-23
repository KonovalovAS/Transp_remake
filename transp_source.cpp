#include "transp_header.h"

Random_solution::Random_solution(double p){
    P = p;
}

mt19937 Random_solution::Mersenne = mt19937( static_cast<mt19937::result_type>(time(nullptr)) );
uniform_real_distribution<> Random_solution::rnd = uniform_real_distribution<>{0,1};
bool Random_solution::operator()(){
    double tmp = rnd(Mersenne);
    return tmp<P;
}

bool pt::operator==(const pt& right){
    return (this->id==right.id);
}

pt& pt::operator=(const pt& right){
    this->x = right.x;
    this->y = right.y;
    this->id = right.id;
    this->demand = right.demand;
    return *this;
}

double dist(const pt& p1, const pt& p2){
    return sqrt( pow(p1.x-p2.x,2)+pow(p1.y-p2.y,2) );
}

Problem::Problem(){}

Problem::Problem(vector<pt>& pts, int v, int c){
    source = *(pts.begin());
    points = vector<pt> ( pts.begin()+1, pts.end() );
    pt_Num = points.size();

    veh_Num = v;
    capacity = c;
}

void Problem::show(){
    cout << pt_Num << " " << veh_Num << " " << capacity << "\n";
    cout << source.id << ") " << source.x << " " << source.y << " " << source.demand << "\n";
    for(auto p: points)
        cout << "\t" << p.id << ") " << p.x << " " << p.y << " " << p.demand << "\n";
    cout << "\n";
}



Solution::Solution(){};

Solution::Solution(const Problem& P){
    pt_Num = P.pt_Num;
    veh_Num = P.veh_Num;
    capacity = P.capacity;
    points = P.points;
    source = P.source;

    order = vector<pt>(0);
    sol_cost = -1;
}

void Solution::show(){
    cout << pt_Num << " " << veh_Num << " " << capacity << "\n";
    cout << source.id << ") " << source.x << " " << source.y << " " << source.demand << "\n";
    for(auto p: points)
        cout << "\t" << p.id << ") " << p.x << " " << p.y << " " << p.demand << "\n";
    cout << "\n";
}

double Solution::Calculate(){

    /// (1) find the closest point to the current position
        // improvement: consider multiple options
    /// (2) go there, update the data
    /// (3) repeat 1-2, while there is still enough carriage in the vehicle
        // improvement: choose between going on further and starting another cycle

    int unused_Veh = veh_Num-1;

    int unvis_Num = pt_Num;
    vector<pt> pts = points;

    pt current = source;
    int carriage = capacity;

    Random_solution rs(0.7);

    while(unvis_Num>0){
        /*
        cout << "BEGIN\n";
        cout << "\tCurrent: " << current.id << "\n";
        cout << "\tCarriage: " << carriage << "\n";
        cout << "\tunvis_Num: " << unvis_Num << "\n";
        cout << "\tunused_Veh: " << unused_Veh << "\n";
        */

        /// sorting other points by distance to the current one
        auto comp = [&](const pt& pt1, const pt& pt2){
            return dist(pt1,current) < dist(pt2,current);
        };
        sort(pts.begin(), pts.end(), comp);

        /// seeking for the next point to head to:
        int next_index = 0;
        while(pts[next_index].demand >= carriage){
            if (next_index < unvis_Num)
                next_index++;
            else break;
        }

        //cout << "\t\tFound the next one!\n";
        //cout << "\t\t" << pts[next_index].id << " " << pts[next_index].demand << "\n";

        bool go = rs();
        go = go || (current==source);
        if(!go) cout << "HERE!\n";
        if( (next_index < unvis_Num) && (pts[next_index].demand <= carriage) && go ){
            /// (2) go there, update the data
            //cout << "\tUpdating stuff.\n\n";
            current = pts[next_index];
            carriage -= current.demand;
            pts.erase(pts.begin()+next_index,pts.begin()+next_index+1);
            unvis_Num -= 1;
        }
        else{
            //cout << "\tBack to the origin!\n\n";
            current = source;
            carriage = capacity;
            unused_Veh -= 1;
        }
        order.push_back(current);

    }

    if(unused_Veh<0){
        order.resize(0);
        return -1;
    }

    /// THE RESULT
    /*
    cout << "\n";
    for(auto p: order)
        cout << p.id << ") " << p.x << " " << p.y << " " << p.demand << "\n";
    cout << "\n";
    */

    sol_cost = dist(source,order[0]);
    for(int i=1; i<order.size(); i++){
        sol_cost += dist( order[i-1], order[i] );
    }
    sol_cost += dist( *(order.end()-1), source );

    //cout << "Cost: " << sol_cost;

    return sol_cost;
}





//
