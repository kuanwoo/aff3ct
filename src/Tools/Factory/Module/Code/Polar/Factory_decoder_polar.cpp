#include "Tools/Exception/exception.hpp"
#include "Tools/Code/Polar/decoder_polar_functions.h"

#include "Module/Decoder/Polar/SC/Decoder_polar_SC_naive.hpp"
#include "Module/Decoder/Polar/SC/Decoder_polar_SC_naive_sys.hpp"
#include "Module/Decoder/Polar/SC/Decoder_polar_SC_fast_sys.hpp"
#include "Module/Decoder/Polar/SCAN/Decoder_polar_SCAN_naive.hpp"
#include "Module/Decoder/Polar/SCAN/Decoder_polar_SCAN_naive_sys.hpp"
#include "Module/Decoder/Polar/SCL/Decoder_polar_SCL_naive.hpp"
#include "Module/Decoder/Polar/SCL/Decoder_polar_SCL_naive_sys.hpp"
#include "Module/Decoder/Polar/SCL/Decoder_polar_SCL_fast_sys.hpp"
#include "Module/Decoder/Polar/SCL/Decoder_polar_SCL_MEM_fast_sys.hpp"
#include "Module/Decoder/Polar/SCL/CRC/Decoder_polar_SCL_naive_CA.hpp"
#include "Module/Decoder/Polar/SCL/CRC/Decoder_polar_SCL_naive_CA_sys.hpp"
#include "Module/Decoder/Polar/SCL/CRC/Decoder_polar_SCL_fast_CA_sys.hpp"
#include "Module/Decoder/Polar/SCL/CRC/Decoder_polar_SCL_MEM_fast_CA_sys.hpp"
#include "Module/Decoder/Polar/ASCL/Decoder_polar_ASCL_fast_CA_sys.hpp"
#include "Module/Decoder/Polar/ASCL/Decoder_polar_ASCL_MEM_fast_CA_sys.hpp"

//#define API_POLAR_DYNAMIC 1

#include "Tools/Code/Polar/API/API_polar_dynamic_seq.hpp"
#include "Tools/Code/Polar/API/API_polar_dynamic_intra.hpp"
#ifdef API_POLAR_DYNAMIC
#include "Tools/Code/Polar/API/API_polar_dynamic_inter.hpp"
#include "Tools/Code/Polar/API/API_polar_dynamic_inter_8bit_bitpacking.hpp"
#else
#include "Tools/Code/Polar/API/API_polar_static_seq.hpp"
#include "Tools/Code/Polar/API/API_polar_static_inter.hpp"
#include "Tools/Code/Polar/API/API_polar_static_inter_8bit_bitpacking.hpp"
#include "Tools/Code/Polar/API/API_polar_static_intra_8bit.hpp"
#include "Tools/Code/Polar/API/API_polar_static_intra_16bit.hpp"
#include "Tools/Code/Polar/API/API_polar_static_intra_32bit.hpp"
#endif

#include "Tools/Code/Polar/nodes_parser.h"

#include "Factory_decoder_polar.hpp"

using namespace aff3ct::tools;
using namespace aff3ct::module;

template <typename B, typename Q>
Decoder_SISO<B,Q>* Factory_decoder_polar
::build_siso(const parameters& params, const mipp::vector<B> &frozen_bits)
{
	if (params.type == "SCAN" && params.systematic)
	{
		if (params.implem == "NAIVE") return new Decoder_polar_SCAN_naive_sys<B, Q, init_LLR<Q>, f_LLR<Q>, v_LLR<Q>, h_LLR<B,Q>>(params.K, params.N_cw, params.n_ite, frozen_bits, params.n_frames);
	}
	else if (params.type == "SCAN" && !params.systematic)
	{
		if (params.implem == "NAIVE") return new Decoder_polar_SCAN_naive    <B, Q, init_LLR<Q>, f_LLR<Q>, v_LLR<Q>, h_LLR<B,Q>>(params.K, params.N_cw, params.n_ite, frozen_bits, params.n_frames);
	}

	throw cannot_allocate(__FILE__, __LINE__, __func__);
}

