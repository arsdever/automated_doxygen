#pragma once
namespace ad
{
	template <typename BYTEBUF_TYPE>
	class ConnectionParticle;

	template <typename BYTEBUF_TYPE>
	class ConnectionPortal
	{
	public:
		typedef BYTEBUF_TYPE bytebuf_t;
		
	public:
		/**
		 * @brief The destructor.
		 */
		virtual ~ConnectionPortal() = default;
		virtual void send(ConnectionParticle<bytebuf_t> &request) = 0;
		virtual void receive(ConnectionParticle<bytebuf_t> &request) = 0;
	};
}
