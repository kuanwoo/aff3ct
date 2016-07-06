#include "Decoder_RSC_BCJR_inter_fast.hpp"
#include "Decoder_RSC_BCJR_inter_very_fast.hpp"

#include "../../../../Tools/MIPP/mipp.h"

template <typename B, typename R, proto_map_i<R> MAP>
Decoder_RSC_BCJR_inter_very_fast<B,R,MAP>
::Decoder_RSC_BCJR_inter_very_fast(const int &K, const std::vector<std::vector<int>> &trellis, const bool buffered_encoding)
: Decoder_RSC_BCJR_inter<B,R>(K, trellis, buffered_encoding)
{
}

template <typename B, typename R, proto_map_i<R> MAP>
Decoder_RSC_BCJR_inter_very_fast<B,R,MAP>
::~Decoder_RSC_BCJR_inter_very_fast()
{
}

// Slower and I don't know why... It should be faster without the loading of the alpha metrics
//
// template <typename B, typename R, proto_map_i<R> MAP>
// void Decoder_RSC_BCJR_inter_very_fast<B,R,MAP>
// ::compute_gamma_alpha(const mipp::vector<R> &sys, const mipp::vector<R> &par)
// {
// 	constexpr auto stride = mipp::nElmtsPerRegister<R>();

// 	auto r_a0_prev = mipp::Reg<R>(&this->alpha[0][0]);
// 	auto r_a1_prev = mipp::Reg<R>(&this->alpha[1][0]);
// 	auto r_a2_prev = mipp::Reg<R>(&this->alpha[2][0]);
// 	auto r_a3_prev = mipp::Reg<R>(&this->alpha[3][0]);
// 	auto r_a4_prev = mipp::Reg<R>(&this->alpha[4][0]);
// 	auto r_a5_prev = mipp::Reg<R>(&this->alpha[5][0]);
// 	auto r_a6_prev = mipp::Reg<R>(&this->alpha[6][0]);
// 	auto r_a7_prev = mipp::Reg<R>(&this->alpha[7][0]);

// 	for (auto i = 0; i < (this->K +3) * stride; i += stride)
// 	{
// 		const auto r_sys = mipp::Reg<R>(&sys[i]);
// 		const auto r_par = mipp::Reg<R>(&par[i]);

// 		const auto r_g0 = RSC_BCJR_inter_div_or_not<R>::apply(r_sys + r_par);
// 		const auto r_g1 = RSC_BCJR_inter_div_or_not<R>::apply(r_sys - r_par);

// 		auto r_a0 = MAP(r_a0_prev + r_g0, r_a1_prev - r_g0);
// 		auto r_a1 = MAP(r_a3_prev + r_g1, r_a2_prev - r_g1);
// 		auto r_a2 = MAP(r_a4_prev + r_g1, r_a5_prev - r_g1);
// 		auto r_a3 = MAP(r_a7_prev + r_g0, r_a6_prev - r_g0);
// 		auto r_a4 = MAP(r_a1_prev + r_g0, r_a0_prev - r_g0);
// 		auto r_a5 = MAP(r_a2_prev + r_g1, r_a3_prev - r_g1);
// 		auto r_a6 = MAP(r_a5_prev + r_g1, r_a4_prev - r_g1);
// 		auto r_a7 = MAP(r_a6_prev + r_g0, r_a7_prev - r_g0);

// 		RSC_BCJR_inter_fast_normalize<R>::apply(r_a0, r_a1, r_a2, r_a3, r_a4, r_a5, r_a6, r_a7, i);

// 		r_a0.store(&this->alpha[0][i +stride]);
// 		r_a1.store(&this->alpha[1][i +stride]);
// 		r_a2.store(&this->alpha[2][i +stride]);
// 		r_a3.store(&this->alpha[3][i +stride]);
// 		r_a4.store(&this->alpha[4][i +stride]);
// 		r_a5.store(&this->alpha[5][i +stride]);
// 		r_a6.store(&this->alpha[6][i +stride]);
// 		r_a7.store(&this->alpha[7][i +stride]);

// 		r_g0.store(&this->gamma[0][i]);
// 		r_g1.store(&this->gamma[1][i]);

// 		r_a0_prev = r_a0;
// 		r_a1_prev = r_a1;
// 		r_a2_prev = r_a2;
// 		r_a3_prev = r_a3;
// 		r_a4_prev = r_a4;
// 		r_a5_prev = r_a5;
// 		r_a6_prev = r_a6;
// 		r_a7_prev = r_a7;
// 	}
// }

