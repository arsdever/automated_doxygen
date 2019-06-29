#pragma once
namespace ad
{
	class Notification;

	/**
	 * \brief This interface is used to implement the notification mechanism. It can be used from receiver
	 * and sender sides.
	 */
	class Notify
	{
	public:
		/**
		 * \brief The destructor.
		 */
		virtual ~Notify() = default;
		
		/**
		 * \brief This function is implementing the core functionality of notification sending and receiving.
		 * \param notification the notification``
		 * \see Notification
		 */
		virtual void notify(Notification const &notification) = 0;
	};
}
