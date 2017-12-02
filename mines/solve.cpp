#include<iostream>
#include<vector>
#include<sstream>
#include<algorithm>    
#include<ctime>        
#include<cstdlib> 
#include<unordered_set>
#include<set>
#include<cstdio>
#include<cstdlib>
#include<ctime>


using namespace std;

bool change;

set<pair<int, int>> get_around_set(vector<vector<int>> &v, int i, int j, int w) {
    set<pair<int,int>> c;
    int frx = max(i-1, 0);
    int fry = max(j-1, 0);
    int tox = min(i+1, (int)(v.size()-1));
    int toy = min(j+1, (int)(v[0].size()-1));
    for(int i = frx; i<=tox; i++) {
        for(int j = fry; j<=toy; j++) {
            if(v[i][j]==w)
                c.insert(make_pair(i,j));
        }
    }
    return c;
}

int get_around(vector<vector<int>> &v, int i, int j, int w) {
    int c=0;
    int frx = max(i-1, 0);
    int fry = max(j-1, 0);
    int tox = min(i+1, (int)(v.size()-1));
    int toy = min(j+1, (int)(v[0].size()-1));
    for(int i = frx; i<=tox; i++) {
        for(int j = fry; j<=toy; j++) {
            if(v[i][j]==w)
                ++c;
        }
    }
    return c;
}

void outputtt(vector<vector<int>> &v) {
    for(int i = 0; i<v.size(); i++) {
        for(int j = 0; j<v[i].size(); j++) {
            cout << v[i][j] << " ";
        }
        cout << "\n";
    }
}

void set_around(vector<vector<int>> &v, int i, int j, int w) {
    cerr << "filling (" << i << "," << j << ") with " << w << "\n";
    //outputtt(v);
    int frx = max(i-1,0);
    int fry = max(j-1,0);
    int tox = min(i+1, (int)(v.size()-1));
    int toy = min(j+1, (int)(v[0].size()-1));
    for(int i = frx; i<=tox; i++) {
        for(int j = fry; j<=toy; j++) {
            if(v[i][j]==0)
                v[i][j]=w;
        }
    }
}



void easy_mines(vector<vector<int>> &v) {
    for(int i =0; i<v.size(); i++) {
        for(int j=0; j<v[i].size(); j++) {
            if(v[i][j]>0 && v[i][j] < 9) {
                int unset = get_around(v, i, j, 0);
                if(unset) {
                    int mines = get_around(v, i, j, 10);
                    if(mines+unset == v[i][j]) {
                        set_around(v, i, j, 10);
                        change = true;
                    }
                    if(mines==v[i][j]) {
                        set_around(v, i, j, 9);
                        change = true;
                    }
                }
            }
        }
    }
}

int get_intersect(vector<vector<int>> &v, int x1, int y1, int x2, int y2) {
    if(v[x1][y1] < 1 || v[x1][y1]>8 || v[x2][y2] < 1 || v[x2][y2] > 8)
        return 0;
    set<pair<int,int>> s1 = get_around_set(v, x1, y1, 0),
                       s2 = get_around_set(v, x2, y2, 0);
    if(s1.size() == 0 || s2.size() == 0)
        return 0;
    bool b1 = true; bool b2 = true;
    for(auto p: s1) {
        if(s2.find(p) == s2.end())
            b1=false;
    }
    for(auto p: s2) {
        if(s1.find(p) == s1.end())
            b2=false;
    }
    if(b1 == b2)
        return 0;
    return s1.size() - s2.size();
}


int set_diff(vector<vector<int>> &v, int x1, int y1, int x2, int y2, int w) {
    cerr << "doing hard on (" << x1 << "," << y1 << ") (" << x2 << "," << y2 << ") to " << w << "\n";
    set<pair<int,int>> s1 = get_around_set(v, x1, y1, 0),
                       s2 = get_around_set(v, x2, y2, 0);
    for(auto p: s1) {
        if(s2.find(p) == s2.end()) {
            v[p.first][p.second] = w;
        }
    }
}