template <typename B, typename Q, class API_polar>
Decoder<B,Q>* Factory_decoder_polar
::_build(const parameters& params, const mipp::vector<B> &frozen_bits, module::CRC<B> *crc)
{
	int idx_r0, idx_r1;
	auto polar_patterns = nodes_parser(params.polar_nodes, idx_r0, idx_r1);

	if (!params.systematic) // non-systematic encoding
	{
		if (params.implem == "NAIVE")
		{
			if (crc == nullptr || crc->get_size() == 0)
			{
				     if (params.type == "SC"  ) return new Decoder_polar_SC_naive        <B,Q,            f_LLR<Q>,g_LLR<B,Q>,h_LLR<B,Q>>(params.K, params.N_cw,               frozen_bits,       params.n_frames);
				else if (params.type == "SCAN") return new Decoder_polar_SCAN_naive      <B,Q,init_LLR<Q>,f_LLR<Q>,v_LLR<  Q>,h_LLR<B,Q>>(params.K, params.N_cw, params.n_ite, frozen_bits,       params.n_frames);
				else if (params.type == "SCL" ) return new Decoder_polar_SCL_naive       <B,Q,            f_LLR<Q>,g_LLR<B,Q>           >(params.K, params.N_cw, params.L,     frozen_bits,       params.n_frames);
			}
			else
				     if (params.type == "SCL" ) return new Decoder_polar_SCL_naive_CA    <B,Q,            f_LLR<Q>,g_LLR<B,Q>           >(params.K, params.N_cw, params.L,     frozen_bits, *crc, params.n_frames);
		}
	}
	else // systematic encoding
	{
		if (params.implem == "NAIVE")
		{
			if (crc == nullptr || crc->get_size() == 0)
			{
				     if (params.type == "SC"  ) return new Decoder_polar_SC_naive_sys    <B,Q,            f_LLR<Q>,g_LLR<B,Q>,h_LLR<B,Q>>(params.K, params.N_cw,               frozen_bits,       params.n_frames);
				else if (params.type == "SCAN") return new Decoder_polar_SCAN_naive_sys  <B,Q,init_LLR<Q>,f_LLR<Q>,v_LLR<  Q>,h_LLR<B,Q>>(params.K, params.N_cw, params.n_ite, frozen_bits,       params.n_frames);
				else if (params.type == "SCL" ) return new Decoder_polar_SCL_naive_sys   <B,Q,            f_LLR<Q>,g_LLR<B,Q>           >(params.K, params.N_cw, params.L,     frozen_bits,       params.n_frames);
			}
			else
				     if (params.type == "SCL" ) return new Decoder_polar_SCL_naive_CA_sys<B,Q,            f_LLR<Q>,g_LLR<B,Q>           >(params.K, params.N_cw, params.L,     frozen_bits, *crc, params.n_frames);
		}
		else if (params.implem == "FAST")
		{
			if (crc == nullptr || crc->get_size() == 0)
			{
				     if (params.type == "SC"  ) return new Decoder_polar_SC_fast_sys<B, Q, API_polar>(params.K, params.N_cw, frozen_bits, polar_patterns, idx_r0, idx_r1, params.n_frames);
			}
		}
	}

	throw cannot_allocate(__FILE__, __LINE__, __func__);
}

