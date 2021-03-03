/************************************************************************************
Added by Ryan Lopez

Soft Repulsive force
*************************************************************************************/
#ifndef __softrepulsiveforce_hpp__
#define __softrepulsiveforce_hpp__

#include <memory>
#include <map>
#include <iostream>
#include <algorithm> 

#include "computeforceclass.hpp"
#include "../neighbourlist/neighbourlistclass.hpp"

class SoftRepulsiveForce : public ComputeForceClass
{
public:
    SoftRepulsiveForce(SystemClass &system, NeighbourListType &neighbourslist) : _neighbourslist(neighbourslist), ComputeForceClass(system)
    {
        name = "Soft Repulsive Force";
        type = "Conservative/Particle";
        this->set_default_properties();
    }
    ~SoftRepulsiveForce() {}

    void set_default_properties(void) override
    {
        k = 1.0;
        float max_radius = 0; //Gets radius of max size particles for rcut
        for(int i = 0; i < _system.Numparticles; i ++)
        {
            if(_system.particles[i].radius > max_radius)
	            max_radius = _system.particles[i].radius;
        }

        rcut = 2*max_radius; //cut off radius to be use in neighbourslist, particles must touch to feel force
    }

    void set_property(const std::string &prop_name, const double &value) override
    {
        if (prop_name.compare("k")==0)
            k = value;
        else
            this->print_warning_property_name(prop_name);
    }
    
    void compute_energy(void) override;
    
    void compute(void) override;

private:
    NeighbourListType &_neighbourslist;
    real k;
};

#endif

/** @} */