void harder_mines(vector<vector<int>> &v) {
    for(int i =0; i<v.size(); i++) {
        for(int j=0; j<v[i].size(); j++) {
            int frx = max(i-2,0);
            int fry = max(j-2,0);
            int tox = min(i+2, (int)(v.size()-1));
            int toy = min(j+2, (int)(v[0].size()-1));
            for(int k = frx; k<=tox; k++) {
                for(int l = fry; l<=toy; l++) {
                    if (change) 
                        return;
                    int c=get_intersect(v, i,j, k, l);
                    if(c) {
                        if(v[i][j]-get_around(v,i,j,10) ==v[k][l] - get_around(v,k,l,10) ) {
                            if(c > 0) {
                                set_diff(v, i, j, k, l, 9);
                            }
                            else {
                                set_diff(v, k, l, i, j, 9);
                            }
                        }
                        else if(v[i][j]-get_around(v,i,j,10)-v[k][l]+get_around(v,k,l,10) == c) {
                            if(c > 0) {
                                set_diff(v, i, j, k, l, 10);
                            }
                            else {
                                set_diff(v, k, l, i, j, 10);
                            }
                        }
                    }
                }
            }
        }
    }
}

int main() {
    change = true;
    int sx, sy, ox, oy;
    cin >> sy >> sx >> oy >> ox;
    int x,y;
    cin >> x >> y;
    vector<vector<int>> mask(x, vector<int>(y));
    for(int i=0; i<x; i++) {
        for(int j=0; j<y; j++) {
            cin >> mask[i][j];
          //  cout << mask[i][j] << " ";
        }
    }
    int a, b, va;
    while(cin >> b >> a >> va) {
        int i = (a*x)/sx, j = (b*y)/sy;
//        cout << i << " " << j << " should be " << v << endl;
        if(mask[i][j] == 11) {
            mask[i][j]=va;
        }
        else if(mask[i][j]!=10) {
            cerr << "problem with coords " << i << " " << j << " - want to place " << va << endl;
        } 
    }

    bool ok=false;
    for(int i = 0; i<mask.size(); i++) {
        for(int j = 0; j<mask[i].size(); j++) {
            if(mask[i][j]==11) {
                cerr << "problem with cords " << i << " " << j << " - not filled number" << endl;
            }
            if(mask[i][j]==0) {
                ok = true;
            }
            if(mask[i][j]==-1) {
                return 20;
            }
        }
    }
    if(!ok)
        return 21;
    vector<vector<int>> v = mask;
        
    while(change) {
        while(change) {
            change=false;
            easy_mines(v);
        } 
        harder_mines(v);
    }

//    for(auto x: v) {
//        for(auto y: x) {
//            cout << y << " ";
//        }
//        cout << "\n";
//    }
    
    string commands = "";
    
//cerr << ox << " " << oy << endl;
    for(int i =0 ; i<mask.size(); i++) {
        for(int j=0; j<mask[i].size(); j++){
            if(mask[i][j]==0 && v[i][j]>=9) {
                //cerr << i << " " << j << endl;
                int cx = (sx*(2*i+1))/2/x + ox;
                int cy = (sy*(2*j+1))/2/y + oy;
                stringstream ss;
                ss << cy << " " << cx;
                commands += "mousemove " + ss.str() + " click ";
                if(v[i][j] == 10) {
                    commands+="3 ";
                }
                else {
                    commands+="1 ";
                }
            }
        }
    }
    if(commands=="") {
        // random move
        srand(time(NULL));
        cerr << "doing random move\n";
        vector<pair<int, int>> vp;
        for(int i = 0; i<v.size(); i++) {
            for(int j = 0; j<v[i].size(); j++) {
                if(v[i][j]==0) {
                    vp.push_back(make_pair(i,j));
                }
            }
        }
        if(vp.size() == 0) {
            cerr << "all filled\n";
            return 1;
        }
        int r = rand() %vp.size();
        int cx = (sx*(2*vp[r].first+1))/2/x + ox;
        int cy = (sy*(2*vp[r].second+1))/2/y + oy;
        stringstream ss;
        ss << cy << " " << cx;
        commands += "mousemove " + ss.str() + " click 1";
    }
    cout << commands << endl;
}
