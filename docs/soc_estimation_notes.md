

#SOC Estimator – Phase 1 Prototype Plan :
    Inputs: I, V, Δt (simulate in future adc_sim.c)
    Estimation method: Basic Coulomb Counting
    Output: float SOC %, timestamp
    Sample logic => SOC += (current * delta_t) / capacity