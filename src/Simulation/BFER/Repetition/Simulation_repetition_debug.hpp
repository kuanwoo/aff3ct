#ifndef SIMULATION_REPETITION_DEBUG_HPP_
#define SIMULATION_REPETITION_DEBUG_HPP_

#include <vector>

#include "Simulation_repetition.hpp"

#include "../../../Tools/Frame_trace/Frame_trace.hpp"

template <typename B, typename R, typename Q>
class Simulation_repetition_debug : public Simulation_repetition<B,R,Q>
{
private:
	Frame_trace<B> ft;

public:
	Simulation_repetition_debug(const t_simulation_param& simu_params,
	                            const t_code_param&       code_params,
	                            const t_encoder_param&    enco_params,
	                            const t_channel_param&    chan_params,
	                            const t_decoder_param&    deco_params);

	virtual ~Simulation_repetition_debug();

protected:
	void simulation_loop();
};

#endif /* SIMULATION_REPETITION_DEBUG_HPP_ */
