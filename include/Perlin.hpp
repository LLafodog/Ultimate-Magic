#ifndef PERLIN_H
#define PERLIN_H

#include<vector>
using namespace std;

class Perlin
/**
    Usefull for a random map generation. Perlin noise class.
**/
{
public:

        Perlin(int w, int h, int step, int style=-1, int min=0, int max=100);

        void interpolate();
        void display();
        double get(int i, int j) {if(i<m_height && j<m_width){return m_tab[i][j];}return -1;}
        const int getWidth() {return m_width;}
        const int getHeight() {return m_height;}

        virtual ~Perlin();

protected:
    void initTab(int min=0, int max=100);
    void initDoubleStrip(int min, int max);
    int random(int min=0, int max=100);
    double linear_interpolation(double a, double b, double t);
    double polynomial_interpolation(double a, double b, double t);
    bool inMap(int i, int j);

    int m_step;
    int m_width;
    int m_height;
    vector<vector<double>> m_tab;
};

#endif // PERLIN_H
