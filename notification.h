#pragma once
namespace ad
{
	/**
	 * @brief This interface used to transfer the notifications using the Notify interface.
	 * @see Notify
	 */
	template <typename BYTEBUF_TYPE>
	class Notification
	{
	public:
		typedef BYTEBUF_TYPE bytebuf_t;

	public:
		/**
		 * @brief The destructor.
		 */
		virtual ~Notification() = default;

		/**
		 * @brief This function is used to get the notification body from the notification.
		 * @return the notification body
		 */
		virtual bytebuf_t body() = 0;
	};
}