template <typename B, typename Q, class API_polar>
Decoder<B,Q>* Factory_decoder_polar
::_build_scl_fast(const parameters& params, const mipp::vector<B> &frozen_bits, module::CRC<B> *crc)
{
	int idx_r0, idx_r1;
	auto polar_patterns = nodes_parser(params.polar_nodes, idx_r0, idx_r1);

	if (params.implem == "FAST" && params.systematic)
	{
		if (crc != nullptr && crc->get_size() > 0)
		{
			     if (params.type == "ASCL"    ) return new Decoder_polar_ASCL_fast_CA_sys    <B, Q, API_polar>(params.K, params.N_cw, params.L, frozen_bits, polar_patterns, idx_r0, idx_r1, *crc, params.full_adaptive, params.n_frames);
			else if (params.type == "ASCL_MEM") return new Decoder_polar_ASCL_MEM_fast_CA_sys<B, Q, API_polar>(params.K, params.N_cw, params.L, frozen_bits, polar_patterns, idx_r0, idx_r1, *crc, params.full_adaptive, params.n_frames);
			else if (params.type == "SCL"     ) return new Decoder_polar_SCL_fast_CA_sys     <B, Q, API_polar>(params.K, params.N_cw, params.L, frozen_bits, polar_patterns, idx_r0, idx_r1, *crc,                       params.n_frames);
			else if (params.type == "SCL_MEM" ) return new Decoder_polar_SCL_MEM_fast_CA_sys <B, Q, API_polar>(params.K, params.N_cw, params.L, frozen_bits, polar_patterns, idx_r0, idx_r1, *crc,                       params.n_frames);
		}
		else
		{
			     if (params.type == "SCL"     ) return new Decoder_polar_SCL_fast_sys        <B, Q, API_polar>(params.K, params.N_cw, params.L, frozen_bits, polar_patterns, idx_r0, idx_r1,                             params.n_frames);
			else if (params.type == "SCL_MEM" ) return new Decoder_polar_SCL_MEM_fast_sys    <B, Q, API_polar>(params.K, params.N_cw, params.L, frozen_bits, polar_patterns, idx_r0, idx_r1,                             params.n_frames);
		}
	}

	throw cannot_allocate(__FILE__, __LINE__, __func__);
}

