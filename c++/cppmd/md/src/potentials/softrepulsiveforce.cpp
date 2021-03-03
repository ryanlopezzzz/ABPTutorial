/************************************************************************************
Added by Ryan Lopez

Soft Repulsive force
*************************************************************************************/
#include "softrepulsiveforce.hpp"


void SoftRepulsiveForce::compute_energy(void)
{
    std::cerr << "Don't use this function! Not programmed yet!" << std::endl;

    for (int pindex_i = 0; pindex_i < _system.Numparticles; pindex_i ++)
    {
        ParticleType pi = _system.particles[pindex_i];
        //loop over the neighbours particles
        for(int c = 0; c < pi.coordination; c ++)
        {
            int pindex_j = c + _neighbourslist.max_ng_per_particle * pindex_i;
            ParticleType pj = _system.particles[pindex_j];

            real2 rij = host::minimum_image(pi.r, pj.r, _system.get_box());
            real lendr = sqrt(vdot(rij, rij));
            if (lendr <= rcut)
                pi.energy+= 0.5*k*(pi.radius + pj.radius - lendr)*(pi.radius + pj.radius - lendr);
        }
        //put back the particle in the list
        _system.particles[pindex_i] = pi;
    }
}

void SoftRepulsiveForce::compute(void)
{
    for (int pindex_i = 0; pindex_i < _system.Numparticles; pindex_i ++)
    {
        ParticleType pi = _system.particles[pindex_i];
        //loop over the neighbours particles
        for(int c = 0; c < pi.coordination; c ++)
        {
            int pindex_j = _neighbourslist.nglist[c + _neighbourslist.max_ng_per_particle * pindex_i];
            const ParticleType pj = _system.particles[pindex_j];
            real2 rij = host::minimum_image(pi.r, pj.r, _system.get_box());
            real lendr = sqrt(vdot(rij, rij));
            if (lendr <= pi.radius + pj.radius)
            {
                real factor = -k*(pi.radius + pj.radius - lendr)/lendr;
                pi.forceC.x+=factor*rij.x;
                pi.forceC.y+=factor*rij.y;
            }
        }
        //put back the particle in the list
        _system.particles[pindex_i] = pi;
    }
    /**/
}
