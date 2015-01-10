#include "Perlin.h"

#include<cstdlib>
#include<iostream>
#include<cmath>

using namespace std;


Perlin::Perlin(int w, int h, int step)
{
    /*int wt=81;
    int ht=81;*/
    int wt=w+(step-w%step+1);
    int ht=h+(step-h%step+1);
    m_tab=vector<vector<double>>();
    m_width=wt;
    m_height=ht;
    m_step=step;

    initTab();
    interpolate();

}

void Perlin::initTab()
{
    for(int i(0);i<m_height;i++)
    {
        vector<double> temp;
        for(int j(0);j<m_width;j++)
        {


            if(i%m_step==0 && j%m_step==0){temp.push_back(random(0,100));}
            else{temp.push_back(0);}
        }
        m_tab.push_back(temp);
    }
}

double Perlin::linear_interpolation(double a, double b, double t)
{
    return a*(1-t) + b*t;
}

double Perlin::polynomial_interpolation(double a, double b, double t)
{
    t*=3.141592653589;
    double u=(1 - cos(t)) * .5;
    return linear_interpolation(a,b,u);

}


bool Perlin::inMap(int i, int j)
{
    return(i>=0 && i<m_height && j>0 && j<m_width);
}

void Perlin::interpolate()
{
    int Ax,Ay,Bx,By,Cx,Cy,Dx,Dy,Ex,Ey,Fx,Fy;

    for(int i(0);i<m_width;i++)
    {
        for(int j(0);j<m_height;j++)
        {
            if(i%m_step==0  && i<m_width)
            {
                Ay=i;
            }
            if(j%m_step==0  && j<m_height)
            {
                Ax=j;
            }

                By=Ay;
                Bx=Ax+m_step;

                Cx=Ax+m_step;
                Cy=Ay+m_step;

                Dx=Ax;
                Dy=Ay+m_step;

                Ex=j;
                Ey=Ay;

                Fx=j;
                Fy=Dy;

                if(inMap(Cx,Cy))
                {
                m_tab[Ex][Ey]=linear_interpolation(m_tab[Ax][Ay],m_tab[Bx][By],(double)(Ex-Ax)/(double)(Bx-Ax));
                m_tab[Fx][Fy]=linear_interpolation(m_tab[Dx][Dy],m_tab[Cx][Cy],(double)(Fx-Dx)/(double)(Cx-Dx));
                m_tab[j][i]=linear_interpolation(m_tab[Ex][Ey],m_tab[Fx][Fy],(double)(i-Ey)/(double)(Fy-Ey));
                }
        }
    }
}

int Perlin::random(int min, int max)
{
    return rand()%max+min;
}

void Perlin::display()
{
    for(int i(0);i<m_height;i++)
    {
        for(int j(0);j<m_width;j++)
        {
            cout << m_tab[i][j] << " ";
        }
        cout << '\n';
    }
}

Perlin::~Perlin()
{
    //dtor
}
