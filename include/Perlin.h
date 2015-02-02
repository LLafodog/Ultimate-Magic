#ifndef PERLIN_H
#define PERLIN_H

#include<vector>

class Perlin
{
    public:

        Perlin(int w, int h, int step, int style=-1, int min=0, int max=100);

        void initTab(int min=0, int max=100);
        void initDoubleStrip(int min, int max);

        int random(int min=0, int max=100);


        void interpolate();
            double linear_interpolation(double a, double b, double t);
            double polynomial_interpolation(double a, double b, double t);
            bool inMap(int i, int j);

        void display();

        double get(int i, int j) {if(i<m_height && j<m_width){return m_tab[i][j];}return -1;}
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
