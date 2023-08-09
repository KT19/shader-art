#ifndef VEC_H
#define VEC_H

class vec2 {
public:
    double x,y;
    vec2(){}
    vec2(double _x, double _y) : x(_x), y(_y) {}

    double length(void) {
        return sqrt(x*x+y*y);
    }

    template <typename T>
    vec2& operator*=(T t) {
        x*=t;
        y*=t;
        return *this;
    } 
    template <typename T>
    vec2& operator-=(T t) {
        x -= t;
        y -= t;
        return *this;
    }
};

class vec3 {
public:
    double x, y, z;
    vec3(){}
    vec3(double _x, double _y, double _z) : x(_x), y(_y), z(_z){}

    double length(void) {
        return sqrt(x*x+y*y+z*z);
    }
    
    template <typename T>
    vec3& operator+=(T t) {
        x += t;
        y += t;
        z += t;
        return *this;
    }
    template <typename T>
    vec3& operator *=(T t) {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }
};

class vec4 {
public:
    double x, y, z, a;
    vec4(){}
    vec4(double _x, double _y, double _z, double _a) : x(_x), y(_y), z(_z), a(_a) {}
    vec4 (vec3 v, double _a) : x(v.x), y(v.y), z(v.z), a(_a) {}
};

/*operator for vec2*/
inline vec2 operator*(const vec2 &u, const vec2 &v) {
    return vec2(u.x*v.x, u.y*v.y);
}
inline vec2 operator+(const vec2 &u, const vec2 &v) {
    return vec2(u.x+v.x, u.y+v.y);
}
template <typename T>
inline vec2 operator*(const vec2 &u, T t) {
    return vec2(u.x*t, u.y*t);
}
template <typename T>
inline vec2 operator*(T t, const vec2 &v) {
    return v*t;
}
template <typename T>
inline vec2 operator-(const vec2 &u, T t) {
    return vec2(u.x - t, u.y - t);
}
template <typename T>
inline vec2 operator-(T t, const vec2 &v) {
    return vec2(t-v.x, t-v.y);
}

/*operator for vec3*/
inline vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(u.x + v.x, u.y + v.y, u.z + v.z);
}
inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u.x * v.x, u.y * v.y, u.z * v.z);
}
template <typename T>
inline vec3 operator*(const vec3 &u, T t) {
    return vec3(u.x*t, u.y*t, u.z*t);
}
template <typename T>
inline vec3 operator*(T t, const vec3 &v) {
    return v*t;
}
#endif