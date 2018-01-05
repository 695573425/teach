#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>



using namespace std;

class Point
{
	public:
	Point(){};
	Point(double x, double y)
	{
	    m_x = x;
        m_y = y;
	}
	~Point(){};

	double get_x() const
	{
	    return m_x;
	}
	double get_y() const
	{
	    return m_y;
	}

	void set_x(double x)
	{
	    m_x = x;
	}
	void set_y(double y)
	{
	    m_y = y;
	}

	void display_point ()  const
	{
         cout<<"("<<m_x<<","<<m_y<<")"<<endl;
	}

	protected:
	double m_x;
	double m_y;
};



class Point3D: public Point
{
    public:
    Point3D(double x =0,double y = 0,double z = 0):m_z(z)
    {
        m_x = x;
        m_y = y;
    }

    void set_z(double z)
    {
        m_z = z;
    }

    double get_z() const
    {
        return m_z;
    }

    void display_point() const
    {
         cout<<"("<<m_x<<","<<m_y<<","<<m_z<<")"<<endl;
    }

    protected:
    double m_z ;
};



class Curve3D: public Point3D
{
    public:
    Curve3D(Point3D p = Point3D(0,0,0),int num=1);
    ~Curve3D();

    void DisplayCurve() const;
    void CurveLen() const;
    Curve3D operator+(const Point3D& p) const;
    Curve3D operator-(const Point3D& p) const;
    const Curve3D& operator=(const Curve3D& c);
    void write_txt(ofstream &os) const;
    void read_txt(ifstream &is);
    void write_binary(ofstream &os) const;
    void read_binary(ifstream &is);



    public:
    int P_num;
    Point3D *P3D;

};

Curve3D::Curve3D(Point3D p,int num)
{
    P_num = num;
    P3D = new Point3D[P_num];
    P3D[0] = p;
}

Curve3D::~Curve3D()
{
    delete[] P3D;
}

void Curve3D::DisplayCurve() const
{
    int i;
    for(i=0;i<P_num;i++)
    {
        P3D[i].display_point();
    }
}

void Curve3D::CurveLen() const
{
    double total_Len = 0;
    double x_len , y_len , z_len;
    int i ;
    for(i=0;i<P_num-1;i++)
    {
        x_len = P3D[i].get_x() - P3D[i+1].get_x();
        y_len = P3D[i].get_y() - P3D[i+1].get_y();
        z_len = P3D[i].get_z() - P3D[i+1].get_z();
        total_Len += sqrt(pow(x_len,2)+pow(y_len,2)+pow(z_len,2));
    }
    cout<<total_Len<<endl;
}

Curve3D Curve3D::operator+(const Point3D& p) const
{
    int i;
    Curve3D temp(Point3D(0,0,0),P_num+1);
    for(i=0;i<P_num;i++)
    {
        temp.P3D[i] = P3D[i];
    }
    temp.P3D[P_num] = p;
    return temp;

}

Curve3D Curve3D::operator-(const Point3D& p) const
{
    int i;
    int j=0;
    Curve3D temp(Point3D(0,0,0),P_num);
    for(i=0;i<P_num;i++)
    {
        if((P3D[i].get_x() != p.get_x())||(P3D[i].get_y() != p.get_y())||(P3D[i].get_z() != p.get_z()))
        {
            temp.P3D[j] = P3D[i];
            j++;
        }

        else
        {
            temp.P_num -= 1;
        }
    }
    return temp;
}

const Curve3D& Curve3D::operator=(const Curve3D& c)
{
    if (this != &c)
    {
        P_num = c.P_num;
        delete[] P3D;
        P3D = new Point3D[P_num];
        for(int i=0; i<P_num; i++)
            P3D[i] = c.P3D[i];
    }
    return *this;
}

void Curve3D::write_txt(ofstream &os) const
{
    for(int i=0; i<P_num; i++)
    {
        os<<P3D[i].get_x()<<"  "
          <<P3D[i].get_y()<<"  "
          <<P3D[i].get_z()<<endl;
    }
}

void Curve3D::read_txt(ifstream &is)
{
    stringstream ss;
    string s;
    double x , y , z;
    while(getline(is,s))
    {
        ss<<s;
        ss>>x>>y>>z;
        *this = *this + Point3D(x,y,z);
        ss.str("");
    }
}

void Curve3D::write_binary(ofstream &os) const
{
    int object_size = sizeof(Point3D);
    for(int i = 0 ; i<P_num ; i++)
    {
        os.write(reinterpret_cast<char *>(&P3D[i]),object_size);
    }
}

void Curve3D::read_binary(ifstream &is)
{
    Point3D add_point ;
    int object_size = sizeof(Point3D);
    while (is.read(reinterpret_cast<char *>(&add_point),object_size))
    {
        *this = *this + add_point;
    }
}



int main()
{


    return 0;
}