template <typename B, typename Q>
Decoder<B,Q>* Factory_decoder_polar
::build(const parameters& params, const mipp::vector<B> &frozen_bits, module::CRC<B> *crc)
{
	if (params.type.find("SCL") != std::string::npos && params.implem == "FAST")
	{
		if (params.simd_strategy == "INTRA")
		{
			if (typeid(B) == typeid(signed char))
			{
				using API_polar = API_polar_dynamic_intra
				                  <B, Q, f_LLR  <Q>, g_LLR  <B,Q>, g0_LLR  <Q>, h_LLR  <B,Q>, xo_STD  <B>,
				                         f_LLR_i<Q>, g_LLR_i<B,Q>, g0_LLR_i<Q>, h_LLR_i<B,Q>, xo_STD_i<B>>;

				return _build_scl_fast<B,Q,API_polar>(params, frozen_bits, crc);
			}
			else if (typeid(B) == typeid(short))
			{
				using API_polar = API_polar_dynamic_intra
				                  <B, Q, f_LLR  <Q>, g_LLR  <B,Q>, g0_LLR  <Q>, h_LLR  <B,Q>, xo_STD  <B>,
				                         f_LLR_i<Q>, g_LLR_i<B,Q>, g0_LLR_i<Q>, h_LLR_i<B,Q>, xo_STD_i<B>>;

				return _build_scl_fast<B,Q,API_polar>(params, frozen_bits, crc);
			}
			else if (typeid(B) == typeid(int))
			{
				using API_polar = API_polar_dynamic_intra
				                  <B, Q, f_LLR  <Q>, g_LLR  <B,Q>, g0_LLR  <Q>, h_LLR  <B,Q>, xo_STD  <B>,
				                         f_LLR_i<Q>, g_LLR_i<B,Q>, g0_LLR_i<Q>, h_LLR_i<B,Q>, xo_STD_i<B>>;

				return _build_scl_fast<B,Q,API_polar>(params, frozen_bits, crc);
			}
		}
		else if (params.simd_strategy.empty())
		{
			using API_polar = API_polar_dynamic_seq
			                  <B, Q, f_LLR<Q>, g_LLR<B,Q>, g0_LLR<Q>, h_LLR<B,Q>, xo_STD<B>>;

			return _build_scl_fast<B,Q,API_polar>(params, frozen_bits, crc);
		}
	}

	if (params.simd_strategy == "INTER" && params.type == "SC" && params.implem == "FAST")
	{
		if (typeid(B) == typeid(signed char))
		{
#ifdef ENABLE_BIT_PACKING
#ifdef API_POLAR_DYNAMIC
			using API_polar = API_polar_dynamic_inter_8bit_bitpacking
			                  <B, Q, f_LLR_i<Q>, g_LLR_i<B,Q>, g0_LLR_i<Q>, h_LLR_i<B,Q>, xo_STD_i<B>>;
#else
			using API_polar = API_polar_static_inter_8bit_bitpacking
			                  <B, Q, f_LLR_i<Q>, g_LLR_i<B,Q>, g0_LLR_i<Q>, h_LLR_i<B,Q>, xo_STD_i<B>>;
#endif
#else
#ifdef API_POLAR_DYNAMIC
			using API_polar = API_polar_dynamic_inter
			                  <B, Q, f_LLR_i<Q>, g_LLR_i<B,Q>, g0_LLR_i<Q>, h_LLR_i<B,Q>, xo_STD_i<B>>;
#else
			using API_polar = API_polar_static_inter
			                  <B, Q, f_LLR_i<Q>, g_LLR_i<B,Q>, g0_LLR_i<Q>, h_LLR_i<B,Q>, xo_STD_i<B>>;
#endif
#endif
			return _build<B,Q,API_polar>(params, frozen_bits, crc);
		}
		else
		{
#ifdef API_POLAR_DYNAMIC
			using API_polar = API_polar_dynamic_inter
			                  <B, Q, f_LLR_i<Q>, g_LLR_i<B,Q>, g0_LLR_i<Q>, h_LLR_i<B,Q>, xo_STD_i<B>>;
#else
			using API_polar = API_polar_static_inter
			                  <B, Q, f_LLR_i<Q>, g_LLR_i<B,Q>, g0_LLR_i<Q>, h_LLR_i<B,Q>, xo_STD_i<B>>;
#endif
			return _build<B,Q,API_polar>(params, frozen_bits, crc);
		}
	}
	else if (params.simd_strategy == "INTRA" && params.implem == "FAST")
	{
		if (typeid(B) == typeid(signed char))
		{
#ifdef API_POLAR_DYNAMIC
			using API_polar = API_polar_dynamic_intra
			                  <B, Q, f_LLR  <Q>, g_LLR  <B,Q>, g0_LLR  <Q>, h_LLR  <B,Q>, xo_STD  <B>,
			                         f_LLR_i<Q>, g_LLR_i<B,Q>, g0_LLR_i<Q>, h_LLR_i<B,Q>, xo_STD_i<B>>;
#else
			using API_polar = API_polar_static_intra_8bit
			                  <B, Q, f_LLR  <Q>, g_LLR  <B,Q>, g0_LLR  <Q>, h_LLR  <B,Q>, xo_STD  <B>,
			                         f_LLR_i<Q>, g_LLR_i<B,Q>, g0_LLR_i<Q>, h_LLR_i<B,Q>, xo_STD_i<B>>;
#endif
			return _build<B,Q,API_polar>(params, frozen_bits, crc);
		}
		else if (typeid(B) == typeid(short))
		{
#ifdef API_POLAR_DYNAMIC
			using API_polar = API_polar_dynamic_intra
			                  <B, Q, f_LLR  <Q>, g_LLR  <B,Q>, g0_LLR  <Q>, h_LLR  <B,Q>, xo_STD  <B>,
			                         f_LLR_i<Q>, g_LLR_i<B,Q>, g0_LLR_i<Q>, h_LLR_i<B,Q>, xo_STD_i<B>>;
#else
			using API_polar = API_polar_static_intra_16bit
			                  <B, Q, f_LLR  <Q>, g_LLR  <B,Q>, g0_LLR  <Q>, h_LLR  <B,Q>, xo_STD  <B>,
			                         f_LLR_i<Q>, g_LLR_i<B,Q>, g0_LLR_i<Q>, h_LLR_i<B,Q>, xo_STD_i<B>>;
#endif
			return _build<B,Q,API_polar>(params, frozen_bits, crc);
		}
		else if (typeid(B) == typeid(int))
		{
#ifdef API_POLAR_DYNAMIC
			using API_polar = API_polar_dynamic_intra
			                  <B, Q, f_LLR  <Q>, g_LLR  <B,Q>, g0_LLR  <Q>, h_LLR  <B,Q>, xo_STD  <B>,
			                         f_LLR_i<Q>, g_LLR_i<B,Q>, g0_LLR_i<Q>, h_LLR_i<B,Q>, xo_STD_i<B>>;
#else
			using API_polar = API_polar_static_intra_32bit
			                  <B, Q, f_LLR  <Q>, g_LLR  <B,Q>, g0_LLR  <Q>, h_LLR  <B,Q>, xo_STD  <B>,
			                         f_LLR_i<Q>, g_LLR_i<B,Q>, g0_LLR_i<Q>, h_LLR_i<B,Q>, xo_STD_i<B>>;
#endif
			return _build<B,Q,API_polar>(params, frozen_bits, crc);
		}
	}
	else if (params.simd_strategy.empty())
	{
#ifdef API_POLAR_DYNAMIC
		using API_polar = API_polar_dynamic_seq
		                  <B, Q, f_LLR<Q>, g_LLR<B,Q>, g0_LLR<Q>, h_LLR<B,Q>, xo_STD<B>>;
#else
		using API_polar = API_polar_static_seq
		                  <B, Q, f_LLR<Q>, g_LLR<B,Q>, g0_LLR<Q>, h_LLR<B,Q>, xo_STD<B>>;
#endif
		return _build<B,Q,API_polar>(params, frozen_bits, crc);
	}

	throw cannot_allocate(__FILE__, __LINE__, __func__);
}

