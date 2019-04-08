#ifndef GUARD_DIFFUSION_H
#define GUARD_DIFFUSION_H


#include "system.h"
#include "xyz.h"

#include <vector>
#include <fstream>
#include <string>


class Diffusion {
public:
    Diffusion(const System& system, unsigned int Ti);

    void sample(const System &system);

    void write(std::ostream &out);
    void write(const char* outname);

private:
    unsigned int N;
    unsigned int Ti; 



    std::vector<XYZ> msd;
    std::vector<double> t;
    unsigned int ti;

    std::vector<XYZ> r0;

};

Diffusion::Diffusion(const System& system, unsigned int Tii)
{
    N = system.N;
    Ti = Tii;

    msd = std::vector<XYZ>(Ti,XYZ(0,0,0));
    t = std::vector<double>(Ti);
    ti = 0;
   
    r0 = system.r; 
}


void Diffusion::sample(const System& system)
{

    
    for( unsigned int i=0;i<N;++i) {
        msd[ti].x += (r0[i].x - system.r[i].x)*(r0[i].x - system.r[i].x);
        msd[ti].y += (r0[i].y - system.r[i].y)*(r0[i].y - system.r[i].y);
        msd[ti].z += (r0[i].z - system.r[i].z)*(r0[i].z - system.r[i].z);
    }
    t[ti] = system.t;
    ++ti;
}

void Diffusion::write(std::ostream &out)
{
    for(unsigned int i=0;i<Ti;++i) {
        out << t[i] << '\t';
        out << msd[i].x/N << '\t';
        out << msd[i].y/N << '\t';
        out << msd[i].z/N;
        if(i < (Ti-1) ) out << '\n';
 
    }
}

void Diffusion::write(const char* outname)
{
    std::ofstream out;
    out.open(outname);
    this->write(out);
}


#endif

