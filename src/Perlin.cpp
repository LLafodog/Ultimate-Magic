#include<Perlin.hpp>

#include<cstdlib>
#include<iostream>
#include<cmath>

using namespace std;


Perlin::Perlin(int w, int h, int step, int style, int min, int max)
{
    int wt=w/step*step+1;
    int ht=h/step*step+1;



    m_tab=vector<vector<double>>();
    m_width=wt;
    m_height=ht;
    m_step=step;
    switch(style)
    {
    case 0: initTab(min,max);break;
    case 1: initDoubleStrip(min,max) ;break;
    default: initTab(min,max);
    }

    //initTab();
    interpolate();

}

void Perlin::initTab(int min, int max)
{
    for(int i(0);i<m_height;i++)
    {
        vector<double> temp;
        for(int j(0);j<m_width;j++)
        {
            if(i%m_step==0 && j%m_step==0){temp.push_back(random(min,max));}
            else{temp.push_back(-1);}
        }
        m_tab.push_back(temp);
    }
}


void Perlin::initDoubleStrip(int min, int max)
{
    int x=random(0,m_width/m_step);
    int y=random(0,m_height/m_step);

    for(int i(0);i<m_height;i++)
    {
        vector<double> temp;
        for(int j(0);j<m_width;j++)
        {
            if(i%m_step==0 && j%m_step==0)
            {
                // giving some alea to do not get a straight river
                if(j/m_step ==x || i/m_step == y)
                {
                    temp.push_back(random(min,max));

                }
                else
                {
                    temp.push_back(random());
                }
            }
            else{temp.push_back(-1);}
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
                m_tab[Ex][Ey]=polynomial_interpolation(m_tab[Ax][Ay],m_tab[Bx][By],(double)(Ex-Ax)/(double)(Bx-Ax));
                m_tab[Fx][Fy]=polynomial_interpolation(m_tab[Dx][Dy],m_tab[Cx][Cy],(double)(Fx-Dx)/(double)(Cx-Dx));
                m_tab[j][i]=polynomial_interpolation(m_tab[Ex][Ey],m_tab[Fx][Fy],(double)(i-Ey)/(double)(Fy-Ey));
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