void Factory_decoder_polar
::build_args(Arguments_reader::arg_map &req_args, Arguments_reader::arg_map &opt_args)
{
	Factory_decoder::build_args(req_args, opt_args);

	opt_args[{"dec-type", "D"}].push_back("SC, SCL, SCL_MEM, ASCL, ASCL_MEM, SCAN");

	opt_args[{"dec-ite", "i"}] =
		{"positive_int",
		 "maximal number of iterations in the SCAN decoder."};

	opt_args[{"dec-lists", "L"}] =
		{"positive_int",
		 "maximal number of paths in the SCL decoder."};

	opt_args[{"dec-simd"}] =
		{"string",
		 "the SIMD strategy you want to use.",
		 "INTRA, INTER"};

	opt_args[{"dec-polar-nodes"}] =
		{"string",
		 "the type of nodes you want to detect in the Polar tree (ex: {R0,R1,R0L,REP_2-8,REPL,SPC_4+})."};

	opt_args[{"dec-partial-adaptive"}] =
		{"",
		 "enable the partial adaptive mode for the ASCL decoder (by default full adaptive is selected)."};

	opt_args[{"dec-no-sys"}] =
		{"",
		 "does not suppose a systematic encoding."};
}

void Factory_decoder_polar
::store_args(const Arguments_reader& ar, parameters &params)
{
	params.type   = "SC";
	params.implem = "FAST";

	Factory_decoder::store_args(ar, params);

	if(ar.exist_arg({"dec-ite", "i"})) params.n_ite = ar.get_arg_int({"dec-ite", "i"});
	if(ar.exist_arg({"dec-lists", "L"})) params.L = ar.get_arg_int({"dec-lists", "L"});
	if(ar.exist_arg({"dec-simd"})) params.simd_strategy = ar.get_arg({"dec-simd"});
	if(ar.exist_arg({"dec-polar-nodes"})) params.polar_nodes = ar.get_arg({"dec-polar-nodes"});
	if(ar.exist_arg({"dec-partial-adaptive"})) params.full_adaptive = false;

	// force 1 iteration max if not SCAN (and polar code)
	if (params.type != "SCAN") params.n_ite = 1;
}

void Factory_decoder_polar
::group_args(Arguments_reader::arg_grp& ar)
{
	Factory_decoder::group_args(ar);
}

