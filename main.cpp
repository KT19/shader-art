#include<iostream>
#include<cstring>
#include<cmath>
#include<chrono>
#include<opencv2/core.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include"vec.hpp"

#define WSIZE_X (600)
#define WSIZE_Y (600)

using namespace cv;
using namespace std;

uint8_t window[WSIZE_Y][WSIZE_X][3] = {255};

#define PI (3.141592)

double clamp(double x, double lowerlimit=0.0, double upperlimit=1.0) {
    if(x < lowerlimit)
        return lowerlimit;
    if(x > upperlimit)
        return upperlimit;

    return x;
}

double smoothstep(double x, double edge0, double edge1) {
    x = clamp((x-edge0)/(edge1-edge0));

    return x * x * (3 - 2 * x);
}

vec3 cos_vec3(const vec3& v) {
    return vec3(cos(v.x), cos(v.y), cos(v.z));
}

vec3 palette(double t) {
    vec3 a(0.5, 0.5, 0.5);
    vec3 b(0.5, 0.5, 0.5);
    vec3 c(1.0, 1.0, 1.0);
    vec3 d(0.625, 0.412, 0.253);

    return a + b*cos_vec3(2*PI*(c*t+d));
}

vec2 fract(const vec2& uv) {
    return vec2(uv.x - floor(uv.x), uv.y - floor(uv.y));
}
vec4 mainImage(int px, int py, double iFrame, int itr, double zoom) {
    vec2 uv(zoom*(px * 2.0 - WSIZE_X)/WSIZE_X, zoom*(py * 2.0 - WSIZE_Y)/WSIZE_Y);
    uv.x *= (1.0*WSIZE_X)/WSIZE_Y;

    vec2 uv0 = uv;
    vec3 finalColor(0, 0, 0);
    const double freq = 8.0;

    for(int i = 0;i < itr;i++) {
        uv = fract(uv*1.5) - 0.5;
        double d = uv.length() * exp(-uv0.length());

        vec3 color = palette(uv0.length() + i*0.7 + iFrame);

        d = cos(d*freq + iFrame)/freq;
        d = sqrt(d*d);

        d = pow(0.01/d, 1.1);
        d = smoothstep(d, 0.0, 1.0);
        d = fmin(d, 1.0);

        finalColor = finalColor + color*d;
    }

    //filter to [0, 1]
    finalColor.x = fmax(0.0,fmin(finalColor.x, 1.0));
    finalColor.y = fmax(0.0,fmin(finalColor.y, 1.0));
    finalColor.z = fmax(0.0,fmin(finalColor.z, 1.0));

    return vec4(finalColor, 1.0);
}

int main(void) {
    string str = "my shader";
    namedWindow(str, WINDOW_AUTOSIZE);
    chrono::system_clock::time_point start, end;
    int iFrame = 0;
    int itr = 1;
    const int max_itr = 8;
    double zoom = 1.0;
    const double max_zoom = 3.0;
    const double min_zoom = 0.2;

    while(true) {
        start = chrono::system_clock::now();
        

        for(int y = 0;y < WSIZE_Y;y++) {
            for(int x = 0;x < WSIZE_X;x++) {
                auto color = mainImage(x, y, iFrame/33.0, itr, zoom);

                window[y][x][2] = (uint8_t)(255.99*color.x);
                window[y][x][1] = (uint8_t)(255.99*color.y);
                window[y][x][0] = (uint8_t)(255.99*color.z);
            }
        }
        end = chrono::system_clock::now();
        double t = chrono::duration_cast<chrono::milliseconds>(end-start).count();
        cout<<"time per frame: "<<t<<"[msec]"<<endl;

        Mat img = Mat(WSIZE_Y, WSIZE_X, CV_8UC3, &window);
        imshow(str, img);
        
        int key = waitKey(1);
        if(key == 'q') {
            break;
        }
        if(key == 'j') {
            itr++;
            itr = min(itr, max_itr);
        } else if(key == 'l') {
            itr--;
            itr = max(itr,1);
        } else if(key == 'i') {
            zoom += 0.1;
            zoom = fmin(zoom, max_zoom);
        } else if(key == 'k') {
            zoom -= 0.1;
            zoom = fmax(zoom, min_zoom);
        }
        iFrame++;
    }
    destroyAllWindows();

    return 0;
}