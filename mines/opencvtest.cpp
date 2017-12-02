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
    
    int maxx=0;
    int maxy=0;
    int minx=image.rows;
    int miny=image.cols;
    Mat_<Vec3b> _I = image;
    Vec3b v(7,10,254);
   // v[0] = 182; v[1]= 189; v[2]=186;
    for( int i = 0; i < image.rows; ++i)
        for( int j = 0; j < image.cols; ++j ) {
            Vec3b act = _I(i,j);
            if (act == empty || act==hover || act == full) {
                vector<int> v = search(_I, image.rows, image.cols, i, j, act);
                if(v[0]>100) {
                    maxx = max(maxx, v[1]);
                    minx = min(minx, v[2]);
                    maxy = max(maxy, v[3]);
                    miny = min(miny, v[4]);
                }
            }
        }
    if(maxx - minx < 30 || maxy - miny < 30) {
        return -1;
    }

   // cout << maxx-minx + 1 << "x" << maxy - miny + 1 << "+" << minx  << "+" << miny << endl; 
    cout << maxy-miny + 1 << "x" << maxx - minx + 1 << "+" << miny  << "+" << minx << endl; 

//    image = _I;
//
//    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
//    imshow( "Display window", image );                   // Show our image inside it.
//
//    waitKey(0);                                          // Wait for a keystroke in the window
    return 0;
}