void Factory_decoder_polar
::header(params_list& head_dec, const parameters& params)
{
	Factory_decoder::header(head_dec, params);

	if (!params.simd_strategy.empty())
		head_dec.push_back(std::make_pair("SIMD strategy", params.simd_strategy));

	if (params.type == "SCAN")
		head_dec.push_back(std::make_pair("Num. of iterations (i)", std::to_string(params.n_ite)));

	if (params.type == "SCL" || params.type == "SCL_MEM")
		head_dec.push_back(std::make_pair("Num. of lists (L)", std::to_string(params.L)));

	if (params.type == "ASCL" || params.type == "ASCL_MEM")
	{
		auto adaptative_mode = params.full_adaptive ? "full" : "partial";
		head_dec.push_back(std::make_pair("Max num. of lists (L)", std::to_string(params.L)));
		head_dec.push_back(std::make_pair("Adaptative mode", adaptative_mode));
	}

	if ((params.type == "SC"      ||
	     params.type == "SCL"     ||
	     params.type == "ASCL"    ||
	     params.type == "SCL_MEM" ||
	     params.type == "ASCL_MEM") && params.implem == "FAST")
		head_dec.push_back(std::make_pair("Polar node types", params.polar_nodes));
}

// ==================================================================================== explicit template instantiation
#include "Tools/types.h"
#ifdef MULTI_PREC
template aff3ct::module::Decoder_SISO<B_8 ,Q_8 >* aff3ct::tools::Factory_decoder_polar::build_siso<B_8 ,Q_8 >(const aff3ct::tools::Factory_decoder_polar::parameters&, const mipp::vector<B_8 >&);
template aff3ct::module::Decoder_SISO<B_16,Q_16>* aff3ct::tools::Factory_decoder_polar::build_siso<B_16,Q_16>(const aff3ct::tools::Factory_decoder_polar::parameters&, const mipp::vector<B_16>&);
template aff3ct::module::Decoder_SISO<B_32,Q_32>* aff3ct::tools::Factory_decoder_polar::build_siso<B_32,Q_32>(const aff3ct::tools::Factory_decoder_polar::parameters&, const mipp::vector<B_32>&);
template aff3ct::module::Decoder_SISO<B_64,Q_64>* aff3ct::tools::Factory_decoder_polar::build_siso<B_64,Q_64>(const aff3ct::tools::Factory_decoder_polar::parameters&, const mipp::vector<B_64>&);
#else
template aff3ct::module::Decoder_SISO<B,Q>* aff3ct::tools::Factory_decoder_polar::build_siso<B,Q>(const aff3ct::tools::Factory_decoder_polar::parameters&, const mipp::vector<B>&);
#endif

#ifdef MULTI_PREC
template aff3ct::module::Decoder<B_8 ,Q_8 >* aff3ct::tools::Factory_decoder_polar::build<B_8 ,Q_8 >(const aff3ct::tools::Factory_decoder_polar::parameters&, const mipp::vector<B_8 >&, module::CRC<B_8 >*);
template aff3ct::module::Decoder<B_16,Q_16>* aff3ct::tools::Factory_decoder_polar::build<B_16,Q_16>(const aff3ct::tools::Factory_decoder_polar::parameters&, const mipp::vector<B_16>&, module::CRC<B_16>*);
template aff3ct::module::Decoder<B_32,Q_32>* aff3ct::tools::Factory_decoder_polar::build<B_32,Q_32>(const aff3ct::tools::Factory_decoder_polar::parameters&, const mipp::vector<B_32>&, module::CRC<B_32>*);
template aff3ct::module::Decoder<B_64,Q_64>* aff3ct::tools::Factory_decoder_polar::build<B_64,Q_64>(const aff3ct::tools::Factory_decoder_polar::parameters&, const mipp::vector<B_64>&, module::CRC<B_64>*);
#else
template aff3ct::module::Decoder<B,Q>* aff3ct::tools::Factory_decoder_polar::build<B,Q>(const aff3ct::tools::Factory_decoder_polar::parameters&, const mipp::vector<B>&, module::CRC<B>*);
#endif
// ==================================================================================== explicit template instantiation