template <typename B, typename R, proto_map_i<R> MAP>
void Decoder_RSC_BCJR_inter_very_fast<B,R,MAP>
::compute_gamma_alpha(const mipp::vector<R> &sys, const mipp::vector<R> &par)
{
	constexpr auto stride = mipp::nElmtsPerRegister<R>();

	for (auto i = 0; i < (this->K +3) * stride; i += stride)
	{
		const auto r_sys = mipp::Reg<R>(&sys[i]);
		const auto r_par = mipp::Reg<R>(&par[i]);

		const auto r_g0 = RSC_BCJR_inter_div_or_not<R>::apply(r_sys + r_par);
		const auto r_g1 = RSC_BCJR_inter_div_or_not<R>::apply(r_sys - r_par);

		const auto r_a0_prev = mipp::Reg<R>(&this->alpha[0][i]);
		const auto r_a1_prev = mipp::Reg<R>(&this->alpha[1][i]);
		const auto r_a2_prev = mipp::Reg<R>(&this->alpha[2][i]);
		const auto r_a3_prev = mipp::Reg<R>(&this->alpha[3][i]);
		const auto r_a4_prev = mipp::Reg<R>(&this->alpha[4][i]);
		const auto r_a5_prev = mipp::Reg<R>(&this->alpha[5][i]);
		const auto r_a6_prev = mipp::Reg<R>(&this->alpha[6][i]);
		const auto r_a7_prev = mipp::Reg<R>(&this->alpha[7][i]);

		auto r_a0 = MAP(r_a0_prev + r_g0, r_a1_prev - r_g0);
		auto r_a1 = MAP(r_a3_prev + r_g1, r_a2_prev - r_g1);
		auto r_a2 = MAP(r_a4_prev + r_g1, r_a5_prev - r_g1);
		auto r_a3 = MAP(r_a7_prev + r_g0, r_a6_prev - r_g0);
		auto r_a4 = MAP(r_a1_prev + r_g0, r_a0_prev - r_g0);
		auto r_a5 = MAP(r_a2_prev + r_g1, r_a3_prev - r_g1);
		auto r_a6 = MAP(r_a5_prev + r_g1, r_a4_prev - r_g1);
		auto r_a7 = MAP(r_a6_prev + r_g0, r_a7_prev - r_g0);

		RSC_BCJR_inter_fast_normalize<R>::apply(r_a0, r_a1, r_a2, r_a3, r_a4, r_a5, r_a6, r_a7, i);

		r_a0.store(&this->alpha[0][i +stride]);
		r_a1.store(&this->alpha[1][i +stride]);
		r_a2.store(&this->alpha[2][i +stride]);
		r_a3.store(&this->alpha[3][i +stride]);
		r_a4.store(&this->alpha[4][i +stride]);
		r_a5.store(&this->alpha[5][i +stride]);
		r_a6.store(&this->alpha[6][i +stride]);
		r_a7.store(&this->alpha[7][i +stride]);

		r_g0.store(&this->gamma[0][i]);
		r_g1.store(&this->gamma[1][i]);
	}
}

