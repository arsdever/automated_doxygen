#pragma once
namespace ad
{
	template <typename BYTE_ARRAY_TYPE>
	class ConnectionParticle;

	template <typename BYTE_ARRAY_TYPE>
	class ConnectionPortal
	{
	public:
		/**
		 * \brief The destructor.
		 */
		virtual ~ConnectionPortal() = default;
		virtual void send(ConnectionParticle<BYTE_ARRAY_TYPE> &request) = 0;
		virtual void receive(ConnectionParticle<BYTE_ARRAY_TYPE> &request) = 0;
	};
}
