/************************************************************************************
Added by Ryan Lopez

Soft Repulsive force
*************************************************************************************/
#ifndef __velocity_align_hpp__
#define __velocity_align_hpp__

#include <memory>
#include <map>
#include <iostream>

#include "computetorqueclass.hpp"
#include "../neighbourlist/neighbourlistclass.hpp"

class VelocityAlign : public ComputeTorqueClass
{
public:
    VelocityAlign(SystemClass &system, NeighbourListType &neighbourslist) : _neighbourslist(neighbourslist), ComputeTorqueClass(system)
    {
        name = "Velocity Align";
        type = "Torque/Particle";
        this->set_default_properties();
    }
    ~VelocityAlign() {}

    void set_default_properties(void) override
    {
        J = 1.0;
        float max_radius = 0; //Gets radius of max size particles for rcut
        for(int i = 0; i < _system.Numparticles; i ++)
        {
            if(_system.particles[i].radius > max_radius)
	            max_radius = _system.particles[i].radius;
        }

        rcut = 2*max_radius; //cut off radius to be use in neighbourslist, particles must touch to feel torque
    }

    void set_property(const std::string &prop_name, const double &value) override
    {
        if (prop_name.compare("k") == 0)
            J = value;
        else
            this->print_warning_property_name(prop_name);
    }

    void compute_energy(void) override;
    void compute(void) override;

private:
    NeighbourListType &_neighbourslist;
    real J, a;
};

#endif

/** @} */
