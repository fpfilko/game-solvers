#include<iostream>
#include<vector>
#include<algorithm>    
#include<ctime>        
#include<cstdlib> 
#include<set>

using namespace std;

void row(vector<int> &v, set<int> &s, int i) {
    int r = i / 9;
    for(int j = 0; j<9; j++) {
        if(v[r*9+j] !=0) {
            s.insert(v[r*9+j]);
        }
    }
}


void col(vector<int> &v, set<int> &s, int i) {
    int c = i % 9;
    for(int j = 0; j<9; j++) {
        if(v[j*9 + c] !=0) {
            s.insert(v[j*9+c]);
        }
    }
}

void sq(vector<int> &v, set<int> &s, int i) {
    int r = ((i / 9)/3)*3;
    int c = ((i % 9)/3)*3;
    
    for(int j = 0; j<3; j++) {
        for(int k = 0; k<3; k++) {
            if(v[(r+j)*9+c+k] !=0) {
                s.insert(v[(r+j)*9+c+k]);
            }
        }
    }
}

bool solve(vector<int> &v, int i) {
    if(i >= 81) {
        return true;
    }
    if(v[i] != 0) {
        return solve(v, i+1);
    }
    set<int> su;
    row(v, su, i);
    col(v, su, i);
    sq(v, su, i);
    vector<int> u;
    for(int j = 1; j<10; j++) {
        if(su.find(j) == su.end()) {
            u.push_back(j);
        }
    }
//    random_shuffle(u.begin(), u.end());
    for(int j = 0; j<u.size(); j++) {
        v[i] = u[j];
        bool r = solve(v, i+1);
        if(r) {
            return true;
        }
    }
    v[i] = 0;
    return false;
}

int main() {
    vector<int> v(81, 0);
    int sx, sy, x, y, z, a;
    cin >> sx >> sy >> z >> a;
    
    while(cin >> x >> y >> a) {
        x = x*9.0/(double)sx;
        y = y*9.0/(double)sy;
 //       cout << "[" << y << "," << x <<"] = " << a << "\n";
        v[y*9+x] = a;
    }

    for(int i = 0; i<9; i++) {
        for(int j = 0; j<9; j++) {
            cerr << v[9*i+j] << " ";
        }
        cerr << endl;
    } 

   // return 0;
    srand (unsigned(time(0)));
    solve(v, 0);
    cout << "xdotool key ";
    for(int i = 0; i<9; i++) {
        for(int j = 0; j<9; j++) {
            if (i % 2) {
                cout << v[i*9+8-j] << " ";
                if( j < 8) {
                    cout << " Left ";
                }
            }
            else {
                cout << v[i*9+j] << " ";
                if (j < 8)
                    cout << " Right ";
            }
        }
        cout << " Down ";
    }
}
