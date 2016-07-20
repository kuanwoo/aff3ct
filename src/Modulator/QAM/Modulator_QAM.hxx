#include <cassert>
#include <cmath>
#include <complex>
#include <limits>

#include "Modulator_QAM.hpp"

/*
 * Constructor / Destructor
 */
template <typename B, typename R, proto_max<R> MAX>
Modulator_QAM<B,R,MAX>
::Modulator_QAM(const int bits_per_symbol, const R sigma)
: bits_per_symbol(bits_per_symbol),
  nbr_symbols    (1 << bits_per_symbol),
  sigma          (sigma),
  sqrt_es        (std::sqrt(2.0 * (this->nbr_symbols -1) / 3.0)),
  constellation  (nbr_symbols)
{
	mipp::vector<B> bits(this->bits_per_symbol);

	for (auto j = 0; j < this->nbr_symbols; j++)
	{
		for (auto l = 0; l < this->bits_per_symbol; l++)
			bits[l] = (j >> l) & 1;

		this->constellation[j] = this->bits_to_symbol(&bits[0]);
	}
}

template <typename B, typename R, proto_max<R> MAX>
Modulator_QAM<B,R,MAX>
::~Modulator_QAM()
{
}

/*
 * int get_buffer_size(const int N)
 * N = number of input bits
 * returns number of output symbols
 */
template <typename B, typename R, proto_max<R> MAX>
int Modulator_QAM<B,R,MAX>
::get_buffer_size(const int N)
{
	assert(this->bits_per_symbol % 2 == 0);
	return std::ceil((float)N / (float)this->bits_per_symbol) * 2;
}

/*
 * Mapping function
 */
template <typename B, typename R, proto_max<R> MAX>
std::complex<R> Modulator_QAM<B,R,MAX>
::bits_to_symbol(const B* bits) const
 {
	auto bps = this->bits_per_symbol;

	auto symbol_I = (R)1.0 - (bits[      0] + bits[      0]);
	auto symbol_Q = (R)1.0 - (bits[bps / 2] + bits[bps / 2]);

	for (auto j = 1; j < bps / 2; j++)
	{
		symbol_I = ((R)1.0 - (bits[         j] + bits[         j])) * ((1 << j) - symbol_I);
		symbol_Q = ((R)1.0 - (bits[bps / 2 +j] + bits[bps / 2 +j])) * ((1 << j) - symbol_Q);
	}

	return std::complex<R>(symbol_I, symbol_Q) / (std::complex<R>)this->sqrt_es;
 }

/*
 * Modulator
 */
template <typename B,typename R, proto_max<R> MAX>
void Modulator_QAM<B,R,MAX>
::modulate(const mipp::vector<B>& X_N1, mipp::vector<R>& X_N2) const
{
	auto size_in  = (int)X_N1.size();
	auto size_out = (int)X_N2.size();
	auto bps      = this->bits_per_symbol;

	auto main_loop_size = size_in / bps;
	for (auto i = 0; i < main_loop_size; i++)
	{
		// compute the symbol "on the fly"
		// auto symbol = bits_to_symbol(&X_N1[i*bps]);

		// determine the symbol with a lookup table
		unsigned idx = 0;
		for (auto j = 0; j < bps; j++)
			idx += (1 << j) * X_N1[i * bps +j];
		auto symbol = this->constellation[idx];

		X_N2[2*i   ] = symbol.real();
		X_N2[2*i +1] = symbol.imag();
	}

	// last elements if "size_in" is not a multiple of the number of bits per symbol
	if (main_loop_size * bps < size_in)
	{
		unsigned idx = 0;
		for (auto j = 0; j < size_in - (main_loop_size * bps); j++)
			idx += (1 << j) * X_N1[main_loop_size * bps +j];
		auto symbol = this->constellation[idx];

		X_N2[size_out -2] = symbol.real();
		X_N2[size_out -1] = symbol.imag();
	}
}

/*
 * Demodulator
 */
template <typename B,typename R, proto_max<R> MAX>
void Modulator_QAM<B,R,MAX>
::demodulate(const mipp::vector<R>& Y_N1, mipp::vector<R>& Y_N2) const
{
	auto size   = (int)Y_N2.size();
	auto sigma2 = this->sigma * this->sigma;

	for (auto n = 0; n < size; n++)// Boucle sur les LLRs
	{
		auto L0 = -std::numeric_limits<R>::infinity();
		auto L1 = -std::numeric_limits<R>::infinity();
		auto b  = n % this->bits_per_symbol; // position du bit
		auto k  = n / this->bits_per_symbol; // Position du symbole

		auto complex_Yk = std::complex<R>(Y_N1[2*k], Y_N1[2*k+1]);

		for (auto j = 0; j < this->nbr_symbols; j++)
			if ((j & (1 << b)) == 0)
				L0 = MAX(L0, -std::norm(complex_Yk - this->constellation[j]) / sigma2);
			else
				L1 = MAX(L1, -std::norm(complex_Yk - this->constellation[j]) / sigma2);

		Y_N2[n] = L0 - L1;
	}
}