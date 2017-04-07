#ifndef CRC_NO_HPP_
#define CRC_NO_HPP_

#include "../CRC.hpp"

namespace aff3ct
{
namespace module
{
template <typename B = int>
class CRC_NO : public CRC<B>
{
public:
	CRC_NO(const int K, const int n_frames = 1, const std::string name = "CRC_NO");
	virtual ~CRC_NO();

	int  size () const;
	void build(B *U_K); using CRC<B>::build;
	bool check(const B *V_K, const int n_frames = -1); using CRC<B>::check;
};
}
}

#endif /* CRC_NO_HPP_ */
