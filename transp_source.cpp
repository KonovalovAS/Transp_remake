#include "transp_header.h"

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

    while(unvis_Num>0){
        /*
        cout << "BEGIN\n";
        cout << "\tCurrent: " << current.id << "\n";
        cout << "\tCarriage: " << carriage << "\n";
        cout << "\tunvis_Num: " << unvis_Num << "\n";
        cout << "\tunused_Veh: " << unused_Veh << "\n";
        */

        /// (1) find the closest point to the current position
        int next_index = 0;

        auto comp = [&](const pt& pt1, const pt& pt2){
            return dist(pt1,current) < dist(pt2,current);
        };
        sort(pts.begin(), pts.end(), comp);

        cout << "\t\tFound the next one!\n";
        cout << "\t\t" << pts[next_index].id << " " << pts[next_index].demand << "\n";

        if( pts[next_index].demand <= carriage ){
            /// (2) go there, update the data
            cout << "\tUpdating stuff.\n\n";
            current = pts[next_index];
            carriage -= current.demand;
            pts.erase(pts.begin()+next_index,pts.begin()+next_index+1);
            unvis_Num -= 1;
        }
        else{
            cout << "\tBack to the origin!\n\n";
            current = source;
            carriage = capacity;
            unused_Veh -= 1;
        }
        order.push_back(current);

        /// (3) repeat 1-2, while there is still enough carriage in the vehicle
    }

    cout << "\n";
    for(auto p: order)
        cout << p.id << ") " << p.x << " " << p.y << " " << p.demand << "\n";
    cout << "\n";

    double cost = dist(source,order[0]);
    for(int i=1; i<order.size(); i++){
        cost += dist( order[i-1], order[i] );
    }
    cost += dist( *(order.end()-1), source );
    cout << "Cost: " << cost;
}





//
