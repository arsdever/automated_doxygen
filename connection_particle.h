#pragma once
#include <transferable.h>

namespace ad
{
	template <typename BYTEBUF_TYPE>
	class ConnectionParticle : public Transferable<BYTEBUF_TYPE>
	{
	public:
		typedef BYTEBUF_TYPE bytebuf_t;
		typedef Transferable<bytebuf_t> base_t;

	public:
		virtual bytebuf_t const& uri() const = 0;
		virtual bytebuf_t const& host() const = 0;
		virtual bytebuf_t const& request() const = 0;
		virtual bytebuf_t const& response() const = 0;
		virtual void setRequest(bytebuf_t const &request) = 0;
		virtual void setResponse(bytebuf_t const &response) = 0;
	};
}
