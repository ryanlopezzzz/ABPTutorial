#include "velocity_align.hpp"

void VelocityAlign::compute_energy(void)
{
    for (int pindex_i = 0; pindex_i < _system.Numparticles; pindex_i ++)
    {
        ParticleType pi = _system.particles[pindex_i];
        pi.energy+=J*vdot(pi.v, pi.n);
        
        //put back the particle in the list
        _system.particles[pindex_i] = pi;
    }

}

void VelocityAlign::compute(void)
{
    for (int pindex_i = 0; pindex_i < _system.Numparticles; pindex_i ++)
    {
        ParticleType pi = _system.particles[pindex_i];
        pi.tau+=J*vcross(pi.v, pi.n);

        //put back the particle in the list
        _system.particles[pindex_i] = pi;
    }
    /**/
}
