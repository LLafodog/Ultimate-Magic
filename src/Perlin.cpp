#include "Perlin.h"

#include<cstdlib>
#include<iostream>
#include<cmath>

using namespace std;


Perlin::Perlin(int w, int h, int step)
{
    /*
    step=(int)(step/10)*10;
    w=(int)(step/10)*10;
    h=(int)(step/10)*10;
    */
    m_tab=vector<vector<double>>();
    m_width=w;
    m_height=h;
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


            if(i%m_step==0 && j%m_step==0){temp.push_back(random(0,256));}
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
    double u=(1 - cos(t)) * .5;
    return linear_interpolation(a,b,u);

}


bool Perlin::inMap(int i, int j)
{
    return(i>=0 && i<=m_height && j>=0 && j<=m_width);
}

void Perlin::interpolate()
{
    int Ax,Ay,Bx,By,Cx,Cy,Dx,Dy,Ex,Ey,Fx,Fy;

    for(int i(0);i<m_height;i++)
    {
        for(int j(0);j<m_width;j++)
        {
            if(i%m_step==0 )
            {
                Ay=i;
            }
            if(j%m_step==0 )
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

                // Inter de E




//                if(i==8 && j==8)
  //              {


//                cout << m_tab[Ax][Ay] << "  " << m_tab[Ay][Ax] << endl;
                //if(inMap(Ex,Ey) && inMap(Ax,Ay) && inMap(Bx,By))
                //{
                //if(inMap(Bx,By) && inMap(Cx,Cy) && inMap(Dx,Dy))
                if(inMap(Cx,Cy) && inMap(Dx,Dy) && inMap(Ex,Ey) && inMap(Fx,Fy))
                {
                m_tab[Ex][Ey]=linear_interpolation(m_tab[Ax][Ay],m_tab[Bx][By],(double)(Ex-Ax)/(double)(Bx-Ax));
                //}else{cout << " 1: " << m_tab[Ax][Ay] << " 2:" << m_tab[Bx][By] << "  3: " << m_tab[Ex][Ey]<<endl;}

                //if(inMap(Fx,Fy) && inMap(Dx,Dy) && inMap(Cx,Cy))
                //{
                m_tab[Fx][Fy]=linear_interpolation(m_tab[Dx][Dy],m_tab[Cx][Cy],(double)(Fx-Dx)/(double)(Cx-Dx));
                //}

                //if(inMap(j,i) && inMap(Ex,Ey) && inMap(Fx,Fy))
                //{
                m_tab[j][i]=linear_interpolation(m_tab[Ex][Ey],m_tab[Fx][Fy],(double)(i-Ey)/(double)(Fy-Ey));
                //}

                }
                /*else
                {
                cout << " a: " << Ax << ";" << Ay << " B:" << Bx<< ";" << By << "  C: " << Cx<< ";" << Cy << " D: " << Dx<< ";" << Dy << " E " << Ex<< ";" << Ey << " F: " << Fx<< ";" << Fy << " W: " << m_width << " h: " << m_height <<endl;
                }*/
                //m_tab[j][i]=11;


                /*m_tab[Fx][Fy]=14;
                m_tab[Ex][Ey]=15;



                    m_tab[j][i]=22;
                    m_tab[Ax][Ay]=10;
                    m_tab[Bx][By]=11;
                    m_tab[Cx][Cy]=12;
                    m_tab[Dx][Dy]=13;*/
    //            }


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
            cout << m_tab[j][i] << " ";
        }
        cout << '\n';
    }
}

Perlin::~Perlin()
{
    //dtor
}