template <typename B, typename R, proto_map_i<R> MAP>
void Decoder_RSC_BCJR_inter_very_fast<B,R,MAP>
::compute_beta_ext(const mipp::vector<R> &sys, mipp::vector<R> &ext)
{
	constexpr auto stride = mipp::nElmtsPerRegister<R>();

	auto r_b0_prev = mipp::Reg<R>(&this->alpha[0][0]);
	auto r_b1_prev = mipp::Reg<R>(&this->alpha[1][0]);
	auto r_b2_prev = mipp::Reg<R>(&this->alpha[2][0]);
	auto r_b3_prev = mipp::Reg<R>(&this->alpha[3][0]);
	auto r_b4_prev = mipp::Reg<R>(&this->alpha[4][0]);
	auto r_b5_prev = mipp::Reg<R>(&this->alpha[5][0]);
	auto r_b6_prev = mipp::Reg<R>(&this->alpha[6][0]);
	auto r_b7_prev = mipp::Reg<R>(&this->alpha[7][0]);

	// compute beta values [trellis backward traversal <-]
	for (unsigned i = (unsigned)((this->K +2) * stride); i >= (unsigned)((this->K +0) * stride); i -= stride)
	{
		const auto r_g0 = mipp::Reg<R>(&this->gamma[0][i]);
		const auto r_g1 = mipp::Reg<R>(&this->gamma[1][i]);

		auto r_b0 = MAP(r_b0_prev + r_g0, r_b4_prev - r_g0);
		auto r_b1 = MAP(r_b4_prev + r_g0, r_b0_prev - r_g0);
		auto r_b2 = MAP(r_b5_prev + r_g1, r_b1_prev - r_g1);
		auto r_b3 = MAP(r_b1_prev + r_g1, r_b5_prev - r_g1);
		auto r_b4 = MAP(r_b2_prev + r_g1, r_b6_prev - r_g1);
		auto r_b5 = MAP(r_b6_prev + r_g1, r_b2_prev - r_g1);
		auto r_b6 = MAP(r_b7_prev + r_g0, r_b3_prev - r_g0);
		auto r_b7 = MAP(r_b3_prev + r_g0, r_b7_prev - r_g0);

		RSC_BCJR_inter_fast_normalize<R>::apply(r_b0, r_b1, r_b2, r_b3, r_b4, r_b5, r_b6, r_b7, i);

		r_b0_prev = r_b0; r_b1_prev = r_b1; r_b2_prev = r_b2; r_b3_prev = r_b3;
		r_b4_prev = r_b4; r_b5_prev = r_b5; r_b6_prev = r_b6; r_b7_prev = r_b7;
	}

	// compute beta values [trellis backward traversal <-] + compute extrinsic values
	for (auto i = (this->K -1) * stride; i >= 0; i -= stride)
	{
		const auto r_g0 = mipp::Reg<R>(&this->gamma[0][i]);
		const auto r_g1 = mipp::Reg<R>(&this->gamma[1][i]);

		const auto r_a0 = mipp::Reg<R>(&this->alpha[0][i]);
		const auto r_a1 = mipp::Reg<R>(&this->alpha[1][i]);
		const auto r_a2 = mipp::Reg<R>(&this->alpha[2][i]);
		const auto r_a3 = mipp::Reg<R>(&this->alpha[3][i]);
		const auto r_a4 = mipp::Reg<R>(&this->alpha[4][i]);
		const auto r_a5 = mipp::Reg<R>(&this->alpha[5][i]);
		const auto r_a6 = mipp::Reg<R>(&this->alpha[6][i]);
		const auto r_a7 = mipp::Reg<R>(&this->alpha[7][i]);

		const auto r_sum0_0 = r_a0 + r_b0_prev + r_g0; auto r_max0 = r_sum0_0;
		const auto r_sum0_1 = r_a1 + r_b4_prev + r_g0;      r_max0 = MAP(r_max0, r_sum0_1);
		const auto r_sum0_2 = r_a2 + r_b5_prev + r_g1;      r_max0 = MAP(r_max0, r_sum0_2);
		const auto r_sum0_3 = r_a3 + r_b1_prev + r_g1;      r_max0 = MAP(r_max0, r_sum0_3);
		const auto r_sum0_4 = r_a4 + r_b2_prev + r_g1;      r_max0 = MAP(r_max0, r_sum0_4);
		const auto r_sum0_5 = r_a5 + r_b6_prev + r_g1;      r_max0 = MAP(r_max0, r_sum0_5);
		const auto r_sum0_6 = r_a6 + r_b7_prev + r_g0;      r_max0 = MAP(r_max0, r_sum0_6);
		const auto r_sum0_7 = r_a7 + r_b3_prev + r_g0;      r_max0 = MAP(r_max0, r_sum0_7);

		const auto r_sum1_0 = r_a0 + r_b4_prev - r_g0; auto r_max1 = r_sum1_0;
		const auto r_sum1_1 = r_a1 + r_b0_prev - r_g0;      r_max1 = MAP(r_max1, r_sum1_1);
		const auto r_sum1_2 = r_a2 + r_b1_prev - r_g1;      r_max1 = MAP(r_max1, r_sum1_2);
		const auto r_sum1_3 = r_a3 + r_b5_prev - r_g1;      r_max1 = MAP(r_max1, r_sum1_3);
		const auto r_sum1_4 = r_a4 + r_b6_prev - r_g1;      r_max1 = MAP(r_max1, r_sum1_4);
		const auto r_sum1_5 = r_a5 + r_b2_prev - r_g1;      r_max1 = MAP(r_max1, r_sum1_5);
		const auto r_sum1_6 = r_a6 + r_b3_prev - r_g0;      r_max1 = MAP(r_max1, r_sum1_6);
		const auto r_sum1_7 = r_a7 + r_b7_prev - r_g0;      r_max1 = MAP(r_max1, r_sum1_7);

		const auto r_post = RSC_BCJR_inter_post<R>::compute(r_max0 - r_max1);
		const auto r_ext  = r_post - &sys[i];
		r_ext.store(&ext[i]);

		// compute beta values
		auto r_b0 = MAP(r_b0_prev + r_g0, r_b4_prev - r_g0);
		auto r_b1 = MAP(r_b4_prev + r_g0, r_b0_prev - r_g0);
		auto r_b2 = MAP(r_b5_prev + r_g1, r_b1_prev - r_g1);
		auto r_b3 = MAP(r_b1_prev + r_g1, r_b5_prev - r_g1);
		auto r_b4 = MAP(r_b2_prev + r_g1, r_b6_prev - r_g1);
		auto r_b5 = MAP(r_b6_prev + r_g1, r_b2_prev - r_g1);
		auto r_b6 = MAP(r_b7_prev + r_g0, r_b3_prev - r_g0);
		auto r_b7 = MAP(r_b3_prev + r_g0, r_b7_prev - r_g0);

		RSC_BCJR_inter_fast_normalize<R>::apply(r_b0, r_b1, r_b2, r_b3, r_b4, r_b5, r_b6, r_b7, i);

		r_b0_prev = r_b0;
		r_b1_prev = r_b1;
		r_b2_prev = r_b2;
		r_b3_prev = r_b3;
		r_b4_prev = r_b4;
		r_b5_prev = r_b5;
		r_b6_prev = r_b6;
		r_b7_prev = r_b7;
	}
}

template <typename B, typename R, proto_map_i<R> MAP>
void Decoder_RSC_BCJR_inter_very_fast<B,R,MAP>
::decode(const mipp::vector<R> &sys, const mipp::vector<R> &par, mipp::vector<R> &ext)
{
	compute_gamma_alpha(sys, par);
	compute_beta_ext   (sys, ext);
}