#ifndef PERLIN_H
#define PERLIN_H

#include<vector>

class Perlin
{
    public:

        Perlin(int w, int h, int step);

        void initTab();

        int random(int min, int max);

        void interpolate();
            double linear_interpolation(double a, double b, double t);
            double polynomial_interpolation(double a, double b, double t);
            bool inMap(int i, int j);

        void display();

        double get(int i, int j) {if(i<m_height && j<m_width){return m_tab[i][j];}}
        const int getWidth() {return m_width;}
        const int getHeight() {return m_height;}



        virtual ~Perlin();

    protected:
    int m_step;
    int m_width;
    int m_height;
    std::vector<std::vector<double>> m_tab;
};

#endif // PERLIN_H
