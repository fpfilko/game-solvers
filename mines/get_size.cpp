#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <queue>
#include <vector>

using namespace cv;
using namespace std;


Vec3b empty(182,189,186);
Vec3b hover(198,206,202);
Vec3b full(220,222,222);
Vec3b black(0,0,0);


vector<int> get_vec(Mat_<Vec3b> line) {
    bool sep = true;
    vector<int> v;
    Mat_<Vec3b>::iterator it=line.begin(), end = line.end();
    for(int i=0; it != end; it++, i++) {
        //if((*it) == hover || (*it) == full || (*it) == empty ) {
        if((*it)[0]<230 ) {
            if(sep) {
                v.push_back(i);
                sep = false;
            }
        }
        else {
            sep = true;
        }
    }
    return v;
}

vector<int> search(Mat_<Vec3b> &img, int rows, int cols, int x, int y, Vec3b c) {
    int lmaxx = x;
    int lmaxy = y;
    int lminx = x;
    int lminy = y;
    img(x,y) = black;
    queue<pair<int,int>> q;
    q.push(make_pair(x,y));
    int count = 1;
    while(!q.empty()) {
        x=q.front().first; y=q.front().second; q.pop();
        if(x>lmaxx) lmaxx=x;
        if(x<lminx) lminx=x;
        if(y>lmaxy) lmaxy=y;
        if(y<lminy) lminy=y;
        if(x>0 && img(x-1,y) == c) {
            q.push(make_pair(x-1,y));
            count++;
            img(x-1,y) = black;
        }
        if(y>0 && img(x,y-1) == c) {
            q.push(make_pair(x,y-1));
            count++;
            img(x,y-1) = black;
        }
        if(x<rows-1 && img(x+1,y) == c) {
            q.push(make_pair(x+1,y));
            count++;
            img(x+1,y) = black;
        }
        if(y<cols-1 && img(x,y+1) == c) {
            q.push(make_pair(x,y+1));
            count++;
            img(x,y+1) = black;
        }
    }
    return {count, lmaxx, lminx, lmaxy, lminy};
}

int main( int argc, char** argv )
{
    if( argc != 2)
    {
     cerr <<" Usage: display_image ImageToLoadAndDisplay" << endl;
     return -1;
    }

    Mat image;
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR);   // Read the file

    if(! image.data )                              // Check for invalid input
    {
        cerr <<  "Could not open or find the image" << std::endl ;
        return -1;
	
    }    
    
    Mat_<Vec3b> _I = image;
    
    vector<int> col = get_vec(_I.row(2));
    vector<int> row = get_vec(_I.col(2));
    
    cout << row.size() << " " << col.size() << endl;
/*
    for(auto c : row) cout << c << " ";
    cout << endl;
    for(auto c : col) cout << c << " ";
    cout << endl;
*/

   // v[0] = 182; v[1]= 189; v[2]=186;
    for( int i = 0; i < row.size(); ++i) {
        for( int j = 0; j < col.size(); ++j) {
            int x = row[i]+2;
            int y = col[j]+2;
            
            Vec3b act = _I(x,y);
            
/*            cout << x << " -- "  << y << endl;   
    image = _I;

    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window", image );                   // Show our image inside it.

    waitKey(0);                                          // Wait for a keystroke in the window  
    */
            if(act == black) {
                cout << -1 << " ";
                continue;
            }
            /* // debug
            if(i == 8 && j == 17) {
 //               cout << v[0] << " - " << v[1]-v[2] << " x " << v[3]-v[4] << " = " << (v[1]-v[2]-1) * (v[3]-v[4]-1) << endl;
                cout << "\n" << (int)act[0] << " " << (int) act[1] << " " << (int) act[2] << "\n";
                image = _I;

                namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
                imshow( "Display window", image );                   // Show our image inside it.

                waitKey(0);                                          // Wait for a keystroke in the window
            }
            */
            vector<int> v = search(_I, image.rows, image.cols, x, y, act);
            if(v[0] > (v[1]-v[2]-1) * (v[3]-v[4]-1)) {
                if(act[0] < 216) 
                    cout << " 0 ";
                else {
                    cout << " 9 ";
                }
            } else {
                if( act[0] < 216) 
                    cout << "10 ";
                else {
                    cout << "11 ";
                }
            }
        }
        cout << endl;
    }

//    image = _I;
//
//    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
//    imshow( "Display window", image );                   // Show our image inside it.
//
//    waitKey(0);                                          // Wait for a keystroke in the window
    return 0;
}
